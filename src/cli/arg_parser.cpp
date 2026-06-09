#include "arg_parser.hpp"
#include "CLI/CLI.hpp"
#include <string>


namespace aix {

  std::string ArgParser::GetContentText(const int argc, char** argv) {
    std::string temp_str = "";

    if (aix.get_option_no_throw("-m") == nullptr) {
      aix.add_option("-p", temp_str, "Prompt message");
    }

    try {
      aix.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
      return std::to_string(aix.exit(e));
    }

    return temp_str;
  }

}
