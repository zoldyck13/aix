#include "arg_parser.hpp"
#include "CLI/CLI.hpp"
#include <string>
#include <tuple>
#include "../utils/file_system.hpp"

namespace aix {
  ConfigOptions ArgParser::ParseArgument(const int argc, char** argv, ConfigOptions& options) {

    if (aix.get_option_no_throw("-p") == nullptr) {
      aix.add_option("-p", options.prompt, "Prompt message");
    }

    if (aix.get_option_no_throw("--sed") == nullptr) {
      aix.add_option("--sed", options.sed_target, "Select lines inside files by numbers");
    }
    
    if (aix.get_option_no_throw("--file-path") == nullptr) {
      aix.add_option("--file-path", options.file_path, "Location of the file");
    }

    try {
      aix.parse(argc, argv);
      std::tie(options.sed_start_line, options.sed_end_line) = aix::ExtractSedNumbers(options.sed_target);
    } catch (const CLI::ParseError &e) {
      aix.exit(e);
    }

    return options;
  }
}
