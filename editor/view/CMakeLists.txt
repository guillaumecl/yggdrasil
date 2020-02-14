find_package(Qt5 COMPONENTS Core Widgets LinguistTools REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_AUTOMOC ON)

add_library(yggdrasil_view STATIC
    gamedisplayer.cpp
    objectdisplayer.cpp
    glwrapper.cpp
)
target_link_libraries(yggdrasil_view
        game
        Qt5::Core Qt5::Widgets)
