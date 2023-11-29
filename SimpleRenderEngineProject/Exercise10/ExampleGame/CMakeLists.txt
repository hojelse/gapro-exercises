# Game Only

file(GLOB_RECURSE MyGame10-src "*.h" "*.cpp")


add_executable(MyGame10 ${MyGame10-src})

target_include_directories(MyGame10 PUBLIC ${MYENGINE10_INCLUDE_DIR})

target_link_libraries(MyGame10 MyEngine10 ${all_libs})

# Copy project data to output path
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


IF (WIN32)
	## Copy dll's to output path
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
ENDIF(WIN32)