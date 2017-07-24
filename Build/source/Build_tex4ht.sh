#! /bin/bash

export distribution=2010
# export distribution=2016

# if [ ! -f configure.orig ]; then cp configure configure.orig; fi
# sed 's/\$SHELL \$CONFIG_STATUS/cp \$CONFIG_STATUS \$CONFIG_STATUS.tmp; python \.\.\/cvt_config\.py < \$CONFIG_STATUS\.tmp \> \$CONFIG_STATUS; \$SHELL \$CONFIG_STATUS/' < configure.orig > configure

mkdir Work
cd Work

# ../configure --disable-autosp --disable-devnag --disable-lacheck --disable-m-tx --disable-make2unc --disable-pmx --disable-ps2eps --disable-t1utils --disable-texdoctk --disable-tpic2pdftex --disable-vlna --disable-xpdfopen --disable-ptex --disable-eptex --disable-uptex --disable-euptex --disable-aleph --disable-pdftex --disable-mp --disable-pmp --disable-upmp --disable-xetex --disable-mf --disable-afm2pl --disable-bibtex-x --disable-bibtex8 --disable-bibtexu --disable-chktex --disable-cjkutils --disable-detex --disable-dtl --disable-dvi2tty --disable-dvidvi --disable-dviljk --disable-dvipdfm-x --disable-dvipng --disable-dvipos --disable-dvipsk --disable-dvisvgm --disable-ed_dvipsk --disable-gregorio --disable-gsftopk --disable-lcdf-typetools --disable-cfftot1 --disable-mmafm --disable-mmpfb --disable-otfinfo --disable-otftotfm --disable-t1dotlessj --disable-t1lint --disable-t1rawafm --disable-t1reencode --disable-t1testpage --disable-ttftotype42 --disable-makeindexk --disable-makejvf --disable-mendexk --disable-musixtnt --disable-ps2pk --disable-psutils --disable-seetexk --disable-luatex --disable-ttf2pk2 --disable-ttfdump --disable-upmendex --disable-xdvik --disable-xdvipsk --disable-texlive -C CFLAGS=-g CXXFLAGS=-g
../configure --disable-all-pkgs --without-x --disable-xetex --disable-xindy --enable-tex4htk -C CFLAGS=-g CXXFLAGS=-g
make

if [ "x$WINDIR" == "x" ]; then
sudo cp texk/tex4htk/tex4ht /usr/local/texlive/$distribution/bin/x86_64-linux
fi
