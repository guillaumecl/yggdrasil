find_package(Qt5 COMPONENTS Core Widgets LinguistTools REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

add_library(yggdrasil_property STATIC
        propertytree.cpp
        propertyitemmodel.cpp
        propertyitem.cpp
        propertywidget.cpp
        screenproperties.cpp
        screenitemproperties.cpp
        screenelementproperties.cpp
        actionproperties.cpp
        propertylist.cpp
        propertyitemdelegate.cpp
        )
target_link_libraries(yggdrasil_property
        game
        Qt5::Core Qt5::Widgets)
