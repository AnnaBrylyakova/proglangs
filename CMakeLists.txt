cmake_minimum_required(VERSION 3.0)

project(repeating_count)
set(SOURCE_FILES repeating_count.cpp)

# Find PythonLibs
find_package(PythonLibs 3.4 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Make module
python_add_module(repeating_count repeating_count.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
target_link_libraries(repeating_count ${PYTHON_LIBRARIES})