#ifndef _CAN_COMM_H
#define _CAN_COMM_H

#include "yaml-cpp/yaml.h"

#include <iostream>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <fstream>
#include <unistd.h>
#include <cstring>

class CanComm
{
    public:
      CanComm(std::string file_name);
      virtual ~CanComm();

      bool initialize();
      bool send_msg();
      bool receive_msg();
      bool _is_connected;

      struct can_frame _frame;

    private:
      void load_option(std::string file_name);

      int _nbytes;
      int _socket_fd;
      
      std::string _if_name;
      struct sockaddr_can _addr;
      struct ifreq _ifr;
      struct timeval timeout;
};
#endif