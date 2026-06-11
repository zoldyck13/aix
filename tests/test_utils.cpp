#include "../src/utils/file_system.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::string test_file = "test_dummy.txt";
    std::ofstream out(test_file);

    out << "Line 1\n";
    out << "Line 2\n";
    out << "Line 3\n";
    out << "Line 4\n";
    out << "Line 5: Hello\n";
    out << "Line 6: World\n";
    out << "Line 7\n";
    out.close();

    int start_line = 5;
    int end_line = 6;

    std::string context = aix::ReadFileContents(test_file, start_line, end_line);

    std::remove(test_file.c_str());

    std::string expected_output = "Line 5: Hello\nLine 6: World\n";

    if (context != expected_output) {
        std::cerr << "Test Failed!\n";
        std::cerr << "Expected:\n" << expected_output;
        std::cerr << "Got:\n" << context;
        return EXIT_FAILURE;
    }

    std::cout << "Utils FileSystem Test Passed Successfully!\n";
    return EXIT_SUCCESS;
}