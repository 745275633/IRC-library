cmake_minimum_required(VERSION 3.5)
project(irc_class)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_Modules/")
include(cmakeapt)
# 版本号
set (major_version 0)
set (minor_version 1)
set (revision_version 0)
# debug和release的参数
SET(CMAKE_CXX_FLAGS_DEBUG "--std=c++11 -O0 -Wall -g -ggdb ")
SET(CMAKE_CXX_FLAGS_RELEASE "--std=c++11 -O3 -Wall")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	SET(DEBUG true)
else(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	SET(DEBUG false)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
# 配置一个头文件，通过它向源代码中传递一些CMake设置。
configure_file (
  "${PROJECT_SOURCE_DIR}/include/irc/version.hpp.in"
  "${PROJECT_SOURCE_DIR}/include/irc/version.hpp"
)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#set(CMAKE_INSTALL_PREFIX /usr/)
#aux_source_directory(${PROJECT_SOURCE_DIR}/lib LIB_LISTS)
#aux_source_directory(${PROJECT_SOURCE_DIR}/bin BIN_LIST)
include_directories(${PROJECT_SOURCE_DIR}/include SYSTEM)
include_directories(${PROJECT_SOURCE_DIR}/head)
#link_directories(${PROJECT_SOURCE_DIR}/lib)
add_subdirectory(test)
install(DIRECTORY include/ DESTINATION include)

