#pragma once

#include <string>
#include <vector>

#include "global_define.h"
#include "global_helper.h"
#include "logger.h"
#include "safe_queue.h"
#include "secnario_manager.h"
#include "thread_action_info.h"
#include "topic_define.h"
#include "yaml-cpp/yaml.h"
// ROS
#include "ros/ros.h"
#include "ros_param_manger.h"
#include "ros_topic_manager.h"
// Topic Message Type
#include "smart_cargo_package/action_complete_msgs.h"
#include "smart_cargo_package/middle_control_msgs.h"
#include "smart_cargo_package/state_monitor.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Int32MultiArray.h"

#ifndef LOGGER
#define LOGGER Logger::get("smart_cargo")
#endif

class SmartCargo
{
public:
  SmartCargo();
  ~SmartCargo();

public:
  void control(std::string str);

protected:
  ros::NodeHandle*   _node_handle;  // ROS System과 통신을 위한 Node Handler
  ros::AsyncSpinner* _spinner;      // ROS System과 통신을 위한 Spinner
  std::string        _node_name;    // 현재 node 이름 저장 변수
  std::unique_ptr<SecnarioManager> _secnario;  // Scenario 객체

  /// @brief ROS Topic, Parameter Server 관리 객체
  std::unique_ptr<RosTopicManager> _topic_manager;
  std::unique_ptr<RosParamManager> _param_manager;

  std::map<std::string, std::vector<std::string>> _subscriber_list;  // 구독자 맵

  std::unique_ptr<SafeQueue<std_msgs::Int32>> _queue_if_wcs;  // if_wcs msg queue
  std::unique_ptr<SafeQueue<smart_cargo_package::state_monitor>>
      _queue_state_monitor;  // state_monitoe msg queue
  std::unique_ptr<SafeQueue<smart_cargo_package::middle_control_msgs>>
      _queue_middle_control;  // middle_control msg queue

  std::unique_ptr<ThreadActionInfo>  _thread_info;        // thread 동작 정보 객체
  std::unique_ptr<ThreadActionInfo>  _thread_node;        // thread 동작 정보 객체
  std::map<std::string, int32_t>     _command_map;        // 명령어 맵
  smart_cargo_package::state_monitor _state_monitor_msg;  // state_monitor msg

  std::once_flag _cargo_init_flag;  // smart_cargo 초기화 once flag

protected:
  void update();  // 실제 thread
  void initialize();
  void init_node();

  void set_subscriber();
  void set_publisher();

  void set_sub_param();
  void delete_sub_param();

  void init_state_monitor_msg();  // state_monitor topic msg 초기화

  void node_update();  // 전체 Topic에 대한 Subscriber 구독 상태 확인
  void pop_msg();      // Queue에 저장된 msg pop하여 publish

  /// @brief Door Control Message Subscriber Func.
  void subscribe_control_door(const std_msgs::Int32::ConstPtr& msg);
  /// @brief Handler Control Message Subscriber Func.
  void subscribe_control_handler(const std_msgs::Int32MultiArray::ConstPtr& msg);
  /// @brief IF_docking Message Subscriber Func.
  void subscribe_if_docking(const std_msgs::Int32::ConstPtr& msg);
  /// @brief IF_locker Message Subscriber Func.
  void subscribe_if_locker(const std_msgs::Int32::ConstPtr& msg);
  /// @brief Action Complete Message Subscriber Func.
  void subscribe_action_complete(
      const smart_cargo_package::action_complete_msgs::ConstPtr& msg);

  /// @brief IF_WCS Message Publisher
  void publish_if_wcs(std_msgs::Int32 msg);
  /// @brief State Monitor Message Publisher
  void publish_state_monitor(std::string target, std::string data);
  /// @brief Middle Contorl을 보내기 위한 Publisher 함수
  void publish_middle_control(int32_t target, int32_t action);

  void initialize_cargo();
  void drop_package();
};
