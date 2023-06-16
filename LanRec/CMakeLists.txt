cmake_minimum_required(VERSION 3.6.0)
project(LanRec)

# message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(lanRec STATIC 

              ${CMAKE_CURRENT_SOURCE_DIR}/grammar.h
              ${CMAKE_CURRENT_SOURCE_DIR}/grammar.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/grammarToAutomaton.h
              ${CMAKE_CURRENT_SOURCE_DIR}/automatonPushDown.h
              ${CMAKE_CURRENT_SOURCE_DIR}/automatonPushDown.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/lexer.h
              ${CMAKE_CURRENT_SOURCE_DIR}/lexer.cpp
              )
# target_link_directories(lanRec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(lanRec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
