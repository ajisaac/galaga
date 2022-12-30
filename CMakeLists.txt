cmake_minimum_required(VERSION 3.0)
project(galaga)

set(CMAKE_CXX_STANDARD 20)
set(SDL2_DIR C:/Users/Aaron/Code/galaga/lib/SDL2-2.26.1)
set(CMAKE_PREFIX_PATH "${SDL2_DIR}")
set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
set(SDL2_LIBRARY "${SDL2_DIR}/lib/x64")
set(SDL2_LIBRARIES "${SDL2_DIR}/lib/x64/SDL2.lib;${SDL2_DIR}/lib/x64/SDL2main.lib")

set(SDL2IMAGE_DIR C:/Users/Aaron/Code/galaga/lib/SDL2_image-2.6.2)
set(CMAKE_PREFIX_PATH "${SDL2IMAGE_DIR}")
set(SDL2IMAGE_INCLUDE_DIR "${SDL2IMAGE_DIR}/include")
set(SDL2IMAGE_LIBRARY "${SDL2IMAGE_DIR}/lib/x64")
set(SDL2IMAGE_LIBRARIES "${SDL2IMAGE_DIR}/lib/x64/SDL2_image.lib")

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2IMAGE_INCLUDE_DIR})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.cpp src/*.h)

set(BINARY ${CMAKE_PROJECT_NAME})
set(SOURCES ${SOURCES})

add_executable(${BINARY} ${SOURCES})
target_link_libraries(${BINARY} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
#add_library(${BINARY}_lib STATIC ${SOURCES})