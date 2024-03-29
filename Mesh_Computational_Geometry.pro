#-------------------------------------------------
#
# Project created by QtCreator 2018-08-28T10:55:17
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mesh_Computational_Geometry
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gldisplaywidget.cpp \
    mesh.cpp \
    Iterator.cpp

HEADERS  += mainwindow.h \
    gldisplaywidget.h \
    mesh.h \
    iterator.h

FORMS    += mainwindow.ui

#---- Comment the following line on MacOS
LIBS = -lGLU
#LIBS += -lglu32
#LIBS += -lOpengl32
QMAKE_CXXFLAGS += -std=c++0x

DISTFILES += \
    test.txt
