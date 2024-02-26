SET(CMAKE_CXX_STANDARD, 20)
cmake_minimum_required(VERSION 3.16)
project(Generator)
add_subdirectory(Generator)
add_subdirectory(Tester)
add_subdirectory(lab1)

add_executable(gen main.cpp Generator/Generator.cpp)
target_link_libraries(gen generator tester)
