# Install script for directory: /home/fieldro/Dev/smart_cargo/src/smart_cargo_package

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/fieldro/Dev/smart_cargo/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smart_cargo_package/home/fieldro/Dev/smart_cargo/src/smart_cargo_package/msg" TYPE FILE FILES
    "/home/fieldro/Dev/smart_cargo/src/smart_cargo_package/msg/middle_control_msgs.msg"
    "/home/fieldro/Dev/smart_cargo/src/smart_cargo_package/msg/sensor_signal_msgs.msg"
    "/home/fieldro/Dev/smart_cargo/src/smart_cargo_package/msg/action_complete_msgs.msg"
    "/home/fieldro/Dev/smart_cargo/src/smart_cargo_package/msg/state_monitor.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smart_cargo_package/cmake" TYPE FILE FILES "/home/fieldro/Dev/smart_cargo/build/smart_cargo_package/catkin_generated/installspace/smart_cargo_package-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/fieldro/Dev/smart_cargo/devel/include/smart_cargo_package")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/fieldro/Dev/smart_cargo/devel/share/roseus/ros/smart_cargo_package")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/fieldro/Dev/smart_cargo/devel/share/common-lisp/ros/smart_cargo_package")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/fieldro/Dev/smart_cargo/devel/share/gennodejs/ros/smart_cargo_package")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/fieldro/Dev/smart_cargo/devel/lib/python2.7/dist-packages/smart_cargo_package")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/fieldro/Dev/smart_cargo/devel/lib/python2.7/dist-packages/smart_cargo_package")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/fieldro/Dev/smart_cargo/build/smart_cargo_package/catkin_generated/installspace/smart_cargo_package.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smart_cargo_package/cmake" TYPE FILE FILES "/home/fieldro/Dev/smart_cargo/build/smart_cargo_package/catkin_generated/installspace/smart_cargo_package-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smart_cargo_package/cmake" TYPE FILE FILES
    "/home/fieldro/Dev/smart_cargo/build/smart_cargo_package/catkin_generated/installspace/smart_cargo_packageConfig.cmake"
    "/home/fieldro/Dev/smart_cargo/build/smart_cargo_package/catkin_generated/installspace/smart_cargo_packageConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smart_cargo_package" TYPE FILE FILES "/home/fieldro/Dev/smart_cargo/src/smart_cargo_package/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smart_cargo_package" TYPE DIRECTORY FILES "/home/fieldro/Dev/smart_cargo/src/smart_cargo_package/launch")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/fieldro/Dev/smart_cargo/build/smart_cargo_package/src/smart_cargo/cmake_install.cmake")
  include("/home/fieldro/Dev/smart_cargo/build/smart_cargo_package/src/sensor_signal/cmake_install.cmake")
  include("/home/fieldro/Dev/smart_cargo/build/smart_cargo_package/src/door_control/cmake_install.cmake")
  include("/home/fieldro/Dev/smart_cargo/build/smart_cargo_package/src/topic_test/cmake_install.cmake")
  include("/home/fieldro/Dev/smart_cargo/build/smart_cargo_package/src/handler_control/cmake_install.cmake")

endif()

