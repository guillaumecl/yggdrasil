TEMPLATE = lib

CONFIG += staticlib \
release \
 console
CONFIG -= debug \
qt \
thread
INCLUDEPATH += ../common

SOURCES += action.cpp \
actionframe.cpp \
collision.cpp \
collisionscreen.cpp \
inputcondition.cpp \
input.cpp \
plane.cpp \
rect.cpp \
screen.cpp \
screenelement.cpp \
sprite.cpp
HEADERS += actionframe.h \
action.h \
basictypes.h \
collision.h \
collisionscreen.h \
inputcondition.h \
input.h \
plane.h \
rect.h \
screenelement.h \
screen.h \
sprite.h
OBJECTS_DIR = ../bin/common/

DESTDIR = ../bin/game/

