#include "smart_cargo.h"

SmartCargo::SmartCargo()
{
  initialize();

  int argc = 0;
  ros::init(argc, nullptr, "smart_cargo");  // smart_cargo node명 초기화

  _node_handle   = new ros::NodeHandle;  // Node Handler 생성
  _topic_manager = make_unique<RosTopicManager>(_node_handle);
  _param_manager = make_unique<RosParamManager>();
  init_node();

  _secnario = make_unique<SecnarioManager>();

  // thread info 설정
  _thread_info = make_unique<ThreadActionInfo>("config/cargo_option.yaml");
  _thread_node = make_unique<ThreadActionInfo>("config/cargo_option.yaml");

  // thread 정보 설정
  _thread_info->_active = true;
  _thread_info->_thread = std::thread(std::bind(&SmartCargo::update, this));
  _thread_node->_active = true;
  _thread_node->_thread = std::thread(std::bind(&SmartCargo::node_update, this));

  // ROS Spin
  _spinner = new ros::AsyncSpinner(5);
  _spinner->start();

  LOGGER->push_log_format("INFO", "PROC", "Node Start!!", "");
}

/**
 * @brief  		  SmartCargo Class Destructor
 * @attention   해제 순서에 주의 !!!
 *              1. thread 정지
 *              2. ROS 관련 객체 해제
 */
SmartCargo::~SmartCargo()
{
  _thread_info->_active = false;
  _thread_node->_active = false;

  // ROS 관련 객체 해제
  delete_sub_param();
  ros::shutdown();
  ros::waitForShutdown();
  safe_delete(_node_handle);

  LOGGER->push_log_format("INFO", "PROC", "Node Stop", "");
}

void SmartCargo::initialize()
{
}

void SmartCargo::control(std::string str)
{
  std::string cmd = parsing_command_map(str, _command_map);

  if(cmd == "door_open")
    publish_middle_control(static_cast<int32_t>(HARDWARE_INDEX::CARGO_DOOR),
                           static_cast<int32_t>(SMART_CARGO_ACTION::OPENING));
  else if(cmd == "door_close")
    publish_middle_control(static_cast<int32_t>(HARDWARE_INDEX::CARGO_DOOR),
                           static_cast<int32_t>(SMART_CARGO_ACTION::CLOSING));

  _command_map.clear();
}

/**
/* @brief   modbus 연결 및 watching thread function
/* @param   void
/* @return  void
/* @note    wago read를 위해 thread로 동작되고 읽어 들인 Data가 있을 경우 callback을
통하여 전달
*/
void SmartCargo::update()
{
  while(_thread_info->_active)
  {
    if(_secnario->get_init_action() != CARGO_INIT::CARGO_INIT_END)
    {
      initialize_cargo();
    }
    // thread 무한 독점을 방지하기 위한 sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(_thread_info->_sleep));
  }
}