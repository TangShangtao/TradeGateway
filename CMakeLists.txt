cmake_minimum_required(VERSION 3.15)
project(TradeGateway)
# 编译选项
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "-g -pg ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "-o3 ${CMAKE_CXX_FLAGS}")
# 三方库
find_package(spdlog REQUIRED)
# 路径设置
get_filename_component(RootDir "${CMAKE_CURRENT_LIST_DIR}/TradeGateway" DIRECTORY)
set(EXECUTABLE_OUTPUT_PATH ${RootDir}/bin)
set(LIBRARY_OUTPUT_PATH ${RootDir}/lib)
# 头文件、库文件搜索路径
include_directories(${RootDir}/Public)
include_directories(${RootDir}/ToolKit)
link_directories(${RootDir}/lib)
# 子项目
add_subdirectory(ToolKit)
add_subdirectory(Test)