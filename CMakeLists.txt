cmake_minimum_required(VERSION 3.13)

project(mu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES
  main.cpp
  mu/Argument.cpp
  mu/Loader.cpp
  mu/Interpreter/Add.cpp
  mu/Interpreter/Subtract.cpp
  mu/InstructionProcessor.cpp
  mu/ReadOnlyMemoryMappedFile.cpp
  mu/ValueStack.cpp
  mu/TestUtilities.cpp)

add_compile_definitions(DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING)

add_subdirectory(external/fmt)
add_subdirectory(external/doctest)

add_executable(mu ${SOURCE_FILES})

target_include_directories(mu PRIVATE ${CMAKE_SOURCE_DIR}/mu) 

target_link_libraries(mu PRIVATE fmt doctest)

target_compile_options(mu PRIVATE -fsanitize=address)
target_link_options(mu PRIVATE -fsanitize=address)
