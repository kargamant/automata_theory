execute_process(COMMAND flex -+ rules.l WORKING_DIRECTORY ../Implimentations/flex)
add_library(flex_recognizer ImpRecognizer.cpp lex.yy.cc)
target_link_libraries(flex_recognizer recognizer)

if(NOT IMP STREQUAL "timing")
	target_include_directories(flex_recognizer PUBLIC .)
endif()
