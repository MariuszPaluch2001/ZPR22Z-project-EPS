include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(Scalar2DRepresentationTest Scalar2DRepresentationTest.cc)

target_link_libraries(Scalar2DRepresentationTest
 PRIVATE
  GTest::GTest
  Scalar2DRepresentation)

add_test(Scalar2DRepresentationTest Scalar2DRepresentationTest)
