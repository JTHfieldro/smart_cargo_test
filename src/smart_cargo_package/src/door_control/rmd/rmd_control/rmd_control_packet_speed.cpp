#include "rmd_control.h"

std::array<uint8_t, 8> RmdControl::set_packet_speed(int32_t rpm)
{
  std::array<uint8_t, 8> packet = {0};
  // Closed_Loop Control
  // 1[rpm] == 6[dps] == 600 * 0.01[dps/LSB]
  int32_t rpm_to_dps = rpm * 600;

  packet[0] = static_cast<uint8_t>(RMD_DEFINE::C_CTRL_SPEED);  // Command Byte 0xA2
  packet[4] = rpm_to_dps & 0xFF;                               // speedControl
  packet[5] = (rpm_to_dps >> 8) & 0xFF;                        // speedControl >> 8
  packet[6] = (rpm_to_dps >> 16) & 0xFF;                       // speedControl >> 16
  packet[7] = (rpm_to_dps >> 24) & 0xFF;                       // speedControl >> 24

  return packet;
}
