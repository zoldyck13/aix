#define CATCH_CONFIG_MAIN
#include "../src/cli/formatter.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("AIRenderer - RenderMarkdown Basic Formatting", "[formatter]") {
    std::string input = "# Hello world\nThis is **bold** text.";

    std::string output = aix::AIRenderer::RenderMarkdown(input);

    REQUIRE_FALSE(output.empty());
    INFO("Actual Glow Output: " << output);
    REQUIRE(output.find("This is") != std::string::npos);
    REQUIRE(output.find("bold") != std::string::npos);
}

TEST_CASE("AIRenderer - RenderMarkdown ANSI Color Code Validation", "[formatter]") {
    std::string input = "# Title";

    std::string output = aix::AIRenderer::RenderMarkdown(input);

    bool has_ansi_colors =
        (output.find("\033[") != std::string::npos) || (output.find("\x1b[") != std::string::npos);

    REQUIRE(has_ansi_colors == true);
}

TEST_CASE("AIRenderer - Empty Input Handling", "[formatter]") {
    std::string input = "";
    std::string output = aix::AIRenderer::RenderMarkdown(input);

    REQUIRE(output.empty());

    SUCCEED("Renderer handled empty input without crashing");
}
