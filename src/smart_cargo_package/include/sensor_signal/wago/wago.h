#pragma once

#include <modbus/modbus.h>
#include <string.h>

#include <fstream>
#include <future>
#include <iostream>
#include <map>
#include <thread>
#include <vector>

#include "global_define.h"
#include "global_helper.h"
#include "safe_queue.h"
#include "signal_info.h"
#include "thread_action_info.h"
#include "wago_define.h"
// Lib
#include "modbus_wrapper.h"
#include "yaml-cpp/yaml.h"
// ROS
#include "ros/ros.h"
#include "ros_param_manger.h"
#include "ros_topic_manager.h"
// Topic Message Type
#include "smart_cargo_package/action_complete_msgs.h"
#include "smart_cargo_package/middle_control_msgs.h"
#include "smart_cargo_package/sensor_signal_msgs.h"
#include "std_msgs/Int32.h"
#include "std_msgs/String.h"

#ifndef LOGGER
#define LOGGER Logger::get("sensor_signal")
#endif

class Wago
{
public:
  Wago();
  ~Wago();

public:
  void control(std::string str);  // cmd를 이용한 제어

protected:
  ros::NodeHandle*   _node_handle;  // ROS System과 통신을 위한 Node Handler
  ros::AsyncSpinner* _spinner;      // ROS System과 통신을 위한 Spinner
  std::string        _node_name;

  /// @brief ROS Topic, Parameter Server 관리 객체
  std::unique_ptr<RosTopicManager> _topic_manager;
  std::unique_ptr<RosParamManager> _param_manager;

  std::map<std::string, std::vector<std::string>> _subscriber_list;  // 구독자 맵

  std::unique_ptr<SafeQueue<SignalInfo>> _queue_signal_info;  // signal_info msg queue
  std::unique_ptr<SafeQueue<smart_cargo_package::sensor_signal_msgs>>
      _queue_sensor_signal;  // sensor_signal msg queue
  std::unique_ptr<SafeQueue<smart_cargo_package::action_complete_msgs>>
      _queue_action_complete;  // action_complete msg queue

  std::unique_ptr<ThreadActionInfo> _thread_info;  // thread 동작 정보 객체
  std::unique_ptr<ThreadActionInfo> _thread_node;  // thread 동작 정보 객체
  std::unique_ptr<ModbusWrapper>    _modbus;       // modbus 객체
  // ModbusWrapper*                    _modbus;       // modbus 객체
  SignalInfo* _signal_info[(int32_t)DI_SIGNAL::DI_COUNT +
                           (int32_t)DO_SIGNAL::DO_COUNT];  // DI/DO Signal 정보

  std::map<std::string, int32_t> _command_map;  // 명령어 맵

  std::once_flag     _signal_init_flag;  // sensor signal 초기화 확인 flag
  bool               _reconnect_flag;    // 재연결 후 초기화용 flag
  SMART_CARGO_ACTION _door_status;

  WAGO_READY _is_ready;  // door_control ready count

protected:
  void update();  // 실제 thread
  void init_node();

  void set_subscriber();
  void set_publisher();

  void set_sub_param();
  void delete_sub_param();

  void node_update();  // Subscriber 구독 상태 확인
  void pop_msg();      // Queue에 저장된 msg pop하여 publish

  /// @brief Middle Contorl 명령을 받기 위한 Subscriber 함수
  void subscribe_middle_control(
      const smart_cargo_package::middle_control_msgs::ConstPtr& msg);
  /// @brief smart_cargo/action_complete subscriber 함수
  void subscribe_action_complete(
      const smart_cargo_package::action_complete_msgs::ConstPtr& msg);
  /// @brief Sensor Signal을 보내기 위한 Publisher 함수
  void publish_sensor_signal(const SignalInfo& signal_info);
  void publish_action_complete(SMART_CARGO_ACTION action);

  void check_init_signal();  // 동작 초기 sensor 값 확인
  void is_ready();
  void read_signal();                                                    // signal 읽기
  void read_do_signal();                                                 // signal 읽기
  void write_signal(const std::map<std::string, int32_t>& command_map);  // signal 쓰기
  SIGNAL_VALUE check_sepcific_do_signal(DO_SIGNAL index);  // 특정 DO signal value 확인

  void get_status();  //

  void set_io_map();     // IO Siganl Map 설정
  void delete_io_map();  // IO Signal Map 해제
};