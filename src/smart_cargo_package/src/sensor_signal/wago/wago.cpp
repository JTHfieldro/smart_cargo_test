#include "wago.h"

Wago::Wago()
{
  _door_status    = SMART_CARGO_ACTION::ACTION_NONE;
  _is_ready       = WAGO_UNPREPARED;
  _reconnect_flag = false;

  int argc = 0;
  ros::init(argc, nullptr, "sensor_signal");  // sensor_signal node명 초기화

  _node_handle   = new ros::NodeHandle;  // Node Handler 생성
  _topic_manager = make_unique<RosTopicManager>(_node_handle);
  _param_manager = make_unique<RosParamManager>();
  init_node();

  set_io_map();  // IO map 설정

  _thread_info = make_unique<ThreadActionInfo>("config/sensor_signal.yaml");
  _thread_node = make_unique<ThreadActionInfo>("config/sensor_signal.yaml");
  _modbus      = make_unique<ModbusWrapper>(ModbusType::TCP,
                                            "config/sensor_signal.yaml");  // modbus 객체 생성
  // _modbus      = new ModbusWrapper(ModbusType::TCP,
  //                                  "config/sensor_signal.yaml");  // modbus 객체 생성

  // thread 정보 설정
  _thread_info->_active = true;
  _thread_info->_thread = std::thread(std::bind(&Wago::update, this));
  _thread_node->_active = true;
  _thread_node->_thread = std::thread(std::bind(&Wago::node_update, this));

  // ROS Spin
  _spinner = new ros::AsyncSpinner(5);
  _spinner->start();

  LOGGER->push_log_format("INFO", "PROC", "Node Start", "");
}

/**
 * @brief  		  Wago Class Destructor
 * @attention   해제 순서에 주의 !!!
 *              1. thread 정지
 *              2. modbus 연결 해제
 *              3. wago 연결 정보 해제
 *              4. ROS 관련 객체 해제
 */
Wago::~Wago()
{
  _thread_info->_active = false;
  _thread_node->_active = false;

  // safe_delete(_modbus);

  // IO Signal Info 해제
  delete_io_map();

  // ROS 관련 객체 해제
  delete_sub_param();
  ros::shutdown();
  ros::waitForShutdown();
  safe_delete(_node_handle);

  LOGGER->push_log_format("INFO", "PROC", "Node Stop", "");
}

void Wago::control(std::string str)
{
  std::string cmd = parsing_command_map(str, _command_map);

  if(cmd == "stop") _thread_info->_active = false;
  else if(cmd == "run") _thread_info->_active = true;
  else if(cmd == "control_output") write_signal(_command_map);

  _command_map.clear();
}

/**
/* @brief   modbus 연결 및 watching thread function
/* @param   void
/* @return  void
/* @note    wago read를 위해 thread로 동작되고 읽어 들인 Data가 있을 경우 callback을
통하여 전달
*/
void Wago::update()
{
  while(_thread_info->_active)
  {
    if(!_modbus->is_connect())  // 미연결 시 io 객체 초기화, 재연결 후 pub위함
    {
      _reconnect_flag = false;
      set_io_map();
    }

    is_ready();
    // Modbus 연결 상태 확인
    if(!_modbus->connect_check()) continue;
    // ROS 연결 상태 확인
    if(!ros::ok()) continue;
    if(!_topic_manager->check_subscriber()) continue;

    if(!_reconnect_flag)
    {
      check_init_signal();
      _reconnect_flag = true;
    }
    std::call_once(_signal_init_flag, std::bind(&Wago::check_init_signal, this));

    // DI Signal Read
    read_signal();

    // thread 무한 독점을 방지하기 위한 sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(_thread_info->_sleep));
  }
}

void Wago::is_ready()
{
  if((!_modbus->is_connect()) && (_is_ready == WAGO_PREPARED))
  {
    _is_ready = WAGO_UNPREPARED;
    publish_action_complete(SMART_CARGO_ACTION::UNPREPARED);
  }
  else if((_modbus->is_connect()) && (_is_ready == WAGO_UNPREPARED))
  {
    _is_ready = WAGO_PREPARED;
    publish_action_complete(SMART_CARGO_ACTION::PREPARED);
  }
}