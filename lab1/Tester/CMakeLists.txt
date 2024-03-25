add_library(tester Tester.cpp ../Generator/Generator.cpp)
target_link_libraries(tester generator recognizer smc_recognizer flex_recognizer regex_recognizer)
target_include_directories(tester PUBLIC .)

if(IMP STREQUAL "timing")
	add_executable(time time.cpp ../Generator/Generator.cpp)
	target_link_libraries(time generator tester)
endif()
