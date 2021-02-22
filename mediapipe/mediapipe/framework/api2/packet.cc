#include "mediapipe/framework/api2/packet.h"

namespace mediapipe {
namespace api2 {

PacketBase FromOldPacket(const mediapipe::Packet& op) {
  return PacketBase(packet_internal::GetHolderShared(op)).At(op.Timestamp());
}

mediapipe::Packet ToOldPacket(const PacketBase& p) {
  return mediapipe::packet_internal::Create(p.payload_, p.timestamp_);
}

}  // namespace api2
}  // namespace mediapipe
