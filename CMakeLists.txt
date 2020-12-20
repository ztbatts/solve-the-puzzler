cmake_minimum_required(VERSION 3.16)

project(SolveThePuzzler)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) # Include Conan-generated file
conan_basic_setup(TARGETS) # Introduce Conan-generated targets
#conan_basic_setup()

add_subdirectory(src)