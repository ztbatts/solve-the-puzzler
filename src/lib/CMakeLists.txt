add_library(Util util.cpp)
target_link_libraries(Util CONAN_PKG::range-v3)
target_include_directories(Util PUBLIC include)