#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct TopicInfo
{
  std::string command;
  std::string message;
  std::string topic;
};

inline void print_topic()
{
  std::vector<TopicInfo> topics = {{"door_open", "1", "/smart_cargo/control_door"},
                                   {"door_close", "2", "/smart_cargo/control_door"},
                                   {"door_cancel", "3", "/smart_cargo/control_door"},
                                   {"request_drop", "1", "/smart_cargo/control_handler"},
                                   {"multi_drop", "1-7", "/smart_cargo/control_handler"},
                                   {"load_req", "1", "/smart_cargo/IF_docking"},
                                   {"unload_req", "2", "/smart_cargo/IF_docking"},
                                   {"request_enter", "1", "/smart_cargo/IF_locker"}};

  std::stringstream ss;
  ss << "\n\n\n\n\n\n\n[" << std::left << std::setw(12) << "topic_test" << "] " << "["
     << std::left << std::setw(20) << "Command" << "] " << "[" << std::left
     << std::setw(10) << "Message" << "] " << "[" << std::left << std::setw(30) << "Topic"
     << "]" << std::endl;

  std::string prev_topic;
  for(const auto& topic : topics)
  {
    ss << std::left << std::setw(15) << " " << "[" << std::left << std::setw(20)
       << topic.command << "] " << "[" << std::left << std::setw(10) << topic.message
       << "] ";

    if(topic.topic != prev_topic)
    {
      ss << "[" << std::left << std::setw(30) << topic.topic << "]";
      prev_topic = topic.topic;
    }
    ss << std::endl;
  }

  std::cout << ss.str();
}