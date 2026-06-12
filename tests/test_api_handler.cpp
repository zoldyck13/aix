#include <string>
#define CATCH_CONFIG_MAIN
#include "../src/network/api_handler.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Gemini Parser VAlidation", "[gemini]") {
    auto parser = aix::ParserFactory::createParser(aix::ProviderType::Gemini);

    SECTION("Extract valid models correctly") {
        std::string rawJson = R"({
            "models": [
                {"name": "models/gemini-2.5-flash"},
                {"name": "models/gemini-2.5-pro"}
            ]
        })";

        std::vector<std::string> result = parser->parseAvailableModels(rawJson);

        REQUIRE(result.size() == 2);
        REQUIRE(result[0] == "models/gemini-2.5-flash");
        REQUIRE(result[1] == "models/gemini-2.5-pro");
    }

    SECTION("Handel empty or corrupted JSON safely") {
        std::string brokenJson = R"({"invalid_key": []})";
        std::vector<std::string> result = parser->parseAvailableModels(brokenJson);

        REQUIRE(result.empty());
    }
}

TEST_CASE("OpenAI Parser Validation", "[openai]") {
    auto parser = aix::ParserFactory::createParser(aix::ProviderType::OpenAI);

    SECTION("Extract valid OpenAI models") {
        std::string rawJson = R"({
            "data": [
                {"id": "gpt-5.5"},
                {"id": "gpt-5.4-mini"}
            ]
        })";

        std::vector<std::string> result = parser->parseAvailableModels(rawJson);

        REQUIRE(result.size() == 2);
        REQUIRE(result[0] == "gpt-5.5");
        REQUIRE(result[1] == "gpt-5.4-mini");
    }
}
