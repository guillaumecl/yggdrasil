TEMPLATE = lib
CONFIG += staticlib \
	release \
	console
CONFIG -= debug \
	qt \
	thread
QT -= core \
	gui
SOURCES += core.cpp \
	exception.cpp \
	log.cpp \
	plugin.cpp \
	archiver.cpp
HEADERS += core.h \
	drawmanager.h \
	exception.h \
	log.h \
	plugin.h \
	soundmanager.h \
	archiver.h
OBJECTS_DIR = ../bin/common/
DESTDIR = ../bin/common/
