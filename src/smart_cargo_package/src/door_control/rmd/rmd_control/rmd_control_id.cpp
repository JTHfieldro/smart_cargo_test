#include "rmd_control.h"

// PC에 연결된 모든 Motor의 ID 확인
void RmdControl::check_canid()
{
  std::array<uint8_t, 8> packet = {0};
  packet    = set_packet_cmd(static_cast<int32_t>(RMD_DEFINE::MOTOR_CTRL_ID));
  packet[2] = 1;

  _can->send_packet_broadcast(packet);

  std::array<uint8_t, 8> recv_packet  = {0};
  bool                   recv_success = _can->receive_packet(recv_packet);

  if(recv_success)
  {
    // 응답 메시지를 성공적으로 읽었습니다.
    // 메시지에서 CAN ID를 추출합니다.
    int32_t can_id = 320 + recv_packet[7];
    std::cout << "CANID: " << std::hex << can_id << std::endl;

    LOGGER->push_log_format("INFO", "PROC", "CAN ID",
                            std::to_string(can_id) + std::string("[DEC]"));
  }
}