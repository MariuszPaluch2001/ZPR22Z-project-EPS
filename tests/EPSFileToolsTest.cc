//
// Created by mariusz on 06.11.22.
//
#include <gtest/gtest.h>
#include <sstream>

#include "EPSFileTools.h"
#include "GraphicCommands.h"

TEST(EPSFileToolsTest, ThrowExceptionGetHeaderTest) {
  std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                     "%%Pages: (atend)\n"
                     "%%BoundingBox: 0 0 302 302\n"
                     "%%EndComments\n";

  std::istringstream iss(data);
  EPSInFileStream EPSFs(iss);
  EPSFs.getHeader();
  ASSERT_ANY_THROW(EPSFs.getHeader());
}

TEST(EPSFileToolsTest, ThrowExceptionWhenHeaderDoesntHaveEndTag) {
  std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                     "%%Pages: (atend)\n"
                     "%%BoundingBox: 0 0 302 302\n";

  std::istringstream iss(data);
  EPSInFileStream EPSFs(iss);
  ASSERT_ANY_THROW(EPSFs.getHeader());
}

TEST(EPSFileToolsTest, TestReadingHeaderFromFile) {
  std::string data = "%!PS-Adobe-3.0\n"
                     "%%BoundingBox: 0 0 302 302\n"
                     "%%EndComments\n"
                     "67.47 72.08 m\n";

  std::istringstream iss(data);
  EPSInFileStream EPSFs(iss);
  Header h = EPSFs.getHeader();
  ASSERT_EQ(h.getHeaderString(),
            "%!PS-Adobe-3.0\n%%BoundingBox: 0 0 302 302\n%%EndComments\n");
}

TEST(EPSFileToolsTest, TestThrowingExceptionWhenResolutionNotFound) {
  ASSERT_ANY_THROW(Header h("Test\n%%EndComments\n"));
}

TEST(EPSFileToolsTest, TestResolutionSize) {
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
                     "%%EndComments\n";

  std::istringstream iss(data);
  EPSInFileStream EPSFs(iss);
  Header h = EPSFs.getHeader();
  Resolution r = h.getResolution();
  ASSERT_EQ(r.getX(), 302);
  ASSERT_EQ(r.getY(), 302);
}

TEST(EPSFileToolsTest, TestSettingResolutionInHeader) {
  Header h("%%BoundingBox: 0 0 302 302\n%%EndComments\n");
  Resolution r(100, 150);
  h.setResolution(r);
  ASSERT_EQ(h.getResolution().getX(), 100);
  ASSERT_EQ(h.getResolution().getY(), 150);
  ASSERT_EQ(h.getHeaderString(), "%%BoundingBox: 0 0 100 150\n%%EndComments\n");
}

TEST(EPSFileToolsTest, TestSettingResolutionInHeaderWithSecondResolution) {
    std::string data = "%!PS-Adobe-3.0\n"
                       "%%DocumentNeededResources: font Helvetica\n"
                       "%%+ font Helvetica-Bold\n"
                       "%%+ font Helvetica-Oblique\n"
                       "%%+ font Helvetica-BoldOblique\n"
                       "%%+ font Symbol\n"
                       "%%DocumentMedia: special 576 576 0 () ()\n"
                       "%%Title: R Graphics Output\n"
                       "%%Creator: R Software\n"
                       "%%Pages: (atend)\n"
                       "%%BoundingBox: 0 0 576 576\n"
                       "%%EndComments\n"
                       "%%BeginProlog\n";

    std::string data_expected = "%!PS-Adobe-3.0\n"
                       "%%DocumentNeededResources: font Helvetica\n"
                       "%%+ font Helvetica-Bold\n"
                       "%%+ font Helvetica-Oblique\n"
                       "%%+ font Helvetica-BoldOblique\n"
                       "%%+ font Symbol\n"
                       "%%DocumentMedia: special 100 150 0 () ()\n"
                       "%%Title: R Graphics Output\n"
                       "%%Creator: R Software\n"
                       "%%Pages: (atend)\n"
                       "%%BoundingBox: 0 0 100 150\n"
                       "%%EndComments\n"
                       "%%BeginProlog\n";


    Header h(data);
    Resolution r(100, 150);
    h.setResolution(r);
    ASSERT_EQ(h.getResolution().getX(), 100);
    ASSERT_EQ(h.getResolution().getY(), 150);
    ASSERT_EQ(h.getHeaderString(), data_expected);
}
TEST(EPSFileToolsTest, TestIsNextRelativeFalse) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "/m   { moveto } bind def\n"
                       "/l  { rlineto } bind def\n"
                       "\n"
                       "newpath\n"
                       "10.03 2.46 l\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_FALSE(EPSFs.isNextRelative());
}

TEST(EPSFileToolsTest, TestIsNextRelativeLeftOrientedCommand) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "10.03 2.46 l\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_TRUE(EPSFs.isNextRelative());
}

TEST(EPSFileToolsTest, TestIsNextRelativeRightOrientedCommand) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "164.72 100.9 lineto\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_TRUE(EPSFs.isNextRelative());
}

TEST(EPSFileToolsTest, TestIsNextAbsoluteFalse) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "10.03 2.46 l\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_FALSE(EPSFs.isNextAbsolute());
}

TEST(EPSFileToolsTest, TestIsNextAbsolutePointCommand) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "234.12 374.92 1.00 1.00 r p2\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_TRUE(EPSFs.isNextAbsolute());
}

TEST(EPSFileToolsTest, TestIsNextAbsoluteMoveCommand) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "67.47 72.08 m\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_TRUE(EPSFs.isNextAbsolute());
}

TEST(EPSFileToolsTest, TestIsNextUnprocessableFalse) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "10.03 2.46 l\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_FALSE(EPSFs.isNextUnprocessable());
}

TEST(EPSFileToolsTest, TestIsNextUnprocessableTrue) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "/m   { moveto } bind def\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_TRUE(EPSFs.isNextUnprocessable());
}

TEST(EPSFileToolsTest, TestGetRelativeCommandVarRightOrientedLineCommand){
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "10.03 2.46 l\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    RelativeCommandVar RelVar = EPSFs.getRelativeCommandVar();
    ASSERT_TRUE(std::get_if<RightOrientedLineCommand>(&RelVar));
}

TEST(EPSFileToolsTest, TestGetRelativeCommandVarLeftOrientedLineCommand){
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "10.03 2.46 lineto\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    RelativeCommandVar RelVar = EPSFs.getRelativeCommandVar();
    ASSERT_TRUE(std::get_if<LeftOrientedLineCommand>(&RelVar));
}

TEST(EPSFileToolsTest, TestGetRelativeCommandVarException){
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "/m   { moveto } bind def\n"
                       "/l  { rlineto } bind def\n"
                       "\n"
                       "newpath\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_ANY_THROW(EPSFs.getRelativeCommandVar());
}

TEST(EPSFileToolsTest, TestGetAbsoluteCommandVarPointCommand){
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "234.12 374.92 1.00 1.00 r p2\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    AbsoluteCommandVar AbsVar = EPSFs.getAbsoluteCommandVar();
    ASSERT_TRUE(std::get_if<PointCommand>(&AbsVar));
}

TEST(EPSFileToolsTest, TestGetAbsoluteCommandVarMoveCommand){
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "67.47 72.08 m\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    AbsoluteCommandVar AbsVar = EPSFs.getAbsoluteCommandVar();
    ASSERT_TRUE(std::get_if<MoveCommand>(&AbsVar));
}

TEST(EPSFileToolsTest, TestGetAbsoluteCommandVarException){
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "/m   { moveto } bind def\n"
                       "/l  { rlineto } bind def\n"
                       "\n"
                       "newpath\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_ANY_THROW(EPSFs.getAbsoluteCommandVar());
}

TEST(EPSFileToolsTest, TestGetNonProcessableCommand){
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "/m   { moveto } bind def\n"
                       "/l  { rlineto } bind def\n";
    std::istringstream iss(data);
    EPSInFileStream EPSFs(iss);
    EPSFs.getHeader();
    NonProcessableCommand c = EPSFs.getNonProcessableCommand();
    ASSERT_EQ(c.toString(), "/m   { moveto } bind def");
}

TEST(EPSFileToolsTest, TestCommandRead) {
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

  std::istringstream iss(data);
  Command *c;
  EPSInFileStream EPSFs(iss);
  EPSFs.getHeader();
  VariantCommand v = EPSFs.getCommand();
  ASSERT_TRUE(c = std::get_if<NonProcessableCommand>(&v));
  ASSERT_EQ(c->toString(), "/m   { moveto } bind def");
  v = EPSFs.getCommand();
  ASSERT_TRUE(c = std::get_if<NonProcessableCommand>(&v));
  ASSERT_EQ(c->toString(), "/l  { rlineto } bind def");
  v = EPSFs.getCommand();
  ASSERT_TRUE(c = std::get_if<NonProcessableCommand>(&v));
  ASSERT_EQ(c->toString(), "");
  v = EPSFs.getCommand();
  ASSERT_TRUE(c = std::get_if<NonProcessableCommand>(&v));
  ASSERT_EQ(c->toString(), "newpath");
  v = EPSFs.getCommand();
  ASSERT_TRUE(c = std::get_if<RightOrientedLineCommand>(
                  std::get_if<RelativeCommandVar>(&v)));
  ASSERT_EQ(c->toString(), "10.03 2.46 l");
  v = EPSFs.getCommand();
  ASSERT_TRUE(c = std::get_if<LeftOrientedLineCommand>(
                  std::get_if<RelativeCommandVar>(&v)));
  ASSERT_EQ(c->toString(), "164.72 100.9 lineto");
  v = EPSFs.getCommand();
}

TEST(EPSFileToolsTest, TestCommandReadWhenFileIsEnd) {
  std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                     "%%BoundingBox: 0 0 302 302\n"
                     "%%EndComments\n"
                     "/m   { moveto } bind def\n"
                     "/l  { rlineto } bind def\n"
                     "\n"
                     "newpath\n"
                     "10.03 2.46 l\n"
                     "164.72 100.9 lineto\n"
                     "234.12 374.92 1.00 1.00 r p2\n";
  std::istringstream iss(data);
  EPSInFileStream EPSFs(iss);
  EPSFs.getHeader();
  for (int i = 1; i < 8; i++)
    EPSFs.getCommand();
  ASSERT_ANY_THROW(EPSFs.getCommand());
}

TEST(EPSFileToolsTest, ThrowExceptionCommandReadWithoutHeaderRead) {
  std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                     "%%DocumentNeededResources: font Courier\n"
                     "%%Title: R Graphics Output\n"
                     "%%Creator: R Software\n"
                     "%%Pages: (atend)\n"
                     "%%BoundingBox: 0 0 302 302\n"
                     "%%EndComments\n"
                     "67.47 72.08 m\n"
                     "2.36 0.66 l";

  std::istringstream iss(data);
  EPSInFileStream EPSFs(iss);
  ASSERT_ANY_THROW(EPSFs.getCommand());
}

TEST(EPSFileToolsTest, EPSOutFileExceptionHeaderDoubleWrite) {
  std::string headerStr = "%!PS-Adobe-3.0 EPSF-3.0\n"
                          "%%BoundingBox: 0 0 302 302\n"
                          "%%EndComments\n";
  Header header(headerStr);
  std::ostringstream oss("");
  EPSOutFileStream EPSFs(oss);
  EPSFs.putHeader(header);
  ASSERT_ANY_THROW(EPSFs.putHeader(header));
}

TEST(EPSFileToolsTest, EPSOutFileExceptionWriteWithoutHeader) {
  std::ostringstream oss("");
  EPSOutFileStream EPSFs(oss);
  NonProcessableCommand c("testCommand");
  ASSERT_ANY_THROW(EPSFs.putCommand(c));
}

TEST(EPSFileToolsTest, EPSOutFileWriteHeader) {
  std::string headerStr = "%!PS-Adobe-3.0 EPSF-3.0\n"
                          "%%BoundingBox: 0 0 302 302\n"
                          "%%EndComments\n";

  Header header(headerStr);
  std::ostringstream oss("");
  EPSOutFileStream EPSFs(oss);
  EPSFs.putHeader(header);
  ASSERT_EQ(oss.str(), headerStr);
}

TEST(EPSFileToolsTest, EPSOutFileWriteHeaderAndCommands) {
  std::string headerStr = "%!PS-Adobe-3.0 EPSF-3.0\n"
                          "%%BoundingBox: 0 0 302 302\n"
                          "%%EndComments\n";

  std::string outputStr = "%!PS-Adobe-3.0 EPSF-3.0\n"
                          "%%BoundingBox: 0 0 302 302\n"
                          "%%EndComments\n"
                          "4.2 6.7 lineto\n"
                          "5.2 7.7 l\n"
                          "9.5 7.5 1 1 r p2\n";

  Header header(headerStr);
  NonProcessableCommand npc("test");
  LeftOrientedLineCommand lolc(CoordinateValue(4.2, 6.7));
  RightOrientedLineCommand rolc(CoordinateValue(5.2, 7.7));
  PointCommand pc(CoordinateValue(9.5, 7.5));
  std::ostringstream oss("");
  EPSOutFileStream EPSFs(oss);
  EPSFs.putHeader(header);
  EPSFs.putCommand(lolc);
  EPSFs.putCommand(rolc);
  EPSFs.putCommand(pc);
  ASSERT_EQ(oss.str(), outputStr);
}
TEST(EPSFileToolsTest, EPSOutFilePutAbsoluteBatch){
    std::string headerStr = "%!PS-Adobe-3.0 EPSF-3.0\n"
                            "%%BoundingBox: 0 0 302 302\n"
                            "%%EndComments\n";

    std::string outputStr = "%!PS-Adobe-3.0 EPSF-3.0\n"
                            "%%BoundingBox: 0 0 302 302\n"
                            "%%EndComments\n"
                            "2 2 1 1 r p2\n"
                            "3 3 m\n";

    Header header(headerStr);
    AbsoluteBatch batch;
    batch.emplace_back(PointCommand({2,2}));
    batch.emplace_back(MoveCommand({3,3}));
    std::ostringstream oss("");
    EPSOutFileStream EPSFs(oss);
    EPSFs.putHeader(header);
    EPSFs.putAbsoluteBatch(batch);
    ASSERT_EQ(oss.str(), outputStr);
}

TEST(EPSFileToolsTest, EPSOutFilePutRelativeBatch){
    std::string headerStr = "%!PS-Adobe-3.0 EPSF-3.0\n"
                            "%%BoundingBox: 0 0 302 302\n"
                            "%%EndComments\n";

    std::string outputStr = "%!PS-Adobe-3.0 EPSF-3.0\n"
                            "%%BoundingBox: 0 0 302 302\n"
                            "%%EndComments\n"
                            "2 2 l\n"
                            "3 3 lineto\n";

    Header header(headerStr);
    RelativeBatch batch;
    batch.emplace_back(RightOrientedLineCommand({2,2}));
    batch.emplace_back(LeftOrientedLineCommand({3,3}));
    std::ostringstream oss("");
    EPSOutFileStream EPSFs(oss);
    EPSFs.putHeader(header);
    EPSFs.putRelativeBatch(batch);
    ASSERT_EQ(oss.str(), outputStr);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
