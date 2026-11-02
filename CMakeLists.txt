cmake_minimum_required(VERSION 3.16)
project(ghostline_net_tycoon VERSION 0.1.0 LANGUAGES CXX)
add_executable(ghostline src/ghostline.cpp)
target_compile_features(ghostline PRIVATE cxx_std_17)
