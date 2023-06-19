cmake_minimum_required(VERSION 3.6.0)
project(LanRec)

# message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(lanRec STATIC 

              ${CMAKE_CURRENT_SOURCE_DIR}/Grammar/grammar.h
              ${CMAKE_CURRENT_SOURCE_DIR}/Grammar/grammar.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/Grammar/grammarTree.h
              ${CMAKE_CURRENT_SOURCE_DIR}/Grammar/grammarTree.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/Grammar/grammarDerivation.h
              ${CMAKE_CURRENT_SOURCE_DIR}/Grammar/grammarDerivation.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/Convert/grammarToAutomaton.h
              ${CMAKE_CURRENT_SOURCE_DIR}/AutomatonPD/automatonPushDown.h
              ${CMAKE_CURRENT_SOURCE_DIR}/AutomatonPD/automatonPushDown.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/lexer.h
              ${CMAKE_CURRENT_SOURCE_DIR}/lexer.cpp
              )
# target_link_directories(lanRec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(lanRec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
