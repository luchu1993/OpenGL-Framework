cmake_minimum_required(VERSION 3.0)

project(OpenGL_Framework)

include_directories (
	include 
	deps/glad/include
	deps/glfw/include
	deps/glm/include
)

link_directories (
	deps/glfw/lib
)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(deps/glad)

aux_source_directory(src SRC_LIST)
add_executable(oglApp ${SRC_LIST})

target_link_libraries(oglApp glfw3dll glad)
