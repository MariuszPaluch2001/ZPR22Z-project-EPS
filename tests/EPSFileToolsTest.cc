//
// Created by mariusz on 06.11.22.
//

#include <gtest/gtest.h>
#include "EPSFileTools.h"
#include "GraphicCommands.h"
#include <sstream>
TEST(EPSFileToolsTest, ThrowExceptionGetHeaderTest)
{
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%Pages: (atend)\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n";

    std::istringstream iss (data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_ANY_THROW(EPSFs.getHeader());
}

TEST(EPSFileToolsTest, TestReadingHeaderFromFile){
    std::string data = "%!PS-Adobe-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "67.47 72.08 m\n";

    std::istringstream iss (data);
    EPSInFileStream EPSFs(iss);
    Header h = EPSFs.getHeader();
    ASSERT_EQ(h.getHeaderString(), "%!PS-Adobe-3.0\n%%BoundingBox: 0 0 302 302\n%%EndComments\n");

}

TEST(EPSFileToolsTest, TestResolutionSize){
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%DocumentNeededResources: font Courier\n"
                       "%%+ font Courier-Bold\n"
                       "%%+ font Courier-Oblique\n"
                       "%%+ font Courier-BoldOblique\n"
                       "%%+ font Symbol\n"
                       "%%Title: R Graphics Output\n"
                       "%%Creator: R Software\n"
                       "%%Pages: (atend)\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments";

    std::istringstream iss (data);
    EPSInFileStream EPSFs(iss);
    Header h = EPSFs.getHeader();
    Resolution r = h.getResolution();
    ASSERT_EQ(r.getX(), 302);
    ASSERT_EQ(r.getY(), 302);

}

TEST(EPSFileToolsTest, TestSettingResolutionInHeader){
    Header h("");
    Resolution r(100, 150);
    h.setResolution(r);
    ASSERT_EQ(h.getResolution().getX(), 100);
    ASSERT_EQ(h.getResolution().getY(), 150);

}

TEST(EPSFileToolsTest, TestCommandRead){
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%DocumentNeededResources: font Courier\n"
                       "%%+ font Courier-Bold\n"
                       "%%+ font Courier-Oblique\n"
                       "%%+ font Courier-BoldOblique\n"
                       "%%+ font Symbol\n"
                       "%%Title: R Graphics Output\n"
                       "%%Creator: R Software\n"
                       "%%Pages: (atend)\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "/m   { moveto } bind def\n"
                       "/l  { rlineto } bind def\n"
                       "\n"
                       "newpath\n"
                       "10.03 2.46 l\n"
                       "164.72 100.9 lineto\n"
                       "234.12 374.92 1.00 1.00 r p2\n";
    std::istringstream iss (data);
    Command* c;
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    variantCommand v = EPSFs.getCommand();
    ASSERT_TRUE(c = std::get_if<NonProcessableCommand>(&v));
    ASSERT_EQ(c->toString(), "/m   { moveto } bind def\n");
    v = EPSFs.getCommand();
    ASSERT_TRUE(c = std::get_if<NonProcessableCommand>(&v));
    ASSERT_EQ(c->toString(), "/l  { rlineto } bind def\n");
    v = EPSFs.getCommand();
    ASSERT_TRUE(c = std::get_if<NonProcessableCommand>(&v));
    ASSERT_EQ(c->toString(), "\n");
    v = EPSFs.getCommand();
    ASSERT_TRUE(c = std::get_if<NonProcessableCommand>(&v));
    ASSERT_EQ(c->toString(), "newpath\n");
    v = EPSFs.getCommand();
    ASSERT_TRUE(c = std::get_if<RightOrientedLineCommand>(&v));
    ASSERT_EQ(c->toString(), "10.03 2.46 l\n");
    v = EPSFs.getCommand();
    ASSERT_TRUE(c = std::get_if<LeftOrientedLineCommand>(&v));
    ASSERT_EQ(c->toString(), "164.72 100.9 lineto\n");
    v = EPSFs.getCommand();
    ASSERT_TRUE(c = std::get_if<PointCommand>(&v));
    ASSERT_EQ(c->toString(), "234.12 374.92 1.00 1.00 r p2\n");

}

TEST(EPSFileToolsTest, ThrowExceptionCommandReadWithoutHeaderRead)
{
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%DocumentNeededResources: font Courier\n"
                       "%%Title: R Graphics Output\n"
                       "%%Creator: R Software\n"
                       "%%Pages: (atend)\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "67.47 72.08 m\n"
                       "2.36 0.66 l";

    std::istringstream iss (data);
    EPSInFileStream EPSFs(iss);
    ASSERT_ANY_THROW(EPSFs.getCommand());
}

TEST(EPSFileToolsTest, EPSOutFile)
{

}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

