#include "topic_test.h"

TopicTest::TopicTest()
{
  _msg_pub_flag = false;
  init_state_monitor_msg();

  int argc = 0;
  ros::init(argc, nullptr, "topic_test");  // topic_test node명 초기화

  _node_handle   = new ros::NodeHandle;  // Node Handler 생성
  _topic_manager = make_unique<RosTopicManager>(_node_handle);
  _param_manager = make_unique<RosParamManager>();

  init_node();

  // thread info 설정
  _thread_info = make_unique<ThreadActionInfo>("config/test_option.yaml");
  _thread_node = make_unique<ThreadActionInfo>("config/test_option.yaml");

  // ROS Spin
  _spinner = new ros::AsyncSpinner(5);
  _spinner->start();

  // thread 정보 설정
  _thread_info->_active = true;
  _thread_info->_thread = std::thread(std::bind(&TopicTest::update, this));
  _thread_node->_active = true;
  _thread_node->_thread = std::thread(std::bind(&TopicTest::node_update, this));

  LOGGER->push_log_format("INFO", "PROC", "Node Start", "");
}

TopicTest::~TopicTest()
{
  _thread_info->_active = false;
  _thread_node->_active = false;
  // safe_delete(_thread_info);

  // ROS 관련 객체 해제
  delete_sub_param();
  ros::shutdown();
  ros::waitForShutdown();
  safe_delete(_node_handle);

  LOGGER->push_log_format("INFO", "PROC", "Node Stop", "");
}

void TopicTest::control(std::string str)
{
  std::string cmd = parsing_command_map(str, _command_map);

  if(cmd == "door_open") publish_control_door(CONTROL_DOOR_OPEN);
  else if(cmd == "door_close") publish_control_door(CONTROL_DOOR_CLOSE);
  else if(cmd == "door_cancel") publish_control_door(CONTROL_DOOR_CANCEL);
  else if(cmd == "request_drop") publish_control_handler();

  _command_map.clear();
}

void TopicTest::update()
{
  while(_thread_info->_active)
  {
    // if(!check_subscriber()) continue;

    // check_publish_msg();
    // pop_msg();

    // thread 무한 독점을 방지하기 위한 sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(_thread_info->_sleep));
  }
}

void TopicTest ::check_publish_msg()
{
  if(!_msg_pub_flag)
  {
    publish_control_door(CONTROL_DOOR_CANCEL);
    _msg_pub_flag = true;
    std::cout << "_msg_pub_flag: " << _msg_pub_flag << std::endl;
  }
}