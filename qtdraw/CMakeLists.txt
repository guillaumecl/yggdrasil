find_package(Qt4 REQUIRED)
include (${QT_USE_FILE})

set(qtdraw_SRCS
  qtimage.cpp
  qtdrawmanager.cpp
  qrenderwidget.cpp
)

add_library(qtdraw SHARED ${qtdraw_SRCS})
target_link_libraries(qtdraw ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
