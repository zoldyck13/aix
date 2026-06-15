# tests/CMakeLists.txt

set(CLI_TEST_FILES
    test_cli.cpp
    ../src/cli/arg_parser.cpp
    ../src/utils/file_system.cpp
)
add_executable(cli_test_runner ${CLI_TEST_FILES})
target_link_libraries(cli_test_runner PRIVATE CLI11::CLI11 CURL::libcurl Catch2::Catch2 Catch2::Catch2WithMain ${CURLPP_LIBRARY})
target_include_directories(cli_test_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
add_test(NAME CLI_Tests COMMAND cli_test_runner) 

set(NETWORK_TEST_FILES
    test_network.cpp
    ../src/network/http_client.cpp
)
add_executable(network_test_runner ${NETWORK_TEST_FILES})
target_link_libraries(network_test_runner PRIVATE CURL::libcurl Catch2::Catch2 Catch2::Catch2WithMain ${CURLPP_LIBRARY})
target_include_directories(network_test_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
add_test(NAME Network_Tests COMMAND network_test_runner) 

set(UTILS_TEST_FILES
    test_utils.cpp
    ../src/utils/file_system.cpp
    ../src/cli/arg_parser.cpp
)
add_executable(utils_test_runner ${UTILS_TEST_FILES})
target_link_libraries(utils_test_runner PRIVATE CURL::libcurl Catch2::Catch2 Catch2::Catch2WithMain ${CURLPP_LIBRARY}) 
target_include_directories(utils_test_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
add_test(NAME Utils_Tests COMMAND utils_test_runner) 

set(API_HANDLER_TEST_FILES
    test_api_handler.cpp
    ../src/network/api_handler.cpp
)
add_executable(api_handler_test_runner ${API_HANDLER_TEST_FILES})
target_link_libraries(api_handler_test_runner PRIVATE nlohmann_json::nlohmann_json Catch2::Catch2 Catch2::Catch2WithMain)
target_include_directories(api_handler_test_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
add_test(NAME Api_Tests COMMAND api_handler_test_runner)


set(FORMATTER_TEST_FILES
    test_formatter.cpp
    ../src/cli/formatter.cpp
)
add_executable(formatter_test_runner ${FORMATTER_TEST_FILES})
target_link_libraries(formatter_test_runner PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
target_include_directories(formatter_test_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
add_test(NAME Formatter_Tests COMMAND formatter_test_runner)
