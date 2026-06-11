// tests/test_network.cpp
#include "../src/network/http_client.hpp"
#include <cstdlib>
#include <iostream>

int main() {
    aix::HttpClient client;

    std::string url = "https://httpbin.org/post";

    std::string json_payload = R"({"title": "test", "body": "testing aix network module"})";

    std::cout << "Sending POST request to " << url << "...\n";

    try {
        std::string response = client.post(url, json_payload);

        std::cout << "Response received successfully:\n" << response << "\n";

        if (response.empty() || response.find("testing aix network module") == std::string::npos) {
            std::cerr << "Test Failed: Response is empty or data mismatch!\n";
            return EXIT_FAILURE;
        }

    } catch (const std::exception &e) {
        std::cerr << "Test Crashed with exception: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    std::cout << "Network POST Test Passed successfully!\n";
    return EXIT_SUCCESS;
}
