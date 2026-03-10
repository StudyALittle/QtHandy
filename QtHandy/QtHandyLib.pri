QT += gui widgets network svg

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/core
INCLUDEPATH += $$PWD/core/logger
INCLUDEPATH += $$PWD/components
INCLUDEPATH += $$PWD/components/style
INCLUDEPATH += $$PWD/components/framelesswindow
INCLUDEPATH += $$PWD/components/basic
INCLUDEPATH += $$PWD/components/complex
INCLUDEPATH += $$PWD/components/customized
INCLUDEPATH += $$PWD/util

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../QtHandyBin_Debug
} else {
    LIBS += -L$$PWD/../../QtHandyBin_Release
}
LIBS += -lQtHandy
