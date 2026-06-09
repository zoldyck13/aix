#pragma once

#include <CLI/CLI.hpp>
#include <string>

namespace aix {
  
  struct ConfigOptions {
    std::string prompt = "";
    std::string sed_target = "";
  };

  class ArgParser {
    private:
      CLI::App aix{"aix"};


    public:
    
      ArgParser() = default;
      
      ConfigOptions ParseArgument(const int argc, char** argv);
  };   

}

