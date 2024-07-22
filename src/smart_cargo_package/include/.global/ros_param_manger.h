#pragma once

#include <ros/ros.h>
#include <xmlrpcpp/XmlRpcValue.h>

#include <string>

class RosParamManager
{
public:
  /// @brief 파라미터 서버에 구독자 정보 등록
  /// @param key ~
  /// @param value
  void set_param(const std::string& key)
  {
    ros::param::set("/subscriber_ready/" + key, true);
  }

  /// @brief 파라미터 서버의 구독자 정보 삭제
  /// @param key
  void delete_param(const std::string& key)
  {
    ros::param::del("/subscriber_ready/" + key);
  }

  bool get_param(const std::string& key, XmlRpc::XmlRpcValue& value)
  {
    return ros::param::get(key, value);
  }
};