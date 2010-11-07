TEMPLATE = lib
CONFIG += dll \
	release
CONFIG -= debug \
	thread
HEADERS += qtimage.h \
	qtdrawmanager.h \
	qrenderwidget.h
SOURCES += qtimage.cpp \
	qtdrawmanager.cpp \
	qrenderwidget.cpp
INCLUDEPATH += ../common ../qtcore
DESTDIR = ../bin/
OBJECTS_DIR = ../bin/qtdraw/
LIBS += ../bin/common/libcommon.a
