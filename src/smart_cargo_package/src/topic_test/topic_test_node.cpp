#include "topic_test.h"

void TopicTest::init_node()
{
  set_subscriber();
  set_publisher();
  set_sub_param();

  // Setup Message Queue
  _queue_control_door    = make_unique<SafeQueue<std_msgs::Int32>>();
  _queue_control_handler = make_unique<SafeQueue<std_msgs::Int32MultiArray>>();
  _queue_if_docking      = make_unique<SafeQueue<std_msgs::Int32>>();
  _queue_if_locker       = make_unique<SafeQueue<std_msgs::Int32>>();

  ros::Duration(0.5).sleep();  // 0.5초 대기
}

void TopicTest::set_subscriber()
{
  _topic_manager->add_subscriber<std_msgs::Int32>("smart_cargo/IF_WCS", 100,
                                                  &TopicTest::subscribe_if_wcs, this);
  _topic_manager->add_subscriber<smart_cargo_package::state_monitor>(
      "smart_cargo/state_monitor", 100, &TopicTest::subscribe_state_monitor, this);
}

void TopicTest::set_publisher()
{
  _node_name = ros::this_node::getName();

  // Set Publisher
  _topic_manager->add_publisher<std_msgs::Int32>("smart_cargo/control_door", 10);
  _topic_manager->add_publisher<std_msgs::Int32MultiArray>("smart_cargo/control_handler",
                                                           10);
  _topic_manager->add_publisher<std_msgs::Int32>("smart_cargo/IF_docking", 10);
  _topic_manager->add_publisher<std_msgs::Int32>("smart_cargo/IF_locker", 10);

  // topic별 구독 Node list
  _subscriber_list.clear();
  _subscriber_list["smart_cargo/control_door"]    = {"smart_cargo"};
  _subscriber_list["smart_cargo/control_handler"] = {"smart_cargo"};
  _subscriber_list["smart_cargo/IF_docking"]      = {"smart_cargo"};
  _subscriber_list["smart_cargo/IF_locker"]       = {"smart_cargo"};

  // Setup required subscribers
  _topic_manager->add_required_subscribers(_subscriber_list);
}

/**
 *  @brief Subscriber Parameter Server 상태 설정
 */
void TopicTest::set_sub_param()
{
  _param_manager->set_param("smart_cargo/IF_WCS" + _node_name);
  _param_manager->set_param("smart_cargo/state_monitor" + _node_name);
}

/**
 *  @brief Node 종료 시 Parameter 삭제
 */
void TopicTest::delete_sub_param()
{
  _param_manager->delete_param("smart_cargo/IF_WCS" + _node_name);
  _param_manager->delete_param("smart_cargo/state_monitor" + _node_name);
}

void TopicTest::node_update()
{
  while(_thread_node->_active)
  {
    if(!_topic_manager->check_subscriber()) continue;
    pop_msg();
    // thread 무한 독점을 방지하기 위한 sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(_thread_node->_sleep));
  }
}

void TopicTest::pop_msg()
{
  std_msgs::Int32           msg_int32;
  std_msgs::Int32MultiArray msg_arr;

  if(_queue_control_door->pop(msg_int32))
    _topic_manager->publish("smart_cargo/control_door", msg_int32);
  else if(_queue_control_handler->pop(msg_arr))
    _topic_manager->publish("smart_cargo/control_handler", msg_arr);
  else if(_queue_if_docking->pop(msg_int32))
    _topic_manager->publish("smart_cargo/IF_docking", msg_int32);
  else if(_queue_if_locker->pop(msg_int32))
    _topic_manager->publish("smart_cargo/IF_locker", msg_int32);
}