cmake_minimum_required(VERSION 3.10)

project(spdlog-vs-zlog VERSION 1.0)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -O3")
set(CMAKE_CXX_COMPILER "g++")

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

if (WIN32)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/WinZlog/Release/head
    )
    find_library(WINZLOG_LIB zlog HINTS ${CMAKE_CURRENT_SOURCE_DIR}/WinZlog/Release/lib/x64)
    if(NOT WINZLOG_LIB)
        message(FATAL_ERROR "zlog.lib not found")
    endif()
    target_link_libraries(
        ${PROJECT_NAME}
        ${WINZLOG_LIB}
    )
else()
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/zlog/build/include
    )
    target_link_libraries(
        ${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/zlog/build/lib/libzlog.a
        -pthread
    )
endif (WIN32)
