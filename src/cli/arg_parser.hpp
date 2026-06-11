#pragma once

#include <CLI/CLI.hpp>
#include <string>

namespace aix {
  
  struct ConfigOptions {
    std::string prompt = "";
    std::string sed_target = "";
    std::string file_path = "";
    std::string file_content = "";
    int sed_start_line, sed_end_line = 0;
  };

  class ArgParser {
    private:
      CLI::App aix{"aix"};


    public:
    
      ArgParser() = default;
      
      ConfigOptions ParseArgument(const int argc, char** argv, ConfigOptions& options);
  };   

}

