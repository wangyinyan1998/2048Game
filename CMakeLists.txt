link_libraries(ws2_32)
cmake_minimum_required(VERSION 3.10)
project(OOPPJ_2048)

set(CMAKE_CXX_STANDARD 11)

add_executable(OOPPJ_2048 main.cpp Console2048.cpp Console2048.h Game2048Operation.cpp Game2048Operation.h Index.cpp Index.h)