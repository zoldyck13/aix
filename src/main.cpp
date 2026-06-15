// src/main.cpp
#include "cli/arg_parser.hpp"
#include "cli/formatter.hpp"
#include "network/api_handler.hpp"
#include "network/http_client.hpp"
#include "utils/file_system.hpp"
#include <cstdlib>
#include <curlpp/cURLpp.hpp>
#include <exception>
#include <future>
#include <iostream>
#include <system_error>

int main(int argc, char *argv[]) {
    aix::ArgParser parser;
    aix::ConfigOptions options;

    try {
        parser.ParseArgument(argc, argv, options);
    } catch (const std::exception &e) {
        std::cerr << "Error parsing arguments: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    curlpp::Cleanup cleanup;
    std::string gemini_response = "";

    std::string json_payload = R"({
      "contents": [{
        "parts":[{
          "text": "Write for me an bash code print hello world"
        }]
      }]
    })";

    std::string env_key_api = aix::EnvAPIKey(options.env_var);

    std::string url = "https://generativelanguage.googleapis.com/v1beta/models/"
                      "gemini-2.5-flash:generateContent?key=" +
                      env_key_api;

    if (options.env_var.empty())
        return EXIT_FAILURE;

    try {
        aix::HttpClient client;
        std::future<std::string> future_response =
            std::async(std::launch::async, [&]() { return client.post(url, json_payload); });

        aix::RunSpinner(future_response);

        gemini_response = future_response.get();

        auto parser = aix::ParserFactory::createParser(aix::ProviderType::Gemini);

        std::string parser_result = parser->parseChatResponse(gemini_response);

        std::string output = aix::AIRenderer::RenderMarkdown(parser_result);

        std::cout << output << std::endl;
    } catch (std::exception &e) {
        std::cout << "Parser of Http request Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
