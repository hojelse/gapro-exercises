# Game Only

file(GLOB_RECURSE MyGame8-src "*.h" "*.cpp")


add_executable(MyGame8 ${MyGame8-src})

target_include_directories(MyGame8 PUBLIC ${MYENGINE8_INCLUDE_DIR})

target_link_libraries(MyGame8 MyEngine8 ${all_libs})

# Copy project data to output path
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


IF (WIN32)
	## Copy dll's to output path
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
ENDIF(WIN32)