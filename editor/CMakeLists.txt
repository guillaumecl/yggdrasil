project(yggdrasil_editor)

find_package(Qt5 COMPONENTS Core Widgets LinguistTools REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(property)
add_subdirectory(view)

QT5_ADD_TRANSLATION(TRS ${yggdrasil_editor_TRS})

add_executable(yggdrasil_editor
        yggdrasil_editor.cpp
        main.cpp
        screentree.cpp
        objecttree.cpp
        namechoose.cpp
        objectitem.cpp
        filterwidget.cpp
        itemfilter.cpp
        qteditorlog.cpp

        resources/application.qrc

        ${TRS})
target_link_libraries(yggdrasil_editor Qt5::Core Qt5::Widgets
  common
  game
  yggdrasil_property
  yggdrasil_view
)
