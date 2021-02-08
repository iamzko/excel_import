QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include(./QtXlsxWriter/src/xlsx/qtxlsx.pri)
include(./qtsingleapplication/src/qtsingleapplication.pri)
#QT      += xlsx
#设置了RC_FILE，那末RC_ICONS，及以下QMAKE_TARGET_XXXX就失效了
win32:RC_FILE = myapp.rc

#RC_ICONS = Resource/title.ico
##版本信息
#VERSION = 0.0.1
##公司名称
#QMAKE_TARGET_COMPANY = "cnki"
##产品名称
#QMAKE_TARGET_PRODUCT = "接收登记"
##文件说明
#QMAKE_TARGET_DESCRIPTION = "接收登记"
##版权信息
#QMAKE_TARGET_COPYRIGHT = "Copyright 2021- The CNKI Company Ltd. All rights reserved."
##语言
#RC_LANG = 0x0004

CONFIG(release,debug|releasea):
{
DEFINES += QT_NO_WARNING_OUTPUT
DEFINES += QT_NO_DEBUG_OUTPUT
}
INCLUDEPATH += src/

SOURCES += \
    ExcelFormat/BasicExcel.cpp \
    ExcelFormat/ExcelFormat.cpp \
    UnitTest/testmainwindow.cpp \
    src/config.cpp \
    src/errortoshow.cpp \
    src/excelchecker.cpp \
    src/excelfieldrule.cpp \
    src/excelreader.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/myglobal.cpp \
    src/sheetmodel.cpp \
    src/sheetmodelprivate.cpp

HEADERS += \
    ExcelFormat/BasicExcel.hpp \
    ExcelFormat/ExcelFormat.h \
    UnitTest/testmainwindow.h \
    src/config.h \
    src/errortoshow.h \
    src/excelchecker.h \
    src/excelfieldrule.h \
    src/excelreader.h \
    src/mainwindow.h \
    src/myglobal.h \
    src/sheetmodel.h \
    src/sheetmodelprivate.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    excel_import_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
