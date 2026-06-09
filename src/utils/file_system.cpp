#include "file_system.hpp"
#include <sstream>
#include <string>
#include <cstdlib>

namespace FileSystem {
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
}

