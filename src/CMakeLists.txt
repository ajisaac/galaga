set(BINARY ${CMAKE_PROJECT_NAME})
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

include_directories(${SDL2_INCLUDE_DIR})

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})
target_link_libraries(${BINARY}_run ${SDL2_LIBRARIES})
add_library(${BINARY}_lib STATIC ${SOURCES})
