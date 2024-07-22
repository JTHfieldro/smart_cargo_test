#pragma once

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

#include "dxl_control.h"
#include "dynamixel_define.h"
#include "global_define.h"
#include "global_helper.h"
#include "logger.h"
#include "safe_queue.h"
#include "thread_action_info.h"
#include "yaml-cpp/yaml.h"
// ROS
#include "ros/ros.h"
#include "ros_param_manger.h"
#include "ros_topic_manager.h"
// Topic Message Type
#include "smart_cargo_package/action_complete_msgs.h"
#include "smart_cargo_package/middle_control_msgs.h"
#include "smart_cargo_package/sensor_signal_msgs.h"

#ifndef LOGGER
#define LOGGER Logger::get("handler_control")
#endif

class Dynamixel
{
public:
  Dynamixel();
  virtual ~Dynamixel();

public:
  void control(std::string command);

protected:
  ros::NodeHandle*   _node_handle;  // ROS System과 통신을 위한 Node Handler
  ros::AsyncSpinner* _spinner;      // ROS System과 통신을 위한 Spinner
  std::string        _node_name;

  /// @brief ROS Topic, Parameter Server 관리 객체
  std::unique_ptr<RosTopicManager> _topic_manager;
  std::unique_ptr<RosParamManager> _param_manager;

  std::map<std::string, std::vector<std::string>> _subscriber_list;  // 구독자 맵

  // action_complete msg queue
  std::unique_ptr<SafeQueue<smart_cargo_package::action_complete_msgs>>
      _queue_action_complete;

  std::shared_ptr<dynamixel::PortHandler> _port_handler;  // Dynamixel Port Handler 객체
  std::shared_ptr<dynamixel::PacketHandler>
                              _packet_handler;  // Dynamixel Packet Handler 객체
  std::unique_ptr<DxlControl> _dxl_control;     // Dynamixel Control 객체

  std::unique_ptr<ThreadActionInfo> _thread_info;  // thread 동작 정보 객체
  std::unique_ptr<ThreadActionInfo> _thread_node;  // thread 동작 정보 객체
  std::map<std::string, int32_t>    _command_map;  // 명령어 맵

protected:
  void update();  // 실제 thread 동작 함수

  void load_option(std::string file_name);

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
  /// @brief Sensor Signal을 확인하기 위한 Subscriber 함수
  void subscribe_sensor_signal(
      const smart_cargo_package::sensor_signal_msgs::ConstPtr& msg);
  /// @brief RMD Status를 보내기 위한 Publisher 함수
  void publish_action_complete(SMART_CARGO_ACTION action);

  void is_ready();
};