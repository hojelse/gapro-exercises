# Engine Only

file(GLOB_RECURSE MyEngine10-src "*.cpp")
file(GLOB_RECURSE MyEngine10-hpp "*.h")

set(MYENGINE10_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "" FORCE)


add_library(MyEngine10 ${MyEngine10-src} ${MyEngine10-hpp})

target_link_libraries(MyEngine10 ${all_libs})

target_include_directories(MyEngine10 PUBLIC ${MYENGINE10_INCLUDE_DIR})
target_include_directories(MyEngine10 PUBLIC "3rdParty")
