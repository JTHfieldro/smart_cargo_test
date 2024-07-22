#pragma once

#include <iostream>
#include <thread>

#include "can_comm.h"
#include "mw_ahrs_define.h"
#include "global_helper.h"
#include "global_define.h"
#include "thread_action_info.h"
#include "safe_queue.h"
#include "logger.h"

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
#define LOGGER Logger::get("imu_signal")
#endif

class Ahrs
{
  public:
    Ahrs();
    virtual ~Ahrs();

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

    std::unique_ptr<SafeQueue<smart_cargo_package::sensor_signal_msgs>>
        _queue_sensor_signal;  // sensor_signal msg queue
    std::unique_ptr<SafeQueue<smart_cargo_package::action_complete_msgs>>
        _queue_action_complete;  // action_complete msg queue

    std::unique_ptr<ThreadActionInfo> _thread_info;  // thread 동작 정보 객체
    std::unique_ptr<ThreadActionInfo> _thread_node;  // thread 동작 정보 객체
    std::unique_ptr<CanComm> _cancomm;

    std::map<std::string, int32_t> _command_map;

  protected:
    void update();  // 실제 thread
    void init_node();

    void set_subscriber();
    void set_publisher();

    void set_sub_param();
    void delete_sub_param();

    void node_update();  // Subscriber 구독 상태 확인
    void pop_msg();      // Queue에 저장된 msg pop하여 publish

    void publish_imu_signal();

    /// @brief Middle Contorl 명령을 받기 위한 Subscriber 함수
    void subscribe_middle_control(
        const smart_cargo_package::middle_control_msgs::ConstPtr& msg);
    /// @brief smart_cargo/action_complete subscriber 함수
    void subscribe_action_complete(
        const smart_cargo_package::action_complete_msgs::ConstPtr& msg);
    void publish_action_complete(SMART_CARGO_ACTION action);

    float _accel_x;
    float _accel_y;
    float _accel_z;
    float _gyro_x;
    float _gyro_y;
    float _gyro_z;
    float _angle_yaw;
    float _angle_pitch;
    float _angle_roll;
    float _mag_x;
    float _mag_y;
    float _mag_z;

    int _type;

    uint8_t _accel_data[6];
    uint8_t _gyro_data[6];
    uint8_t _angle_data[6];
    uint8_t _mag_data[6];
    uint8_t _can_write_data[8];
    uint8_t _can_read_data[8];

    int16_t get_data(uint8_t low, uint8_t high);

    void input_data();
    void show_data(int _type);
};