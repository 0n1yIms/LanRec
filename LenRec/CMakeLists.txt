cmake_minimum_required(VERSION 3.6.0)
project(LenRec)

# message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(lenRec STATIC 
              ${CMAKE_CURRENT_SOURCE_DIR}/automatonPushdown.h
              ${CMAKE_CURRENT_SOURCE_DIR}/automatonPushdown.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/lexer.h
              ${CMAKE_CURRENT_SOURCE_DIR}/lexer.cpp
              )
# target_link_directories(lenRec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(lenRec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
