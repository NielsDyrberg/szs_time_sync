cmake_minimum_required(VERSION 3.16) # CMake version check
project(custom_timekeeper VERSION 0.0.1) # Create project "simple_example"
set(CMAKE_CXX_STANDARD 20) # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(custom_timekeeper main.cpp)

# configure a header file to pass the version number only
configure_file(CustomTimeKeeperConfig.h.in CustomTimeKeeperConfig.h.in)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(custom_timekeeper main.cpp
        tests/Tmetest/ss.c
        src/Final/timeKeeper.cpp src/Final/timeKeeper.h src/Final/syncMaster.cpp src/Final/syncMaster.h src/Final/syncSlave.cpp src/Final/syncSlave.h)

# -----Add wiringPi-----
#add_library(wiringPi STATIC IMPORTED)
#set_target_properties(wiringPi PROPERTIES IMPORTED_LOCATION /usr/lib/libwiringPi.so)
#set_target_properties(wiringPi PROPERTIES INTERFACE_INCLUDE_DIRECTORIES /usr/include)
#target_link_libraries(custom_timekeeper wiringPi)
# For at better import of wiringPi
# https://discourse.cmake.org/t/how-to-statically-link-external-library-by-target-link-libraries/1718/2
# Locate libraries and headers
#find_package(WIRINGPI_LIBRARIES NAMES wiringPi)
# ----- -----
# -----Add pigpio-----
add_library(pigpio STATIC IMPORTED)
set_target_properties(pigpio PROPERTIES IMPORTED_LOCATION /usr/lib/libpigpio.so)
set_target_properties(pigpio PROPERTIES INTERFACE_INCLUDE_DIRECTORIES /usr/include)
target_link_libraries(custom_timekeeper pigpio)
# ----- -----