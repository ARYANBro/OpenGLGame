cmake_minimum_required(VERSION 3.0.0)
project(stb_image VERSION 2.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(stb_image stb_image.cpp)

target_include_directories(stb_image
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
