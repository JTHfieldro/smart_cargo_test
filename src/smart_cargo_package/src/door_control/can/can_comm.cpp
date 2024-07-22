#include "can.h"

bool Can::send_packet(std::array<uint8_t, 8> packet)
{
  // CAN Message 전송
  // hnd : CAN Channel Handle, canOpenChannel 반환값
  // id : 전송할 CAN Message의 식별자
  // msg : 전송할 데이터에 대한 Pointer
  // dlc : 전송할 데이터의 길이(Byte)
  // flag : Message 전송 옵션을 지정하는 Bit Mask
  //        canMSG_STD          표준 CAN Message 전송
  //        canMSG_EXT          확전 CAN Message 전송
  //        canMSG_RTR          원격 전송 요청(RTR) Message 전송
  //        canMSG_WAKEUP       Wakeup Message 전송
  //        canMSG_NERR         NERR Bit 설정
  //        canMSG_ERROR_FRAME  오류 Frame 전송
  //        canMSG_TXNEXT       전송 대기열의 다음 슬롯에 Message 배치
  // ret : 성공 시 canOK 반환, 실패 시 음수 오류 코드 반환
  _can_status = canWrite(_can_handle, _send_id, packet.data(), packet.size(), canMSG_STD);
  if(_can_status == canOK) return true;
  else if(_can_status != canOK)
  {
    char error_message[256];
    canGetErrorText(_can_status, error_message, sizeof(error_message));
    LOGGER->push_log_format("ERROR", "PROC", "can_write fail !!!", error_message);

    return false;
  }
}

bool Can::send_packet_broadcast(std::array<uint8_t, 8> packet)
{
  // 수신된 Buffer 비우기
  if(canFlushReceiveQueue(_can_handle) == canOK)

    _can_status =
        canWrite(_can_handle, 0x140 + 0x00, packet.data(), packet.size(), canMSG_STD);
  if(_can_status == canOK) return true;
  else if(_can_status != canOK)
  {
    char error_message[256];
    canGetErrorText(_can_status, error_message, sizeof(error_message));
    LOGGER->push_log_format("ERROR", "PROC", "can_write_broadcast fail !!!", "");
    LOGGER->push_log_format("ERROR", "PROC", "Error Message", error_message);
    return false;
  }
}

bool Can::receive_packet(std::array<uint8_t, 8> packet)
{
  // CAN Message 수신
  // hnd : CAN Channel Handle, canOpenChannel 반환값
  // id : 수신된 Message의 식별자를 저장할 변수에 대한 Pointer
  // msg : 수신된 데이터를 저장할 Buffer에 대한 Pointer
  // dlc : 수신된 데이터의 길이(Byte)를 저장할 변수에 대한 Pointer
  // flag : 수신된 Message의 옵션을 저장할 변수에 대한 Pointer
  // time : 수신된 Message의 Timestamp를 저장할 변수에 대한 Pointer

  long          id = _reply_id;
  unsigned int  dlc;
  unsigned int  flag;
  unsigned long time;

  _can_status =
      canReadWait(_can_handle, &id, packet.data(), &dlc, &flag, &time, _time_out);
  // 수신 Message 처리
  if(_can_status == canOK)
  {
    if(dlc != 8)
    {
      LOGGER->push_log_format("ERROR", "PROC", "Receive Message Size is Wrong", "");
      return false;
    }
    return true;
  }
  else if(_can_status == canERR_NOMSG)
  {
    LOGGER->push_log_format("WARN", "PROC", "There is No Message", "");
    return false;
  }
  else
  {
    char error_message[256];
    canGetErrorText(_can_status, error_message, sizeof(error_message));
    LOGGER->push_log_format("ERROR", "PROC", "can_read Fail!", error_message);
    return false;
  }
}
