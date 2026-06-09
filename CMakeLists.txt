cmake_minimum_required(VERSION 3.15)
project(aix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(CLI11 REQUIRED)

find_library(CURLPP_LIBRARY NAMES curlpp REQUIRED)
find_path(CURLPP_INCLUDE_DIR NAMES curlpp/cURLpp.hpp REQUIRED)

set(POJECT_SOURCES
    src/cli/arg_parser.cpp 
    src/network/http_client.cpp
    src/utils/file_system.cpp
    src/test.cpp
)

add_executable(aix ${POJECT_SOURCES})

target_include_directories(aix PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cli
    ${CMAKE_CURRENT_SOURCE_DIR}/src/network
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    ${CURLPP_INCLUDE_DIR}
)

target_link_libraries(aix PRIVATE
    ${CURLPP_LIBRARY}
    CLI11::CLI11
)
