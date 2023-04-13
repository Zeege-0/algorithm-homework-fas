
add_executable(fas main.cpp)
target_link_libraries(fas PRIVATE argparse)
target_link_libraries(fas PRIVATE indicators)
install(TARGETS fas)
