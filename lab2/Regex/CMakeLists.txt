add_library(reg Regex.cpp ../AST/AST.cpp)
target_link_libraries(reg ast automat)
target_include_directories(reg PUBLIC .)
