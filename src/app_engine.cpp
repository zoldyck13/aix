// src/app_engine.cpp
#include "app_engine.hpp"
#include "cli/arg_parser.hpp"
#include "cli/formatter.hpp"
#include "network/api_handler.hpp"
#include "network/http_client.hpp"
#include "utils/file_system.hpp"
#include <cstdlib>
#include <curlpp/cURLpp.hpp>
#include <future>
#include <iostream>
#include <nlohmann/json.hpp>

namespace aix {
int AppEngine::Run(const aix::ConfigOptions &options) {
    if (options.prompt.empty()) {
        std::cerr << "Prompt must not be empty, Try -p <Text>.\n";
        return EXIT_FAILURE;
    }

    std::string api_key = aix::EnvAPIKey(options.env_var);
    if (api_key.empty()) {
        std::cerr << "API Key not found in environment variable: " << options.env_var << "\n";
        return EXIT_FAILURE;
    }

    curlpp::Cleanup cleanup;
    nlohmann::json payload_json;
    payload_json["contents"] = {{{"parts", {{{"text", options.prompt}}}}}};
    std::string json_payload = payload_json.dump();

    std::string url = "https://generativelanguage.googleapis.com/v1beta/models/"
                      "gemini-2.5-flash:generateContent?key=" +
                      api_key;

    try {
        aix::HttpClient client;
        std::future<std::string> future_response =
            std::async(std::launch::async, [&]() { return client.post(url, json_payload); });

        aix::RunSpinner(future_response);
        std::string gemini_response = future_response.get();

        auto parser = aix::ParserFactory::createParser(aix::ProviderType::Gemini);
        std::string parser_result = parser->parseChatResponse(gemini_response);

        std::string output = aix::AIRenderer::RenderMarkdown(parser_result);

        aix::animateText(output, 4);

        return EXIT_SUCCESS;

    } catch (const std::exception &e) {
        std::cerr << "Execution Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
}
} // namespace aix
