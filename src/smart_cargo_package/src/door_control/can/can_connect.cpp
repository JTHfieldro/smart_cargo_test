#include "can.h"

bool Can::connect_check()
{
  // _can_status의 값이 연결이 끊어진 상태를 확인할 수 있는 값인지 확인
  if(!get_channel_flag())
  {
    return false;
  }
  return true;
}

bool Can::is_connected()
{
  return _is_connected;
}

bool Can::try_connect_can()
{
  //   if((_last_try_connect_time + _retry_turm) > std::time(nullptr)) return false;
  if(_retry_count <= 0) return false;

  _last_try_connect_time = std::time(nullptr);
  _retry_count--;

  if(!connect_can())
  {
    char error_message[256];
    canGetErrorText(_can_status, error_message, sizeof(error_message));
    LOGGER->push_log_format("ERROR", "PROC", "can_connect fail !!!", "");
    LOGGER->push_log_format("ERROR", "PROC", "Error Message", error_message);
    return false;
  }
  else
  {
    LOGGER->push_log_format("INFO", "PROC", "can_connection Success", "");
  }

  _is_connected = true;
  return true;
}

bool Can::connect_can()
{
  // CAN Channel Open 및 해당 Channel에 대한 Handle 반환
  // channel : 열리는 CAN Channel Number
  // flags : CAN Channel Open 시 적용할 옵션을 지정하는 Bit Mask
  //        canOPEN_EXCLUSIVE           Channel에 대한 독점 접근 요청
  //        canOPEN_REQUIRE_EXTENDED    확장 CAN Message만 허용
  //        canOPEN_ACCEPT_VIRTUAL      가상 CAN Channel 생성을 허용
  //        canOPEN_OVERRIDE_EXCLUSIVE  Channel이 다른 App에 의해 독점 모드로
  //        열려 있어도 강제로 Open
  //        canOPEN_REQUIRE_INIT_ACCESS Channel 초기화 중 CAN Bus에 대한 접근 요청
  //        canOPEN_NO_INIT_ACCESS      Channel 초기화 중 CAN Bus에 대한 접근 없음
  //        canOPEN_ACCEPT_LARGE_DLC    CAN FD 형식의 긴 데이터 길이 코딩을 허용
  // callback : CAN Message 수신 시 호출될 CallBack 함수에 대한 포인터, 미사용
  // 시 NULL 전달 ret : 성공 시 Channel Handle 반환, 실패 시 음수 오류 코드 반환
  _can_handle = canOpenChannel(_channel, canOPEN_OVERRIDE_EXCLUSIVE);
  // CAN 채널 Open Error 처리
  if(_can_handle < 0)
  {
    char name[256];
    // 채널 이름 가져오기
    _can_status =
        canGetChannelData(_can_handle, canCHANNELDATA_DEVDESCR_ASCII, name, sizeof(name));
    if(_can_status == canOK)
    {
      std::cout << "Channel " << _channel << " name: " << name << std::endl;
    }

    char error_message[256];
    canGetErrorText(_can_status, error_message, sizeof(error_message));
    LOGGER->push_log_format("ERROR", "PROC", "open_channel fail !!!", "");
    LOGGER->push_log_format("ERROR", "PROC", "Error Message", error_message);
    return false;
  }

  // CAN Bus Bitrate 및 기타 매개변수 설정
  // hnd : CAN Channel Handle, canOpenChannel의 반환값
  // freq : CAN Bus Bitrate 설정
  // tseg1 : 위상 Segmen1의 시간 양을 지정, CAN Controller의 Clock 주기 단위로
  // 표현 tseg2 : 위상 Segmen2의 시간 양을 지정, CAN Controller의 Clock 주기
  // 단위로 표현 sjw : 동기화 점프 폭을 지정, CAN Controller의 Clock 주기 단위로
  // 표현 noSamp : Sampling Point 지정, 1은 Sampling Point가 tseg1의 끝에 있음을
  // 3은 tesg2의 끝에 있음을 의미 syncmode : CAN Controller의 동기화 모드 지정,
  // 0: 기본 동기화 모드 ret : 성공 시 canOK, 실패 시 음수 오류 코드 반환
  _can_status = canSetBusParams(_can_handle, canBITRATE_1M, 0, 0, 0, 0, 0);
  // CAN 매개변수 설정 Error 처리
  if(_can_status != canOK)
  {
    char error_message[256];
    canGetErrorText(_can_status, error_message, sizeof(error_message));
    LOGGER->push_log_format("ERROR", "PROC", "set_bus_params fail !!!", "");
    LOGGER->push_log_format("ERROR", "PROC", "Error Message", error_message);
    return false;
  }

  // CAN Filter 설정
  canSetAcceptanceFilter(_can_handle, _reply_id, 0x7FF, 1);

  // CAN Controller를 작동 상태(Bus On)으로 설정
  // hnd : CAN Channel Handle, canOpenChannel 반환값
  // ret : 성공 시 canOK 반환, 실패 시 음수 오류 코드 반환
  _can_status = canBusOn(_can_handle);
  // CAN Bus Activation Error 처리
  if(_can_status != canOK)
  {
    char error_message[256];
    canGetErrorText(_can_status, error_message, sizeof(error_message));
    LOGGER->push_log_format("ERROR", "PROC", "bus_on fail !!!", "");
    LOGGER->push_log_format("ERROR", "PROC", "Error Message", error_message);
    return false;
  }

  return true;
}

void Can::disconnect_can()
{
  // CAN 채널 닫기
  // hnd : CAN Channel Handle, canOpenChannel 반환값
  _can_status = canClose(_can_handle);
  _can_status = canUnloadLibrary();

  _is_connected = false;

  LOGGER->push_log_format("INFO", "PROC", "can_disconnection Success", "");
}