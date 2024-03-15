cmake_minimum_required(VERSION 3.5)

project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab2 main.cpp
    Regex.h
    Automat.h
    State.h
    TreeLib/plots/AddNode.png TreeLib/plots/DelNode.png TreeLib/plots/Max.png TreeLib/plots/Search.png TreeLib/plots/Traversing.png TreeLib/results/plots10to6/AddNode.png TreeLib/results/plots10to6/DelNode.png TreeLib/results/plots10to6/Max.png TreeLib/results/plots10to6/Search.png TreeLib/results/plots10to6/Traversing.png TreeLib/results/plots10to7/AddNode.png TreeLib/results/plots10to7/DelNode.png TreeLib/results/plots10to7/Max.png TreeLib/results/plots10to7/Search.png TreeLib/results/plots10to7/Traversing.png TreeLib/results/plots4_10to6/AddNode.png TreeLib/results/plots4_10to6/DelNode.png TreeLib/results/plots4_10to6/Max.png TreeLib/results/plots4_10to6/Search.png TreeLib/results/plots4_10to6/Traversing.png TreeLib/results/plots4_10to6_1_25/AddNode.png TreeLib/results/plots4_10to6_1_25/DelNode.png TreeLib/results/plots4_10to6_1_25/Max.png TreeLib/results/plots4_10to6_1_25/Search.png TreeLib/results/plots4_10to6_1_25/Traversing.png TreeLib/test_trees/test.txt TreeLib/test_trees/test2.txt TreeLib/test_trees/test3.txt TreeLib/timing/AddNode.txt TreeLib/timing/DelNode.txt TreeLib/timing/Max.txt TreeLib/timing/Search.txt TreeLib/timing/Traversing.txt TreeLib/BinTree.c TreeLib/BinTree.h TreeLib/funcs.c TreeLib/funcs.h TreeLib/main.c TreeLib/menue.c TreeLib/menue.h TreeLib/plot.py TreeLib/timer.c TreeLib/timer.h
    Regex.cpp)

include(GNUInstallDirs)
install(TARGETS lab2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
