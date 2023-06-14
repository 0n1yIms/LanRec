cmake_minimum_required(VERSION 3.6.0)
project(LenRec)




add_subdirectory(LenRec)


add_executable(main main.cpp)

target_link_libraries(main lenRec)