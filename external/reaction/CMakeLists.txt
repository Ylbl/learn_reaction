cmake_minimum_required(VERSION 3.10)
project(reaction)

set(CMAKE_CXX_STANDARD 20)

aux_source_directory(src SRC_LIST)
add_library(reaction STATIC ${SRC_LIST})
target_include_directories(reaction PUBLIC include)