cmake_minimum_required(VERSION 3.0)

project(compressor)
set(SOURCE_FILES compressor.cpp)

# Find PythonLibs
find_package(PythonLibs 3.4 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Make module
python_add_module(compressor compressor.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
target_link_libraries(compressor ${PYTHON_LIBRARIES})