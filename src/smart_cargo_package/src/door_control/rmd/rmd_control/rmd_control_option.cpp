#include "rmd_control.h"

void RmdControl::load_option(std::string option_file)
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

    // RMD option
    _gear_ratio   = yaml["rmd_comm"]["gear_ratio"].as<int32_t>();
    _step_per_rev = yaml["rmd_comm"]["step_per_rev"].as<int32_t>();
    _rpm          = yaml["rmd_comm"]["rpm"].as<int32_t>();
    _max_limit    = yaml["rmd_comm"]["max_limit"].as<int32_t>();
    _min_limit    = yaml["rmd_comm"]["min_limit"].as<int32_t>();
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