
add_executable(fas main.cpp)
target_link_libraries(fas PRIVATE argparse)
install(TARGETS fas)
