#-------------------------------------------------
#
# Project created by QtCreator 2021-07-07T16:09:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YantoolQt
TEMPLATE = app

DEFINES += NO_ROS_FLAG

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=\
        mainwindow.cpp \
    tooldialog.cpp \
    recoverywidget.cpp \
    uploadlogwidget.cpp \
    toastdialog.cpp \
    noticedialog.cpp \
    roshelper.cpp \
    savepowerwidget.cpp \
    yan_tool_node.cpp \
    mainwidget.cpp \
    custombutton.cpp \
    icontoastdialog.cpp \
    uploadlogthread.cpp \
    recoverythread.cpp \
    customlabel.cpp \
    customtextedit.cpp \
    customstyledmenu.cpp

HEADERS  += mainwindow.h \
    tooldialog.h \
    recoverywidget.h \
    uploadlogwidget.h \
    toastdialog.h \
    noticedialog.h \
    roshelper.h \
    savepowerwidget.h \
    mainwidget.h \
    custombutton.h \
    icontoastdialog.h \
    uploadlogthread.h \
    recoverythread.h \
    customlabel.h \
    customtextedit.h \
    customstyledmenu.h

FORMS    += mainwindow.ui \
    tooldialog.ui \
    recoverywidget.ui \
    uploadlogwidget.ui \
    toastdialog.ui \
    noticedialog.ui \
    savepowerwidget.ui \
    mainwidget.ui \
    custombutton.ui \
    icontoastdialog.ui

RESOURCES += \
    res.qrc

TRANSLATIONS = yantool.ts

include(qtsingleapplication/src/qtsingleapplication.pri)
