cmake_minimum_required( VERSION 2.6 )
find_package ( Qt4 REQUIRED )
include(${QT_USE_FILE})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
include_directories (
	${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTOPENGL_INCLUDE_DIR})

set(qtdrawgl_SRCS
  qtglimage.cpp
  qtdrawglmanager.cpp
  glwidget.cpp
)

add_library(qtdrawgl SHARED ${qtdrawgl_SRCS})
target_link_libraries(qtdrawgl  ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY})
