#include "formatter.hpp"
#include <array>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace aix {
std::string AIRenderer::RenderMarkdown(const std::string &markdown_content) {
    if (markdown_content.empty())
        return "";

    std::string temp_filename = ".temp_markdown.md";
    std::ofstream temp_file(temp_filename);
    if (!temp_file) {
        std::cerr << "[Error]: Cannot create temporary file." << std::endl;
        return markdown_content;
    }
    temp_file << markdown_content;
    temp_file.close();

    std::string command = "CLICOLOR_FORCE=1 glow --width 80 " + temp_filename + " 2>&1";

    FILE *pipe = popen(command.c_str(), "r");

    if (!pipe) {
        std::cerr << "[Warning!!]: glow tool not installed." << std::endl;
        std::remove(temp_filename.c_str());
        return markdown_content;
    }

    std::string result;
    std::array<char, 128> buffer;
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    pclose(pipe);
    std::remove(temp_filename.c_str());

    return result;
}

} // namespace aix
