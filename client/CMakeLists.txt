cmake_minimum_required(VERSION 3.11)
project(client)

set(CMAKE_CXX_STANDARD 17)

set (SRCS 
    src/main.cpp
    src/Client.cpp
    src/Handler.cpp
)

add_executable(${PROJECT_NAME} ${SRCS})