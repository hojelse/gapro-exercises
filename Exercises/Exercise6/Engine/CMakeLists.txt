# Engine Only

file(GLOB_RECURSE MyEngine-src "*.cpp")
file(GLOB_RECURSE MyEngine-hpp "*.h")

set(MYENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "" FORCE)
target_link_libraries(MyEngine ${all_libs})

add_library(MyEngine ${MyEngine-src} ${MyEngine-hpp})

target_include_directories(MyEngine PUBLIC "Engine")
target_include_directories(MyEngine PUBLIC "3rdParty")
