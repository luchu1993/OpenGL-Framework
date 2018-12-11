include_directories(include)
aux_source_directory(src SRC_LIST)
add_library(imgui ${SRC_LIST})
