add_executable(main_smc main.cpp ../Recognizer/Recognizer.cpp SmcRecognizer.cpp automat_sm.cpp)
set_property(TARGET main_smc PROPERTY OUTPUT_NAME main)
target_link_libraries(main_smc recognizer)
target_include_directories(main_smc PUBLIC .)
