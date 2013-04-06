
QT       += core gui

TARGET = abc
TEMPLATE = app

SOURCES += main.cpp \
    dialog.cpp \
    io.cpp \
    com.cpp

HEADERS  +=  dialog.h \
    io.h \
    com.h


INCLUDEPATH += C:/Users/Sun/Desktop/Qt/qextserialport/src/
QMAKE_LIBDIR += C:/Users/Sun/Desktop/Qt/qextserialport/build/

CONFIG      += qt warn_on console

LIBS  += -lqextserialportd1


INCLUDEPATH += C:/Users/Sun/Desktop/Qt/Qwt-6.0.1/include/
QMAKE_LIBDIR += C:/Users/Sun/Desktop/Qt/Qwt-6.0.1/lib/

CONFIG += qwt

LIBS  += -lqwt

win32:DEFINES  = _TTY_WIN_

FORMS += \
    com.ui
