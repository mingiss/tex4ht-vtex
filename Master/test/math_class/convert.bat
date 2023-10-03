set jobname=test2

:: set TEX4HTBIN=tex4ht.exe
:: set TEX4HTBIN=tex4ht_vtex.exe
:: set TEX4HTBIN=E:\vtex\tex4htx\src\tex4htx\src\tex4ht-vtex\Build\source\texk\build-tex4ht-Desktop_Qt_5_3_MinGW_32bit-Debug\debug\win32\tex4ht.exe
:: set TEX4HTBIN=E:\vtex\tex4htx\src\tex4htx\src\tex4ht-vtex\Build\source\texk\tex4htk\tex4htx_vs17\Debug\win32\tex4htx_vs17.exe
:: set TEX4HTBIN=tex4htx_vs17.exe
:: set TEX4HTBIN=tex4htx.exe
set TEX4HTBIN=tex4htx_msys.exe

:: set TEX4HTFONTSET=unified,alias,iso8859,unicode

:: set TEXMF=D:\texroot\vtex-dist

set KPATHSEA_DEBUG=4

:: call vtex 2019 %TEX4HTBIN% %jobname% -cunihtf > tex4htx.log 2>&1
call vtex 2019 %TEX4HTBIN% %jobname% -hm -a -cunihtf > tex4htx.log 2>&1

tidy.exe -xml -wrap 300 -indent -utf8 -o %jobname%.out.html %jobname%.html

