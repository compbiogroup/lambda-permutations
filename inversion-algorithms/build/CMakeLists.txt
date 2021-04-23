cmake_minimum_required(VERSION 3.5.1)
project(directory_test)
set (CMAKE_CXX_STANDARD 11)
 
#Bring the headers, such as Student.h into the project
include_directories(include)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "../src/*.cpp")
 
add_executable(exec ${SOURCES})
