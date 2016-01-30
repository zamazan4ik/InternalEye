#-------------------------------------------------
#
# Project created by QtCreator 2016-01-29T15:29:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InternalEye
TEMPLATE = app

CONFIG += c++11\
          c++14\
          c++17


SOURCES += main.cpp\
        MainWindow.cpp \
    cpu.cpp \
    Computer.cpp \
    OperatingSystem.cpp \
    Util.cpp \
    MemoryInfo.cpp \
    DisplayInfo.cpp

HEADERS  += MainWindow.h \
    cpu.h \
    Computer.h \
    Util.h
