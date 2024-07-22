#include <cstring>
#include "mw_ahrs.h"

void Ahrs::input_data()
{
    if(_cancomm->receive_msg())
    {
      std::memcpy(_can_read_data, _cancomm->_frame.data, sizeof(_can_read_data));
      if(_can_read_data[0] == 0xF0)
      {
        if(_can_read_data[1] == ACCELERATION)
        {
          std::memcpy(_accel_data, &_can_read_data[2], 6);
          _accel_x = get_data(_accel_data[0], _accel_data[1]) / 1000.0f;
          _accel_y = get_data(_accel_data[2], _accel_data[3]) / 1000.0f;
          _accel_z = get_data(_accel_data[4], _accel_data[5]) / 1000.0f;
        }

        else if(_can_read_data[1] == GYROSCOPE)
        {
          std::memcpy(_gyro_data, &_can_read_data[2], 6);
          _gyro_x = get_data(_gyro_data[0], _gyro_data[1]) / 10.0f;
          _gyro_y = get_data(_gyro_data[2], _gyro_data[3]) / 10.0f;
          _gyro_z = get_data(_gyro_data[4], _gyro_data[5]) / 10.0f;
        }

        else if(_can_read_data[1] == ANGLE)
        {
          std::memcpy(_angle_data, &_can_read_data[2], 6);
          _angle_roll  = get_data(_angle_data[0], _angle_data[1]) / 100.0f;
          _angle_pitch = get_data(_angle_data[2], _angle_data[3]) / 100.0f;
          _angle_yaw   = get_data(_angle_data[4], _angle_data[5]) / 100.0f;
        }

        else if(_can_read_data[1] == MAGNETIC)
        {
          std::memcpy(_mag_data, &_can_read_data[2], 6);
          _mag_x = get_data(_mag_data[0], _mag_data[1]) / 10.0f;
          _mag_y = get_data(_mag_data[2], _mag_data[3]) / 10.0f;
          _mag_z = get_data(_mag_data[4], _mag_data[5]) / 10.0f;
        }
      }
    }
}

int16_t Ahrs::get_data(uint8_t low, uint8_t high)
{
    return static_cast<int16_t>(low + (static_cast<uint16_t>(high) << 8));
}

void Ahrs::show_data(int _type)
{
  if(_type==DT_ACC)
  {
  std::cout << "=================" << std::endl;
  std::cout << "X: " << _accel_x << "\nY: " << _accel_y << "\nZ: " << _accel_z << std::endl;
  }

  else if(_type==DT_GYRO)
  {
  std::cout << "=================" << std::endl;
  std::cout << "X: " << _gyro_x << "\nY: " << _gyro_y << "\nZ: " << _gyro_z << std::endl;
  }

  else if(_type==DT_ANGLE)
  {
  std::cout << "=================" << std::endl;
  std::cout << "Roll: " << _angle_roll << "\nPitch: " << _angle_pitch << "\nYaw: " << _angle_yaw << std::endl;
  }

  else if(_type==DT_MAGNETIC)
  {
  std::cout << "=================" << std::endl;
  std::cout << "X: " << _mag_x << "\nY: " << _mag_y << "\nZ: " << _mag_z << std::endl;
  }
}