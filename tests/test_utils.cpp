#include "../src/utils/file_system.hpp"
#include <catch2/catch_test_macros.hpp>
#include <fstream>

TEST_CASE("Utils_TEST - ReadFileContent Extraction Validation", "[file_system]") {
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
    REQUIRE_FALSE(context.empty());
    REQUIRE(context == expected_output);
}
