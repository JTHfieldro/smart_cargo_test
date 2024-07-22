#include <string.h>
#include <iostream>

#include "mw_ahrs.h"

int main()
{
  bool loop = true;
  char cmd_input[256];
  std::cout << "main start!!!" << std::endl;

  Ahrs* ahrs = new Ahrs();

  while(loop)
  {
    if(!check_std_in(10000)) continue;

    std::string              str   = get_user_input();
    std::vector<std::string> input = find_command_target(str, ' ');

    if(input.size() < 1) continue;

    if(input[0] == "finish") loop = false;
    else if(input[0] == "clear") system("clear");
    else if(input[0] == "imu") ahrs->control(str);
  }

  safe_delete(ahrs);

  std::cout << "main end" << std::endl;

  return 0;
}