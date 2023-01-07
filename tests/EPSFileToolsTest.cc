//
// Created by mariusz on 06.11.22.
//
#include <gtest/gtest.h>
#include <sstream>

#include "EPSFileTools.hpp"
#include "GraphicCommands.h"

TEST(EPSFileToolsTest, ThrowExceptionGetHeaderTest) {
  std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                     "%%Pages: (atend)\n"
                     "%%BoundingBox: 0 0 302 302\n"
                     "%%EndComments\n";

  std::istringstream iss(data);
  EPSInFile EPSFs(iss);
  EPSFs.getHeader();
  ASSERT_ANY_THROW(EPSFs.getHeader());
}

TEST(EPSFileToolsTest, ThrowExceptionWhenHeaderDoesntHaveEndTag) {
  std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                     "%%Pages: (atend)\n"
                     "%%BoundingBox: 0 0 302 302\n";

  std::istringstream iss(data);
  EPSInFile EPSFs(iss);
  ASSERT_ANY_THROW(EPSFs.getHeader());
}

TEST(EPSFileToolsTest, TestReadingHeaderFromFile) {
  std::string data = "%!PS-Adobe-3.0\n"
                     "%%BoundingBox: 0 0 302 302\n"
                     "%%EndComments\n"
                     "67.47 72.08 m\n";

  std::istringstream iss(data);
  EPSInFile EPSFs(iss);
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
  EPSInFile EPSFs(iss);
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
    EPSInFile EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_FALSE(EPSFs.isNextRelative());
}

TEST(EPSFileToolsTest, TestIsNextRelativeLeftCommand) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "10.03 2.46 l\n";
    std::istringstream iss(data);
    EPSInFile EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_TRUE(EPSFs.isNextRelative());
}

TEST(EPSFileToolsTest, TestIsNextRelativeRightCommand) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "164.72 100.9 lineto\n";
    std::istringstream iss(data);
    EPSInFile EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_TRUE(EPSFs.isNextRelative());
}

TEST(EPSFileToolsTest, TestIsNextAbsoluteFalse) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "10.03 2.46 l\n";
    std::istringstream iss(data);
    EPSInFile EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_FALSE(EPSFs.isNextAbsolute());
}

TEST(EPSFileToolsTest, TestIsNextAbsolutePointCommand) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "234.12 374.92 1.00 1.00 r p2\n";
    std::istringstream iss(data);
    EPSInFile EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_TRUE(EPSFs.isNextAbsolute());
}

TEST(EPSFileToolsTest, TestIsNextAbsoluteMoveCommand) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "67.47 72.08 m\n";
    std::istringstream iss(data);
    EPSInFile EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_TRUE(EPSFs.isNextAbsolute());
}

TEST(EPSFileToolsTest, TestIsNextUnprocessableFalse) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "10.03 2.46 l\n";
    std::istringstream iss(data);
    EPSInFile EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_FALSE(EPSFs.isNextUnprocessable());
}

TEST(EPSFileToolsTest, TestIsNextUnprocessableTrue) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "/m   { moveto } bind def\n";
    std::istringstream iss(data);
    EPSInFile EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_TRUE(EPSFs.isNextUnprocessable());
}

TEST(EPSFileToolsTest, TestGetRelativeCommandVarRightLineCommand){
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "10.03 2.46 l\n";
    std::istringstream iss(data);
    EPSInFile EPSFs(iss);
    EPSFs.getHeader();
    RelativeCommandVar RelVar = EPSFs.getRelativeCommandVar();
    ASSERT_TRUE(std::get_if<RightLineCommand>(&RelVar));
}

TEST(EPSFileToolsTest, TestGetRelativeCommandVarLeftLineCommand){
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "10.03 2.46 lineto\n";
    std::istringstream iss(data);
    EPSInFile EPSFs(iss);
    EPSFs.getHeader();
    RelativeCommandVar RelVar = EPSFs.getRelativeCommandVar();
    ASSERT_TRUE(std::get_if<LeftLineCommand>(&RelVar));
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
    EPSInFile EPSFs(iss);
    EPSFs.getHeader();
    ASSERT_ANY_THROW(EPSFs.getRelativeCommandVar());
}

TEST(EPSFileToolsTest, TestGetAbsoluteCommandVarPointCommand){
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "234.12 374.92 1.00 1.00 r p2\n";
    std::istringstream iss(data);
    EPSInFile EPSFs(iss);
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
    EPSInFile EPSFs(iss);
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
    EPSInFile EPSFs(iss);
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
    EPSInFile EPSFs(iss);
    EPSFs.getHeader();
    NonProcessableCommand c = EPSFs.getNonProcessableCommand();
    ASSERT_EQ(c.toString(), "/m   { moveto } bind def");
}

TEST(EPSFileToolsTest, TestGetCommandsFunctions) {
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
  EPSInFile EPSFs(iss);
  EPSFs.getHeader();
  NonProcessableCommand npc = EPSFs.getNonProcessableCommand();
  ASSERT_EQ(npc.toString(), "/m   { moveto } bind def");
  npc = EPSFs.getNonProcessableCommand();
  ASSERT_EQ(npc.toString(), "/l  { rlineto } bind def");
  npc = EPSFs.getNonProcessableCommand();
  ASSERT_EQ(npc.toString(), "");
  npc = EPSFs.getNonProcessableCommand();
  ASSERT_EQ(npc.toString(), "newpath");
  RelativeCommandVar rcv = EPSFs.getRelativeCommandVar();
  RightLineCommand* rolc = std::get_if<RightLineCommand>(&rcv);
  ASSERT_TRUE(rolc);
  ASSERT_EQ(rolc->toString(), "10.03 2.46 l");
  rcv = EPSFs.getRelativeCommandVar();
  LeftLineCommand* lolc = std::get_if<LeftLineCommand>(&rcv);
  ASSERT_TRUE(lolc);
  ASSERT_EQ(lolc->toString(), "164.72 100.9 lineto");
  AbsoluteCommandVar acv = EPSFs.getAbsoluteCommandVar();
  PointCommand* pc = std::get_if<PointCommand>(&acv);
  ASSERT_TRUE(pc);
  ASSERT_EQ(pc->toString(), "234.12 374.92 1 1 r p2");
}

TEST(EPSFileToolsTest, TestGetRelativeCommandVarWhenFileIsEnd) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "5.52 1.50 l\n"
                       "164.72 100.90 lineto\n";

    std::istringstream iss(data);
    EPSInFile EPSFs(iss);
    EPSFs.getHeader();
    for (int i = 1; i < 3; i++)
        EPSFs.getRelativeCommandVar();
    ASSERT_ANY_THROW(EPSFs.getRelativeCommandVar());
}

TEST(EPSFileToolsTest, TestGetAbsoluteCommandVarWhenFileIsEnd) {
    std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                       "%%BoundingBox: 0 0 302 302\n"
                       "%%EndComments\n"
                       "234.12 374.92 1.00 1.00 r p2\n"
                       "67.47 72.08 m\n";

    std::istringstream iss(data);
    EPSInFile EPSFs(iss);
    EPSFs.getHeader();
    for (int i = 1; i < 3; i++)
        EPSFs.getAbsoluteCommandVar();
    ASSERT_ANY_THROW(EPSFs.getAbsoluteCommandVar());
}

TEST(EPSFileToolsTest, TestGetNonProcessableCommandWhenFileIsEnd) {
  std::string data = "%!PS-Adobe-3.0 EPSF-3.0\n"
                     "%%BoundingBox: 0 0 302 302\n"
                     "%%EndComments\n"
                     "/m   { moveto } bind def\n"
                     "/l  { rlineto } bind def\n";

  std::istringstream iss(data);
  EPSInFile EPSFs(iss);
  EPSFs.getHeader();
  for (int i = 1; i < 3; i++)
    EPSFs.getNonProcessableCommand();
  ASSERT_ANY_THROW(EPSFs.getNonProcessableCommand());
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
                     "2.36 0.66 l\n";

  std::istringstream iss(data);
  EPSInFile EPSFs(iss);
  ASSERT_ANY_THROW(EPSFs.getAbsoluteCommandVar());
}

TEST(EPSFileToolsTest, EPSOutFileExceptionHeaderDoubleWrite) {
  std::string headerStr = "%!PS-Adobe-3.0 EPSF-3.0\n"
                          "%%BoundingBox: 0 0 302 302\n"
                          "%%EndComments\n";
  Header header(headerStr);
  std::ostringstream oss("");
  EPSOutFile EPSFs(oss);
  EPSFs.putHeader(header);
  ASSERT_ANY_THROW(EPSFs.putHeader(header));
}

TEST(EPSFileToolsTest, EPSOutFileExceptionWriteWithoutHeader) {
  std::ostringstream oss("");
  EPSOutFile EPSFs(oss);
  NonProcessableCommand c("testCommand");
  ASSERT_ANY_THROW(EPSFs.putCommand(c));
}

TEST(EPSFileToolsTest, EPSOutFileWriteHeader) {
  std::string headerStr = "%!PS-Adobe-3.0 EPSF-3.0\n"
                          "%%BoundingBox: 0 0 302 302\n"
                          "%%EndComments\n";

  Header header(headerStr);
  std::ostringstream oss("");
  EPSOutFile EPSFs(oss);
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
  LeftLineCommand lolc(CoordinateValue(4.2, 6.7));
  RightLineCommand rolc(CoordinateValue(5.2, 7.7));
  PointCommand pc(CoordinateValue(9.5, 7.5));
  std::ostringstream oss("");
  EPSOutFile EPSFs(oss);
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
    EPSOutFile EPSFs(oss);
    EPSFs.putHeader(header);
    EPSFs.putBatch(batch);
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
    batch.emplace_back(RightLineCommand({2,2}));
    batch.emplace_back(LeftLineCommand({3,3}));
    std::ostringstream oss("");
    EPSOutFile EPSFs(oss);
    EPSFs.putHeader(header);
    EPSFs.putBatch(batch);
    ASSERT_EQ(oss.str(), outputStr);
}

TEST(EPSFileToolsTest, TestEpsPutStringCommandWithoutHeader){

    RelativeBatch batch;
    batch.emplace_back(RightLineCommand({2,2}));
    batch.emplace_back(LeftLineCommand({3,3}));
    std::ostringstream oss("");
    EPSOutFile EPSFs(oss);
    ASSERT_THROW(EPSFs.putBatch(batch), std::runtime_error);
}

TEST(EPSFileToolsTest, TestStripCommandSignatureOnlySignature){
    std::istringstream iss ( "%!PS-Adobe-3.0 EPSF-3.0\n"
                            "%%BoundingBox: 0 0 302 302\n"
                            "%%EndComments\n"
                            "l");

    EPSInFile eps(iss);
    eps.getHeader();
    ASSERT_TRUE(eps.isNextRelative());


}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
