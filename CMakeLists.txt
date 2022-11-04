cmake_minimum_required(VERSION 3.1.0)
project(zpr VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} Main.cc src/Scalar2DRepresentation.h src/Scalar2DRepresentation.cc src/EPSCommandRepresentation.h src/EPSCommandRepresentation.cc src/GraphicCommands.h)
add_compile_options(-Wall -Wextra -pedantic -Werror)
