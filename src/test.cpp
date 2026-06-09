#include "arg_parser.hpp"


int main(int argc, char** argv) {
  aix::ArgParser parser;
  aix::ConfigOptions options;

  parser.ParseArgument(argc, argv, options);

  std::cout << "sed values: " << options.sed_start_line << "," << options.sed_end_line << std::endl;
  return 0;
}
