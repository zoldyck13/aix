#define CATCH_CONFIG_MAIN
#include "../src/cli/formatter.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unistd.h>

bool is_terminal_interactive() {
    return isatty(STDOUT_FILENO);
}

TEST_CASE("AIRenderer - RenderMarkdown Basic Formatting", "[formatter]") {
    std::string input = "# Hello world\nThis is **bold** text.";

    std::string output = aix::AIRenderer::RenderMarkdown(input);

    if (!is_terminal_interactive()) {
        SUCCEED("SKipping strcit TTY rendering check in non-interactive envirmonet (CI)");
        return;
    }

    REQUIRE_FALSE(output.empty());
    INFO("Actual Glow Output: " << output);
    REQUIRE(output.find("This is") != std::string::npos);
    REQUIRE(output.find("bold") != std::string::npos);
}

TEST_CASE("AIRenderer - RenderMarkdown ANSI Color Code Validation", "[formatter]") {
    std::string input = "# Title";

    std::string output = aix::AIRenderer::RenderMarkdown(input);

    if (!is_terminal_interactive()) {
        SUCCEED("Skipping ANSI color validation non-interactive environment (CI)");
        return;
    }

    bool has_ansi_colors =
        (output.find("\033[") != std::string::npos) || (output.find("\x1b[") != std::string::npos);

    REQUIRE(has_ansi_colors == true);
}

TEST_CASE("AIRenderer - Empty Input Handling", "[formatter]") {
    std::string input = "";
    std::string output = aix::AIRenderer::RenderMarkdown(input);

    if (!is_terminal_interactive()) {
        SUCCEED("Skipping Empty input handling validation in non-interactive environment (CI)");
        return;
    }

    REQUIRE(output.empty());

    SUCCEED("Renderer handled empty input without crashing");
}
