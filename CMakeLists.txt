cmake_minimum_required(VERSION 3.23)
project(MonoLaneMappingInterFace)

set(CMAKE_CXX_STANDARD 11)

# Warning settings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp  -Wall -Wextra -Werror")
# add_definitions(-w)

# Build Type Set;
set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")
# set(CMAKE_BUILD_TYPE Release CACHE STRING "set build type to release")

set(HOME /home/MonoLaneMapping/)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Ceres REQUIRED)
find_package(Glog REQUIRED)
find_package(Gflags REQUIRED)
find_package(nlohmann_json REQUIRED)

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
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/modules/
        ${EIGEN3_INCLUDE_DIR}
        ${OpenCV_INCLUDE_DIRS}
        ${CERES_INCLUDE_DIRS}
        nlohmann_json::nlohmann_json
        ${Glog_INCLUDE_DIR}
        ${Gflags_INCLUDE_DIR}
)

add_executable(MonoLaneMapping main.cpp)
target_link_libraries(MonoLaneMapping PUBLIC
        MonoLaneMappingInterFace
        MonoLaneMappingSLAM
        common
        tools
        nlohmann_json::nlohmann_json
        ${CERES_LIBRARIES}
        ${OpenCV_LIBRARIES}
        glog::glog
        ${Gflags_LIBRARIES}
)