add_library(automat Automat.cpp)
target_include_directories(automat PUBLIC .)
target_link_libraries(automat state_set transition reg)
