#-------------------------------------------------
#
# Project created by QtCreator 2012-05-16T15:39:51
#
#-------------------------------------------------

QT       += widgets
CONFIG += release
TARGET = Zenobie
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    write.cpp \
    traitement.cpp \
    read.cpp \
    data.cpp

HEADERS  += dialog.h \
    data.h

FORMS    += dialog.ui

TRANSLATIONS = Zenobie_nl.ts

OTHER_FILES += \
    android/Makefile \
    android/libjava.so \
    android/android-libjava.so-deployment-settings.json
