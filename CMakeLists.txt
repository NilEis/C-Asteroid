cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(asteroid)

# Asteroid

add_executable(${PROJECT_NAME} src/main.c)
#set(raylib_VERBOSE 1)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/)

add_subdirectory(src/audio)
add_subdirectory(src/video)
add_subdirectory(src/structs)
add_subdirectory(src/game)

list(APPEND LIBS raylib)
list(APPEND LIBS asteroid_audio)
list(APPEND LIBS asteroid_video)
list(APPEND LIBS asteroid_structs)
list(APPEND LIBS asteroid_game)

file(READ ${CMAKE_SOURCE_DIR}/shader/main.fs MAIN_SHADER_fs_file)
string(REPLACE "\n" "\\n\"\\\n\"" MAIN_SHADER_fs "${MAIN_SHADER_fs_file}")
file(READ ${CMAKE_SOURCE_DIR}/shader/main.vs MAIN_SHADER_vs_file)
string(REPLACE "\n" "\\n\"\\\n\"" MAIN_SHADER_vs "${MAIN_SHADER_vs_file}")

configure_file(${CMAKE_SOURCE_DIR}/include/video/shader.h.in ${CMAKE_SOURCE_DIR}/include/video/shader.h @ONLY)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBS})

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()