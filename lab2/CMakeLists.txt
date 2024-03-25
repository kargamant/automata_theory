cmake_minimum_required(VERSION 3.5)

project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab2 main.cpp
    Regex.h
    Automat.h
    State.h
    Regex.cpp
    AST.h)

include(GNUInstallDirs)
install(TARGETS lab2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
