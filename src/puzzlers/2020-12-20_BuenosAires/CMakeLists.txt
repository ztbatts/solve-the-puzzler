add_executable(BuenosAires BuenosAires.cpp)
target_link_libraries(BuenosAires Util CONAN_PKG::range-v3)