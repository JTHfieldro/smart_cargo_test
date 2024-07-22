#include "modbus_wrapper.h"

void ModbusWrapper::load_option_tcp(std::string file_name)
{
  try
  {
    // file open
    std::ifstream yaml_file(file_name);
    YAML::Node    yaml = YAML::Load(yaml_file);
    yaml_file.close();

    // data read
    std::string config_name = yaml["config_name"].as<std::string>();
    std::cout << config_name << std::endl;

    // modbus tcp ip, port 정보
    _ip          = yaml["modbus"]["ip"].as<std::string>();
    _port        = yaml["modbus"]["port"].as<int32_t>();
    _retry_count = yaml["modbus"]["retry_count"].as<int32_t>();
    _retry_turm  = yaml["modbus"]["retry_turm"].as<int32_t>();
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