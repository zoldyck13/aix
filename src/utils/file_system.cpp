#include "file_system.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>


namespace aix {
  std::pair<int, int> ExtractSedNumbers(const std::string &target) {
      std::stringstream ss(target);
      std::string first_str, second_str = "";
      if (std::getline(ss, first_str, ',')) {
        if (std::getline(ss, second_str, 'p')){
          int sed_start_line = std::stoi(first_str);
          int sed_end_line = std::stoi(second_str);

          return {sed_start_line, sed_end_line};
        }
      }
    return {EXIT_FAILURE, EXIT_FAILURE};
  }

  std::string ReadFileContents(const std::string& file_path, const int &start_line_number, const int &end_line_number) {
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open()) {
      std::cerr << "Error: Could not open " << file_path << std::endl;
      exit(EXIT_FAILURE);
    }

    std::string current_line;
    std::stringstream line_buffer;
    int current_line_number = 0;

    while (std::getline(file_stream, current_line)) {
      current_line_number++;

      if (current_line_number < start_line_number) continue;
      if(current_line_number > end_line_number) break;

      line_buffer << current_line << "\n";
    }
    file_stream.close();
    std::string isolated_text = line_buffer.str();
    
    return isolated_text;
  }

}

