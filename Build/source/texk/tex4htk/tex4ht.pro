TEMPLATE = app

DEFINES -= UNICODE
DEFINES += DEBUG Debug
DEFINES += KPATHSEA
DEFINES += KPSE_DEBUG
DEFINES += QT_DEBUG

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += tex4ht.c \
    tex4ht_add.cpp \
    ../../libs/kplib/src/kpcapp.cpp \
    ../../libs/kplib/src/KpCharWgt.cpp \
    ../../libs/kplib/src/kpctype.cpp \
    ../../libs/kplib/src/chr/kptt.cpp \
    ../../libs/kplib/src/kperr.cpp \
    ../../libs/kplib/src/kpsort.cpp \
    ../../libs/kplib/src/kpstdio.cpp \
    ../../libs/kplib/src/kpstdlib.cpp \
    ../../libs/kplib/src/kpstring.cpp \
    ../../libs/kplib/src/win/kpwindow.cpp \
    ../kpathsea/progname.c \
    ../kpathsea/debug.c \
    ../kpathsea/variable.c \
    ../kpathsea/tex-file.c \
    ../kpathsea/xputenv.c \
    ../kpathsea/mingw32.c \
    ../kpathsea/xdirname.c \
    ../kpathsea/xbasename.c \
    ../kpathsea/find-suffix.c \
    ../kpathsea/rm-suffix.c \
    ../kpathsea/kpathsea.c \
    ../kpathsea/concat3.c \
    ../kpathsea/cnf.c \
    ../kpathsea/expand.c \
    ../kpathsea/xrealloc.c \
    ../kpathsea/xmalloc.c \
    ../kpathsea/xstrdup.c \
    ../kpathsea/fn.c \
    ../kpathsea/knj.c \
    ../kpathsea/kdefault.c \
    ../kpathsea/path-elt.c \
    ../kpathsea/concat.c \
    ../kpathsea/uppercasify.c \
    ../kpathsea/concatn.c \
    ../kpathsea/fontmap.c \
    ../kpathsea/pathsearch.c \
    ../kpathsea/tex-make.c \
    ../kpathsea/absolute.c \
    ../kpathsea/xcalloc.c \
    ../kpathsea/hash.c \
    ../kpathsea/xfopen.c \
    ../kpathsea/line.c \
    ../kpathsea/db.c \
    ../kpathsea/tilde.c \
    ../kpathsea/str-list.c \
    ../kpathsea/elt-dirs.c \
    ../kpathsea/extend-fname.c \
    ../kpathsea/readable.c \
    ../kpathsea/str-llist.c \
    ../kpathsea/magstep.c \
    ../kpathsea/file-p.c \
    ../kpathsea/dir.c \
    ../kpathsea/tex-hush.c

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
    tex4ht_add.h \
    kpathsea/config.h \
    ../kpathsea/fn.h \
    ../kpathsea/variable.h \
    ../kpathsea/absolute.h \
    ../kpathsea/c-ctype.h \
    ../kpathsea/c-dir.h \
    ../kpathsea/c-errno.h \
    ../kpathsea/c-fopen.h \
    ../kpathsea/c-limits.h \
    ../kpathsea/c-memstr.h \
    ../kpathsea/c-minmax.h \
    ../kpathsea/c-namemx.h \
    ../kpathsea/cnf.h \
    ../kpathsea/concatn.h \
    ../kpathsea/config.h \
    ../kpathsea/c-pathch.h \
    ../kpathsea/c-pathmx.h \
    ../kpathsea/c-proto.h \
    ../kpathsea/c-stat.h \
    ../kpathsea/c-std.h \
    ../kpathsea/c-unistd.h \
    ../kpathsea/db.h \
    ../kpathsea/debug.h \
    ../kpathsea/default.h \
    ../kpathsea/expand.h \
    ../kpathsea/fn.h \
    ../kpathsea/fontmap.h \
    ../kpathsea/getopt.h \
    ../kpathsea/hash.h \
    ../kpathsea/knj.h \
    ../kpathsea/lib.h \
    ../kpathsea/line.h \
    ../kpathsea/magstep.h \
    ../kpathsea/mingw32.h \
    ../kpathsea/pathsearch.h \
    ../kpathsea/proginit.h \
    ../kpathsea/progname.h \
    ../kpathsea/readable.h \
    ../kpathsea/simpletypes.h \
    ../kpathsea/str-list.h \
    ../kpathsea/str-llist.h \
    ../kpathsea/systypes.h \
    ../kpathsea/tex-file.h \
    ../kpathsea/tex-glyph.h \
    ../kpathsea/tex-hush.h \
    ../kpathsea/tex-make.h \
    ../kpathsea/tilde.h \
    ../kpathsea/types.h \
    ../kpathsea/variable.h \
    ../kpathsea/version.h \
    ../kpathsea/win32lib.h \
    ../kpathsea/xopendir.h \
    ../kpathsea/xstat.h

INCLUDEPATH += . ../../Work/texk/tex4htk .. ../../Work/texk \
    ../../libs/kplib/include ../../libs/kplib/src ../../libs/kplib/src/net ../../libs/kplib/src/win

# QMAKE_CXXFLAGS += -ggdb -O0
# QMAKE_CFLAGS += -ggdb -O0
# QMAKE_CFLAGS += -Waddress
# QMAKE_CFLAGS -= -Wmisleading-indentation -Wimplicit-fallthrough
# QMAKE_CFLAGS -= -Wimplicit-function-declaration
QMAKE_CFLAGS += -std=c99

# QMAKE_CXXFLAGS -= -DUNICODE
# QMAKE_CFLAGS -= -DUNICODE

# LIBS += ../../Work/texk/kpathsea/.libs/libkpathsea.a
# LIBS += D:/kp/bin/Qt/Qt5.3.2/Tools/mingw482_32/i686-w64-mingw32/lib/libmingwex.a
