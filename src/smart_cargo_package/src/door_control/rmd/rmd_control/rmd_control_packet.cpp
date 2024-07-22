#include "rmd_control.h"

std::array<uint8_t, 8> RmdControl::set_packet_cmd(int32_t cmd)
{
  std::array<uint8_t, 8> packet = {0};
  switch(cmd)
  {
    case static_cast<int32_t>(RMD_DEFINE::MOTOR_READ_ACCEL):  // Command Byte 0x42
      packet[0] = static_cast<uint8_t>(RMD_DEFINE::MOTOR_READ_ACCEL);
      break;
    case static_cast<int32_t>(RMD_DEFINE::MOTOR_WRITE_ACCEL):  // Command Byte 0x43
      packet[0] = static_cast<uint8_t>(RMD_DEFINE::MOTOR_WRITE_ACCEL);
      break;
    case static_cast<int32_t>(
        RMD_DEFINE::M_WRITE_OFFSET_POS_CURRENT):  // Command Byte 0x64
      packet[0] = static_cast<uint8_t>(RMD_DEFINE::M_WRITE_OFFSET_POS_CURRENT);
      break;
    case static_cast<int32_t>(RMD_DEFINE::MOTOR_CTRL_ID):  // Command Byte 0x79
      packet[0] = static_cast<uint8_t>(RMD_DEFINE::MOTOR_CTRL_ID);
      break;
    case static_cast<int32_t>(RMD_DEFINE::MOTOR_CTRL_STOP):  // Command Byte 0x81
      packet[0] = static_cast<uint8_t>(RMD_DEFINE::MOTOR_CTRL_STOP);
      break;
    case static_cast<int32_t>(RMD_DEFINE::M_READ_ABS_POS):  // Command Byte 0x92
      packet[0] = static_cast<uint8_t>(RMD_DEFINE::M_READ_ABS_POS);
      break;
    case static_cast<int32_t>(RMD_DEFINE::MOTOR_CTRL_BREAK_ON):  // Command Byte 0x78
      packet[0] = static_cast<uint8_t>(RMD_DEFINE::MOTOR_CTRL_BREAK_ON);
      break;
  }
  return packet;
}
