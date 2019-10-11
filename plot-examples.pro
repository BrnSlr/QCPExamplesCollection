#
#  QCustomPlot Plot Examples
#

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11
DEFINES += QCUSTOMPLOT_USE_OPENGL

TARGET = plot-examples
TEMPLATE = app

SOURCES += main.cpp\
           mainwindow.cpp \
         qcustomplot.cpp \
    axistag.cpp

HEADERS  += mainwindow.h \
         qcustomplot.h \
    axistag.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc

