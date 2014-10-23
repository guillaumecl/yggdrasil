
set(view_SRCS
  gamedisplayer.cpp
  objectdisplayer.cpp
  glwrapper.cpp
)

set(view_MOCS
  gamedisplayer.h
  objectdisplayer.h
  glwrapper.h
)
QT4_WRAP_CPP(MOCS ${view_MOCS})

add_library(yggdrasil_view STATIC ${view_SRCS} ${MOCS})
