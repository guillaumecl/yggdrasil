project(yggdrasil_editor)

find_package(Qt4 REQUIRED)
include (${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(property)
add_subdirectory(view)

set(yggdrasil_editor_SRCS
  yggdrasil_editor.cpp
  main.cpp
  screentree.cpp
  objecttree.cpp
  namechoose.cpp
  objectitem.cpp
  filterwidget.cpp
  itemfilter.cpp
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
  screentree.h
  objecttree.h
  namechoose.h
  filterwidget.h
)
QT4_WRAP_CPP(MOCS ${yggdrasil_editor_MOCS})

add_executable(yggdrasil_editor ${yggdrasil_editor_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS})
target_link_libraries(yggdrasil_editor ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY}
  common
  game
  yggdrasil_property
  yggdrasil_view
)
