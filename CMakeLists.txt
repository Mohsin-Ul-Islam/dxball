cmake_minimum_required(VERSION 3.9)

project(dxball)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

file(GLOB APP_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

include_directories(./include ./src)

find_package(SFML 2.5 COMPONENTS graphics system REQUIRED)

add_executable(dxball ${APP_SOURCES})

target_link_libraries(dxball sfml-graphics sfml-system sfml-audio)
