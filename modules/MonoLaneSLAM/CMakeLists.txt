cmake_minimum_required(VERSION 3.23)
project(MonoLaneMappingSLAM)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

file(GLOB_RECURSE ALL_SOURCE "*.cpp" "*.c")

add_library(MonoLaneMappingSLAM ${ALL_SOURCE})
target_include_directories(MonoLaneMappingSLAM PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..        # 该路径为其他模块引自己模块设定;
        ${CMAKE_CURRENT_SOURCE_DIR}/include/  # 该路径为自己模块引自己头文件设定;
)