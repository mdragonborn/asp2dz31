cmake_minimum_required(VERSION 3.5)
project(asp2dz31)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp HashTable.cpp HashTable.h AddressFunction.h table.cpp table.h AddressFunction.cpp)
add_executable(asp2dz31 ${SOURCE_FILES})