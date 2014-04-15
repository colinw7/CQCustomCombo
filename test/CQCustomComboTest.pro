TEMPLATE = app

TARGET = CQCustomComboTest

QT += widgets

DEPENDPATH += .

#CONFIG += debug

# Input
SOURCES += \
CQCustomComboTest.cpp \

HEADERS += \
CQCustomComboTest.h \

DESTDIR     = .
OBJECTS_DIR = .

INCLUDEPATH += \
../include \
.

unix:LIBS += \
-L../lib \
-lCQCustomCombo
