#include "dynamixel.h"

Dynamixel::Dynamixel()
{
  int argc = 0;
  ros::init(argc, nullptr, "door_control");  // rmd_control node명 초기화

  _node_handle   = new ros::NodeHandle;  // Node Handler 생성
  _topic_manager = make_unique<RosTopicManager>(_node_handle);
  _param_manager = make_unique<RosParamManager>();
  init_node();

  /**
   *  객체 소유권 확보를 위해 unique_ptr 사용
   * 객체 소멸 시 메모리 자동 해제
   */
  _dxl_control = make_unique<DxlControl>("config/handler_option.yaml");
  _thread_info = make_unique<ThreadActionInfo>("config/handler_option.yaml");
  _thread_node = make_unique<ThreadActionInfo>("config/handler_option.yaml");

  // thread 정보 설정
  _thread_info->_active = true;
  _thread_info->_thread = std::thread(std::bind(&Dynamixel::update, this));
  _thread_node->_active = true;
  _thread_node->_thread = std::thread(std::bind(&Dynamixel::node_update, this));

  // ROS Spin
  _spinner = new ros::AsyncSpinner(5);
  _spinner->start();
}

/**
 * @brief  		  SmartCargo Class Destructor
 * @attention   해제 순서에 주의 !!!
 *              1. thread 정지
 *              2. ROS 관련 객체 해제
 */
Dynamixel::~Dynamixel()
{
  _thread_info->_active = false;
  _thread_node->_active = false;

  // ROS 관련 객체 해제
  delete_sub_param();
  ros::shutdown();
  ros::waitForShutdown();
  safe_delete(_node_handle);

  LOGGER->push_log_format("INFO", "PROC", "Node STOP!", "");
}

void Dynamixel::control(std::string command)
{
  /// [dxl] [cmd] [key]=[vlaue]
  std::string cmd = parsing_command_map(command, _command_map);

  if(cmd == "") return;

  _dxl_control->control(cmd, _command_map);

  _command_map.clear();
}

void Dynamixel::update()
{
  while(_thread_info->_active)
  {
    // thread 무한 독점을 방지하기 위한 sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(_thread_info->_sleep));
  }
}

void Dynamixel::load_option(std::string file_name)
{
  try
  {
    // file open
    std::ifstream yaml_file(file_name);
    YAML::Node    yaml = YAML::Load(yaml_file);
    yaml_file.close();

    // data read
    std::string config_name = yaml["config_name"].as<std::string>();
    config_name += std::string(": Dynamixel");
    std::cout << config_name << std::endl;

    // Dynamixel 설정값
  }
  catch(YAML::Exception& e)
  {
    std::cout << "YAML Exception : " << e.what() << std::endl;
  }
  catch(std::exception& e)
  {
    std::cout << "Exception : " << e.what() << std::endl;
  }
  catch(...)
  {
    std::cout << "Unknown Exception" << std::endl;
  }
}