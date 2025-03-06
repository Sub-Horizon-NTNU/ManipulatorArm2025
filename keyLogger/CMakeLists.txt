cmake_minimum_required(VERSION 3.8)
project(keyLogger)

# Default to C++17
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find ROS2 dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# Create executable
add_executable(key_logger_node 
  src/main.cpp
  include/KeyLoggerNode.hpp
  include/KeyLoggerNode.hpp
)

# Link ROS2 dependencies
ament_target_dependencies(key_logger_node
  rclcpp
  std_msgs
)

# Install the executable
install(TARGETS key_logger_node
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()