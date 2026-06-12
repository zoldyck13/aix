#pragma once
#include <string>

namespace aix {
class AIRenderer {
  public:
    AIRenderer() = default;
    ~AIRenderer() = default;

    static void RenderMarkdown(const std::string &markdown_content);
};
} // namespace aix
