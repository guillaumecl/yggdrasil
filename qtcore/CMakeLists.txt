cmake_minimum_required( VERSION 2.6 )
find_package ( Qt4 REQUIRED )

include(${QT_USE_FILE})
include_directories(
  ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
  ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
)

set(qtcore_SRCS
  qtcore.cpp
  displaywidget.cpp
)

add_library(qtcore SHARED ${qtcore_SRCS})
target_link_libraries(qtcore ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
