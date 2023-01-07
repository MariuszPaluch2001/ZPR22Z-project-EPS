cmake_minimum_required(VERSION 3.1.0)
project(zpr)
set (CMAKE_CXX_STANDARD 17)


add_executable(${PROJECT_NAME} Main.cc
        src/Scalar2DRepresentation.h
        src/Scalar2DRepresentation.cc
        src/EPSCommandRepresentation.h
        src/EPSCommandRepresentation.cc
        src/GraphicCommands.h
        src/GraphicCommands.cc
        src/EPSFileTools.cc
        src/EPSFileTools.hpp
        src/Algorithm.hpp

)


add_compile_options(-Wall -Werror)


enable_testing()

include_directories(src)
add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(${PROJECT_NAME} Scalar2DRepresentation EPSFileTools EPSCommands)

