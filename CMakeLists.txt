cmake_minimum_required(VERSION 3.23)
project(MonoLaneMappingInterFace)

set(CMAKE_CXX_STANDARD 11)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Ceres REQUIRED)
find_package(glog REQUIRED)
find_package(Gflags REQUIRED)

add_subdirectory(modules/tools)
add_subdirectory(modules/common)
add_subdirectory(modules/MonoLaneSLAM)
add_subdirectory(modules/MonoLaneMappingInterFace)

message(STATUS "${CERES_INCLUDED_DIRS}")
message(STATUS "${EIGEN3_INCLUDE_DIR}")
message(STATUS "${OpenCV_INCLUDE_DIRS}")
message(STATUS "${GFLAGS_INCLUDE_DIRS}")
message(STATUS "${GLOG_INCLUDE_DIRS}")

include_directories(
        ${EIGEN3_INCLUDE_DIR}
        ${OpenCV_INCLUDE_DIRS}
        ${CERES_INCLUDE_DIRS}
        ${GFLAGS_INCLUDE_DIRS}
        ${GLOG_INCLUDE_DIRS})

add_executable(MonoLaneMapping main.cpp)
target_link_libraries(MonoLaneMapping
        ${CERES_LIBRARIES}
        ${OpenCV_LIBRARIES}
        ${GFLAGS_LIBRARIES}
        ${GLOG_LIBRARIES})