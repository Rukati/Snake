cmake_minimum_required(VERSION 3.30)
project(Snake)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED COMPONENTS system thread)

add_executable(Snake main.cpp
        Objects.h
        Objects.cpp)

target_link_libraries(Snake PRIVATE Boost::system Boost::thread)