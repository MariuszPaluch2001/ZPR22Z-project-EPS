# CMake generated Testfile for 
# Source directory: /home/kacper/Pulpit/zpr_eps/tests
# Build directory: /home/kacper/Pulpit/zpr_eps/cmake-build-debug-coverage/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(EPSFileToolsTest "EPSFileToolsTest")
set_tests_properties(EPSFileToolsTest PROPERTIES  _BACKTRACE_TRIPLES "/home/kacper/Pulpit/zpr_eps/tests/CMakeLists.txt;21;add_test;/home/kacper/Pulpit/zpr_eps/tests/CMakeLists.txt;0;")
add_test(Scalar2DRepresentationTest "Scalar2DRepresentationTest")
set_tests_properties(Scalar2DRepresentationTest PROPERTIES  _BACKTRACE_TRIPLES "/home/kacper/Pulpit/zpr_eps/tests/CMakeLists.txt;52;add_test;/home/kacper/Pulpit/zpr_eps/tests/CMakeLists.txt;0;")
add_test(GraphicCommandTest "GraphicCommandTest")
set_tests_properties(GraphicCommandTest PROPERTIES  _BACKTRACE_TRIPLES "/home/kacper/Pulpit/zpr_eps/tests/CMakeLists.txt;53;add_test;/home/kacper/Pulpit/zpr_eps/tests/CMakeLists.txt;0;")
add_test(EPSCommandRepresentationTest "EPSCommandRepresentationTest")
set_tests_properties(EPSCommandRepresentationTest PROPERTIES  _BACKTRACE_TRIPLES "/home/kacper/Pulpit/zpr_eps/tests/CMakeLists.txt;54;add_test;/home/kacper/Pulpit/zpr_eps/tests/CMakeLists.txt;0;")
add_test(AlgorithmTest "AlgorithmTest")
set_tests_properties(AlgorithmTest PROPERTIES  _BACKTRACE_TRIPLES "/home/kacper/Pulpit/zpr_eps/tests/CMakeLists.txt;55;add_test;/home/kacper/Pulpit/zpr_eps/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
