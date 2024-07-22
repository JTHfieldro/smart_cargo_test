#include "dxl_485.h"

Dxl485::Dxl485(dynamixel::PortHandler*     port_handler,
               dynamixel::PacketHandler*   packet_handler,
               std::shared_ptr<std::mutex> tx_mtx, std::string file_name)
{
  _port_handler   = port_handler;
  _packet_handler = packet_handler;
  _tx_mtx         = tx_mtx;

  _file_name = file_name;
  load_option(_file_name);

  _thread_info = new ThreadActionInfo(file_name);  // thread info 설정

  // thread 정보 설정
  _thread_info->_active = true;
  _thread_info->_thread = std::thread(std::bind(&Dxl485::update, this));
  initialize();
}

Dxl485::~Dxl485()
{
  disconnect_485();
}

void Dxl485::initialize()
{
  _comm_result           = 0;
  _error                 = 0;
  _last_try_connect_time = 0;
  _is_connected          = false;

  LOGGER->push_log_format("INFO", "PROC", "Node START!", "");
}

void Dxl485::update()
{
  while(_thread_info->_active)
  {
    if(connect_check()) continue;

    // thread 무한 독점을 방지하기 위한 sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

void Dxl485::load_option(std::string file_name)
{
  try
  {
    // file open
    std::ifstream yaml_file(_file_name);
    YAML::Node    yaml = YAML::Load(yaml_file);
    yaml_file.close();

    // data read
    std::string config_name = yaml["config_name"].as<std::string>();
    std::cout << config_name << std::endl;

    // Dynamixel 설정값
    _id          = yaml["dxl"]["id"].as<int>();
    _baudrate    = yaml["dxl"]["baudrate"].as<int>();
    _retry_turm  = yaml["dxl"]["retry_turm"].as<int>();
    _retry_count = yaml["dxl"]["retry_count"].as<int>();
    _ping_count  = yaml["dxl"]["ping_count"].as<int>();
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

bool Dxl485::is_connected()
{
  return _is_connected;
}

bool Dxl485::is_fail(std::string target)
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