cmake_minimum_required(VERSION 3.16)

project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(AST)

#target_sources(lab2
#  PRIVATE
#    AST/CMakeLists.txt
#    Regex/CMakeLists.txt
#)
add_subdirectory(Regex)
add_executable(main main.cpp Regex/Regex.cpp AST/AST.cpp AST/AST.h Regex/Regex.h)
target_link_libraries(main reg)
#target_link_libraries(main ast)

#include(GNUInstallDirs)
#install(TARGETS lab2
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
