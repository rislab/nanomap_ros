cmake_minimum_required(VERSION 2.8.3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")
project(nanomap_ros)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  visualization_msgs
  nav_msgs
  roscpp
  std_msgs
  std_srvs
  tf
  tf2
  cv_bridge
  image_transport
  message_generation
  sensor_msgs
  pcl_ros
  parameter_utils
  tf2_sensor_msgs
)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)

add_message_files(
  FILES
  NanoMapQuery.msg
  NanoMapQueryArray.msg
)

generate_messages(
  DEPENDENCIES
  geometry_msgs
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  # CATKIN_DEPENDS roscpp
#  DEPENDS other non-ROS libs
)
add_compile_options(-pg)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${PCL_INCLUDE_DIRS}
)
link_directories(${PCL_LIBRARY_DIRS})

find_package(orocos_kdl REQUIRED)
find_library(OROCOS_KDL orocos-kdl)
set(orocos_kdl_LIBRARIES ${OROCOS_KDL})


add_library( nanomap_ros 
  src/nanomap.cc 
  src/pose_manager.cc 
  src/structured_point_cloud_chain.cc 
  src/fov_evaluator.cc 
  src/nanomap_visualizer.cc
)

target_link_libraries( nanomap_ros 
  ${catkin_LIBRARIES} 
  ${PCL_LIBRARIES} 
  orocos-kdl
)

add_executable( benchmarking_node 
  example_nodes/benchmarking_node.cpp 
)
target_link_libraries( benchmarking_node 
  nanomap_ros 
  ${catkin_LIBRARIES} 
  ${PCL_LIBRARIES} 
  orocos-kdl
)

add_executable( visualization_node 
  example_nodes/visualization_node.cpp 
)
target_link_libraries( visualization_node 
  nanomap_ros 
  ${catkin_LIBRARIES} 
  ${PCL_LIBRARIES} 
  orocos-kdl
)

install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)
install(
  DIRECTORY include
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
