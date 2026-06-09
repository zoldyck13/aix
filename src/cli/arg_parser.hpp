#pragma once

#include <CLI/CLI.hpp>
#include <string.h>

namespace aix {
  class ArgParser {
    private:
      CLI::App aix{"aix"};


    public:
    
      ArgParser() = default;
    
      std::string GetContentText(const int argc, char** argv);
  };   

}

