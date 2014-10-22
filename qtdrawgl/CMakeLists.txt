find_package ( Qt4 REQUIRED )
include(${QT_USE_FILE})

include_directories(${QT_QTOPENGL_INCLUDE_DIR})

set(qtdrawgl_SRCS
  qtglimage.cpp
  qtdrawglmanager.cpp
  glwidget.cpp
)

add_library(qtdrawgl SHARED ${qtdrawgl_SRCS})
target_link_libraries(qtdrawgl  ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY})
