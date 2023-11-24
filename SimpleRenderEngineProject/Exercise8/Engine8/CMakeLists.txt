# Engine Only

file(GLOB_RECURSE MyEngine8-src "*.cpp")
file(GLOB_RECURSE MyEngine8-hpp "*.h")

set(MYENGINE8_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "" FORCE)


add_library(MyEngine8 ${MyEngine8-src} ${MyEngine8-hpp})

target_link_libraries(MyEngine8 ${all_libs})

target_include_directories(MyEngine8 PUBLIC ${MYENGINE8_INCLUDE_DIR})
target_include_directories(MyEngine8 PUBLIC "3rdParty")
