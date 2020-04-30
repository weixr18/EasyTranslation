#-------------------------------------------------
#
# Project created by QtCreator 2019-07-06T10:26:54
#
#-------------------------------------------------

# This is 2.0 version of the project.
# Reconstruction may fail.

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyTranslation
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 c++14

SOURCES += \
    main.cpp\
    src/aplmcfmdialog.cpp \
    src/apltcfmdialog.cpp \
    src/cfmdialog.cpp \
    src/chargecfmdialog.cpp \
    src/chargepage.cpp \
    src/checktranslation.cpp \
    src/choosemanager.cpp \
    src/choosetranslator.cpp \
    src/chsmcfmdialog.cpp \
    src/Datum.cpp \
    src/DBOP.cpp \
    src/DBOP2.cpp \
    src/homepage.cpp \
    src/homepage2.cpp \
    src/lastsubmittal.cpp \
    src/login.cpp \
    src/mainwindow.cpp \
    src/managemission.cpp \
    src/message.cpp \
    src/messagebox.cpp \
    src/mission.cpp \
    src/mission2.cpp \
    src/missionassign.cpp \
    src/missionhall.cpp \
    src/missioninfo.cpp \
    src/p_mng.cpp \
    src/p_msn.cpp \
    src/p_sub.cpp \
    src/p_user.cpp \
    src/paycfmdialog.cpp \
    src/payformission.cpp \
    src/Platform.cpp \
    src/Platform2.cpp \
    src/rcrtmfailproc.cpp \
    src/regist.cpp \
    src/regist_2.cpp \
    src/regist_3.cpp \
    src/releasemission.cpp \
    src/releasemission_2.cpp \
    src/stateupdatec.cpp \
    src/stateupdatew.cpp \
    src/submission.cpp \
    src/submittranslation.cpp \
    src/user.cpp \
    src/useraccount.cpp \
    src/userinfo.cpp

HEADERS += \
    src/aplmcfmdialog.h \
    src/apltcfmdialog.h \
    src/cfmdialog.h \
    src/chargecfmdialog.h \
    src/chargepage.h \
    src/checktranslation.h \
    src/choosemanager.h \
    src/choosetranslator.h \
    src/chsmcfmdialog.h \
    src/Datum.h \
    src/DBOP.h \
    src/homepage.h \
    src/lastsubmittal.h \
    src/login.h \
    src/mainwindow.h \
    src/managemission.h \
    src/message.h \
    src/messagebox.h \
    src/mission.h \
    src/missionassign.h \
    src/missionhall.h \
    src/missioninfo.h \
    src/p_mng.h \
    src/p_msn.h \
    src/p_sub.h \
    src/p_user.h \
    src/paycfmdialog.h \
    src/payformission.h \
    src/Platform.h \
    src/rcrtmfailproc.h \
    src/regist.h \
    src/regist_2.h \
    src/regist_3.h \
    src/releasemission.h \
    src/releasemission_2.h \
    src/stateupdatec.h \
    src/stateupdatew.h \
    src/submission.h \
    src/submittranslation.h \
    src/user.h \
    src/useraccount.h \
    src/userinfo.h

FORMS += \
    ui/cfmdialog.ui \
    ui/chargepage.ui \
    ui/checktranslation.ui \
    ui/choosemanager.ui \
    ui/choosetranslator.ui \
    ui/homepage.ui \
    ui/lastsubmittal.ui \
    ui/login.ui \
    ui/messagebox.ui \
    ui/missionassign.ui \
    ui/missionhall.ui \
    ui/missioninfo.ui \
    ui/payformission.ui \
    ui/rcrtmfailproc.ui \
    ui/regist.ui \
    ui/regist_2.ui \
    ui/regist_3.ui \
    ui/releasemission.ui \
    ui/releasemission_2.ui \
    ui/start_page.ui \
    ui/stateupdatew.ui \
    ui/submittranslation.ui \
    ui/useraccount.ui \
    ui/userinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += ./src

DISTFILES += \
    Note1 \
    ProjectFile.txt

QT       += core gui sql

# disable C4819 warning
# QMAKE_CXXFLAGS_WARN_ON += -wd4819
