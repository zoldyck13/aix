#include "../src/cli/arg_parser.hpp"
#include <iostream>
#include <cstdlib>
#include <execution>

int main() {
    aix::ArgParser parser;
    aix::ConfigOptions options;

    char* argv[] = {
        (char*)"aix",
        (char*)"--sed",                    
        (char*)"4,6p",                     
    };

    try {
        parser.ParseArgument(3, argv, options);
    } catch (const std::exception& e) {
        std::cerr << "Test Failed: CLI parser threw an unexpected exception: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    if (options.sed_start_line != 4 || options.sed_end_line != 6) {
        std::cerr << "Test Failed: Mismatch in parsed lines! Expected start=4, end=6. Got start=" 
                  << options.sed_start_line << ", end=" << options.sed_end_line << "\n";
        return EXIT_FAILURE;
    }

    std::cout << "CLI Parsing Test Passed Successfully!\n";
    return EXIT_SUCCESS;
}
