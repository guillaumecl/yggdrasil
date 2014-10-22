find_package(Qt4 REQUIRED)
find_package(SDL REQUIRED)
include(${QT_USE_FILE})

set(qtsdldraw_SRCS
  sdlimage.cpp
  qtsdldrawmanager.cpp
  qrenderwidget.cpp
)

add_library(qtsdldraw SHARED ${qtsdldraw_SRCS})
target_link_libraries(qtsdldraw
  common
)
