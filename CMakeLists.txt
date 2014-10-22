cmake_minimum_required(VERSION 2.6)
add_definitions(-Wall)
include_directories(${CMAKE_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

option(BUILD_QTDRAWGL "Build the OpenGL version of the renderer" ON)
option(BUILD_QTDRAW "Build the 2D version of the renderer" ON)
option(BUILD_QTSDLDRAW "Build the SDL version of the renderer" OFF)
option(BUILD_EDITOR "Build the editor" ON)
option(BUILD_GAME "Build the main game" OFF)


add_subdirectory(common)
add_subdirectory(game)

if (BUILD_EDITOR)
  add_subdirectory(editor)
endif()

if (BUILD_GAME)
  add_subdirectory(yggdrasil)
endif()

add_subdirectory(qtcore)

if (BUILD_QTSDLDRAW)
  add_subdirectory(qtsdldraw)
endif()

if (BUILD_QTDRAW)
  add_subdirectory(qtdraw)
endif()

if (BUILD_QTDRAWGL)
  add_subdirectory(qtdrawgl)
endif()
