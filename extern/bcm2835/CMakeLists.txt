
cmake_minimum_required(VERSION 3.16)

project(BCM2835)

add_library(BCM2835 INTERFACE)

target_sources(BCM2835 INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/bcm2835.c
        )

target_include_directories(BCM2835 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "From bcm2835: ${BCM2835}")