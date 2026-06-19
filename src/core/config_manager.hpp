#pragma once
#include <string>

namespace aix {
class ConfigManager {
  public:
    ConfigManager() = default;

    int SetAPI(const std::string &key_to_set);

    std::string GetAPI();

    void EnsureConfigExists();
};
} // namespace aix
