QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    createnewacount.cpp \
    main.cpp \
    mainwindow.cpp \
    queryoption.cpp \
    secondmain.cpp \
    task_dialog.cpp \
    thirdmain.cpp

HEADERS += \
    createnewacount.h \
    mainwindow.h \
    queryoption.h \
    secondmain.h \
    task_dialog.h \
    thirdmain.h

FORMS += \
    createnewacount.ui \
    mainwindow.ui \
    secondmain.ui \
    task_dialog.ui \
    thirdmain.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
