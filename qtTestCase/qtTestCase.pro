QT += testlib gui sql charts core network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    tst_unittestcase.cpp \
    ../create_todolist_dialog.cpp \
    ../mainwindow.cpp \
    ../queryoption.cpp \
    ../secondmain.cpp \
    ../statistics.cpp \
    ../task_dialog.cpp \
    ../sent_notification.cpp \
    ../thirdmain.cpp

HEADERS += \
    ../create_todolist_dialog.h \
    ../mainwindow.h \
    ../queryoption.h \
    ../secondmain.h \
    ../statistics.h \
    ../task_dialog.h \
    ../sent_notification.h \
    ../thirdmain.h

FORMS += \
    ../create_todolist_dialog.ui \
    ../mainwindow.ui \
    ../secondmain.ui \
    ../statistics.ui \
    ../task_dialog.ui \
    ../thirdmain.ui

INCLUDEPATH += ../
