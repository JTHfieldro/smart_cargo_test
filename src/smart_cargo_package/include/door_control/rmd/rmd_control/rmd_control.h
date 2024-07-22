#pragma once

#include <map>
#include <string>

#include "can.h"
#include "global_define.h"
#include "global_helper.h"
#include "logger.h"
#include "rmd_define.h"
#include "rmd_enum.h"
#include "std_msgs/Int32.h"
#include "std_msgs/String.h"
#include "thread_action_info.h"

#ifndef LOGGER
#define LOGGER Logger::get("door_control")
#endif

enum class ACCEL_TYPE
{
  POS_ACCEL   = 0x00,  // 위치 제어 가속도
  POS_DECEL   = 0x01,  // 위치 제어 감속도
  SPEED_ACCEL = 0x02,  // 속도 제어 가속도
  SPEED_DECEL = 0x03,  // 속도 제어 감속도
  ACCEL_TYPE_END,
};

class RmdControl
{
private:
  RmdControl(){};

public:
  RmdControl(Can* can, std::string option_file,
             std::function<void(RMD_ACTION, RMD_DEFINE)> update_callback);
  ~RmdControl();

public:
  void control_stop();  // motor 정지
  // motor speed control(using in command message)
  void control_speed(std::string                                    str,
                     const std::map<std::__cxx11::string, int32_t>& command_map);
  // motor speed control(using in scenario)
  bool control_speed(std::string direction);
  // motor incremental position control
  void control_position(const std::map<std::__cxx11::string, int32_t>& command_map);

  void set_home();
  void set_accel(const std::map<std::__cxx11::string, int32_t>& command_map);
  void set_accel(ACCEL_TYPE type, uint32_t accel);
  void check_accel();
  void check_canid();

protected:
  Can*                           _can;          // can 객체 참조 객체
  std::map<std::string, int32_t> _command_map;  // 명령어 맵

  ThreadActionInfo* _thread_info;  // thread action 객체

  uint8_t _packet[8];  // can 발신 packet 변수

  // RMD Option 설정
  int32_t _gear_ratio;    // motor gear ration 변수
  int32_t _step_per_rev;  // motor encoder 변수
                          // Single-Resoultion Value(Pulses)
  int32_t _rpm;           // 동작 rpm 변수
  int32_t _target_step;   // motor 정지 position
  int32_t _mode;

  bool    _check_position;    // check position 동작 여부
  int32_t _init_position;     // program 시작 시 위치 값
  int32_t _prev_position;     // check position 동작 후 위치 값
  int32_t _current_position;  // check position 동작 중 위치 값
  int32_t _max_limit;         // Max limit Encoder 값
  int32_t _min_limit;         // Min limit Encoder 값

  std::function<void(RMD_ACTION, RMD_DEFINE)>
      _update_callback;  // action, mode update callback

protected:
  void update();  // 실제 thread 함수

  void load_option(std::string option_file);  // motor can 변수 호출

  std::array<uint8_t, 8> set_packet_cmd(int32_t cmd);  // command 발신용 패킷 생성
  std::array<uint8_t, 8> set_packet_speed(
      int32_t rpm = 0);  // speed control 발신용 패킷 생성
  // position control 발신용 패킷 생성
  std::array<uint8_t, 8> set_packet_position(int32_t rpm = 0, int32_t repeat = 1);
  // incremental position control 발신용 패킷 생성(0~360 각도 제어)
  std::array<uint8_t, 8> set_packet_inc_position(int32_t rpm, int32_t angle);
  // incremental position control 발신용 패킷 생성(반복 회전)
  std::array<uint8_t, 8> set_packet_inc_position_repeat(int32_t  rpm    = 0,
                                                        uint32_t repeat = 1);

  float   check_speed_reply();       // speed control reply 판단 함수
  int32_t check_current_position();  // motor position update

  void update_rmd_status(RMD_ACTION action, RMD_DEFINE mode);  // 상태 update
};