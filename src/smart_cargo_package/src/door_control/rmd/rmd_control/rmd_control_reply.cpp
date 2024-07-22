#include "rmd_control.h"

/// @brief  [0xA2] Speed_Closed-loop Control에 대한 응답
/// @return
/// @note   응답값 중 위치값만을 확인
float RmdControl::check_speed_reply()
{
  /** [0xA2] Speed_Closed-loop Control Reply
   * DATA[0] = 0xA2
   * DATA[1] = (uint8_t)(temperature)
   * DATA[2] = (uint8_t)(iq)
   * DATA[3] = (uint8_t)(iq>>8)
   * DATA[4] = (uint8_t)(speed)
   * DATA[5] = (uint8_t)(speed>>8)
   * DATA[6] = (uint8_t)(degree)
   * DATA[7] = (uint8_t)(degree>>8)
   */
  std::array<uint8_t, 8> receive_packet  = {0};
  bool                   receive_success = _can->receive_packet(receive_packet);

  if((!receive_success) ||
     (receive_packet[0] != static_cast<uint8_t>(RMD_DEFINE::C_CTRL_SPEED)))
    return 0.0f;

  // Motor output shaft angle related to the zero position
  int16_t shaft_angle = (static_cast<int16_t>(receive_packet[7]) << 8) |
                        (static_cast<int16_t>(receive_packet[6]) & 0xFF);
  float actual_angle = static_cast<float>(shaft_angle);

  return actual_angle;
}

int32_t RmdControl::check_current_position()
{
  _can->send_packet(set_packet_cmd(static_cast<int32_t>(RMD_DEFINE::M_READ_ABS_POS)));

  float degree;

  // Command Byte 0x92
  // DATA[4] angle low byte 1    DATA[4] = (uint8_t)(motorAngle)
  // DATA[5] angle bytes2        DATA[5] = (uint8_t)(motorAngle>>8)
  // DATA[6] angle bytes3        DATA[6] = (uint8_t)(motorAngle>>16)
  // DATA[7] angle bytes4        DATA[7] = (uint8_t)(motorAngle>>24)
  std::array<uint8_t, 8> recv_packet  = {0};
  bool                   ret_successd = _can->receive_packet(recv_packet);

  if(ret_successd)
  {
    int32_t motor_position = (recv_packet[7] << 24) | (recv_packet[6] << 16) |
                             (recv_packet[5] << 8) | recv_packet[4];
    // degree = motor_angle * 0.01;
    motor_position * 0.01;

    // std::cout << "Motor Current Angle: " << degree << "[']" << std::endl;
    LOGGER->push_log_format("INFO", "PROC", "Current Position",
                            std::to_string(motor_position));

    _current_position = motor_position;

    return motor_position;
  }

  return 0;
}