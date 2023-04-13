

file(GLOB LALA_FILES "test_*")

foreach(file ${LALA_FILES})
  get_filename_component(filename ${file} NAME_WE)
  add_executable(${filename} ${file})
  target_include_directories(${filename} PRIVATE ${CMAKE_HOME_DIRECTORY})
  target_link_libraries(${filename} PRIVATE indicators)
endforeach()
