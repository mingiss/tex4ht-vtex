# `tex4ht-vtex`

Enhanced version of the `tex4ht` converter.


## Add-ons to the module `tex4ht`


### Space recognition

Following are attempts to deal with the problem, that original heuristic recognition of
spaces in `tex4ht` doesn't work correctly enough &ndash; there are situations with
disappearing or redundant spaces.

- Command line switch `-r`

  Correction of spaces recognition threshold

  The percentage of the initial threshold value should be provided:

      -r100   no change, the algorithm operates as usual;

      -r50    threshold of spaces generation is increased twice &ndash; resulting
                amount of spaces decreases;

      -r200   threshold decreased by half &ndash; more spaces;

  Feature at the moment activated outside of math equations solely &ndash;
  spaces inside of formulae meet more sophisticated postprocessing
  (are converted to `<mml:mspace width="2.5pt" />`, for example),
  therefore, more investigations should be carried out here.

- command line switch -n

  Totally cuts off the heuristic algorithm for recognition of spaces in `.dvi` file;
  spaces then should be generated using some explicit means, for example by
  inserting commands

      \special{t4ht=\&\#32;}

  into the source `.tex` file. It could be done using the script 

      Master/texmf-dist/scripts/4hsp/4hspship.lua

  Look corresponding `README` for details:

    > https://github.com/mingiss/tex4ht-vtex/blob/master/Master/texmf-dist/scripts/4hsp/README.md


### `OpenType` font character encoding

Character mappings are provided during `LaTex` file compilation by additional
`LuaTeX` script `luafonts.lua`.
Encoding files are placed in a subdirectory of the working folder named `.xdvips`.
They are used instead of *.htf encoding files.

`OpenType` font encoding exporter `luafonts.lua` with supplementing `LaTeX` styles could
be found at

> https://github.com/vtex-soft/texlive.xdvipsk/tree/master/Master/texmf-dist/tex/luatex/luafonts

Follow instructions as provided in the file

> https://github.com/vtex-soft/texlive.xdvipsk/blob/master/README.overview.md

sections `Opentype font support` and `Running xdvipsk`.

Alternatively encoding extractor script `extractdvipsk.lua` could be used:

> https://github.com/michal-h21/extractxdvipsk.git


### Math sub/superscripts base

Attempt to solve the problem in `MathML` sub/superscript tag sending back algorithm.

The problem arises in case of baseless sub/superscript, for instance:

    $a_b{}^c$

`tex4ht` has a mechanism of sub/superscript base searching through sending
back initial `MathML` tags prior to the last printable character. In case
when that character already is inside of a previous tagged structure,
the not well-formed output file is produced. Such back-sending
is organized through `DVI` file specials `t4ht~<*`.

Following modification implemented: when in between of the last printable
character and the sub/superscript there are verbatim insertions `t4ht=`,
containing tag characters `<` or `>` (`XML`/`HTML`/`MathML` tags hopefully),
back sending of the initiating tags is suppressed, resulting in the verbatim
insertion of the special `t4ht~<*` contents right in the place, where it was
encountered. (The result is like as the special `t4ht~<*` was entered as
`t4ht=`.)

- Command line option `-p` switches on the enhanced superscript base recognition algorithm.


### Math letters conversion to their Latin equivalents

Letters with `bold`, `italic`, `fraktur`, `sans-serif`, etc. attributes in math equations
could be represented as `Unicode` characters in corresponding code ranges.
There is implemented possibility to convert such letters to their Latin counterparts.  

- Command line switch `-m` switches on the conversion of math `Unicode` letters to their Latin equivalents,
  enveloped into corresponding math variant `MathML` tags with corresponding attributes.


### Grouping of math classes

When configuring math clases to particulary symbols, `tex4ht` converter assigns them not to individual fonts,
rather to font families, grouped according to the tree structure of `.htf` files.
For example, the top level family file of the `cmmib` font is the `cmmi.htf` &ndash;
math classes of the bold italic and regular italic fonts are managed together.
Therefore, when assigning bold class to some symbol of `cmmib` font,
the corresponding symbol of the `cmmi` font will obtain the bold class as well:

      Master/test/math_class/test2_group.out.html

Source files:

      Master/test/math_class/test2.tex
      Master/test/math_class/article.4ht

- The problem could be partially solved by enhancing the `.htf` font tree structure &ndash;
adding individual `.htf` file for the font `cmmib` as well:

      Master/test/math_class/cmmib.htf

- Alternativelly the command line parameter `-a` has been added to the `tex4ht` converter
to switch off the font grouping feature during the math class assignement.
Example result file, using the `-a` switch:

      Master/test/math_class/test2.out.html


## Repository structure

Designed as a mirror copy of `TeX Live` (`TL`) build tree structure.

There are problems in running standard `TL` script `Build/source/reautoconf` under `MS Windows`
in `MSYS` environment, hence an additional set of prepared configure scripts are provided.

Modified executables and libraries should be copied from the repository folder `Master/bin` to
the relevant local `TL` deployment path, for example, either

    D:\texroot\texlive2010\bin

or

    /usr/local/texlive/2016/bin


## Prerequisites

For the use of the GNU Automake environment under `MS Windows` following tools should be
additionally installed:

- `MinGW` `gcc` compiler:

  > https://sourceforge.net/projects/mingw-w64/files/latest/download?source=files

  Be careful &ndash; Bitdefender antivirus complains about
  `MinGW v.7.1.0 build 4.3.0` distribution package of `05.03.2017` &ndash;
  files `mingw32\opt\bin\python*.exe` and `mingw32\bin\gdb.exe` are
  recognized as infected by malware `Gen:Variant.Razy.191694`.
  Be prepared to delete these files or use another `MinGW` distribution,
  `v.5.1.0` for instance:

  > https://sourceforge.net/projects/tdm-gcc/files/latest/download?source=rw_typ_t5

  (not tested yet)

  Path of installed binaries

      %ProgramFiles%\mingw-w64\i686-7.1.0-posix-dwarf-rt_v5-rev0\mingw32\bin

  should be added to the environment variable `PATH`

- `MSYS` `POSIX` shell environment:

  > https://sourceforge.net/projects/mingw-w64/files/External%20binary%20packages%20%28Win64%20hosted%29/MSYS%20%2832-bit%29/MSYS-20111123.zip/download

- GNU Autoconf / Automake:

  > http://gnuwin32.sourceforge.net/packages/automake.htm
  > http://gnuwin32.sourceforge.net/packages/autoconf.htm
  > http://gnuwin32.sourceforge.net/packages/m4.htm
  > http://gnuwin32.sourceforge.net/packages/regex.htm


## Build sequence and optional build possibilities

### TeXlive automake scripts

- `win32`, `win64`, `x86_64-linux` and `x86_64-darwin` targets.

- Mount current `TL` repository version to some local path:

      svn co svn://username:password@tug.org/texlive/trunk

- Overwrite original `TL` source files with those provided here.
  The whole tree has to be overwritten, supposing the root of this repo with the subfolders `Build/source` and `Master` 
  contain all additional or changed files for the `TL` tree subfolders `trunk/Build/source and trunk/Master`.
  This repo could be simply mapped to the same folder, where the `TL` `trunk` is mapped &ndash; 
  the rest of `TL` files will be separated from `git` scope using `.gitignore`. 

- Execute scripts:

      cd Build/source
      ./reautoconf            (not for `MS Windows` `MSYS` environment)
      ./Build_tex4ht.sh

- Resulting binary executables are created here:

      Build/source/Work/texk/tex4htk/tex4ht     (tex4ht.exe)

- and manually copied to the relevant deployment path inside of

      Master/bin

- Following `MingW` system library files should be copied to the deployment folder:

      libgcc_s_dw2-1.dll
      libstdc++-6.dll
      libwinpthread-1.dll

`reautoconf` does not work yet under `MSYS`. Necessary slightly corrected `Linux` build
environment configure scripts are provided here.


### Make under `MSYS`

- `win64` or `win32` (?) targets only.

- Simple makefile for build in `MSYS` environment using `MingW` compiler:

      Build/source/texk/tex4htk/Makefile_msys

- The shell script:

      Build/source/texk/tex4htk/make_msys

- `Kpathsea` package is linked statically, no need for external `kpathsea*.dll` file.

- Necessary `MingW` system library files should be copied to the deployment folder.


### `QT Creator`

- `win32`, `win64` (?) or `x86_64-linux` (?) targets.

- `QT v.5` (`QT Creator v.4`) build script:

      Build/source/texk/tex4htk/tex4ht.pro

- `Kpathsea` package is linked statically, no need for external `kpathsea*.dll`/`kpathsea*.so` file.

- In case of `MS Windows` build necessary `MingW` system library files should be copied to the deployment folder.


### `MS Visual Studio`

- `win32` or `win64` (?) targets only.

- `MSVC v.17` (`VS 2022`) project and solution files:

      Build/source/texk/tex4htk/tex4htx_vs17/tex4htx_vs17.sln
      Build/source/texk/tex4htk/tex4htx_vs17/tex4htx_vs17.vcxproj

- `Kpathsea` package is linked statically, no need for external `kpathsea*.dll` file.

- Following `MSVC` system library files should be copied to the deployment folder:

      msvcp140d.dll
      vcruntime140d.dll
      ucrtbased.dll


## TODO

- [x] Bug in command line parameters recognition:

   command line

        tex4ht foo -cunihtf -n

   is not recognized until the order of parameters is changed to

        tex4ht foo -n -cunihtf

    - The limitation to enter all single letter keys prior to the keys with values is intentional, file `tex4ht.c`:

          if( (int) strlen((char *)  argv[i] ) == 2 ){
             if( ++i == argc ) bad_arg;

- [ ] Additional option for switching on the action of the feature `-r` for inside of equations as well.

- [ ] Additional functionality to the script `4hspship.lua` &ndash; output of mathematical
   spaces in the form `<mml:mspace width="2.5pt" />` instead of calculating
   them as product of count of space characters generated and font space width.

- [ ] `reautoconf` under `MSYS`

- [ ] MathML sub/superscript tag sending back algorithm:
   Stepping over is not allowed not just through tags, entered inside of verbatim
   specials `t4ht=`. All tag insertion specials, including `t4ht~<*` itself,
   should be examined as well.

- [ ] Extract space width feature of `OpenType` fonts instead of calculating median character width.

- [ ] Integrate `OpenType` encoding extractor functionality `extractdvipsk.lua` into the `tex4ht` binary &ndash;
   instant extraction of encodings, generated by `luaotfload` scripts.

- [ ] Implement generation of `OpenType` encodings as sets of `.htf` files, corresponding to
   the virtual internal subsets of the `OpenType` fonts, generated by `luaotfload`.
   Could be either instant dynamic or permanently prepared during installation of the `TeX` environment.
   No need for additional `OpenType` features in the `tex4ht` converter then.

- [ ] Merge `TL2019` changes, especially for processing of `XDV` files produced by `XeTeX`.

- [ ] Provide font `<span>` tags with `@class` or `@style` attributes
   according to font style keywords (`italic` / `bold` / `monospaced`) generated by `extractdvipsk.lua`
   instead of `@class` attributes with simply decorated font name.

- [ ] Example with Arabic font.

- [ ] Rebuild `Linux` executable.

- [ ] Mathematic font features.
  - Extract font style features (`italic` / `bold` / `monospaced`) using `luafonts.lua` script as well;
  - in case of no success &ndash; directly from the `.otf` files using the `FreeType` library.

- [ ] Escape characters `<`, `>` and `&` to their `HTML` entity equivalents when used in `OpenType` fonts.

- [ ] Move `Build\source\libs\kplib` features to `tex4ht_add.h` and `tex4ht_add.cpp`, remove `Build\source\libs\kplib`.

- [ ] Rename `tex4ht_vtex` / `tex4ht-vtex` to `xtex4ht`.

- [ ] Free all allocated memory (`font_tbl[].name`, `font_tbl[].family_name`, `font_tbl[].htf_family_name`, `font_tbl[].math`, `font_tbl[].math_closing`, etc.).
