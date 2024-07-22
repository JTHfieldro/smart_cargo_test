#include "can/can_comm.h"

CanComm::CanComm(std::string file_name)
{
  _is_connected = false;
  timeout.tv_sec = 1;
  timeout.tv_usec = 0;
  memset(&_ifr, 0x00, sizeof(struct ifreq));
  load_option(file_name);
  initialize();
}

CanComm::~CanComm()
{
  close(_socket_fd);
  _is_connected = false;
}

void CanComm::load_option(std::string file_name)
{
  try
  {
    std::ifstream yaml_file(file_name);
    YAML::Node yaml = YAML::Load(yaml_file);
    yaml_file.close();
    std::string interface_str = yaml["can"]["INTERFACE"].as<std::string>();
    const char* _if_name      = interface_str.c_str();
    _frame.can_id  = yaml["can"]["ID"].as<canid_t>();
    _frame.can_dlc = yaml["can"]["DLC"].as<__u8>();
  }
  catch (YAML::Exception& e)
  {
      std::cout << "YAML Exception : " << e.what() << std::endl;
  }
  catch (std::exception& e)
  {
      std::cout << "Exception : " << e.what() << std::endl;
  }
  catch (...)
  {
      std::cout << "Unknown Exception" << std::endl;
  }
}

bool CanComm::initialize() 
{
  _socket_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  if(_socket_fd < 0)
  {
    _is_connected = false;
    return false;
  }

  strcpy(_ifr.ifr_name, _if_name.c_str());
  ioctl(_socket_fd, SIOCGIFINDEX, &_ifr);

  _addr.can_family  = AF_CAN;
  _addr.can_ifindex = _ifr.ifr_ifindex;

  if (bind(_socket_fd, (struct sockaddr*)&_addr, sizeof(_addr)) < 0) 
  {
    _is_connected = false;
    return false;
  }

  if (setsockopt(_socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0) 
  {
    _is_connected = false;
    return false;
  }
  
  _is_connected = true;
  return true;
}

bool CanComm::send_msg() 
{
  _nbytes = write(_socket_fd, &_frame, sizeof(struct can_frame));
  if (_nbytes != sizeof(struct can_frame))
  {
    _is_connected = false;
    return false;
  }

  if (setsockopt(_socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0) 
  {
    _is_connected = false;
    return false;
  }
  return true;
}

bool CanComm::receive_msg() 
{
  _nbytes = read(_socket_fd, &_frame, sizeof(struct can_frame));
  if (_nbytes != sizeof(struct can_frame))
  {
    _is_connected = false;
    return false;
  }

  if (setsockopt(_socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0) 
  {
    _is_connected = false;
    return false;
  }
  return true;
}