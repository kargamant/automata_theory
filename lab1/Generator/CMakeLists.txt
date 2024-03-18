add_library(generator Generator.cpp main.cpp)
target_include_directories(generator PUBLIC .)
add_executable(gen main.cpp Generator.cpp)
target_link_libraries(gen generator)
