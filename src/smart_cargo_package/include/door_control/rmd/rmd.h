#pragma once

#include <canlib.h>
#include <string.h>
#include <xmlrpcpp/XmlRpcValue.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <vector>

#include "can.h"
#include "global_define.h"
#include "global_helper.h"
#include "logger.h"
#include "rmd_control.h"
#include "rmd_define.h"
#include "rmd_enum.h"
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
#include "std_msgs/Int32.h"
#include "std_msgs/String.h"

#ifndef LOGGER
#define LOGGER Logger::get("door_control")
#endif

class RmdControl;

class Rmd
{
public:
  Rmd();
  virtual ~Rmd();

public:
  void       control(std::string str);  // target 할당 함수
  RMD_ACTION get_action();              // _action getter

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

  std::unique_ptr<ThreadActionInfo> _thread_info;  // thread 동작 정보 객체
  std::unique_ptr<ThreadActionInfo> _thread_node;  // thread 동작 정보 객체
  Can*                              _can;          // can 객체
  RmdControl*                       _control;      // rmd control 객체

  std::map<std::string, int32_t> _command_map;  // 명령어 맵

  RMD_DEFINE         _mode;          // motor can command
  RMD_ACTION         _action;        // motor action
  SMART_CARGO_ACTION _cargo_action;  // smart cargo action
  RMD_CLOSE_FLAG     _close_flag;    // door close flag

  RMD_READY _is_ready;  // door_control ready count

protected:
  void initialize();

  void update();  // 실제 thread 함수
  void init_node();

  void set_subscriber();
  void set_publisher();

  void set_sub_param();
  void delete_sub_param();

  void node_update();                // Subscriber 구독 상태 확인
  bool check_action_complete_sub();  // if_wcs Subscriber 구독 상태 확인
  void pop_msg();                    // Queue에 저장된 msg pop하여 publish

  /// @brief Middle Contorl 명령을 받기 위한 Subscriber 함수
  void subscribe_middle_control(
      const smart_cargo_package::middle_control_msgs::ConstPtr& msg);
  /// @brief Sensor Signal을 확인하기 위한 Subscriber 함수
  void subscribe_sensor_signal(
      const smart_cargo_package::sensor_signal_msgs::ConstPtr& msg);
  /// @brief RMD Status를 보내기 위한 Publisher 함수
  void publish_action_complete(SMART_CARGO_ACTION action);
  /// @brief rmd action, mode update callback 함수
  void update_rmd_status(RMD_ACTION action, RMD_DEFINE mode);

  void is_ratch_unlocked(const smart_cargo_package::sensor_signal_msgs::ConstPtr& msg);
  void is_open_detected(const smart_cargo_package::sensor_signal_msgs::ConstPtr& msg);
  void is_close_detected(const smart_cargo_package::sensor_signal_msgs::ConstPtr& msg);
  void check_init_signal(const smart_cargo_package::sensor_signal_msgs::ConstPtr& msg);
  void check_door_close();
  void is_ready();
};