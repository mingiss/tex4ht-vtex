#! /bin/bash

# ./reautoconf > reautoconf.log 2>&1    -- not for Windows
# ./Build_tex4ht.sh > Build_tex4ht.sh.log 2>&1

if [ "x$WINDIR" == "x" ]; then
export distribution=2016
else
export distribution=2010
fi

cd tex4ht-lit
# errors here could be ignored
if [ "x$WINDIR" == "x" ]; then
./tex4ht-c.sh
# else
# ./tex4ht-c.bat
fi
cd ..
cp tex4ht-lit/tex4ht.c texk/tex4htk/tex4ht.c

# if [ ! -f configure.orig ]; then cp configure configure.orig; fi
# sed 's/\$SHELL \$CONFIG_STATUS/cp \$CONFIG_STATUS \$CONFIG_STATUS.tmp; python \.\.\/cvt_config\.py < \$CONFIG_STATUS\.tmp \> \$CONFIG_STATUS; \$SHELL \$CONFIG_STATUS/' < configure.orig > configure

mkdir Work
cd Work

# ../configure --disable-autosp --disable-devnag --disable-lacheck --disable-m-tx --disable-make2unc --disable-pmx --disable-ps2eps --disable-t1utils --disable-texdoctk --disable-tpic2pdftex --disable-vlna --disable-xpdfopen --disable-ptex --disable-eptex --disable-uptex --disable-euptex --disable-aleph --disable-pdftex --disable-mp --disable-pmp --disable-upmp --disable-xetex --disable-mf --disable-afm2pl --disable-bibtex-x --disable-bibtex8 --disable-bibtexu --disable-chktex --disable-cjkutils --disable-detex --disable-dtl --disable-dvi2tty --disable-dvidvi --disable-dviljk --disable-dvipdfm-x --disable-dvipng --disable-dvipos --disable-dvipsk --disable-dvisvgm --disable-ed_dvipsk --disable-gregorio --disable-gsftopk --disable-lcdf-typetools --disable-cfftot1 --disable-mmafm --disable-mmpfb --disable-otfinfo --disable-otftotfm --disable-t1dotlessj --disable-t1lint --disable-t1rawafm --disable-t1reencode --disable-t1testpage --disable-ttftotype42 --disable-makeindexk --disable-makejvf --disable-mendexk --disable-musixtnt --disable-ps2pk --disable-psutils --disable-seetexk --disable-luatex --disable-ttf2pk2 --disable-ttfdump --disable-upmendex --disable-xdvik --disable-xdvipsk --disable-texlive -C CFLAGS=-g CXXFLAGS=-g
../configure --disable-all-pkgs --without-x --without-ln-s --disable-xetex --disable-xindy --enable-tex4htk -C CFLAGS=-g CXXFLAGS=-g

mkdir texk/tex4htk
cd texk/tex4htk
../../../texk/tex4htk/configure  '--disable-option-checking' '--prefix=/usr/local' '--disable-all-pkgs' '--without-x' '--disable-xetex' '--disable-xindy' '--enable-tex4htk' 'CFLAGS=-g' 'CXXFLAGS=-g' '--enable-native-texlive-build' '--enable-largefile' '--disable-silent-rules' '--enable-multiplatform=yes' '--enable-cxx-runtime-hack=yes' '--enable-libtool-hack=yes' '--disable-shared' '--enable-texlive-build' '--bindir=${exec_prefix}/bin/i686-pc-mingw32' '--libdir=${exec_prefix}/lib/i686-pc-mingw32' '--enable-autosp=no' '--enable-devnag=no' '--enable-lacheck=no' '--enable-m-tx=no' '--enable-pmx=no' '--enable-ps2eps=no' '--enable-t1utils=no' '--enable-texdoctk=no' '--enable-tpic2pdftex=no' '--enable-vlna=no' '--with-clisp-runtime=default' '--disable-xpdfopen' '--enable-web2c=no' '--enable-afm2pl=no' '--enable-bibtex-x=no' '--enable-chktex=no' '--enable-cjkutils=no' '--enable-detex=no' '--enable-dtl=no' '--enable-dvi2tty=no' '--enable-dvidvi=no' '--enable-dviljk=no' '--enable-dvipdfm-x=no' 
cd ../..

if [ ! -f texk/tex4htk/Makefile.orig ]; then cp texk/tex4htk/Makefile texk/tex4htk/Makefile.orig; fi
# sed 's/@CXX@/g++/; s/@CXXFLAGS@/$(CFLAGS)/; s/@am__fastdepCXX_TRUE@//; s/@am__fastdepCXX_FALSE@/#/; s/..\/libs\/kplib\/src\/kpsort.cpp ..\/..\/libs\/kplib\/src\/kpcapp.cpp/..\/..\/libs\/kplib\/src\/kpsort.cpp ..\/..\/libs\/kplib\/src\/win\/kpwindow.cpp ..\/..\/libs\/kplib\/src\/kpcapp.cpp/; s/..\/..\/libs\/kplib\/src\/kpsort.\$(OBJEXT) \\/..\/..\/libs\/kplib\/src\/kpsort.\$(OBJEXT) ..\/..\/libs\/kplib\/src\/win\/kpwindow.$(OBJEXT) \\/' < texk/tex4htk/Makefile.orig > texk/tex4htk/Makefile
sed 's/@CXX@/g++/; s/@CXXFLAGS@/$(CFLAGS)/; s/@am__fastdepCXX_TRUE@//; s/@am__fastdepCXX_FALSE@/#/' < texk/tex4htk/Makefile.orig > texk/tex4htk/Makefile

make

if [ "x$WINDIR" == "x" ]; then
sudo cp texk/tex4htk/tex4ht /usr/local/texlive/$distribution/bin/x86_64-linux
else
cp texk/tex4htk/tex4ht.exe /D/texroot/texlive$distribution/bin/win32
fi
