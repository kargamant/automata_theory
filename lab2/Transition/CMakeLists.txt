add_library(transition Transition.cpp)
target_include_directories(transition PUBLIC .)
target_link_libraries(transition state)
