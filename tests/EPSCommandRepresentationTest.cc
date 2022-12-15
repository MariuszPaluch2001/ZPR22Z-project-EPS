//
// Created by kacper on 04.12.2022.
//
#include "EPSCommandRepresentation.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(EPSCommandRepresentation, testCreateNonProcessableCommand) {
  auto _ = NonProcessableCommand("");
}

TEST(EPSCommandRepresentation, testNonProcessableCommandStringForm) {
  auto np = NonProcessableCommand("abc");
  ASSERT_EQ(np.toString(), std::string("abc"));
}

TEST(EPSCommandRepresentation, testNonProcessableCommandEmptyStringForm) {
  auto np = NonProcessableCommand("");
  ASSERT_EQ(np.toString(), std::string(""));
}

TEST(EPSCommandRepresentation, testPrintingCommand) {
  auto np = NonProcessableCommand("abc");
  std::ostringstream oss;
  oss << np;
  ASSERT_EQ(oss.str(), "abc");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}