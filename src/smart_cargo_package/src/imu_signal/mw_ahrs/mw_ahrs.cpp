#include "mw_ahrs.h"

Ahrs::Ahrs()
{
  _type          = DT_NONE;

  int argc = 0;
  ros::init(argc, nullptr, "imu_signal");

  _node_handle   = new ros::NodeHandle;  // Node Handler 생성
  _topic_manager = make_unique<RosTopicManager>(_node_handle);
  _param_manager = make_unique<RosParamManager>();
  init_node();

  _cancomm     = make_unique<CanComm>("config/imu_signal.yaml");
  // thread info 설정
  _thread_info = make_unique<ThreadActionInfo>("config/imu_signal.yaml");
  _thread_node = make_unique<ThreadActionInfo>("config/imu_signal.yaml");
  // thread 정보 설정
  _thread_info->_active = true;
  _thread_info->_thread = std::thread(std::bind(&Ahrs::update, this));
  _thread_node->_active = true;
  _thread_node->_thread = std::thread(std::bind(&Ahrs::node_update, this));
  // ROS Spin
  _spinner = new ros::AsyncSpinner(5);
  _spinner->start();

  LOGGER->push_log_format("INFO", "PROC", "Node Start", "");
}

/**
 * @brief  		  Ahrs Class Destructor
 * @attention   해제 순서에 주의 !!!
 *              1. thread 정지
 *              2. can 연결 해제
 *              3. ROS 관련 객체 해제
 */
Ahrs::~Ahrs()
{
  _thread_info->_active = false;
  _thread_node->_active = false;
  safe_delete(_cancomm);

  // ROS 관련 객체 해제
  delete_sub_param();
  ros::shutdown();
  ros::waitForShutdown();
  safe_delete(_node_handle);

  LOGGER->push_log_format("INFO", "PROC", "Node STOP", "");
}

void Ahrs::control(std::string str)
{
    std::string cmd = parsing_command_map(str, _command_map);

    if(cmd=="stop") _type = DT_NONE;
    else if(cmd=="accel") _type = DT_ACC;
    else if(cmd=="gyro") _type = DT_GYRO;
    else if(cmd=="angle") _type = DT_ANGLE;
    else if(cmd=="mag") _type = DT_MAGNETIC;

    _command_map.clear();
}

void Ahrs::update()
{
  while(_thread_info->_active)
  {
    if(!_cancomm->_is_connected)
    {
      std::cout << "try connecting..." << std::endl;
      _cancomm->initialize();
    }

    for(int i = DT_ACC; i <= DT_MAGNETIC; i++)
    {
      input_data();
    }

    if(_cancomm->_is_connected)
    {
      show_data(_type);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(_thread_info->_sleep));
  }
}