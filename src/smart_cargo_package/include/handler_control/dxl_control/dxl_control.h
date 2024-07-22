#pragma once

#include <dynamixel_sdk/dynamixel_sdk.h>

#include <chrono>
#include <mutex>
#include <random>
#include <string>

#include "dxl_485.h"
#include "dynamixel_define.h"
#include "global_helper.h"
#include "logger.h"
#include "thread_action_info.h"
#include "yaml-cpp/yaml.h"

#ifndef LOGGER
#define LOGGER Logger::get("handler_control")
#endif

class DxlControl
{
private:
  DxlControl();

public:
  DxlControl(std::string file_name);
  ~DxlControl();

public:
  void control(std::string cmd, const std::map<std::string, int32_t>& command_map);

protected:
  dynamixel::PortHandler*     _port_handler;    // Dynamixel Port Handler 객체
  dynamixel::PacketHandler*   _packet_handler;  // Dynamixel Packet Handler 객체
  std::unique_ptr<Dxl485>     _dxl_485;         // Dynamixel Connection 객체
  std::shared_ptr<std::mutex> _tx_mtx;          // tx mutex 객체
  ThreadActionInfo*           _thread_info;     // thread 동작 정보 객체

  int32_t        _comm_result;       // read/write 결과 저장 변수
  uint8_t        _error;             // read/write error 저장 변수
  uint32_t       _present_position;  // 현재 위치 저장 변수
  uint8_t        _in_position;       // Moving Status - In Positino 저장 변수
  std::once_flag _init_flag;         // initialize flag
  bool           _torque_flag;       // Torque Enable flag

  // config file에서 가져오는 변수
  std::string _device_name;        // COM Port name
  float       _protocol_ver;       // Dynamixel Protocol Version
  uint8_t     _id;                 // Dynamixel Motor ID
  uint8_t     _op_mode;            // Dynamixel Operating Mode
  uint8_t     _drive_mode;         // Dynamixel Dirve Mode
  int32_t     _goal_rpm;           // GOAL_VELOCITY rpm
  uint32_t    _profile_acc;        // Position Contorl - Profile Acceleration
  uint32_t    _profile_vel;        // Position Contorl - Profile Maximum Velocity
  int32_t     _goal_position_max;  // Position Contorl - Goal Maximum Position
  int32_t     _goal_position_min;  // Position Contorl - Goal Minimum Position

protected:
  void update();

  void load_option(std::string file_name);

  void initialize();
  bool is_fail(std::string target);  // Fail, Error Log Format

  void set_operating_mode(OPERATION_MODE mode);  // Dynamixel Operating Mode 설정
  void set_drive_mode(uint8_t mode);             // Dynamixel Dirve Mode 설정
  void set_home_position();                      // Dynamixel Home Position 설정

  void check_operating_mode();  // Dynamixel Operating Mode 확인
  void check_drive_mode();      // Dynamixel Dirve Mode 확인
  void get_current_pos();       // 현재 위치 확인
  bool is_move();               // 동작 상태 확인

  void torque_control(TORQUE_CONTROL togle);  // Torque On/Off 설정
  void stop();                                // Dynamixel 정지

  /// @brief 속도 제어
  void move_velocity(int32_t vel);      // Velocity Control 설정 속도로 동작
  void move_velocity();                 // Velocity Control 목표 속도로 동작
  void set_velocity_mode(int32_t vel);  // Velocity Control 목표 속도 설정

  /// @brief 속도 지정 및 위치 제어
  void move_position(int32_t position);  // 임의 위치로 이동
  void move_home_position();             // Home 위치로 이동
  void move_max_position();              // 최대 설정 위치로 이동
  void move_min_position();              // 최소 설정 위치로 이동
  void move_random_position();           // 무작위 위치로 이동

  void set_profile_acc(uint32_t acceleration);  // Position Contorl 가속도 설정
  void set_profile_vel(uint32_t velocity);      // Position Control 속도 설정
  void set_goal_position(int32_t position);     // Position Control 목표 위치 설정

  void check_profile_acc();     // Position Control 가속도 확인
  void check_profile_vel();     // Position Control 속도 확인
  void check_goal_position();   // Position Control 목표 위치 확인
  void check_profile_status();  // Profile Mode 상태 확인
  bool check_moving_status();   // In Position 비트 확인
};