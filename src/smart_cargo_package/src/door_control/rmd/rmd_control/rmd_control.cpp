#include "rmd_control.h"

RmdControl::RmdControl(Can* can, std::string option_file,
                       std::function<void(RMD_ACTION, RMD_DEFINE)> update_callback)
{
  load_option(option_file);

  _can              = can;  // can 객체 참조
  _init_position    = 0;
  _current_position = 0;
  _check_position   = false;
  _target_step      = 0;
  _mode             = static_cast<int32_t>(RMD_DEFINE::NEXT_PACKET_NONE);

  _update_callback = update_callback;

  _thread_info = new ThreadActionInfo("config/door_control.yaml");  // thread 정보 객체

  // _init_position = check_current_position();

  // thread 정보 설정
  _thread_info->_active = true;
  _thread_info->_thread = std::thread(std::bind(&RmdControl::update, this));
}

RmdControl::~RmdControl()
{
  control_stop();
  _thread_info->_active = false;

  safe_delete(_thread_info);
}

void RmdControl::update()
{
  while(_thread_info->_active)
  {
    if(!_can->is_connected()) continue;

    if((_mode == static_cast<int32_t>(RMD_DEFINE::C_CTRL_SPEED)))
    {
      float angle = check_speed_reply();
      std::cout << "Motor Shaft Angle: " << angle << std::endl;
    }

    // thread 무한 독점을 방지하기 위한 sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(_thread_info->_sleep));
  }
}

void RmdControl::update_rmd_status(RMD_ACTION action, RMD_DEFINE mode)
{
  if(_update_callback == nullptr) return;

  _update_callback(action, mode);

  return;
}