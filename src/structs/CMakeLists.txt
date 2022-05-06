cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(asteroid_structs)



add_library(${PROJECT_NAME} asteroid.c player.c bullet.c particle.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/ ${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} asteroid_game)