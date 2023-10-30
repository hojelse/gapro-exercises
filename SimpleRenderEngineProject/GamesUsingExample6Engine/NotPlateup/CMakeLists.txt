# Game Only

file(GLOB_RECURSE NotPlateup-src "*.h" "*.cpp")


add_executable(NotPlateup ${NotPlateup-src})

target_include_directories(NotPlateup PUBLIC ${MYENGINE_INCLUDE_DIR})

target_link_libraries(NotPlateup MyEngine ${all_libs})

# Copy project data to output path
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


IF (WIN32)
	## Copy dll's to output path
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
ENDIF(WIN32)