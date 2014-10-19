cmake_minimum_required(VERSION 2.6)
add_definitions(-Wall)
include_directories(
  ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
)
add_subdirectory(common)
add_subdirectory(game)
add_subdirectory(editor)
add_subdirectory(qtcore)
add_subdirectory(qtsdldraw)
add_subdirectory(qtdraw)
add_subdirectory(qtdrawgl)
