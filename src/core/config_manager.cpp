#include "config_manager.hpp"
#include "utils/file_system.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <toml++/impl/parse_error.hpp>
#include <toml++/toml.h>

namespace aix {

void ConfigManager::EnsureConfigExists() {
    std::string path = aix::GetConfigPath();

    if (!std::filesystem::exists(path)) {
        std::ofstream file(path);
        if (file.is_open()) {
            file << "[api]\n";
            file << "provider = \"gemini\"\n";
            file << "api_key = \"\"\n\n";
            file << "[model]\n";
            file << "temperature = 0.7\n";
            file.close();
        }
    }
}

int ConfigManager::SetAPI(const std::string &key_to_set) {

    if (key_to_set.empty()) {
        std::cerr << "please pass API Key through enviremont variable: aix --key-env MYAPI\n";
        return EXIT_FAILURE;
    }

    this->EnsureConfigExists();

    try {
        auto config = toml::parse_file(aix::GetConfigPath());

        if (auto api_table = config["api"].as_table()) {
            api_table->insert_or_assign("api_key", toml::value<std::string>(key_to_set));
        }

        std::ofstream file(aix::GetConfigPath());
        if (file.is_open()) {
            file << config;
            file.close();
        } else {
            std::cerr << "Failed to open file for writing.\n";
        }

    } catch (const toml::parse_error &e) {
        std::cerr << "Paring failed: " << e << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

std::string ConfigManager::GetAPI() {
    this->EnsureConfigExists();

    try {
        auto config = toml::parse_file(aix::GetConfigPath());

        std::string api_key = config["api"]["api_key"].ref<std::string>();

        return api_key;
    } catch (const toml::parse_error &e) {
        std::cerr << "Parsing failed: " << e << "\n";
        return "";
    }
}

} // namespace aix
