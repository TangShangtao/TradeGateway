aux_source_directory(. src)
add_library(ToolKit SHARED ${src})
target_link_libraries(ToolKit pthread)