#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

using json = nlohmann::json;

namespace aix {
class IAiProviderParser {
  public:
    virtual ~IAiProviderParser() = default;

    virtual std::vector<std::string> parseAvailableModels(const std::string &rawjson) = 0;
    virtual std::string parseChatResponse(const std::string &rawjson) = 0;
};

class GeminiParser : public IAiProviderParser {
  public:
    std::vector<std::string> parseAvailableModels(const std::string &rawjson) override;

    std::string parseChatResponse(const std::string &rawjson) override;
};

class OpenAiParser : public IAiProviderParser {
  public:
    std::vector<std::string> parseAvailableModels(const std::string &rawjson) override;

    std::string parseChatResponse(const std::string &rawjson) override;
};

enum class ProviderType { Gemini, OpenAI };

class ParserFactory {
  public:
    static std::unique_ptr<IAiProviderParser> createParser(ProviderType type);
};

} // namespace aix
