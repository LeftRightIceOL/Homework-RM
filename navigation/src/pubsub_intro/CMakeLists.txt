cmake_minimum_required(VERSION 3.8)
project(pubsub_intro)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)         #找到依赖的ros2构建系统


include_directories(include)

add_executable(intro_node 
    src/intro_node.cpp 
    src/main.cpp
)                      #生成可知性文件



ament_target_dependencies(intro_node 
    rclcpp 
    std_msgs
)


install(TARGETS
    intro_node
    DESTINATION lib/${PROJECT_NAME}
)           #安装可执行文件到 install 目录的 lib/pubsub_intro 下


ament_package()