#pragma once 
#include <utility>
#include <string>

namespace aix{
    std::pair<int, int> ExtractSedNumbers(const std::string& target);
    std::string ReadFileContents(const std::string& file_path, const int& start_line_number, const int& end_line_number);
}
