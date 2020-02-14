find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(qtcore_SRCS
  qtcore.cpp
  displaywidget.cpp
)

add_library(qtcore SHARED ${qtcore_SRCS})
target_link_libraries(qtcore common Qt5::Core Qt5::Widgets)
