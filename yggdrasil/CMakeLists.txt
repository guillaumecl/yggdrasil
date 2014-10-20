project(yggdrasil)

include_directories(${CMAKE_SOURCE_DIR})

set(yggdrasil_SRCS
  yggdrasil.cpp
)
add_executable(yggdrasil_bin ${yggdrasil_SRCS})

target_link_libraries(yggdrasil_bin
  common
  game
  -ldl
)
