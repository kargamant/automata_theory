add_library(smc_recognizer ImpRecognizer.cpp automat_sm.cpp)
target_link_libraries(smc_recognizer recognizer)
target_include_directories(smc_recognizer PUBLIC .)
