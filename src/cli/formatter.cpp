#include "formatter.hpp"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace aix {
void AIRenderer::RenderMarkdown(const std::string &markdown_conten) {

    FILE *pipe = popen("glow -s dracula -", "w");

    if (!pipe) {
        std::cerr << "[Warning!!]: glow tool not installed." << std::endl;
        std::cout << markdown_conten << std::endl;
        return;
    }

    fwrite(markdown_conten.c_str(), sizeof(char), markdown_conten.size(), pipe);

    pclose(pipe);
}

} // namespace aix
