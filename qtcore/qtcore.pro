TEMPLATE = lib
CONFIG += dll \
	release
CONFIG -= debug \
	thread
HEADERS += qtcore.h \
	displaywidget.h \
	qtdrawmanagerbase.h
SOURCES += qtcore.cpp \
	displaywidget.cpp
QT += opengl
INCLUDEPATH += ../common
DESTDIR = ../bin/
OBJECTS_DIR = ../bin/qtcore/
LIBS += ../bin/common/libcommon.a
