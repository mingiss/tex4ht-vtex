## ---------------------------------------
## tex4ht project using Automake
##
## Changes:
##  2013-04-04  mp  Initial creation
##

## Additional flags to pass to aclocal when it is invoked automatically at
## make time. The ${ACLOCAL_FLAGS} variable is picked up from the environment
## to provide a way for the user to supply additional arguments.
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

## Define an executable target "hello", which will be installed into the
## directory named by the predefined variable $(bindir).
bin_PROGRAMS = tex4ht

## Define the list of source files for the "hello" target. The file extension
## .cc is recognized by Automake, and causes it to produce rules which invoke
## the C++ compiler to produce an object file (.o) from each source file. The
## header files (.h) do not result in object files by themselves, but will be
## included in distribution archives of the project.
tex4ht_SOURCES = tex4ht.c

## Define an independent executable script for inclusion in the distribution
## archive. It will not be installed on an end user's system, however.
# dist_noinst_SCRIPTS = autogen.sh

default_dependencies = 

tex4ht_INCLUDES = -I../../../luatex/src/src_distr/source/texk
tex4ht_INCLUDES += -I../../../luatex/src/src_distr/build/texk

AM_CPPFLAGS = -I$(HOME)
AM_CPPFLAGS +=  -DKPATHSEA -include config.h
AM_CPPFLAGS += $(tex4ht_INCLUDES)
AM_CPPFLAGS += -g
# AM_CPPFLAGS += -D_WIN32_WINNT=0x0500
# AM_CPPFLAGS += -D UNICODE -D _UNICODE
# AM_CPPFLAGS += -mwindows -mconsole

tex4ht_LDFLAGS = -Wl,-Map,tex4ht$(EXEEXT).map
tex4ht_LDFLAGS += -static-libstdc++ -static-libgcc
tex4ht_LDFLAGS += -g
# tex4ht_LDFLAGS += -Wl,--subsystem,windows
# tex4ht_LDFLAGS += -mwindows -mconsole

LIBS = ../../../luatex/src/src_distr/build/texk/kpathsea/.libs/libkpathsea.a

