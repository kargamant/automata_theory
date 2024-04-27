add_library(state_set StateSet.cpp)
target_include_directories(state_set PUBLIC .)
target_link_libraries(state_set state)
