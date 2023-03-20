
add_executable(test_linegraph test_linegraph.cpp)
target_include_directories(test_linegraph PRIVATE ${CMAKE_HOME_DIRECTORY})

add_executable(test_pagerank test_pagerank.cpp)
target_include_directories(test_pagerank PRIVATE ${CMAKE_HOME_DIRECTORY})
