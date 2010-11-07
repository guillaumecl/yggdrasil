TEMPLATE = lib
CONFIG += dll \
	release
CONFIG -= debug thread
HEADERS += qtglimage.h qtdrawglmanager.h glwidget.h
SOURCES += qtglimage.cpp qtdrawglmanager.cpp glwidget.cpp
QT += opengl

INCLUDEPATH += ../common  ../qtcore
DESTDIR = ../bin/
OBJECTS_DIR = ../bin/qtdrawgl/
LIBS += ../bin/common/libcommon.a
