#pragma once

#include <dynamixel_sdk/dynamixel_sdk.h>

#include <ctime>
#include <mutex>
#include <string>

#include "dynamixel_define.h"
#include "global_helper.h"
#include "logger.h"
#include "thread_action_info.h"
#include "yaml-cpp/yaml.h"

#ifndef LOGGER
#define LOGGER Logger::get("handler_control")
#endif

class Dxl485
{
private:
  Dxl485(){};

public:
  Dxl485(dynamixel::PortHandler* port_handler, dynamixel::PacketHandler* packet_handler,
         std::shared_ptr<std::mutex> tx_mtx, std::string file_name);
  ~Dxl485();

public:
  bool is_connected();
  bool connect_check();

protected:
  dynamixel::PortHandler*     _port_handler;    // Dynamixel Port Handler 객체
  dynamixel::PacketHandler*   _packet_handler;  // Dynamixel Packet Handler 객체
  std::shared_ptr<std::mutex> _tx_mtx;          // tx mutex 객체
  ThreadActionInfo*           _thread_info;     // thread 동작 정보 객체

  std::string _file_name;              // config file path 저장 변수
  int32_t     _comm_result;            // read/write 결과 저장 변수
  uint8_t     _error;                  // read/write error 저장 변수
  int32_t     _last_try_connect_time;  // 최근 재연결 시간

  bool _is_connected;  // dxl 연결 여부

  // config file에서 가져오는 변수
  uint8_t _id;           // Dynamixel Motor ID
  int32_t _baudrate;     // Dynamixel Baudrate
  int32_t _retry_turm;   // 재연결 시도 간격
  int32_t _retry_count;  // 재연결 시도 횟수
  int32_t _ping_count;   // Ping 시도 횟수

protected:
  void update();

  void initialize();
  void load_option(std::string file_name);
  bool is_fail(std::string target);  // Fail, Error Log Format

  bool connect_485();
  bool try_connect_485();

  void disconnect_485();

  void reboot();
};