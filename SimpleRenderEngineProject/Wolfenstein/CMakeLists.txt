file(GLOB_RECURSE Sources "*.h" "*.cpp") # will get all the .cpp and all the .h files in directory and subdirectories
add_executable(ExampleGame2 ${Sources})

target_link_libraries(ExampleGame2 ${all_libs})

# Copy project data to output path
file(COPY media DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY media DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY media DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(Engine)
add_subdirectory(ExampleGame)
