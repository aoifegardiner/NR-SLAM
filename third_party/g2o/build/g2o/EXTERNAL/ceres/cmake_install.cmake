# Install script for directory: /mnt/c/Users/Aoife/scared_env/NR-SLAM/third_party/g2o/g2o/EXTERNAL/ceres

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/g2o/EXTERNAL/ceres" TYPE FILE FILES
    "/mnt/c/Users/Aoife/scared_env/NR-SLAM/third_party/g2o/g2o/EXTERNAL/ceres/array_selector.h"
    "/mnt/c/Users/Aoife/scared_env/NR-SLAM/third_party/g2o/g2o/EXTERNAL/ceres/autodiff.h"
    "/mnt/c/Users/Aoife/scared_env/NR-SLAM/third_party/g2o/g2o/EXTERNAL/ceres/disable_warnings.h"
    "/mnt/c/Users/Aoife/scared_env/NR-SLAM/third_party/g2o/g2o/EXTERNAL/ceres/eigen.h"
    "/mnt/c/Users/Aoife/scared_env/NR-SLAM/third_party/g2o/g2o/EXTERNAL/ceres/fixed_array.h"
    "/mnt/c/Users/Aoife/scared_env/NR-SLAM/third_party/g2o/g2o/EXTERNAL/ceres/integer_sequence_algorithm.h"
    "/mnt/c/Users/Aoife/scared_env/NR-SLAM/third_party/g2o/g2o/EXTERNAL/ceres/jet.h"
    "/mnt/c/Users/Aoife/scared_env/NR-SLAM/third_party/g2o/g2o/EXTERNAL/ceres/memory.h"
    "/mnt/c/Users/Aoife/scared_env/NR-SLAM/third_party/g2o/g2o/EXTERNAL/ceres/parameter_dims.h"
    "/mnt/c/Users/Aoife/scared_env/NR-SLAM/third_party/g2o/g2o/EXTERNAL/ceres/reenable_warnings.h"
    "/mnt/c/Users/Aoife/scared_env/NR-SLAM/third_party/g2o/g2o/EXTERNAL/ceres/types.h"
    "/mnt/c/Users/Aoife/scared_env/NR-SLAM/third_party/g2o/g2o/EXTERNAL/ceres/variadic_evaluate.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/g2o/EXTERNAL/ceres" TYPE FILE FILES "/mnt/c/Users/Aoife/scared_env/NR-SLAM/third_party/g2o/g2o/EXTERNAL/ceres/LICENSE")
endif()

