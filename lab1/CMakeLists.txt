SET(CMAKE_CXX_STANDARD, 20)
cmake_minimum_required(VERSION 3.16)
project(Translator)

add_subdirectory(Generator)
add_subdirectory(Tester)
add_subdirectory(Implimentations)
file(COPY txts DESTINATION .)

