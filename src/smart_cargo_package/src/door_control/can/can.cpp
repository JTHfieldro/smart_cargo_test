#include "can.h"

Can::Can(std::string option_file)
{
  // CANlib 초기화 및 현재 사용 가능한 모든 CAN Channel 열거
  // Lib에 대한 첫 호출은 canInitializeLibrary이어야 함
  // 한 번 호출로 충족하며 여러번 초기화 해도 아무런 효과 없음
  canInitializeLibrary();

  _is_connected          = false;  // CAN 연결 여부 초기화
  _last_try_connect_time = 0;      // 마지막 can 연결 시도 시간 초기화

  load_option(option_file);  // CAN Config 호출
}

Can::~Can()
{
  disconnect_can();
}

void Can::load_option(std::string option_file)
{
  try
  {
    // file open
    std::ifstream yaml_file(option_file);
    YAML::Node    yaml = YAML::Load(yaml_file);
    yaml_file.close();

    // data read
    std::string config_name = yaml["config_name"].as<std::string>();
    std::cout << config_name << std::endl;

    // CAN option
    _send_id     = yaml["can"]["send_id"].as<long>();
    _reply_id    = yaml["can"]["reply_id"].as<long>();
    _channel     = yaml["can"]["channel"].as<int32_t>();
    _bitrate     = yaml["can"]["bitrate"].as<int32_t>();
    _retry_turm  = yaml["can"]["retry_turm"].as<int32_t>();
    _retry_count = yaml["can"]["retry_count"].as<int32_t>();
    _time_out    = yaml["can"]["time_out"].as<int32_t>();
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

bool Can::get_channel_flag()
{
  if(!_is_connected) try_connect_can();
  if(_retry_count <= 0) return false;

  ulong flags;
  _can_status =
      canGetChannelData(_can_handle, canCHANNELDATA_CHANNEL_FLAGS, &flags, sizeof(flags));

  if(_can_status == canOK)
  {
    if((flags & canCHANNEL_IS_OPEN) != 0)
    {
      // std::cout << "CAN channel is open" << std::endl;
      return true;
    }
    else
    {
      char error_message[256];
      canGetErrorText(_can_status, error_message, sizeof(error_message));
      LOGGER->push_log_format("ERROR", "PROC", "can_channel is closed !!!", "");
      LOGGER->push_log_format("ERROR", "PROC", "Error Message", error_message);
      _is_connected = false;
      try_connect_can();
      return false;
    }
  }
  else
  {
    char error_message[256];
    canGetErrorText(_can_status, error_message, sizeof(error_message));
    LOGGER->push_log_format("ERROR", "PROC", "Failed to get channel data !!!", "");
    LOGGER->push_log_format("ERROR", "PROC", "Error Message", error_message);

    _is_connected = false;
    try_connect_can();
    return false;
  }
}

bool Can::is_status_ok()
{
  if(_can_status == canOK) return true;
  else return false;
}