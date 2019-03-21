cmake_minimum_required(VERSION 2.8.4)
project(RECIPES)

set(CMAKE_CXX_STANDARD 14)

add_executable(RECIPES main.cpp ThreadPool/ThreadPool.h test/test.h utils/cpp_utils/print.h calllback.h)

#include_directories(C:/N-5CG719422G-Data/loohan/Desktop/nokia/OpenSource/boost_1_64_0)

SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_BUILD_TYPE "Release")

find_package(Boost COMPONENTS system filesystem REQUIRED)
if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
add_definitions(-DBOOST_SYSTEM_NO_DEPRECATED)
