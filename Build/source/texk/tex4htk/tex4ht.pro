TEMPLATE = app

DEFINES -= UNICODE
DEFINES += DEBUG Debug
# DEFINES += KPATHSEA

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += tex4ht.c \
    tex4ht_add.cpp \
    ../../libs/kplib/src/kpcapp.cpp \
    ../../libs/kplib/src/KpCharWgt.cpp \
    ../../libs/kplib/src/kpctype.cpp \
    ../../libs/kplib/src/kperr.cpp \
    ../../libs/kplib/src/kpsort.cpp \
    ../../libs/kplib/src/kpstdio.cpp \
    ../../libs/kplib/src/kpstdlib.cpp \
    ../../libs/kplib/src/kpstring.cpp \
    ../../libs/kplib/src/win/kpwindow.cpp

HEADERS += \
    ../../libs/kplib/include/kpctype.h \
    ../../libs/kplib/include/kperr.h \
    ../../libs/kplib/include/kperrno.h \
    ../../libs/kplib/include/kpmsg.h \
    ../../libs/kplib/include/kpstdio.h \
    ../../libs/kplib/include/kpstdlib.h \
    ../../libs/kplib/include/kpstring.h \
    ../../libs/kplib/include/kptt.h \
    ../../libs/kplib/src/kpcapp.h \
    ../../libs/kplib/src/kpmsg_en.h \
    ../../libs/kplib/src/kpsort.h \
    ../../libs/kplib/src/kptree.h \
    tex4ht_add.h

INCLUDEPATH += ../../Work/texk/tex4htk ../../libs/kplib/include ../../libs/kplib/src ../../libs/kplib/src/net ../../libs/kplib/src/win

# QMAKE_CXXFLAGS += -ggdb -O0
# QMAKE_CFLAGS += -ggdb -O0
# QMAKE_CFLAGS += -Waddress

# QMAKE_CXXFLAGS -= -DUNICODE
# QMAKE_CFLAGS -= -DUNICODE
