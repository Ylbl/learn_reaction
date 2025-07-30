cmake_minimum_required(VERSION 3.31)
project(SSH)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(external/reaction)

aux_source_directory(src SRC_LIST)
add_executable(SSH ${SRC_LIST})
target_include_directories(SSH PUBLIC include)

target_link_libraries(SSH PUBLIC reaction)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(SSH PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(SSH PRIVATE spdlog::spdlog)