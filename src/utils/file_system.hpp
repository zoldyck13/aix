#pragma once
#include <future>
#include <string>
#include <utility>

namespace aix {
std::pair<int, int> ExtractSedNumbers(const std::string &target);
std::string ReadFileContents(const std::string &file_path, const int &start_line_number,
                             const int &end_line_number);

void RunSpinner(const std::future<std::string> &future_reslut);
} // namespace aix
