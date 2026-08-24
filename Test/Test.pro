QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

include($$PWD/../Global.pri)
include($$PWD/../QtHandy/QtHandyLib.pri)

SOURCES += \
    main.cpp \
    qhmcomboboxtest.cpp \
    qsstest.cpp \
    testwidgettable.cpp \
    widget.cpp

HEADERS += \
    qhmcomboboxtest.h \
    qsstest.h \
    testwidgettable.h \
    widget.h

FORMS += \
    qhmcomboboxtest.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
