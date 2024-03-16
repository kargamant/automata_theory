add_executable(main_regex main.cpp RegexRecognizer.cpp ../Recognizer/Recognizer.cpp)
set_property(TARGET main_regex PROPERTY OUTPUT_NAME main)
target_link_libraries(main_regex recognizer)
target_include_directories(main_regex PUBLIC .)
