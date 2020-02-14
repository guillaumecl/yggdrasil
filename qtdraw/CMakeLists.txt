find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(qtdraw_SRCS
  qtimage.cpp
  qtdrawmanager.cpp
  qrenderwidget.cpp
)

add_library(qtdraw SHARED ${qtdraw_SRCS})
target_link_libraries(qtdraw common Qt5::Core Qt5::Widgets)
