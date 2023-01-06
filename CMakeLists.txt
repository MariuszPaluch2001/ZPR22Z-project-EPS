cmake_minimum_required(VERSION 3.1.0)
project(zpr)

set (CMAKE_CXX_STANDARD 17)
set(wxWidgets_USE_LIBS)
find_package(wxWidgets)
include(${wxWidgets_USE_FILE})

include_directories(${wxWidgets_INCLUDE_DIRS})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(zprGUI
  GUIMain.cc
  src/GUI.h
  src/GUI.cc
  src/EPSFileTools.h
  src/EPSFileTools.cc
  src/GraphicCommands.h
  src/GraphicCommands.cc
  src/Scalar2DRepresentation.h
  src/Scalar2DRepresentation.cc)
add_executable(${PROJECT_NAME}
        Main.cc
        src/Scalar2DRepresentation.h
        src/Scalar2DRepresentation.cc
        src/EPSCommandRepresentation.h
        src/EPSCommandRepresentation.cc
        src/GraphicCommands.h
        src/GraphicCommands.cc
        src/EPSFileTools.cc
        src/EPSFileTools.h
        src/Algorithm.hpp
        src/utils.hpp
        )

target_link_libraries(zprGUI
  ${wxWidgets_LIBRARIES})


add_compile_options(-Wall -Werror)


enable_testing()
include_directories(src)
add_subdirectory(src)
add_subdirectory(tests)
include_directories(tmp)
add_subdirectory(tmp)

target_link_libraries(${PROJECT_NAME})
target_link_libraries(zprGUI Scalar2DRepresentation EPSFileTools EPSCommands)

