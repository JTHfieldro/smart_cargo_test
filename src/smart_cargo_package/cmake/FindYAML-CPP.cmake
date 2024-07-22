# YAML_CPP_INCLUDE_DIR
find_path(YAML_CPP_INCLUDE_DIR
  NAMES yaml-cpp/yaml.h
  PATHS
    /usr/include
    /usr/local/include
  DOC "YAML-CPP include directory"
)

# YAML_CPP_LIBRARY
find_library(YAML_CPP_LIBRARY
  NAMES yaml-cpp
  PATHS
    /usr/lib
    /usr/local/lib
  DOC "YAML-CPP library"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(YAML_CPP
  DEFAULT_MSG
  YAML_CPP_LIBRARY
  YAML_CPP_INCLUDE_DIR
)

if(YAML_CPP_FOUND)
  set(YAML_CPP_LIBRARIES ${YAML_CPP_LIBRARY})
  set(YAML_CPP_INCLUDE_DIRS ${YAML_CPP_INCLUDE_DIR})
else()
  set(YAML_CPP_LIBRARIES)
  set(YAML_CPP_INCLUDE_DIRS)
endif()

mark_as_advanced(YAML_CPP_INCLUDE_DIR YAML_CPP_LIBRARY)