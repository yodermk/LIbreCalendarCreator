#-------------------------------------------------
#
# Project created by QtCreator 2014-01-11T16:00:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibreCalendarCreator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    newcalendar.cpp \
    monthclass.cpp \
    editmonth.cpp \
    choosecropphotodialog.cpp \
    photocropper.cpp

HEADERS  += mainwindow.h \
    newcalendar.h \
    monthclass.h \
    editmonth.h \
    choosecropphotodialog.h \
    photocropper.h

FORMS    += mainwindow.ui \
    newcalendar.ui \
    editmonth.ui \
    choosecropphotodialog.ui

QMAKE_CXXFLAGS += -std=c++11
