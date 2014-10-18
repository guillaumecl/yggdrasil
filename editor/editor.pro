SOURCES = yggdrasil_editor.cpp \
    main.cpp \
    gamedisplayer.cpp \
    screentree.cpp \
    objecttree.cpp \
    namechoose.cpp \
    objectitem.cpp \
    filterwidget.cpp \
    itemfilter.cpp \
    screendockwidget.cpp \
    objectdockwidget.cpp \
    propertytree.cpp \
    propertyitemmodel.cpp \
    propertyitem.cpp \
    objectdisplayer.cpp \
    propertywidget.cpp \
    screenproperties.cpp \
    screenitemproperties.cpp \
    screenelementproperties.cpp \
    actionproperties.cpp \
    propertylist.cpp \
    propertyitemdelegate.cpp \
    glwrapper.cpp \
    qteditorlog.cpp
HEADERS = yggdrasil_editor.h \
    gamedisplayer.h \
    screentree.h \
    mime.h \
    objecttree.h \
    namechoose.h \
    objectitem.h \
    filterwidget.h \
    itemfilter.h \
    screendockwidget.h \
    objectdockwidget.h \
    propertytree.h \
    propertyitemmodel.h \
    propertyitem.h \
    objectdisplayer.h \
    propertywidget.h \
    screenproperties.h \
    screenitemproperties.h \
    screenelementproperties.h \
    actionproperties.h \
    propertylist.h \
    propertyitemdelegate.h \
    glwrapper.h \
    qteditorlog.h
TEMPLATE = app
CONFIG += warn_on \
    thread \
    qt \
    opengl \
    console \
    debug \
    stl
RESOURCES = application.qrc
QT += opengl
FORMS += main.ui \
    nameChoose.ui
TRANSLATIONS += yggdrasil_editor_fr.ts
RC_FILE = winicon.rc
INCLUDEPATH += ../common \
    ../game \
    ../qtcore \
    ../qtdraw
DESTDIR = ../bin/
OBJECTS_DIR = ../bin/editor/
TARGET = yggdrasil_editor
LIBS += ../bin/game/libgame.a \
    ../bin/common/libcommon.a
POST_TARGETDEPS += ../bin/game/libgame.a \
    ../bin/common/libcommon.a
UI_DIR = ../bin/editor/ui/
MOC_DIR = ../bin/editor/moc/
RCC_DIR = ../bin/editor/rcc/
!win32:LIBS += -ldl
