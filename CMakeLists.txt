cmake_minimum_required(VERSION 3.13)

project(mu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --save-temps")

set(SOURCE_FILES
  main.cpp
  mu/Interpreter/Add.cpp
  mu/Interpreter/Subtract.cpp
  mu/Mutext/Parser.cpp
  mu/Mutext/StringUtils.cpp
  mu/Argument.cpp
  mu/Bytecode.cpp
  mu/Loader.cpp
  mu/Log.cpp
  mu/InstructionProcessor.cpp
  mu/ReadOnlyMemoryMappedFile.cpp
  mu/ValueStack.cpp
  mu/TestUtilities.cpp)

add_compile_definitions(DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING)

add_subdirectory(external/fmt)
add_subdirectory(external/doctest)
add_subdirectory(external/nanobench)

add_executable(mu ${SOURCE_FILES})

include(CTest)
include(doctest.cmake)
doctest_discover_tests(mu)

target_include_directories(mu PRIVATE ${CMAKE_SOURCE_DIR}/mu) 

target_link_libraries(mu PRIVATE fmt doctest nanobench)

target_compile_options(mu PRIVATE $<$<CONFIG:Debug>: -fsanitize=address>)
target_link_options(mu PRIVATE $<$<CONFIG:Debug>: -fsanitize=address>)
