
add_library(argparse INTERFACE)
add_library(argparse::argparse ALIAS argparse)

target_compile_features(argparse INTERFACE cxx_std_17)
target_include_directories(argparse INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
