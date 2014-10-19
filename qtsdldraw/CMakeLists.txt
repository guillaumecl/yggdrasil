cmake_minimum_required( VERSION 2.6 )
find_package(Qt4 REQUIRED)
find_package(SDL REQUIRED)
include(${QT_USE_FILE})
include_directories(
  ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
  ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
)

set(qtsdldraw_SRCS
  sdlimage.cpp
  qtsdldrawmanager.cpp
  qrenderwidget.cpp
)

add_library(qtsdldraw SHARED ${qtsdldraw_SRCS})
target_link_libraries(qtsdldraw
  common
)
