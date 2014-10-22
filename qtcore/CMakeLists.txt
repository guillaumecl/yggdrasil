find_package ( Qt4 REQUIRED )

include(${QT_USE_FILE})

set(qtcore_SRCS
  qtcore.cpp
  displaywidget.cpp
)

add_library(qtcore SHARED ${qtcore_SRCS})
target_link_libraries(qtcore ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
