add_subdirectory(Recognizer)

set(IMP "regex" CACHE STRING "")
set(DEBUG_FLAG "" CACHE STRING "")

if(IMP STREQUAL "flex")
	add_subdirectory(flex)
elseif(IMP STREQUAL "smc")
	add_subdirectory(smc)
elseif(IMP STREQUAL "regex")
	add_subdirectory(regex)
endif()

if(DEBUG_FLAG STREQUAL "1")
	add_compile_definitions(DEBUG_INFO)
endif()
add_executable(main_recompile main.cpp ${IMP}/ImpRecognizer.cpp)
target_link_libraries(main_recompile ${IMP}_recognizer recognizer)
