cmake_minimum_required(VERSION 3.10)

project(spdlog-vs-zlog VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -O3")
set(CMAKE_CXX_COMPILER "g++")

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/zlog/build/include
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/zlog/build/lib/libzlog.a
    -pthread
)
