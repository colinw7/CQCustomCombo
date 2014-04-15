TEMPLATE = lib

TARGET = CQCustomCombo

QT += widgets

DEPENDPATH += .

CONFIG += staticlib

# Input
HEADERS += \
../include/CQCustomCombo.h \

SOURCES += \
CQCustomCombo.cpp \

OBJECTS_DIR = ../obj

DESTDIR = ../lib

INCLUDEPATH += \
. \
../include \
