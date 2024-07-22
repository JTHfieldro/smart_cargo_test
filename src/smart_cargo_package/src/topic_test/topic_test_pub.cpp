#include "topic_test.h"

void TopicTest::publish_control_door(CONTROL_DOOR value)
{
  std_msgs::Int32 msg_int32;
  msg_int32.data = value;

  if(_topic_manager->is_topic_connected("smart_cargo/control_door"))
    _topic_manager->publish("smart_cargo/control_door", msg_int32);
  else _queue_control_door->push(msg_int32);
}

void TopicTest::publish_control_handler()
{
  std_msgs::Int32MultiArray msg_arr;
  std::vector<int32_t>      data;

  // msg_arr 작성 로직 구현
  data         = {1, 0, 0, 0, 1};
  msg_arr.data = data;

  if(_topic_manager->is_topic_connected("smart_cargo/control_handler"))
    _topic_manager->publish("smart_cargo/control_handler", msg_arr);
  else _queue_control_handler->push(msg_arr);
}

void TopicTest::publish_if_docking()
{
  std_msgs::Int32 msg_int32;
  msg_int32.data = 1;

  if(_topic_manager->is_topic_connected("smart_cargo/IF_docking"))
    _topic_manager->publish("smart_cargo/IF_docking", msg_int32);
  else _queue_if_docking->push(msg_int32);
}

void TopicTest::publish_if_locker()
{
  std_msgs::Int32 msg_int32;

  if(_topic_manager->is_topic_connected("smart_cargo/IF_docking"))
    _topic_manager->publish("smart_cargo/IF_locker", msg_int32);
  else _queue_if_locker->push(msg_int32);
}
