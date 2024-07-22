#include "dxl_control.h"

DxlControl::DxlControl(std::string file_name)
{
  load_option(file_name);

  _port_handler   = dynamixel::PortHandler::getPortHandler(_device_name.c_str());
  _packet_handler = dynamixel::PacketHandler::getPacketHandler(_protocol_ver);
  _tx_mtx         = std::make_shared<std::mutex>();

  /**
   * 객체 소유권 확보를 위해 unique_ptr 사용
   * 객체 소멸 시 메모리 자동 해제
   * get() 메서드를 사용해 raw ptr 전달
   * _packet_handler의 소유권은 Dxl485에 없고 참조만 함
   */
  _dxl_485 = make_unique<Dxl485>(_port_handler, _packet_handler, _tx_mtx,
                                 "config/handler_option.yaml");

  _thread_info = new ThreadActionInfo(file_name);  // thread info 설정

  // thread 정보 설정
  _thread_info->_active = true;
  _thread_info->_thread = std::thread(std::bind(&DxlControl::update, this));
}

DxlControl::~DxlControl()
{
  stop();

  _thread_info->_active = false;
  safe_delete(_thread_info);

  // safe_delete(_dxl_485);
}

void DxlControl::initialize()
{
  std::unique_lock<std::mutex> lock(*_tx_mtx);
  _comm_result      = 0;
  _error            = 0;
  _present_position = 0;
  _in_position      = 0;
  _torque_flag      = false;

  torque_control(TORQUE_CONTROL::TORQUE_DISABLE);
  set_operating_mode(OPERATION_MODE::EXTENDED_POSITION_CONTROL);
  set_profile_vel(_profile_vel);
}

void DxlControl::control(std::string                                    cmd,
                         const std::map<std::__cxx11::string, int32_t>& command_map)
{
  if(cmd == "torque_on") torque_control(TORQUE_CONTROL::TORQUE_ENABLE);
  else if(cmd == "torque_off") torque_control(TORQUE_CONTROL::TORQUE_DISABLE);
  else if(cmd == "stop") stop();
  else if(cmd == "move") move_position(command_map.find("pos")->second);
  else if(cmd == "move") move_velocity(command_map.find("vel")->second);
  else if(cmd == "home") move_home_position();
  else if(cmd == "random") move_random_position();
  else if(cmd == "drive_mode") check_drive_mode();
  else if(cmd == "moving_status") check_moving_status();
  else if(cmd == "cur_pos") get_current_pos();
  else if(cmd == "set_home") set_home_position();
  else if(cmd == "set")
  {
    if(command_map.find("op") != command_map.end())
      set_operating_mode(static_cast<OPERATION_MODE>(command_map.find("op")->second));
    else if(command_map.find("rpm") != command_map.end())
      set_velocity_mode(command_map.find("rpm")->second);
    else if(command_map.find("pos") != command_map.end())
      set_goal_position(command_map.find("pos")->second);
  }
}

void DxlControl::update()
{
  while(_thread_info->_active)
  {
    if(!_dxl_485->is_connected()) continue;

    std::call_once(_init_flag, std::bind(&DxlControl::initialize, this));

    if(_torque_flag)
      if(check_moving_status()) stop();
    // thread 무한 독점을 방지하기 위한 sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(_thread_info->_sleep));
  }
}

void DxlControl::load_option(std::string file_name)
{
  try
  {
    // file open
    std::ifstream yaml_file(file_name);
    YAML::Node    yaml = YAML::Load(yaml_file);
    yaml_file.close();

    // data read
    std::string config_name = yaml["config_name"].as<std::string>();
    config_name += std::string(": DxlControl");
    std::cout << config_name << std::endl;

    // DxlControl 설정값
    _device_name  = yaml["dxl"]["device_name"].as<std::string>();
    _protocol_ver = yaml["dxl"]["protocol_ver"].as<float>();
    _id           = yaml["dxl"]["id"].as<int>();
    _op_mode      = yaml["dxl_op_mode"]["mode"].as<int>();
    _drive_mode   = yaml["dxl_drive_mode"]["mode"].as<int>();
    // 1 unit == 0.229 rpm
    _goal_rpm    = (yaml["dxl_comm"]["rpm"].as<int>()) / 0.229;
    _profile_acc = yaml["dxl_comm"]["acc"].as<int>();
    // 1 unit == 0.229 rpm
    _profile_vel = (yaml["dxl_comm"]["rpm"].as<int>()) / 0.229;
    // 1 unit == 0.088 degree
    _goal_position_max = (yaml["dxl_comm"]["max_position"].as<int>()) / 0.088;
    _goal_position_min = (yaml["dxl_comm"]["min_position"].as<int>()) / 0.088;
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

bool DxlControl::is_fail(std::string target)
{
  if(_comm_result != COMM_SUCCESS)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Failed to" + target, "");
    LOGGER->push_log_format("ERROR", "PROC", "Result",
                            _packet_handler->getTxRxResult(_comm_result));
    return false;
  }
  else if(_error != 0)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Error to" + target, "");
    LOGGER->push_log_format("ERROR", "PROC", "Error",
                            _packet_handler->getRxPacketError(_error));
    return false;
  }
  return true;
}