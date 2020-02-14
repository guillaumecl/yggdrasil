find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

find_package(SDL REQUIRED)

set(qtsdldraw_SRCS
  sdlimage.cpp
  qtsdldrawmanager.cpp
  qrenderwidget.cpp
)

add_library(qtsdldraw SHARED ${qtsdldraw_SRCS})
target_link_libraries(qtsdldraw common Qt5::Core Qt5::Widgets
  common
)
