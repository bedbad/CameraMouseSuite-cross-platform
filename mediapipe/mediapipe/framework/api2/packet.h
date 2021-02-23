// This file defines a typed Packet type. It fully interoperates with the older
// mediapipe::Packet; creating an api::Packet<T> that refers to an existing
// Packet (or vice versa) is cheap, just like copying a Packet. Ownership of
// the payload is shared. Consider this as a typed view into the same data.
//
// Conversion is currently done explicitly with the FromOldPacket and
// ToOldPacket functions, but calculator code does not need to concern itself
// with it.

#ifndef MEDIAPIPE_FRAMEWORK_API2_PACKET_H_
#define MEDIAPIPE_FRAMEWORK_API2_PACKET_H_

#include <functional>
#include <type_traits>

#include "mediapipe/framework/api2/tuple.h"
#include "mediapipe/framework/packet.h"
#include "mediapipe/framework/port/logging.h"

namespace mediapipe {
namespace api2 {

using Timestamp = mediapipe::Timestamp;
using HolderBase = mediapipe::packet_internal::HolderBase;

template <typename T>
class Packet;

// Type-erased packet.
class PacketBase {
 public:
  // Empty.
  PacketBase() = default;
  // Copy.
  PacketBase(const PacketBase&) = default;
  PacketBase& operator=(const PacketBase&) = default;
  // Move.
  PacketBase(PacketBase&&) = default;
  PacketBase& operator=(PacketBase&&) = default;

  // Get timestamp.
  Timestamp timestamp() const { return timestamp_; }
  // The original API has a Timestamp method, but it shadows the Timestamp
  // type within this class, which is annoying.
  // Timestamp Timestamp() const { return timestamp_; }

  PacketBase At(Timestamp timestamp) const&;
  PacketBase At(Timestamp timestamp) &&;

  bool IsEmpty() const { return payload_ == nullptr; }

  template <typename T>
  Packet<T> As() const;

  // Returns the reference to the object of type T if it contains
  // one, crashes otherwise.
  template <typename T>
  const T& Get() const;

  // Conversion to old Packet type.
  operator mediapipe::Packet() const { return ToOldPacket(*this); }

 protected:
  explicit PacketBase(std::shared_ptr<HolderBase> payload)
      : payload_(std::move(payload)) {}

  std::shared_ptr<HolderBase> payload_;
  Timestamp timestamp_;

  template <typename T>
  friend PacketBase PacketBaseAdopting(const T* ptr);
  friend PacketBase FromOldPacket(const mediapipe::Packet& op);
  friend mediapipe::Packet ToOldPacket(const PacketBase& p);
};

PacketBase FromOldPacket(const mediapipe::Packet& op);
mediapipe::Packet ToOldPacket(const PacketBase& p);

template <typename T>
inline const T& PacketBase::Get() const {
  CHECK(payload_);
  packet_internal::Holder<T>* typed_payload = payload_->As<T>();
  CHECK(typed_payload) << absl::StrCat(
      "The Packet stores \"", payload_->DebugTypeName(), "\", but \"",
      MediaPipeTypeStringOrDemangled<T>(), "\" was requested.");
  return typed_payload->data();
}

// This is used to indicate that the packet could be holding one of a set of
// types, e.g. Packet<OneOf<A, B>>.
//
// A Packet<OneOf<T...>> has an interface similar to std::variant<T...>.
// However, we cannot use std::variant directly, since it requires that the
// contained object be stored in place within the variant.
// Suppose we have a stream that accepts an Image or an ImageFrame, and it
// receives a Packet<ImageFrame>. To present it as a
// std::variant<Image, ImageFrame> we would have to move the ImageFrame into
// the variant (or copy it), but that is not compatible with Packet's existing
// ownership model.
// We could have Get() return a std::variant<std::reference_wrapper<Image>,
// std::reference_wrapper<ImageFrame>>, but that would just make user code more
// convoluted.
//
// TODO: should we just use Packet<T...>?
template <class... T>
struct OneOf {};

namespace internal {

template <class T>
inline void CheckCompatibleType(const HolderBase& holder, internal::Wrap<T>) {
  const packet_internal::Holder<T>* typed_payload = holder.As<T>();
  CHECK(typed_payload) << absl::StrCat(
      "The Packet stores \"", holder.DebugTypeName(), "\", but \"",
      MediaPipeTypeStringOrDemangled<T>(), "\" was requested.");
  //  CHECK(payload_->has_type<T>());
}

template <class... T>
inline void CheckCompatibleType(const HolderBase& holder,
                                internal::Wrap<OneOf<T...>>) {
  bool compatible = (holder.As<T>() || ...);
  CHECK(compatible)
      << "The Packet stores \"" << holder.DebugTypeName() << "\", but one of "
      << absl::StrJoin(
             {absl::StrCat("\"", MediaPipeTypeStringOrDemangled<T>(), "\"")...},
             ", ")
      << " was requested.";
}

struct Generic {
  Generic() = delete;
};

};  // namespace internal

template <typename T>
inline Packet<T> PacketBase::As() const {
  if (!payload_) return Packet<T>().At(timestamp_);
  packet_internal::Holder<T>* typed_payload = payload_->As<T>();
  internal::CheckCompatibleType(*payload_, internal::Wrap<T>{});
  return Packet<T>(payload_).At(timestamp_);
}

template <>
inline Packet<internal::Generic> PacketBase::As<internal::Generic>() const;

template <typename T = internal::Generic>
class Packet;
#if __cplusplus >= 201703L
// Deduction guide to silence -Wctad-maybe-unsupported.
explicit Packet()->Packet<internal::Generic>;
#endif  // C++17

template <>
class Packet<internal::Generic> : public PacketBase {
 public:
  Packet() = default;

  Packet<internal::Generic> At(Timestamp timestamp) const&;
  Packet<internal::Generic> At(Timestamp timestamp) &&;

 protected:
  explicit Packet(std::shared_ptr<HolderBase> payload)
      : PacketBase(std::move(payload)) {}

  friend PacketBase;
};

// Having Packet<T> subclass Packet<Generic> will require hiding some methods
// like As. May be better not to subclass, and allow implicit conversion
// instead.
template <typename T>
class Packet : public Packet<internal::Generic> {
 public:
  Packet() = default;

  Packet<T> At(Timestamp timestamp) const&;
  Packet<T> At(Timestamp timestamp) &&;

  const T& Get() const {
    CHECK(payload_);
    packet_internal::Holder<T>* typed_payload = payload_->As<T>();
    CHECK(typed_payload);
    return typed_payload->data();
  }
  const T& operator*() const { return Get(); }

  template <typename U>
  T GetOr(U&& v) const {
    return IsEmpty() ? static_cast<T>(absl::forward<U>(v)) : **this;
  }

 private:
  explicit Packet(std::shared_ptr<HolderBase> payload)
      : Packet<internal::Generic>(std::move(payload)) {}

  friend PacketBase;
  template <typename U, typename... Args>
  friend Packet<U> MakePacket(Args&&... args);
  template <typename U>
  friend Packet<U> PacketAdopting(const U* ptr);
  template <typename U>
  friend Packet<U> PacketAdopting(std::unique_ptr<U> ptr);
};

namespace internal {
template <class... F>
struct Overload : F... {
  using F::operator()...;
};
template <class... F>
explicit Overload(F...) -> Overload<F...>;

template <class T, class... U>
struct First {
  using type = T;
};
}  // namespace internal

template <class... T>
class Packet<OneOf<T...>> : public PacketBase {
 public:
  Packet() = default;

  template <class U>
  using AllowedType = std::enable_if_t<(std::is_same_v<U, T> || ...)>;

  template <class U, class = AllowedType<U>>
  Packet(const Packet<U>& p) : PacketBase(p) {}
  template <class U, class = AllowedType<U>>
  Packet<OneOf<T...>>& operator=(const Packet<U>& p) {
    PacketBase::operator=(p);
    return *this;
  }

  template <class U, class = AllowedType<U>>
  Packet(Packet<U>&& p) : PacketBase(std::move(p)) {}
  template <class U, class = AllowedType<U>>
  Packet<OneOf<T...>>& operator=(Packet<U>&& p) {
    PacketBase::operator=(std::move(p));
    return *this;
  }

  Packet<OneOf<T...>> At(Timestamp timestamp) const& {
    return Packet<OneOf<T...>>(*this).At(timestamp);
  }
  Packet<OneOf<T...>> At(Timestamp timestamp) && {
    timestamp_ = timestamp;
    return std::move(*this);
  }

  template <class U, class = AllowedType<U>>
  const U& Get() const {
    CHECK(payload_);
    packet_internal::Holder<U>* typed_payload = payload_->As<U>();
    CHECK(typed_payload);
    return typed_payload->data();
  }

  template <class U, class = AllowedType<U>>
  bool Has() const {
    return payload_ && payload_->As<U>();
  }

  template <class... F>
  auto Visit(const F&... args) const {
    CHECK(payload_);
    auto f = internal::Overload{args...};
    using FirstT = typename internal::First<T...>::type;
    using ResultType = absl::result_of_t<decltype(f)(const FirstT&)>;
    static_assert(
        (std::is_same_v<ResultType, absl::result_of_t<decltype(f)(const T&)>> &&
         ...),
        "All visitor overloads must have the same return type");
    return Invoke<decltype(f), T...>(f);
  }

 protected:
  explicit Packet(std::shared_ptr<HolderBase> payload)
      : PacketBase(std::move(payload)) {}

  friend PacketBase;

 private:
  template <class F, class U>
  auto Invoke(const F& f) const {
    return f(Get<U>());
  }

  template <class F, class U, class V, class... W>
  auto Invoke(const F& f) const {
    return Has<U>() ? f(Get<U>()) : Invoke<F, V, W...>(f);
  }
};

template <>
inline Packet<internal::Generic> PacketBase::As<internal::Generic>() const {
  if (!payload_) return Packet<internal::Generic>().At(timestamp_);
  return Packet<internal::Generic>(payload_).At(timestamp_);
}

inline PacketBase PacketBase::At(Timestamp timestamp) const& {
  return PacketBase(*this).At(timestamp);
}

inline PacketBase PacketBase::At(Timestamp timestamp) && {
  timestamp_ = timestamp;
  return std::move(*this);
}

template <typename T>
inline Packet<T> Packet<T>::At(Timestamp timestamp) const& {
  return Packet<T>(*this).At(timestamp);
}

template <typename T>
inline Packet<T> Packet<T>::At(Timestamp timestamp) && {
  timestamp_ = timestamp;
  return std::move(*this);
}

inline Packet<internal::Generic> Packet<internal::Generic>::At(
    Timestamp timestamp) const& {
  return Packet<internal::Generic>(*this).At(timestamp);
}

inline Packet<internal::Generic> Packet<internal::Generic>::At(
    Timestamp timestamp) && {
  timestamp_ = timestamp;
  return std::move(*this);
}

template <typename T, typename... Args>
Packet<T> MakePacket(Args&&... args) {
  return Packet<T>(std::make_shared<packet_internal::Holder<T>>(
      new T(std::forward<Args>(args)...)));
}

template <typename T>
Packet<T> PacketAdopting(const T* ptr) {
  return Packet<T>(std::make_shared<packet_internal::Holder<T>>(ptr));
}

template <typename T>
Packet<T> PacketAdopting(std::unique_ptr<T> ptr) {
  return Packet<T>(std::make_shared<packet_internal::Holder<T>>(ptr.release()));
}

}  // namespace api2
}  // namespace mediapipe

#endif  // MEDIAPIPE_FRAMEWORK_API2_PACKET_H_
