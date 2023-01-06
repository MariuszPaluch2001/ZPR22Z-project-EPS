include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(EPSFileToolsTest EPSFileToolsTest.cc)

target_link_libraries(EPSFileToolsTest
        PRIVATE
        GTest::GTest
        EPSFileTools
        Scalar2DRepresentation
        EPSCommands)

add_test(EPSFileToolsTest EPSFileToolsTest)

add_executable(Scalar2DRepresentationTest Scalar2DRepresentationTest.cc)
add_executable(GraphicCommandTest GraphicCommandTest.cc)
add_executable(EPSCommandRepresentationTest EPSCommandRepresentationTest.cc)
add_executable(AlgorithmTest AlgorithmTest.cc)
target_link_libraries(Scalar2DRepresentationTest
 PRIVATE
  GTest::GTest
  Scalar2DRepresentation)


target_link_libraries(GraphicCommandTest
        PRIVATE
        GTest::GTest
        EPSCommands
        Scalar2DRepresentation)

target_link_libraries(EPSCommandRepresentationTest
        PRIVATE
        GTest::GTest
        EPSCommands
        Scalar2DRepresentation)


target_link_libraries(AlgorithmTest
        PRIVATE
        GTest::GTest
        EPSCommands
        Scalar2DRepresentation)

add_test(Scalar2DRepresentationTest Scalar2DRepresentationTest)
add_test(GraphicCommandTest GraphicCommandTest)
add_test(EPSCommandRepresentationTest EPSCommandRepresentationTest)
add_test(AlgorithmTest AlgorithmTest)
