QT       += core gui network charts webengine webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    OAuthClient/authdialog.cpp \
    apiauthenticator.cpp \
    devicesdialog.cpp \
    easyhttp.cpp \
    main.cpp \
    mainwindow.cpp \
    wifiapi.cpp

HEADERS += \
    OAuthClient/authdialog.h \
    apiauthenticator.h \
    devicesdialog.h \
    easyhttp.h \
    mainwindow.h \
    wifiapi.h

FORMS += \
    OAuthClient/authdialog.ui \
    devicesdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
