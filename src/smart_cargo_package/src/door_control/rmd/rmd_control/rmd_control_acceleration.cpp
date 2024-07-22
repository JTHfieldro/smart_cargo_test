#include "rmd_control.h"

void RmdControl::check_accel()
{
  _can->send_packet(set_packet_cmd(static_cast<int32_t>(RMD_DEFINE::MOTOR_READ_ACCEL)));

  std::array<uint8_t, 8> recv_packet  = {0};
  bool                   recv_success = _can->receive_packet(recv_packet);

  if(recv_success)
  {
    int32_t accel = (recv_packet[7] << 24) | (recv_packet[6] << 16) |
                    (recv_packet[5] << 8) | recv_packet[4];
    LOGGER->push_log_format("INFO", "PROC", "Acceleration",
                            std::to_string(accel) + std::string("[dps/s]"));
  }
}

void RmdControl::set_accel(const std::map<std::__cxx11::string, int32_t>& command_map)
{
  std::array<uint8_t, 8> packet       = {0};
  int32_t                accel_target = _command_map.find("accel")->second;
  packet    = set_packet_cmd(static_cast<int32_t>(RMD_DEFINE::MOTOR_WRITE_ACCEL));
  packet[4] = accel_target & 0xFF;
  packet[5] = (accel_target >> 8) & 0xFF;
  packet[6] = (accel_target >> 16) & 0xFF;
  packet[7] = (accel_target >> 24) & 0xFF;

  _can->send_packet(packet);

  std::array<uint8_t, 8> recv_packet  = {0};
  bool                   recv_success = _can->receive_packet(recv_packet);

  if(recv_success)
  {
    int32_t accel = (recv_packet[7] << 24) | (recv_packet[6] << 16) |
                    (recv_packet[5] << 8) | recv_packet[4];
    LOGGER->push_log_format("INFO", "PROC", "Acceleration Set",
                            std::to_string(accel) + std::string("[dps/s]"));
  }
}

void RmdControl::set_accel(ACCEL_TYPE type, uint32_t accel)
{
  std::array<uint8_t, 8> packet       = {0};
  uint32_t               accel_target = accel;
  packet[0] = static_cast<uint8_t>(RMD_DEFINE::MOTOR_WRITE_ACCEL);
  packet[1] = static_cast<uint8_t>(type);  // 가감속 타입
  packet[4] = accel_target & 0xFF;
  packet[5] = (accel_target >> 8) & 0xFF;
  packet[6] = (accel_target >> 16) & 0xFF;
  packet[7] = (accel_target >> 24) & 0xFF;

  _can->send_packet(packet);

  std::array<uint8_t, 8> recv_packet  = {0};
  bool                   recv_success = _can->receive_packet(recv_packet);

  if(recv_success)
  {
    int32_t accel = (recv_packet[7] << 24) | (recv_packet[6] << 16) |
                    (recv_packet[5] << 8) | recv_packet[4];
    LOGGER->push_log_format("INFO", "PROC", "Acceleration Set",
                            std::to_string(accel) + std::string("[dps/s]"));
  }
}