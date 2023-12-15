# include_directories(libCTP/include)

# file(GLOB CTP_SO "./libCTP/lib/*.so")

aux_source_directory(. src)
add_library(TestApi SHARED ${src})
target_link_libraries(TestApi Service)