#-------------------------------------------------
#
# Project created by QtCreator 2017-01-08T12:01:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = teste222
TEMPLATE = app
LIBS        += -lGL -pthread
LIBS        += -L/usr/local/lib -L/usr/lib -lmysqlcppconn
INCLUDEPATH += -I/usr/include -I/usr/local/include
               -I/usr/local/include/cppconn

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    lib/database/mysql_factory.cpp \
    lib/core_todo.cpp

HEADERS  += mainwindow.h \
    include/database/mysql_constants.h \
    include/database/mysql_factory.h \
    include/core_todo.h \
    include/preprocessor.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
