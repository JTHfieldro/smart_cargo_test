#pragma once

#include <string>
#include <vector>

#include "global_helper.h"
#include "logger.h"
#include "safe_queue.h"
#include "thread_action_info.h"
#include "topic_define.h"
// ROS
#include "ros/ros.h"
#include "ros_param_manger.h"
#include "ros_topic_manager.h"
// Topic Messgae Type
#include "smart_cargo_package/sensor_signal_msgs.h"
#include "smart_cargo_package/state_monitor.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/String.h"

#ifndef LOGGER
#define LOGGER Logger::get("topic_test")
#endif

class TopicTest
{
public:
  TopicTest();
  ~TopicTest();

public:
  void control(std::string str);

protected:
  ros::NodeHandle*   _node_handle;  // ROS System과 통신을 위한 Node Handler
  ros::AsyncSpinner* _spinner;      // ROS System과 통신을 위한 Spinner
  std::string        _node_name;

  /// @brief ROS Topic, Parameter Server 관리 객체
  std::unique_ptr<RosTopicManager> _topic_manager;
  std::unique_ptr<RosParamManager> _param_manager;

  std::unique_ptr<ThreadActionInfo> _thread_info;  // thread 동작 정보 객체
  std::unique_ptr<ThreadActionInfo> _thread_node;  // thread 동작 정보 객체

  std::map<std::string, int32_t>                  _command_map;      // 명령어 맵
  std::map<std::string, std::vector<std::string>> _subscriber_list;  // 구독자 맵

  std::unique_ptr<SafeQueue<std_msgs::Int32>>
      _queue_control_door;  // control_door msg queue
  std::unique_ptr<SafeQueue<std_msgs::Int32MultiArray>>
      _queue_control_handler;  // control_handler msg queue
  std::unique_ptr<SafeQueue<std_msgs::Int32>> _queue_if_docking;  // if_docking msg queue
  std::unique_ptr<SafeQueue<std_msgs::Int32>> _queue_if_locker;   // if_locker msg queue

  smart_cargo_package::state_monitor _state_monitor_msg;  // state_monitor msg

  bool _msg_pub_flag;

protected:
  void update();
  void init_node();

  void set_subscriber();  // Set Subscriber Object
  void set_publisher();   // Set Publisher Object

  void set_sub_param();
  void delete_sub_param();

  void node_update();        // Subscriber 구독 상태 확인
  void check_publish_msg();  // 초기화 후 msg발행 확인 용
  void pop_msg();            // Queue에 저장된 msg pop하여 publish

  void init_state_monitor_msg();

  /// @brief smart_cargo/IF_WCS Subscriber Func.
  void subscribe_if_wcs(const std_msgs::Int32::ConstPtr& msg);
  /// @brief smart_cargo/state_monitor Subscriber Func.
  void subscribe_state_monitor(const smart_cargo_package::state_monitor::ConstPtr& msg);
  /// @brief smart_cargo/control_door Publisher Func.
  void publish_control_door(CONTROL_DOOR msg);
  void publish_control_handler();  // smart_cargo/control_handler Publisher Func.
  void publish_if_docking();       // smart_cargo/IF_docking Publisher Func.
  void publish_if_locker();        // smart_cargo/IF_locker Publisher Func.
};