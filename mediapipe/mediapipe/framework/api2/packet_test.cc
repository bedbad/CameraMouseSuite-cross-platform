#include "mediapipe/framework/api2/packet.h"

#include "absl/strings/str_cat.h"
#include "mediapipe/framework/port/gtest.h"

namespace mediapipe {
namespace api2 {
namespace {

class LiveCheck {
 public:
  explicit LiveCheck(bool* alive) : alive_(*alive) { alive_ = true; }
  ~LiveCheck() { alive_ = false; }

 private:
  bool& alive_;
};

TEST(PacketTest, PacketBaseDefault) {
  PacketBase p;
  EXPECT_TRUE(p.IsEmpty());
}

TEST(PacketTest, PacketBaseNonEmpty) {
  PacketBase p = PacketAdopting(new int(5));
  EXPECT_FALSE(p.IsEmpty());
}

TEST(PacketTest, PacketBaseRefCount) {
  bool alive = false;
  PacketBase p = PacketAdopting(new LiveCheck(&alive));
  EXPECT_TRUE(alive);
  PacketBase p2 = p;
  p = {};
  EXPECT_TRUE(alive);
  p2 = {};
  EXPECT_FALSE(alive);
}

TEST(PacketTest, PacketBaseSame) {
  int* ip = new int(5);
  PacketBase p = PacketAdopting(ip);
  PacketBase p2 = p;
  EXPECT_EQ(&p2.Get<int>(), ip);
}

TEST(PacketTest, PacketNonEmpty) {
  Packet<int> p = MakePacket<int>(5);
  EXPECT_FALSE(p.IsEmpty());
}

TEST(PacketTest, Get) {
  Packet<int> p = MakePacket<int>(5);
  EXPECT_EQ(*p, 5);
  EXPECT_EQ(p.Get(), 5);
}

TEST(PacketTest, GetOr) {
  Packet<int> p_0 = MakePacket<int>(0);
  Packet<int> p_5 = MakePacket<int>(5);
  Packet<int> p_empty;
  EXPECT_EQ(p_0.GetOr(1), 0);
  EXPECT_EQ(p_5.GetOr(1), 5);
  EXPECT_EQ(p_empty.GetOr(1), 1);
}

// This show how GetOr can be used with a lambda that is only called if the "or"
// case is needed. Can be useful when generating the fallback value is
// expensive.
// We could also add an overload to GetOr for types which are not convertible to
// T, but are callable and return T.
// TODO: consider adding it to make things easier.
template <typename F>
struct Lazy {
  F f;
  using ValueT = decltype(f());
  Lazy(F fun) : f(fun) {}
  operator ValueT() const { return f(); }
};
template <typename F>
Lazy(F f) -> Lazy<F>;

TEST(PacketTest, GetOrLazy) {
  int expensive_call_count = 0;
  auto expensive_string_generation = [&expensive_call_count] {
    ++expensive_call_count;
    return "an expensive fallback";
  };

  auto p_hello = MakePacket<std::string>("hello");
  Packet<std::string> p_empty;

  EXPECT_EQ(p_hello.GetOr(Lazy(expensive_string_generation)), "hello");
  EXPECT_EQ(expensive_call_count, 0);
  EXPECT_EQ(p_empty.GetOr(Lazy(expensive_string_generation)),
            "an expensive fallback");
  EXPECT_EQ(expensive_call_count, 1);
}

TEST(PacketTest, OneOf) {
  Packet<OneOf<std::string, int>> p = MakePacket<std::string>("hi");
  EXPECT_TRUE(p.Has<std::string>());
  EXPECT_FALSE(p.Has<int>());
  EXPECT_EQ(p.Get<std::string>(), "hi");
  std::string out =
      p.Visit([](std::string s) { return absl::StrCat("string: ", s); },
              [](int i) { return absl::StrCat("int: ", i); });
  EXPECT_EQ(out, "string: hi");

  p = MakePacket<int>(2);
  EXPECT_FALSE(p.Has<std::string>());
  EXPECT_TRUE(p.Has<int>());
  EXPECT_EQ(p.Get<int>(), 2);
  out = p.Visit([](std::string s) { return absl::StrCat("string: ", s); },
                [](int i) { return absl::StrCat("int: ", i); });
  EXPECT_EQ(out, "int: 2");
}

TEST(PacketTest, PacketRefCount) {
  bool alive = false;
  auto p = MakePacket<LiveCheck>(&alive);
  EXPECT_TRUE(alive);
  auto p2 = p;
  p = {};
  EXPECT_TRUE(alive);
  p2 = {};
  EXPECT_FALSE(alive);
}

TEST(PacketTest, PacketTimestamp) {
  auto p = MakePacket<int>(5);
  EXPECT_EQ(p.timestamp(), Timestamp::Unset());
  auto p2 = p.At(Timestamp(1));
  EXPECT_EQ(p.timestamp(), Timestamp::Unset());
  EXPECT_EQ(p2.timestamp(), Timestamp(1));
  auto p3 = std::move(p2).At(Timestamp(3));
  EXPECT_EQ(p3.timestamp(), Timestamp(3));
}

TEST(PacketTest, PacketFromGeneric) {
  Packet<> pb = PacketAdopting(new int(5));
  Packet<int> p = pb.As<int>();
  EXPECT_EQ(p.Get(), 5);
}

TEST(PacketTest, PacketAdopting) {
  Packet<float> p = PacketAdopting(new float(1.0));
  EXPECT_FALSE(p.IsEmpty());
}

TEST(PacketTest, PacketGeneric) {
  // With C++17, Packet<> could be written simply as Packet.
  Packet<> p = PacketAdopting(new float(1.0));
  EXPECT_FALSE(p.IsEmpty());
}

TEST(PacketTest, PacketGenericTimestamp) {
  Packet<> p = MakePacket<int>(5);
  EXPECT_EQ(p.timestamp(), mediapipe::Timestamp::Unset());
  auto p2 = p.At(Timestamp(1));
  EXPECT_EQ(p.timestamp(), mediapipe::Timestamp::Unset());
  EXPECT_EQ(p2.timestamp(), Timestamp(1));
  auto p3 = std::move(p2).At(Timestamp(3));
  EXPECT_EQ(p3.timestamp(), Timestamp(3));
}

TEST(PacketTest, FromOldPacket) {
  mediapipe::Packet op = mediapipe::MakePacket<int>(7);
  Packet<int> p = FromOldPacket(op).As<int>();
  EXPECT_EQ(p.Get(), 7);
}

TEST(PacketTest, ToOldPacket) {
  auto p = MakePacket<int>(7);
  mediapipe::Packet op = ToOldPacket(p);
  EXPECT_EQ(op.Get<int>(), 7);
}

TEST(PacketTest, OldRefCounting) {
  bool alive = false;
  PacketBase p = PacketAdopting(new LiveCheck(&alive));
  EXPECT_TRUE(alive);
  mediapipe::Packet op = ToOldPacket(p);
  p = {};
  EXPECT_TRUE(alive);
  PacketBase p2 = FromOldPacket(op);
  op = {};
  EXPECT_TRUE(alive);
  p2 = {};
  EXPECT_FALSE(alive);
}

}  // namespace
}  // namespace api2
}  // namespace mediapipe
