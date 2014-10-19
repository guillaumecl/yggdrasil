cmake_minimum_required( VERSION 2.6 )
find_package(Qt4 REQUIRED)
include (${QT_USE_FILE})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
include_directories (
  ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
  ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
)

set(qtdraw_SRCS
  qtimage.cpp
  qtdrawmanager.cpp
  qrenderwidget.cpp
)

add_library(qtdraw SHARED ${qtdraw_SRCS})
target_link_libraries(qtdraw ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
