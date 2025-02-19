# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fieldro/Dev/smart_cargo/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fieldro/Dev/smart_cargo/build

# Utility rule file for copy_config_files.

# Include the progress variables for this target.
include smart_cargo_package/CMakeFiles/copy_config_files.dir/progress.make

smart_cargo_package/CMakeFiles/copy_config_files: /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/cargo_option.yaml
smart_cargo_package/CMakeFiles/copy_config_files: /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/door_control.yaml
smart_cargo_package/CMakeFiles/copy_config_files: /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/handler_option.yaml
smart_cargo_package/CMakeFiles/copy_config_files: /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/sensor_signal.yaml
smart_cargo_package/CMakeFiles/copy_config_files: /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/test_option.yaml


/home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/cargo_option.yaml: /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/cargo_option.yaml
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/fieldro/Dev/smart_cargo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/cargo_option.yaml"
	cd /home/fieldro/Dev/smart_cargo/build/smart_cargo_package && /usr/bin/cmake -E copy_if_different /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/cargo_option.yaml /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/cargo_option.yaml

/home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/door_control.yaml: /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/door_control.yaml
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/fieldro/Dev/smart_cargo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/door_control.yaml"
	cd /home/fieldro/Dev/smart_cargo/build/smart_cargo_package && /usr/bin/cmake -E copy_if_different /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/door_control.yaml /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/door_control.yaml

/home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/handler_option.yaml: /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/handler_option.yaml
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/fieldro/Dev/smart_cargo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/handler_option.yaml"
	cd /home/fieldro/Dev/smart_cargo/build/smart_cargo_package && /usr/bin/cmake -E copy_if_different /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/handler_option.yaml /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/handler_option.yaml

/home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/sensor_signal.yaml: /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/sensor_signal.yaml
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/fieldro/Dev/smart_cargo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Generating /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/sensor_signal.yaml"
	cd /home/fieldro/Dev/smart_cargo/build/smart_cargo_package && /usr/bin/cmake -E copy_if_different /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/sensor_signal.yaml /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/sensor_signal.yaml

/home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/test_option.yaml: /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/test_option.yaml
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/fieldro/Dev/smart_cargo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Generating /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/test_option.yaml"
	cd /home/fieldro/Dev/smart_cargo/build/smart_cargo_package && /usr/bin/cmake -E copy_if_different /home/fieldro/Dev/smart_cargo/src/smart_cargo_package/config/test_option.yaml /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/test_option.yaml

copy_config_files: smart_cargo_package/CMakeFiles/copy_config_files
copy_config_files: /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/cargo_option.yaml
copy_config_files: /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/door_control.yaml
copy_config_files: /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/handler_option.yaml
copy_config_files: /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/sensor_signal.yaml
copy_config_files: /home/fieldro/Dev/smart_cargo/devel/lib/smart_cargo_package/config/test_option.yaml
copy_config_files: smart_cargo_package/CMakeFiles/copy_config_files.dir/build.make

.PHONY : copy_config_files

# Rule to build all files generated by this target.
smart_cargo_package/CMakeFiles/copy_config_files.dir/build: copy_config_files

.PHONY : smart_cargo_package/CMakeFiles/copy_config_files.dir/build

smart_cargo_package/CMakeFiles/copy_config_files.dir/clean:
	cd /home/fieldro/Dev/smart_cargo/build/smart_cargo_package && $(CMAKE_COMMAND) -P CMakeFiles/copy_config_files.dir/cmake_clean.cmake
.PHONY : smart_cargo_package/CMakeFiles/copy_config_files.dir/clean

smart_cargo_package/CMakeFiles/copy_config_files.dir/depend:
	cd /home/fieldro/Dev/smart_cargo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fieldro/Dev/smart_cargo/src /home/fieldro/Dev/smart_cargo/src/smart_cargo_package /home/fieldro/Dev/smart_cargo/build /home/fieldro/Dev/smart_cargo/build/smart_cargo_package /home/fieldro/Dev/smart_cargo/build/smart_cargo_package/CMakeFiles/copy_config_files.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : smart_cargo_package/CMakeFiles/copy_config_files.dir/depend

