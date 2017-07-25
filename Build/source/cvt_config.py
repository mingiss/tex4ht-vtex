#!/usr/bin/env python
# coding=UTF-8

__author__ = "Mindaugas Piešina <mindaugas.piesina@vtex.lt>"
__version__ = "0.1"

"""
cvt_config.py

    Sulipdo perlaužtas config.status eilutes, pvz.
            S["DEFS"]="-DPACKAGE_NAME=\\\"TeX\\ Live\\\" -DPACKAGE_TARNAME=\\\"tex-live\\\" -DPACKAGE_VERSION=\\\"2016-05-23\\\" -DPACKAGE_STRING=\\\"TeX\\ Live\\ 2016-05-23\\\" -DPACKAGE_BU"\
            "GREPORT=\\\"tex-k@tug.org\\\" -DPACKAGE_URL=\\\"\\\" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_ME"\
            "MORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DPACKAGE=\\\"tex-live\\\" -DVERSION=\\\"2016-05-23\\\" -DLT_OBJDIR=\\\".l"\
            "ibs/\\\" -D_FILE_OFFSET_BITS=64 -DHAVE_FSEEKO=1 -DHAVE_DIRENT_H=1 -DSTDC_HEADERS=1 -DHAVE_ASSERT_H=1 -DHAVE_FLOAT_H=1 -DHAVE_LIMITS_H=1 -DHAVE_STDLIB_"\
            "H=1 -DHAVE_SYS_PARAM_H=1 -DHAVE_PUTENV=1 -DHAVE_GETCWD=1 -DHAVE_MEMCMP=1 -DHAVE_MEMCPY=1 -DHAVE_MKSTEMP=1 -DHAVE_MKTEMP=1 -DHAVE_STRCHR=1 -DHAVE_STR"\
            "RCHR=1 -DHAVE_DECL_ISASCII=1 -DX_DISPLAY_MISSING=1"
        i viena
            S["DEFS"]="-DPACKAGE_NAME=\\\"TeX\\ Live\\\" -DPACKAGE_TARNAME=\\\"tex-live\\\" -DPACKAGE_VERSION=\\\"2016-05-23\\\" -DPACKAGE_STRING=\\\"TeX\\ Live\\ 2016-05-23\\\" -DPACKAGE_BUGREPORT=\\\"tex-k@tug.org\\\" -DPACKAGE_URL=\\\"\\\" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DPACKAGE=\\\"tex-live\\\" -DVERSION=\\\"2016-05-23\\\" -DLT_OBJDIR=\\\".libs/\\\" -D_FILE_OFFSET_BITS=64 -DHAVE_FSEEKO=1 -DHAVE_DIRENT_H=1 -DSTDC_HEADERS=1 -DHAVE_ASSERT_H=1 -DHAVE_FLOAT_H=1 -DHAVE_LIMITS_H=1 -DHAVE_STDLIB_H=1 -DHAVE_SYS_PARAM_H=1 -DHAVE_PUTENV=1 -DHAVE_GETCWD=1 -DHAVE_MEMCMP=1 -DHAVE_MEMCPY=1 -DHAVE_MKSTEMP=1 -DHAVE_MKTEMP=1 -DHAVE_STRCHR=1 -DHAVE_STRRCHR=1 -DHAVE_DECL_ISASCII=1 -DX_DISPLAY_MISSING=1" 

    Naudojamas Automake scriptų paleidimui Windowsuose (MSYS'e) -- sprendžia ./configure klaidą
        gawk: ./confrphLUA/subs.awk:114: S["DEFS"]="-DPACKAGE_NAME=\\\"TeX\\ Live\\\" -DPACKAGE_TARNAME=\\\"tex-live\\\" -DPACKAGE_VERSION=\\\"2016-05-23\\\" -DPACKAGE_STRING=\\\"TeX\\ Live\\ 2016-05-23\\\" -DPACKAGE_BU"\
        gawk: ./confrphLUA/subs.awk:114:                                                                                                                                                                                    ^ backslash not last character on line
    Scripto iškvietimas įklijuojamas į configure failą prieš config.status iškvietimą
        $SHELL $CONFIG_STATUS
    Tai galima padaryti, pvz., komandomis:
        cp configure configure.tmp
        sed 's/\$SHELL \$CONFIG_STATUS/cp \$CONFIG_STATUS \$CONFIG_STATUS.tmp; python cvt_config\.py < \$CONFIG_STATUS.tmp \> \$CONFIG_STATUS; \$SHELL \$CONFIG_STATUS/' < configure.tmp > configure

Syntax:
    cp config.status config.status.tmp
    python cvt_config.py < config.status.tmp > config.status 

Changelog:
    2017-07-21  mp  initial creation

"""


import sys
import re
# from enum import Enum

# class Mode(Enum):
#     scan
#     concat

# skanerio būsena -- kintamojo mode reikšmės
mode_scan = 0       # pradinis skanavimas
mode_concat = 1     # pratęsimo eilučių apjungimas

# mode = Mode.scan
mode = mode_scan

# kaupiama eilutė, apjungta su pratęsimais
concat_line = ""

# ---------------------------
while 1:
    try:
        line = sys.stdin.readline()
    except KeyboardInterrupt:
        break

    if not line:
        break

    # numetam eilutės pabaigą
    line = line.split("\n")[0]

#   flds = line.split("\"]=\"")
#   if (len(flds) > 1):
#       if (flds[0] == "S[\"DEFS"):

    # ar priskyrimo eilutė?
    assignment = re.search("S\[\"[A-Z,a-z,0-9,_]+\"\]\=\".*", line)

    # ar eilutė turi pratęsimą -- ar galas su "\ ?
    flds = line.split("\"\\")
    continues = (len(flds) > 1) and (flds[-1] == "")

    if (assignment and continues) or (mode == mode_concat):
        if continues:
            mode = mode_concat
            # numetam pratęsimo požymį "\ gale
            del flds[-1]
            line = "\"\\".join(flds)
        if not assignment:
            # pratęsimo eilutės turi prasidėti kabutėm
            flds = line.split("\"")
            if (len(flds) > 1) and (flds[0] == ""):
                # kabutes numetam
                del flds[0]
                line = "\"".join(flds)
            else:
                raise ValueError("Pratęsimo eilutė be kabučių pradžioje: " + line)
        # kaupiam apjungtą eilutę
        concat_line += line
        if not continues:
            # kaupimas baigėsi -- išvedam sukauptą eilutę
            print concat_line
            concat_line = ""
            mode = mode_scan
    else:
        print line
