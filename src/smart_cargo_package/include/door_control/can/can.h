#pragma once

#include <canlib.h>

#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>

#include "global_define.h"
#include "logger.h"
#include "thread_action_info.h"
#include "yaml-cpp/yaml.h"

#ifndef LOGGER
#define LOGGER Logger::get("door_control")
#endif

enum class CAN_CONNECTION
{
  CAN_DISCONNECTED = 0,  // CAN 연결 끊김
  CAN_CONNECTED    = 1,  // CAN 연결 됨
  CAN_END,
};

class Can
{
public:
  Can(std::string option_file);
  ~Can();

public:
  bool connect_check();  // can 연결 상태 확인, thread 동작 함수
  bool is_connected();   // can 연결 상태 변수값 반환
  bool is_status_ok();

  bool send_packet_broadcast(std::array<uint8_t, 8> packet);  // can message 전역 발신
  bool send_packet(std::array<uint8_t, 8> packet);            // can message 발신
  bool receive_packet(std::array<uint8_t, 8> packet);         // can message 수신

  void set_filter();  // CAN filter 확인

protected:
  canHandle _can_handle;  // can channel 객체
  canStatus _can_status;  // can bus 객체

  // CAN ID 설정
  long    _send_id;   // motor can send id 변수
  long    _reply_id;  // motor can reply id 변수
  int32_t _channel;   // motor can channel 변수
  int32_t _bitrate;   // motor can bitrate 변수

  bool        _is_connected;           // can 연결 상태 변수
  std::time_t _last_try_connect_time;  // 마지막 CAN 연결 시도 시간
  int32_t     _retry_turm;             // 재시도 간격
  int32_t     _retry_count;            // CAN 연결 재시도 횟수
  uint32_t    _time_out;               // read, write time out

protected:
  void load_option(std::string option_file);  // motor can 변수 호출

  bool try_connect_can();  // can 연결 시도
  bool connect_can();      // can 연결
  void disconnect_can();   // can 해제

  bool get_channel_flag();  // _can_status 객체 update
};