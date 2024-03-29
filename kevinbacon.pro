TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    src/mylib.cpp \
    src/parser.cpp \
    src/graph.cpp \
    src/menu.cpp

HEADERS += \
    include/map.h \
    include/mylib.h \
    include/parser.h \
    include/graph.h \
    include/actorcrew.h \
    include/myqueue.h \
    include/avl.h \
    include/menu.h \
    include/node.h
