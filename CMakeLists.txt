cmake_minimum_required(VERSION 3.12)
project(asteroid)

# Asteroid

add_executable(${PROJECT_NAME} src/main.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/)

add_subdirectory(extern/raylib)
add_subdirectory(src/audio)
add_subdirectory(src/video)
add_subdirectory(src/structs)
add_subdirectory(src/game)

list(APPEND LIBS raylib)
list(APPEND LIBS asteroid_audio)
list(APPEND LIBS asteroid_video)
list(APPEND LIBS asteroid_structs)
list(APPEND LIBS asteroid_game)
list(APPEND LIBS m)

file(READ ${CMAKE_SOURCE_DIR}/shader/main.fs MAIN_SHADER_fs_file)
string(REPLACE "\n" "\\n\"\\\n\"" MAIN_SHADER_fs "${MAIN_SHADER_fs_file}")
file(READ ${CMAKE_SOURCE_DIR}/shader/main.vs MAIN_SHADER_vs_file)
string(REPLACE "\n" "\\n\"\\\n\"" MAIN_SHADER_vs "${MAIN_SHADER_vs_file}")

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/shader/main.fs)

configure_file(${CMAKE_SOURCE_DIR}/include/video/shader.h.in ${CMAKE_SOURCE_DIR}/include/video/shader.h @ONLY)

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBS})

SET(CMAKE_EXE_LINKER_FLAGS "-static")

# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")
# Tell Emscripten to build an example.html file.
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

find_package(Doxygen)
if(DOXYGEN_FOUND)
  option(ASTEROID_GENERATE_DOCS "Generate documentation for the project" OFF)
  if(ASTEROID_GENERATE_DOCS)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_USE_MATHJAX YES)
    set(DOXYGEN_RECURSIVE YES)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "README.md")
    set(DOXYGEN_PROJECT_BRIEF "A clone of the asteroid game in c with raylib")
    doxygen_add_docs(asteroid_docs README.md ${CMAKE_SOURCE_DIR}/include ALL)
  endif()
endif()