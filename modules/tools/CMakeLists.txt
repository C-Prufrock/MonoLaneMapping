cmake_minimum_required(VERSION 3.23)
project(tools)

set(CMAKE_CXX_STANDARD 11)

#find_package(glog REQUIRED)
#find_package(Gflags REQUIRED)

file(GLOB_RECURSE ALL_SOURCE "*.cpp" "*.c")

add_library(tools SHARED ${ALL_SOURCE})

target_link_libraries(tools PUBLIC
        glog::glog
        ${Gflags_LIBRARIES}
)

target_include_directories(tools PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..        # 该路径为其他模块引自己模块设定;
    ${CMAKE_CURRENT_SOURCE_DIR}/          # 为内部模块相互引用;

    ${CMAKE_CURRENT_SOURCE_DIR}/IO/include/ # 为IO模块自引;


    ${GLOG_INCLUDE_DIRS}
    ${GFLAGS_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

