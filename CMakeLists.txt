cmake_minimum_required(VERSION 3.15)
project(aix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(CLI11 REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)
find_package(tomlplusplus REQUIRED)

find_library(CURLPP_LIBRARY NAMES curlpp REQUIRED)
find_path(CURLPP_INCLUDE_DIR NAMES curlpp/cURLpp.hpp REQUIRED)
find_program(GLOW_BIN glow)

if(NOT GLOW_BIN)
    message(FATAL_ERROR 
        "\n"
        "=================================================================\n"
        " ERROR: Required command-line utility 'glow' was not found!\n"
        " Please install 'glow' to continue. On Arch Linux, you can run:\n"
        "   sudo pacman -S glow\n"
        "=================================================================\n"
    )
endif()

message(STATUS "Found glow: ${GLOW_BIN}")

set(PROJECT_SOURCES
    src/cli/arg_parser.cpp 
    src/cli/formatter.cpp
    src/network/http_client.cpp
    src/utils/file_system.cpp
    src/network/api_handler.cpp
    src/core/config_manager.cpp
    src/app_engine.cpp
)

add_library(aix_core STATIC ${PROJECT_SOURCES})

target_include_directories(aix_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(aix_core PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cli
    ${CMAKE_CURRENT_SOURCE_DIR}/src/network
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    ${CURLPP_INCLUDE_DIR}
    ${CURL_INCLUDE_DIRS}
)

target_link_libraries(aix_core PRIVATE
    ${CURLPP_LIBRARY}
    CURL::libcurl
    CLI11::CLI11
    nlohmann_json::nlohmann_json
    tomlplusplus::tomlplusplus
)

add_executable(aix src/main.cpp)
target_link_libraries(aix PRIVATE aix_core)

enable_testing()

find_package(Catch2 REQUIRED)

add_subdirectory(tests)
