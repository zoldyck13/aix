#include "api_handler.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace aix {

std::vector<std::string> GeminiParser::parseAvailableModels(const std::string &rawJson) {
    std::vector<std::string> modelNames;
    try {
        auto data = json::parse(rawJson);
        if (data.contains("models") && data["models"].is_array()) {
            for (const auto &model : data["models"]) {
                if (model.contains("name")) {
                    modelNames.push_back(model["name"].get<std::string>());
                }
            }
        }
    } catch (const json::parse_error &e) {
        std::cerr << "Gemini Parse Error: " << e.what() << std::endl;
    }
    return modelNames;
}

std::string GeminiParser::parseChatResponse(const std::string &rawJson) {
    try {
        auto data = json::parse(rawJson);
        return data["candidates"][0]["content"]["parts"][0]["text"].get<std::string>();
    } catch (...) {
        return "Error parsing Gemini chat response";
    }
}

std::vector<std::string> OpenAiParser::parseAvailableModels(const std::string &rawJson) {
    std::vector<std::string> modelNames;
    try {
        auto data = json::parse(rawJson);
        if (data.contains("data") && data["data"].is_array()) {
            for (const auto &model : data["data"]) {
                if (model.contains("id")) {
                    modelNames.push_back(model["id"].get<std::string>());
                }
            }
        }
    } catch (const json::parse_error &e) {
        std::cerr << "OpenAI Parse Error: " << e.what() << std::endl;
    }
    return modelNames;
}

std::string OpenAiParser::parseChatResponse(const std::string &rawJson) {
    try {
        auto data = json::parse(rawJson);
        return data["choices"][0]["message"]["content"].get<std::string>();
    } catch (...) {
        return "Error parsing OpenAI chat response";
    }
}

std::unique_ptr<IAiProviderParser> ParserFactory::createParser(ProviderType type) {
    switch (type) {
    case ProviderType::Gemini:
        return std::make_unique<GeminiParser>();
    case ProviderType::OpenAI:
        return std::make_unique<OpenAiParser>();
    default:
        throw std::invalid_argument("Unkown AI Provider");
    }
}
} // namespace aix
