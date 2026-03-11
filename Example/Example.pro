QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

include($$PWD/../Global.pri)
include($$PWD/../QtHandy/QtHandyLib.pri)

SOURCES += \
    demobutton.cpp \
    democheckbox.cpp \
    demodatetime.cpp \
    demoimagebutton.cpp \
    demolabel.cpp \
    demolineedit.cpp \
    demolineeditdatetime.cpp \
    demonavbarproxy.cpp \
    demopaging.cpp \
    demopopup.cpp \
    demotextedit.cpp \
    demowidget.cpp \
    main.cpp \
    popupway1.cpp \
    popupway2.cpp

HEADERS += \
    demobutton.h \
    democheckbox.h \
    demodatetime.h \
    demoimagebutton.h \
    demolabel.h \
    demolineedit.h \
    demolineeditdatetime.h \
    demonavbarproxy.h \
    demopaging.h \
    demopopup.h \
    demotextedit.h \
    demowidget.h \
    popupway1.h \
    popupway2.h

FORMS += \
    popupway2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
