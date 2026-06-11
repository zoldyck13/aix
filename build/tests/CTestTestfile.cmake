# CMake generated Testfile for 
# Source directory: /home/mohammed/aix/tests
# Build directory: /home/mohammed/aix/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(CLI_Tests "/home/mohammed/aix/build/tests/cli_test_runner")
set_tests_properties(CLI_Tests PROPERTIES  _BACKTRACE_TRIPLES "/home/mohammed/aix/tests/CMakeLists.txt;11;add_test;/home/mohammed/aix/tests/CMakeLists.txt;0;")
add_test(Network_Tests "/home/mohammed/aix/build/tests/network_test_runner")
set_tests_properties(Network_Tests PROPERTIES  _BACKTRACE_TRIPLES "/home/mohammed/aix/tests/CMakeLists.txt;20;add_test;/home/mohammed/aix/tests/CMakeLists.txt;0;")
add_test(Utils_Tests "/home/mohammed/aix/build/tests/utils_test_runner")
set_tests_properties(Utils_Tests PROPERTIES  _BACKTRACE_TRIPLES "/home/mohammed/aix/tests/CMakeLists.txt;30;add_test;/home/mohammed/aix/tests/CMakeLists.txt;0;")
