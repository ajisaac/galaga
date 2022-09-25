cmake_minimum_required(VERSION 3.0)
project(galaga)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

find_package(SDL2 REQUIRED)

set(CMAKE_PREFIX_PATH C:/Users/Aaron/Code/galaga/lib/SDL2-2.24.0/)
set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
set(SDL2_LIBRARY "${SDL2_DIR}/lib/x64")
set(SDL2_LIBRARIES "${SDL2_DIR}/lib/x64/SDL2.lib;${SDL2_DIR}/lib/x64/SDL2main.lib")

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)

