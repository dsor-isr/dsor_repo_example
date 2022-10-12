cmake_minimum_required(VERSION 3.1.0)
project(cpp_counter)

find_package(catkin
 # ROS components
 REQUIRED COMPONENTS
 std_msgs 
 farol_msgs
 roscpp

 # farol_gimmicks_library
 farol_gimmicks_library
)

catkin_package(
 CATKIN_DEPENDS
)

add_compile_options(-std=c++17 -Wall -O3) 

include_directories(
 include/cpp_counter_ros
 include/cpp_counter_algorithms
 ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node src/cpp_counter_ros/CppCounterNode.cpp src/cpp_counter_algorithms/CppCounterAlgorithm.cpp)
add_dependencies(${PROJECT_NAME}_node ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})
