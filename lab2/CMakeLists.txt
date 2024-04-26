cmake_minimum_required(VERSION 3.2)
project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(AST)

#target_sources(lab2
#  PRIVATE
#    AST/CMakeLists.txt
#    Regex/CMakeLists.txt
#)
add_subdirectory(Automat)
add_subdirectory(Regex)
file(COPY scripts DESTINATION .)
add_executable(main  Regex/Regex.cpp AST/AST.cpp AST/AST.h Regex/Regex.h
    Automat/Automat.cpp Automat/Automat.h
    main.cpp
    )
target_link_libraries(main reg automat)
#target_link_libraries(main ast)

#include(GNUInstallDirs)
#install(TARGETS lab2
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
