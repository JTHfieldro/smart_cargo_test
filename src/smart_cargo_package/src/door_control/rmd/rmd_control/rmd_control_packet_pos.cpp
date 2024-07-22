#include "rmd_control.h"

std::array<uint8_t, 8> RmdControl::set_packet_position(int32_t val, int32_t repeat)
{
  std::array<uint8_t, 8> packet = {0};
  // Position Control
  int32_t max_speed = val * 6;
  int32_t angle     = 0;

  packet[0] = static_cast<uint8_t>(RMD_DEFINE::C_CTRL_POSITION);  // Command Byte 0xA4
  packet[2] = max_speed & 0xFF;                                   // maxSpeed
  packet[3] = (max_speed >> 8) & 0xFF;                            // maxSpeed >> 8
  packet[4] = angle & 0xFF;                                       // angleControl
  packet[5] = (angle >> 8) & 0xFF;                                // angleControl >> 8
  packet[6] = (angle >> 16) & 0xFF;                               // angleControl >> 16
  packet[7] = (angle >> 24) & 0xFF;                               // angleControl >> 24

  return packet;
}

std::array<uint8_t, 8> RmdControl::set_packet_inc_position(int32_t rpm, int32_t angle)
{
  std::array<uint8_t, 8> packet = {0};
  // Position Control
  int32_t max_speed = rpm * 6;
  int32_t target    = angle * 100;

  packet[0] = static_cast<uint8_t>(RMD_DEFINE::C_CTRL_INC_POSITION);  // Command Byte 0xA8
  packet[2] = max_speed & 0xFF;                                       // maxSpeed
  packet[3] = (max_speed >> 8) & 0xFF;                                // maxSpeed >> 8
  packet[4] = target & 0xFF;                                          // angleControl
  packet[5] = (target >> 8) & 0xFF;                                   // angleControl >> 8
  packet[6] = (target >> 16) & 0xFF;  // angleControl >> 16
  packet[7] = (target >> 24) & 0xFF;  // angleControl >> 24

  return packet;
}

std::array<uint8_t, 8> RmdControl::set_packet_inc_position_repeat(int32_t  rpm,
                                                                  uint32_t repeat)
{
  // Position Control
  std::array<uint8_t, 8> packet    = {0};
  int32_t                max_speed = rpm * 6;
  int32_t                target    = repeat * 36000;

  if(rpm < 0)
  {
    max_speed = max_speed * (-1);
    target    = target * (-1);
  }

  packet[0] = static_cast<uint8_t>(RMD_DEFINE::C_CTRL_INC_POSITION);  // Command Byte 0xA8
  packet[2] = max_speed & 0xFF;                                       // maxSpeed
  packet[3] = (max_speed >> 8) & 0xFF;                                // maxSpeed >> 8
  packet[4] = target & 0xFF;                                          // angleControl
  packet[5] = (target >> 8) & 0xFF;                                   // angleControl >> 8
  packet[6] = (target >> 16) & 0xFF;  // angleControl >> 16
  packet[7] = (target >> 24) & 0xFF;  // angleControl >> 24

  return packet;
}