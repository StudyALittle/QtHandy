QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32 {
    RC_FILE = $$PWD/resource/resource.rc
}

CONFIG += c++11

include($$PWD/../Global.pri)
include($$PWD/../QtHandy/QtHandyLib.pri)

SOURCES += \
    db/dbmanager.cpp \
    db/dirgroupdb.cpp \
    db/dirgroupdirdb.cpp \
    main.cpp \
    ui/dirtoolgroupui.cpp \
    ui/dirtoolui.cpp \
    ui/homeui.cpp \
    ui/popupdirgroupdirui.cpp \
    ui/popupdirgroupui.cpp \
    ui/treedirgroupdiritemui.cpp \
    ui/treedirgroupitemui.cpp

HEADERS += \
    core/modeldefine.h \
    db/dbmanager.h \
    db/dirgroupdb.h \
    db/dirgroupdirdb.h \
    ui/dirtoolgroupui.h \
    ui/dirtoolui.h \
    ui/homeui.h \
    ui/popupdirgroupdirui.h \
    ui/popupdirgroupui.h \
    ui/treedirgroupdiritemui.h \
    ui/treedirgroupitemui.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

FORMS += \
    ui/popupdirgroupdirui.ui \
    ui/popupdirgroupui.ui \
    ui/treedirgroupdiritemui.ui \
    ui/treedirgroupitemui.ui
