cmake_minimum_required(VERSION 3.13)

project(mu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES
  main.cpp
  mu/Loader.cpp
  mu/Interpreter.cpp
  mu/InstructionProcessor.cpp
  mu/ValueStack.cpp)

option(PRODUCTION "Remove test code" OFF)
if (PRODUCTION)
  add_compile_definitions(DOCTEST_CONFIG_DISABLE=1)
endif()

add_subdirectory(external/fmt)
add_subdirectory(external/doctest)

add_executable(mu ${SOURCE_FILES})

target_link_libraries(mu PRIVATE fmt doctest)

