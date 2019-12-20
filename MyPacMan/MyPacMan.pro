QT += core gui
QT += widgets
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyPacMan
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp \
    Game_window.cpp \
    map.cpp \
    pacman.cpp \
    foodball.cpp \
    powerball.cpp \
    ghost.cpp \
    textstartend.cpp \
    sounds.cpp \
    speedball.cpp

HEADERS += \
    Game_window.h \
    map.h \
    pacman.h \
    foodball.h \
    powerball.h \
    ghost.h \
    textstartend.h \
    sounds.h \
    speedball.h

FORMS += \
    Game_window.ui

RESOURCES += \
    images.qrc \
    sounds.qrc

DISTFILES +=
