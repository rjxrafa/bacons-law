TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    src/mylib.cpp \
    src/parser.cpp

HEADERS += \
    include/mylib.h \
    include/parser.h
