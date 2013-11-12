TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
    src/simplex.c \
    src/main.c

HEADERS += \
    src/simplex.h

OTHER_FILES += \
    test/Example.lp

