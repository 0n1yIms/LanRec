cmake_minimum_required(VERSION 3.6.0)
project(LanRec)


# set release by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


add_subdirectory(LanRec)


add_executable(main main.cpp)

target_link_libraries(main lanRec)