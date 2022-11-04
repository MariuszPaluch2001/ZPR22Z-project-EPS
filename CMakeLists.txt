cmake_minimum_required(VERSION 3.1.0)
project(zpr VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)
add_compile_options(-Wall -Wextra -pedantic -Werror)
