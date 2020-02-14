find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)

add_library(qtdrawgl SHARED
        qtglimage.cpp
        qtdrawglmanager.cpp
        glwidget.cpp)
target_link_libraries(qtdrawgl common Qt5::Core Qt5::Widgets Qt5::OpenGL opengl32)
