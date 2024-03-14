cmake_minimum_required(VERSION 3.16)
SET(CMAKE_CXX_STANDARD, 20)
project(Turnstile_v2)

add_subdirectory(Locked)
add_subdirectory(Unlocked)
add_subdirectory(State)
add_subdirectory(Turnstile)

add_executable(main main.cpp Turnstile/turnstile.cpp)
target_link_libraries(main locked unlocked state turnstile)
