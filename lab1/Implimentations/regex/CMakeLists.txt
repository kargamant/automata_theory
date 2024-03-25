add_library(regex_recognizer ImpRecognizer.cpp)

if(NOT IMP STREQUAL "timing")
	target_include_directories(regex_recognizer PUBLIC .)
endif()

target_link_libraries(regex_recognizer recognizer)
