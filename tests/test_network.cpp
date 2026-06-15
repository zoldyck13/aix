// tests/test_network.cpp
#include "../src/network/http_client.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("Network_Tests - HttpClient POST Functionality", "[network]") {
    aix::HttpClient client;

    std::string url = "https://postman-echo.com/post";

    std::string json_payload = R"({"title": "test", "body": "testing aix network module"})";

    std::string response = client.post(url, json_payload);

    REQUIRE_FALSE(response.empty());
    REQUIRE(response.find("testing aix network module") != std::string::npos);
}
