cmake_minimum_required(VERSION 3.10)
project(homework_2)  

set(CMAKE_CXX_STANDARD 11)   
#强制项目使用C++11标准防止报错
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui aruco)
  
#找 OpenCV 依赖
include_directories(include ${OpenCV_INCLUDE_DIRS})   
#去include找头文件


add_executable(homework_2    
    src/main.cpp
    src/Detector.cpp
)                                        
#生成可执行文件


target_link_libraries(homework_2 ${OpenCV_LIBS})   
#链接 OpenCV 库
