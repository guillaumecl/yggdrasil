project(yggdrasil_editor)

find_package(Qt4 REQUIRED)
include (${QT_USE_FILE})
include_directories(
  ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
  ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
)

set(yggdrasil_editor_SRCS
  yggdrasil_editor.cpp
  main.cpp
  gamedisplayer.cpp
  screentree.cpp
  objecttree.cpp
  namechoose.cpp
  objectitem.cpp
  filterwidget.cpp
  itemfilter.cpp
  screendockwidget.cpp
  objectdockwidget.cpp
  propertytree.cpp
  propertyitemmodel.cpp
  propertyitem.cpp
  objectdisplayer.cpp
  propertywidget.cpp
  screenproperties.cpp
  screenitemproperties.cpp
  screenelementproperties.cpp
  actionproperties.cpp
  propertylist.cpp
  propertyitemdelegate.cpp
  glwrapper.cpp
  qteditorlog.cpp
)

set(yggdrasil_editor_UIS
  main.ui
  nameChoose.ui
)

QT4_WRAP_UI(UIS ${yggdrasil_editor_UIS})

set(yggdrasil_editor_RSCS
  resources/application.qrc
)

QT4_ADD_RESOURCES(RSCS ${yggdrasil_editor_RSCS})

set(yggdrasil_editor_TRS
  yggdrasil_editor_fr.ts
)
QT4_ADD_TRANSLATION(TRS ${yggdrasil_editor_TRS})

set(yggdrasil_editor_MOCS
  yggdrasil_editor.h
  gamedisplayer.h
  screentree.h
  objecttree.h
  namechoose.h
  filterwidget.h
  screendockwidget.h
  objectdockwidget.h
  propertytree.h
  propertyitemmodel.h
  objectdisplayer.h
  propertywidget.h
  screenproperties.h
  screenitemproperties.h
  screenelementproperties.h
  actionproperties.h
  propertylist.h
  propertyitemdelegate.h
  glwrapper.h
)
QT4_WRAP_CPP(MOCS ${yggdrasil_editor_MOCS})

add_executable(yggdrasil_editor ${yggdrasil_editor_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS})
target_link_libraries(yggdrasil_editor ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY}
  common
  game
)
