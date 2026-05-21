:: @echo off

make -f Makefile_msys clean > make_dos.log 2>&1
make -f Makefile_msys >> make_dos.log 2>&1
copy tex4ht.exe xtex4ht.exe
del tex4ht.exe

:: copy xtex4ht.exe D:\texroot\2019\bin\win32
copy xtex4ht.exe D:\texroot\2024\bin\windows\tex4ht_vtex.exe
