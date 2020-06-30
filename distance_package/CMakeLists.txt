cmake_minimum_required(VERSION 2.8.3)
project(distance_package)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation 
)

 generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime  #Agregado!!
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


###TOPICOS####

add_executable(Distance_x ~/catkin_ws/src/distance_package/src/Distance_x.cpp)
target_link_libraries(Distance_x ${catkin_LIBRARIES})
add_dependencies(Distance_x distance_package_generate_messages_cpp)


