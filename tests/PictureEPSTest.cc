//
// Created by mariusz on 06.11.22.
//

#include <gtest/gtest.h>
#include "PictureEPS.h"
TEST(PictureEPSTest, ThrowExceptionConstructorTest)
{
    bool exceptionThrown = false;
    try
    {
        PictureEPS p("eee", 123);
    }
    catch(const std::exception & e) // special exception type
    {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

