#-------------------------------------------------
#
# Project created by QtCreator 2013-06-23T22:49:52
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = MyZip
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += QUAZIP_BUILD
CONFIG(staticlib): DEFINES += QUAZIP_STATIC

SOURCES += main.cpp \
    quazip/zip.c \
    quazip/unzip.c \
    quazip/quazipnewinfo.cpp \
    quazip/quazipfileinfo.cpp \
    quazip/quazipfile.cpp \
    quazip/quazipdir.cpp \
    quazip/quazip.cpp \
    quazip/quaziodevice.cpp \
    quazip/quagzipfile.cpp \
    quazip/quacrc32.cpp \
    quazip/quaadler32.cpp \
    quazip/qioapi.cpp \
    quazip/JlCompress.cpp

HEADERS += \
    quazip/zip.h \
    quazip/unzip.h \
    quazip/quazipnewinfo.h \
    quazip/quazipfileinfo.h \
    quazip/quazipfile.h \
    quazip/quazipdir.h \
    quazip/quazip_global.h \
    quazip/quazip.h \
    quazip/quaziodevice.h \
    quazip/quagzipfile.h \
    quazip/quacrc32.h \
    quazip/quachecksum32.h \
    quazip/quaadler32.h \
    quazip/JlCompress.h \
    quazip/ioapi.h \
    quazip/crypt.h
