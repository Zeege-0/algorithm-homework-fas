

add_executable(test_linegraph test_linegraph.cpp)
target_include_directories(test_linegraph PRIVATE ${CMAKE_HOME_DIRECTORY})

add_executable(test_pagerank test_pagerank.cpp)
target_include_directories(test_pagerank PRIVATE ${CMAKE_HOME_DIRECTORY})

add_executable(test_scc test_scc.cpp)
target_include_directories(test_scc PRIVATE ${CMAKE_HOME_DIRECTORY})

add_executable(test_hascycle test_hascycle.cpp)
target_include_directories(test_hascycle PRIVATE ${CMAKE_HOME_DIRECTORY})

add_executable(test_pgfas test_pgfas.cpp)
target_include_directories(test_pgfas PRIVATE ${CMAKE_HOME_DIRECTORY})
