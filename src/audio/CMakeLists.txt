cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(asteroid_audio)


add_library(${PROJECT_NAME} audio_main.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/ ${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})