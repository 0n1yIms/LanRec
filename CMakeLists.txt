cmake_minimum_required(VERSION 3.6.0)
project(LanRec)




add_subdirectory(LanRec)


add_executable(main main.cpp)

target_link_libraries(main lanRec)