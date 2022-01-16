cmake_minimum_required(VERSION 3.13)
project(mu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES main.cpp muvm.cpp)

option(PRODUCTION "Remove test code" OFF)
if (PRODUCTION)
  add_compile_definitions(DOCTEST_CONFIG_DISABLE=1)
endif()

add_executable(mu ${SOURCE_FILES})

