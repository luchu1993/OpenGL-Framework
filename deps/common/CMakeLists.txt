include_directories(include)
aux_source_directory(src SRC_LIST)
add_library(common ${SRC_LIST})
