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

    try {
      aix.parse(argc, argv);
      std::tie(options.sed_start_line, options.sed_end_line) = FileSystem::ExtractSedNumbers(options.sed_target);
    } catch (const CLI::ParseError &e) {
      aix.exit(e);
    }

    return options;
  }
}
