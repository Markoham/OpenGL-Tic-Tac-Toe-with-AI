TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ai.cpp \
    board.cpp \
    engine.cpp \
    game.cpp

include(deployment.pri)
qtcAddDeployment()

LIBS += -lGL -lglfw

HEADERS += \
    ai.h \
    board.h \
    engine.h \
    settings.h \
    game.h
