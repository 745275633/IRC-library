cmake_minimum_required(VERSION 3.5)
project(irc_class)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_Modules/")
include(cmakeapt)
# 版本号
set(major_version 0)
set(minor_version 1)
set(revision_version 0)
file(STRINGS build-times build_version)
# debug和release的参数
SET(CMAKE_CXX_FLAGS_DEBUG "--std=c++11 -O0 -Wall -g -ggdb ")
SET(CMAKE_CXX_FLAGS_RELEASE "--std=c++11 -O3 -Wall")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	SET(DEBUG true)
else(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	SET(DEBUG false)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
configure_file (
  "${PROJECT_SOURCE_DIR}/version.hpp.in"
  "${PROJECT_SOURCE_DIR}/include/DA/irc/version.hpp"
)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/include SYSTEM)
add_subdirectory(test)
execute_process(COMMAND doxygen ${PROJECT_SOURCE_DIR}/Doxyfile WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
install(DIRECTORY include/ DESTINATION include)
