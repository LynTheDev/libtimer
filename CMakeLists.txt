cmake_minimum_required(VERSION 3.11)
project(libtimer LANGUAGES CXX)

add_library(${PROJECT_NAME}
    src/timer.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include/
)