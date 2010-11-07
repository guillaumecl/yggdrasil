TEMPLATE = lib
CONFIG += dll \
    release
CONFIG -= debug \
    thread
HEADERS += sdlimage.h \
    qtsdldrawmanager.h \
    qrenderwidget.h
SOURCES += sdlimage.cpp \
    qtsdldrawmanager.cpp \
    qrenderwidget.cpp
INCLUDEPATH += ../common \
    ../qtcore
DESTDIR = ../bin/
OBJECTS_DIR = ../bin/qtsdldraw/
LIBS += ../bin/common/libcommon.a \
    -lSDL \
	-lSDL_image
