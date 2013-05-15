
QT       += core gui

#TARGET = abc
TEMPLATE = app

SOURCES += main.cpp \
    dialog.cpp \
    io.cpp \
    com.cpp

HEADERS  +=  dialog.h \
    io.h \
    com.h



INCLUDEPATH += C:/qextserialport-1.2win-alpha/include
#QMAKE_LIBDIR += C:/qextserialport-1.2win-alpha/build

CONFIG      += qt warn_on console
CONFIG      += extserialport
LIBS  += -L"C:/qextserialport-1.2win-alpha/build" -lqextserialportd


INCLUDEPATH += C:/Qwt/include
#QMAKE_LIBDIR += C:/Qwt/lib

CONFIG += qwt
LIBS  += -L"C:/Qwt/lib" -lqwt

win32:DEFINES  = _TTY_WIN_

FORMS += \
    com.ui


CONFIG += debug_and_release
CONFIG(debug, debug|release) {
    CONFIG -= debug release
    CONFIG += debug
    DESTDIR = debug
    OBJECTS_DIR = debug/.obj
    MOC_DIR = debug/.moc
    RCC_DIR = debug/.rcc
    UI_DIR = debug/.ui
    DESTDIR_TARGET = abc
    TARGET = abc
}

CONFIG(release, debug|release) {
    CONFIG -= debug release
    CONFIG += release
    DESTDIR = release
    OBJECTS_DIR = release/.obj
    MOC_DIR = release/.moc
    RCC_DIR = release/.rcc
    UI_DIR = release/.ui
    DESTDIR_TARGET = abc
    TARGET = abc
}
