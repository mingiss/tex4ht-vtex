#! /bin/sh

# cd /home/mingis/F/kp/src/vtex/tex/luatex/src/src_distr
## ./build.sh --debug > build.log 2>&1
# ./build.sh > build.log 2>&1

## cd /home/mingis/F/kp/src/vtex/tex/tex4ht/src_kp/tex4ht
## ./build.sh > build.log 2>&1

rm depcomp
autoscan
aclocal
autoheader
automake --add-missing
autoconf
./configure

cp depcomp depcomp_

echo "//" >> config.h
echo "#undef HAVE_UNISTD_H" >> config.h

./make.sh
