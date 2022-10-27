cmake_minimum_required(VERSION 3.21.2)

project(Damien)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow")
if(${CMAKE_BUILD_TYPE} MATCHES Debug)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

message(CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
message(EXECUTABLE_OUTPUT_PATH=${CMAKE_BINARY_DIR}/bin)

set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)
message(LIBRARY_OUTPUT_PATH=${CMAKE_BINARY_DIR}/lib)

add_subdirectory(libs/googletest)

set(EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/eigen")

add_library(libDamien SHARED libDamien/common.cpp
                             libDamien/instruments.cpp
                             libDamien/pricers.cpp)
target_include_directories(libDamien PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories(libDamien PUBLIC ${EIGEN3_INCLUDE_DIR})


add_subdirectory(tests)

#-----------------------------------------------------------------#
