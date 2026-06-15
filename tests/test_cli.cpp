#include "../src/cli/arg_parser.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("CLI_TEST - ArgParser Line Extraction Validation", "[cli]") {
    aix::ArgParser parser;
    aix::ConfigOptions options;
    options.sed_start_line = 0;
    options.sed_end_line = 0;

    char *argv[] = {
        (char *)"aix",
        (char *)"--sed",
        (char *)"4,6p",
    };

    parser.ParseArgument(3, argv, options);

    REQUIRE(options.sed_start_line == 4);
    REQUIRE(options.sed_end_line == 6);
}
