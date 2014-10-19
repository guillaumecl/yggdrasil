cmake_minimum_required( VERSION 2.6 )

set(common_SRCS
  core.cpp
  exception.cpp
  log.cpp
  plugin.cpp
  archiver.cpp
)

add_library(common SHARED ${common_SRCS})
target_link_libraries(common)
