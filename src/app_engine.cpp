// src/app_engine.cpp
#include "app_engine.hpp"
#include "cli/arg_parser.hpp"
#include "cli/formatter.hpp"
#include "core/config_manager.hpp"
#include "network/api_handler.hpp"
#include "network/http_client.hpp"
#include "utils/file_system.hpp"
#include <cstdlib>
#include <curlpp/cURLpp.hpp>
#include <future>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

namespace aix {
int AppEngine::Run(const aix::ConfigOptions &options) {
    aix::ConfigManager config;

    if (!options.env_var.empty()) {
        std::string api_key = aix::EnvAPIKey(options.env_var);

        if (api_key.empty()) {
            std::cerr << "Error: Environment variable '" << options.env_var
                      << "' not found or empty.\n";
            return EXIT_FAILURE;
        }

        std::string current_key = config.GetAPI();

        if (api_key == current_key) {
            std::cout << "API Key already exists and is identical. See ~/.config/aix/config.toml\n";
        } else {
            bool is_new = current_key.empty();

            if (config.SetAPI(api_key) == EXIT_SUCCESS) {
                if (is_new) {
                    std::cout
                        << "The key was exported to ~/.config/aix/config.toml successfully.\n";
                } else {
                    std::cout << "API Key updated successfully in ~/.config/aix/config.toml\n";
                }
            } else {
                std::cerr << "Failed to update API Key.\n";
                return EXIT_FAILURE;
            }
        }

        return EXIT_SUCCESS;
    }

    if (options.prompt.empty()) {
        std::cerr << "Prompt must not be empty, Try -p <Text>. \n";
        return EXIT_FAILURE;
    }

    std::string get_api = config.GetAPI();
    if (get_api.empty()) {
        std::cerr
            << "Error: API Key not found. Please set it via config file or environment variable.\n";
        std::cerr << "Try: aix --env-var EXAMPLE_API_KEY\n";
        return EXIT_FAILURE;
    }

    curlpp::Cleanup cleanup;
    nlohmann::json payload_json;
    payload_json["contents"] = {{{"parts", {{{"text", options.prompt}}}}}};
    std::string json_payload = payload_json.dump();

    std::string url = "https://generativelanguage.googleapis.com/v1beta/models/"
                      "gemini-2.5-flash:generateContent?key=" +
                      get_api;

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
