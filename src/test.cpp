#include "arg_parser.hpp"
#include "file_system.hpp"

int main(int argc, char** argv) {
  //Testing ParseArgument() passing the options to ConfigOptions.
  aix::ArgParser parser;
  aix::ConfigOptions options;
  parser.ParseArgument(argc, argv, options);
  
  //Testing ReadFileContents
  std::string content = aix::ReadFileContents(options.file_path, options.sed_start_line, options.sed_end_line);


  std::cout << content << std::endl;
  return 0;
}
