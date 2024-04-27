cmake_minimum_required(VERSION 3.2)
project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-g)

add_subdirectory(AST)

#target_sources(lab2
#  PRIVATE
#    AST/CMakeLists.txt
#    Regex/CMakeLists.txt
add_subdirectory(Automat)
add_subdirectory(Regex)
add_subdirectory(StateSet)
add_subdirectory(State)
add_subdirectory(Transition)
file(COPY genPng.sh DESTINATION .)
file(COPY viz.py DESTINATION .)
file(COPY regex_exp.txt DESTINATION .)
add_executable(main  Regex/Regex.cpp AST/AST.cpp AST/AST.h Regex/Regex.h
    Automat/Automat.cpp Automat/Automat.h
    main.cpp
    StateMap/StateMap.cpp StateMap/StateMap.h
    StateSet/StateSet.cpp StateSet/StateSet.h
    State/State.cpp State/State.h
    Transition/Transition.cpp Transition/Transition.h
    regex_exp.txt

    )
target_link_libraries(main reg automat)
#target_link_libraries(main ast)

#include(GNUInstallDirs)
#install(TARGETS lab2
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
