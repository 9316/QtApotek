#-------------------------------------------------
#
# Project created by QtCreator 2013-09-05T16:03:54
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       +=webkitwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MedicineShopApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    addmed.cpp \
    selldialog.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    addmed.h \
    selldialog.h

FORMS    += mainwindow.ui \
    dialog.ui \
    addmed.ui \
    selldialog.ui

RESOURCES += \
    icons.qrc
