//
// Created by mariusz on 06.11.22.
//

#include <gtest/gtest.h>
#include "EPSFileTools.h"
#include "GraphicCommands.h"

TEST(EPSFileToolsTest, ThrowExceptionGetHeaderTest)
{
    EPSInFileStream EPSFs("test1.eps"); //Filename here is irrelevant
    bool exceptionThrown = false;

    EPSFs.getHeader();
    try{
        EPSFs.getHeader();
    }
    catch(const std::exception & e)
    {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

}

TEST(EPSFileToolsTest, TestReadingHeaderFromFile){
    EPSInFileStream EPSFs("test1.eps");
    Header h = EPSFs.getHeader();
    ASSERT_EQ(h.getHeaderString(), "\n%!PS-Adobe-3.0\n%%BoundingBox: 0 0 576 600");

}

TEST(EPSFileToolsTest, TestResolutionSize){
    EPSInFileStream EPSFs("test1.eps");
    Header h = EPSFs.getHeader();
    Resolution r = h.getResolution();
    ASSERT_EQ(r.getX(), 576);
    ASSERT_EQ(r.getY(), 600);

}

TEST(EPSFileToolsTest, TestSettingResolutionInHeader){
    Header h("");
    Resolution r(100, 150);
    h.setResolution(r);
    ASSERT_EQ(h.getResolution().getX(), 100);
    ASSERT_EQ(h.getResolution().getY(), 150);

}

TEST(EPSFileToolsTest, TestCommandRead){
    cPtr ptr;
    std::unique_ptr<GraphicCommand> gCmd;
    EPSInFileStream e("test2.eps");
    e.getHeader();
    e >> ptr;
    ASSERT_EQ(ptr->toString(), "newpath");
    e >> ptr;
    ASSERT_EQ(ptr->toString(), "m");
    e >> ptr;
    gCmd = (std::unique_ptr<GraphicCommand> &&) std::move(ptr);
    ASSERT_EQ(gCmd->toString(), "LeftOrientedLineCommand");
    ASSERT_EQ(gCmd->getMovePoint().getX(), 10.03);
    ASSERT_EQ(gCmd->getMovePoint().getY(), 2.46);
    e >> ptr;
    gCmd = (std::unique_ptr<GraphicCommand> &&) std::move(ptr);
    ASSERT_EQ(gCmd->toString(), "PointCommand");
    ASSERT_EQ(gCmd->getMovePoint().getX(), 387.19);
    ASSERT_EQ(gCmd->getMovePoint().getY(), 298.76);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

