cmake_minimum_required(VERSION 3.11)
project(server)

set(CMAKE_CXX_STANDARD 17)

set (SRCS 
    src/Server.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SRCS})