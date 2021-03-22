cmake_minimum_required(VERSION 3.0.2)
project(ex)

find_package(PCL REQUIRED)

include_directories(
    /usr/include/pcl-1.8
    /usr/include/eigen3
)


add_executable(ex main.cpp)
target_link_libraries(ex ${PCL_LIBRARIES})



