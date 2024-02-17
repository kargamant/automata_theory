cmake_minimum_required(VERSION 3.16)
SET(CMAKE_CXX_STANDARD, 20)
project(Turnstile_v3)

add_subdirectory(gen)
add_subdirectory(Turnstile)

add_executable(main main.cpp)
target_link_libraries(main turnstile turnstile_sm)
