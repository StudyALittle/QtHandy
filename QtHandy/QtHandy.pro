QT += gui widgets network svg xml sql

TEMPLATE = lib
DEFINES += QTHANDY_LIBRARY

CONFIG += c++11

include($$PWD/../Global.pri)

# mode QCustomplot
#DEFINES += USE_MODULE_QCUSTOMPLOT
contains(DEFINES, USE_MODULE_QCUSTOMPLOT) {
    message('module: USE_MODULE_QCUSTOMPLOT')
    include($$PWD/3rdparty/qcustomplot/qcustomplot.pri)

    SOURCES += \
    components/chart/qhcustomplotex.cpp

    HEADERS += \
    components/chart/qhcustomplotex.h \
    components/chart/qhcustomplotex_p.h
}

INCLUDEPATH += $$PWD/core
INCLUDEPATH += $$PWD/core/logger
INCLUDEPATH += $$PWD/components
INCLUDEPATH += $$PWD/components/style
INCLUDEPATH += $$PWD/components/framelesswindow
INCLUDEPATH += $$PWD/components/basic
INCLUDEPATH += $$PWD/components/complex
INCLUDEPATH += $$PWD/components/customized
INCLUDEPATH += $$PWD/util

SOURCES += \
    components/basic/qhcheckbox.cpp \
    components/basic/qhcombobox.cpp \
    components/basic/qhimagebutton.cpp \
    components/basic/qhlabel.cpp \
    components/basic/qhlineedit.cpp \
    components/basic/qhlineeditdatetime.cpp \
    components/basic/qhprogressbar.cpp \
    components/basic/qhpushbutton.cpp \
    components/basic/qhradiobutton.cpp \
    components/basic/qhscrollbar.cpp \
    components/basic/qhslider.cpp \
    components/basic/qhtextedit.cpp \
    components/complex/qhdatepicker.cpp \
    components/complex/qhdatetimepicker.cpp \
    components/complex/qhfloating.cpp \
    components/complex/qhnavbar.cpp \
    components/complex/qhnavbaritem.cpp \
    components/complex/qhnavbarproxy.cpp \
    components/complex/qhpaging.cpp \
    components/complex/qhtimepicker.cpp \
    components/customized/qhbasepopup.cpp \
    components/customized/qhbasepopupcontent.cpp \
    components/customized/qhloading.cpp \
    components/customized/qhmessagebox.cpp \
    components/framelesswindow/qhframelesswindow.cpp \
    components/framelesswindow/qhframelesswindow_unix.cpp \
    components/framelesswindow/qhframelesswindow_windows.cpp \
    components/framelesswindow/qhwidgetmoveresize.cpp \
    components/framework/qhpage.cpp \
    components/framework/qhpagemanager.cpp \
    components/framework/qhwidgetzoom.cpp \
    components/style/qhqss.cpp \
    components/style/qhqssmanager.cpp \
    components/style/qhqssparser.cpp \
    core/datebase/qhdatabase.cpp \
    core/datebase/qhsqltemplate.cpp \
    core/logger/qhlogger.cpp \
    core/logger/qhloggerfileappender.cpp \
    core/qhsingletonprocess.cpp \
    util/qhfileutil.cpp \
    util/qhimageutil.cpp \
    util/qhutil.cpp \
    util/qhwidgetutil.cpp \
    util/semvertool.cpp

HEADERS += \
    QH_global.h \
    components/basic/qhcheckbox.h \
    components/basic/qhcheckbox_p.h \
    components/basic/qhcombobox.h \
    components/basic/qhcombobox_p.h \
    components/basic/qhimagebutton.h \
    components/basic/qhimagebutton_p.h \
    components/basic/qhlabel.h \
    components/basic/qhlabel_p.h \
    components/basic/qhlineedit.h \
    components/basic/qhlineedit_p.h \
    components/basic/qhlineeditdatetime.h \
    components/basic/qhlineeditdatetime_p.h \
    components/basic/qhprogressbar.h \
    components/basic/qhpushbutton.h \
    components/basic/qhpushbutton_p.h \
    components/basic/qhradiobutton.h \
    components/basic/qhscrollbar.h \
    components/basic/qhslider.h \
    components/basic/qhtextedit.h \
    components/basic/qhtextedit_p.h \
    components/complex/qhdatepicker.h \
    components/complex/qhdatepicker_p.h \
    components/complex/qhdatetimepicker.h \
    components/complex/qhdatetimepicker_p.h \
    components/complex/qhfloating.h \
    components/complex/qhfloating_p.h \
    components/complex/qhnavbar.h \
    components/complex/qhnavbar_p.h \
    components/complex/qhnavbaritem.h \
    components/complex/qhnavbarproxy.h \
    components/complex/qhpaging.h \
    components/complex/qhpaging_p.h \
    components/complex/qhtimepicker.h \
    components/complex/qhtimepicker_p.h \
    components/customized/qhbasepopup.h \
    components/customized/qhbasepopup_p.h \
    components/customized/qhbasepopupcontent.h \
    components/customized/qhloading.h \
    components/customized/qhloading_p.h \
    components/customized/qhmessagebox.h \
    components/customized/qhmessagebox_p.h \
    components/framelesswindow/qhframelesswindow.h \
    components/framelesswindow/qhframelesswindow_p.h \
    components/framelesswindow/qhwidgetmoveresize.h \
    components/framelesswindow/qhwidgetmoveresize_p.h \
    components/framework/qhpage.h \
    components/framework/qhpage_p.h \
    components/framework/qhpagemanager.h \
    components/framework/qhpagemanager_p.h \
    components/framework/qhwidgetzoom.h \
    components/framework/qhwidgetzoom_p.h \
    components/style/qhqss.h \
    components/style/qhqss_p.h \
    components/style/qhqssmanager.h \
    components/style/qhqssparser.h \
    core/datebase/qhdatabase.h \
    core/datebase/qhdatabase_p.h \
    core/datebase/qhsqltemplate.h \
    core/datebase/qhsqltemplate_p.h \
    core/logger/qhlogger.h \
    core/logger/qhlogger_p.h \
    core/logger/qhloggerfileappender.h \
    core/logger/qhloggerfileappender_p.h \
    core/qhdtwrapper.h \
    core/qhsingletonprocess.h \
    core/qhsingletonprocess_p.h \
    qhdefine.h \
    qhmacro.h \
    util/qhfileutil.h \
    util/qhimageutil.h \
    util/qhutil.h \
    util/qhwidgetutil.h \
    util/semvertool.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../README.md
