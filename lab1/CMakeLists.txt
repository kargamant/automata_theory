SET(CMAKE_CXX_STANDARD, 20)
cmake_minimum_required(VERSION 3.16)
project(Translator)
add_subdirectory(Generator)
add_subdirectory(Tester)
add_subdirectory(Implimentations)

add_executable(time main.cpp Generator/Generator.cpp)
target_link_libraries(time generator tester)
