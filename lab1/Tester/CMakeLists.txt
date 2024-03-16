add_library(tester Tester.cpp ../Generator/Generator.cpp)
target_link_libraries(tester generator)
target_include_directories(tester PUBLIC .)
