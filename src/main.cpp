// src/main.cpp
#include "cli/arg_parser.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    aix::ArgParser parser;
    aix::ConfigOptions options;

    try {
        parser.ParseArgument(argc, argv, options);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing arguments: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    std::cout << "aix executed successfully with specified configurations.\n";

    return EXIT_SUCCESS;
}
