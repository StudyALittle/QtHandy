QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

include($$PWD/../Global.pri)
include($$PWD/../QtHandy/QtHandyLib.pri)

SOURCES += \
    main.cpp \
    qsstest.cpp \
    widget.cpp

HEADERS += \
    qsstest.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
