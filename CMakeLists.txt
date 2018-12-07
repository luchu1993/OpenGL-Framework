cmake_minimum_required(VERSION 3.0)

project(OpenGL_Framework)

include_directories(/usr/local/include)
include_directories(include glad/include)

link_directories(/usr/local/lib)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(glad)

aux_source_directory(src SRC_LIST)
add_executable(oglApp ${SRC_LIST})

target_link_libraries(oglApp glfw glad)
