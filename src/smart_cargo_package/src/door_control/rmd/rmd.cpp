#include "rmd.h"

Rmd::Rmd()
{
  initialize();

  int argc = 0;
  ros::init(argc, nullptr, "door_control");  // rmd_control node명 초기화

  _node_handle   = new ros::NodeHandle;  // Node Handler 생성
  _topic_manager = make_unique<RosTopicManager>(_node_handle);
  _param_manager = make_unique<RosParamManager>();

  init_node();

  // thread info 설정
  _thread_info = make_unique<ThreadActionInfo>("config/door_control.yaml");
  _thread_node = make_unique<ThreadActionInfo>("config/door_control.yaml");
  _can         = new Can("config/door_control.yaml");  // can lib 객체
  _control =
      new RmdControl(_can, "config/door_control.yaml",
                     std::bind(&Rmd::update_rmd_status, this, std::placeholders::_1,
                               std::placeholders::_2));  // Rmd Control 객체

  // thread 정보 설정
  _thread_info->_active = true;
  _thread_info->_thread = std::thread(std::bind(&Rmd::update, this));
  _thread_node->_active = true;
  _thread_node->_thread = std::thread(std::bind(&Rmd::node_update, this));

  // ROS Spin
  _spinner = new ros::AsyncSpinner(5);
  _spinner->start();

  LOGGER->push_log_format("INFO", "PROC", "Node Start", "");
}

/**
 * @brief  		  Rmd Class Destructor
 * @attention   해제 순서에 주의 !!!
 *              1. thread 정지
 *              2. Can 연결 해제
 *              4. ROS 관련 객체 해제
 */
Rmd::~Rmd()
{
  _thread_info->_active = false;
  _thread_node->_active = false;

  safe_delete(_control);
  safe_delete(_can);

  // ROS 관련 객체 해제
  delete_sub_param();
  ros::shutdown();
  ros::waitForShutdown();
  safe_delete(_node_handle);

  LOGGER->push_log_format("INFO", "PROC", "Node STOP", "");
}

void Rmd::initialize()
{
  _action       = RMD_ACTION::RMD_STOP;             // Motor 동작 상태
  _mode         = RMD_DEFINE::NEXT_PACKET_NONE;     // RMD Protocol 상태
  _close_flag   = RMD_CLOSE_FLAG::RMD_CLOSE_NONE;   // door_close flag
  _cargo_action = SMART_CARGO_ACTION::ACTION_NONE;  // smart_cargo action flag
  _is_ready     = RMD_READY::RMD_UNPREPARED;        // door_control ready flag
}

void Rmd::control(std::string str)
{
  std::string cmd = parsing_command_map(str, _command_map);

  if(cmd == "") return;

  if((cmd == "front") || (cmd == "rear")) _control->control_speed(cmd, _command_map);
  else if(cmd == "position") _control->control_position(_command_map);
  else if(cmd == "stop") _control->control_stop();
  else if(cmd == "canid") _control->check_canid();
  else if(cmd == "accelread") _control->check_accel();
  else if(cmd == "accelset") _control->set_accel(_command_map);
  else if(cmd == "topic_action") publish_action_complete(SMART_CARGO_ACTION::PREPARED);
  else if(cmd == "set_filter") _can->set_filter();

  _command_map.clear();
}

void Rmd::update()
{
  while(_thread_info->_active)
  {
    if(!_can->connect_check()) continue;
    if(!ros::ok()) continue;
    if(!_topic_manager->check_subscriber()) continue;

    is_ready();
    check_door_close();

    // thread Hz 싱크 및 독점 방지를 위한 sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(_thread_info->_sleep));
  }
}

void Rmd::update_rmd_status(RMD_ACTION action, RMD_DEFINE mode)
{
  _action = action;
  _mode   = mode;
}

void Rmd::is_ready()
{
  if((!_can->is_connected()) && (_is_ready == RMD_READY::RMD_PREPARED))
  {
    _is_ready = RMD_READY::RMD_UNPREPARED;
    publish_action_complete(SMART_CARGO_ACTION::UNPREPARED);
  }
  else if((_can->is_connected()) && (_is_ready == RMD_READY::RMD_UNPREPARED))
  {
    _is_ready = RMD_READY::RMD_PREPARED;
    publish_action_complete(SMART_CARGO_ACTION::PREPARED);
  }
}