cmake_minimum_required(VERSION 3.0)

project(OpenGL_Engine)

set(INCLUDES include deps/imgui/include)


if (WIN32)
	include_directories (
		${INCLUDES}
		deps/common/include
		deps/glew/include
		deps/glfw/include
		deps/glm/include
		
	)
	link_directories (
		deps/glfw/lib
		deps/glew/lib
	)
elseif (UNIX)
	include_directories (
		${INCLUDES}
		deps/common
	)
endif()


# set output directory
if (WIN32)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)
else()
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
endif()

add_subdirectory(deps/imgui)
add_subdirectory(deps/common)

aux_source_directory(src SRC_LIST)
add_executable(Engine ${SRC_LIST})


if (WIN32)
	set(LIBS common glfw3dll glew32 opengl32 imgui)
elseif (UNIX)
	set(LIBS common glfw GL GLEW imgui)
endif ()
target_link_libraries(Engine ${LIBS})
	
