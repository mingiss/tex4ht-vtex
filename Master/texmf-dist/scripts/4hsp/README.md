## `tex4ht` tarpų įterpinėjimo `script`ai

Skirti `tex4ht` konverterio tarpų atpažinimo problemų apeidinėjimui.
`tex4ht` konverteris tarpus dokumento maketo faile `.idv` atpažįsta, skaičiuodamas atstumus tarp teksto elementų.
Jei tas atstumas viršija tam tikrą slenkstį, generuojamas tarpas.
Algoritmas neveikia idealiai, būna situacijų, kai tarpų prigeneruojama kur nereikia, ar jie iš viso neatpažįstami &ndash;
atsiranda tarpų žodžių viduryje, ar žodžiai sulimpa.

Problema buvo bandyta spręsti, modifikuojant `tex4ht` konverterį &ndash; realizuoti du papildomi vykdomojo modulio raktai:

- `-r` &ndash; tarpų atpažinimo slenksčio reikšmės korekcijai &ndash; po rakto nurodoma korekcijos koeficiento procentinė išraiška;

- `-n` &ndash; visiškam tarpų atpažinimo mechanizmo atjungimui. Pastaruoju atveju failas turi būti kompiliuojamas, naudojant vieną iš šioje saugykloje pateikiamų skriptų.

Detaliau žr. failą README saugykloje

```
https://gitlab.vtex.vmt/texgr/tex4ht-vtex.git
```

Surinkti vykdomieji moduliai yra šios saugyklos aplanke `Master`, `win32` versija yra ir `texroot` medyje šalia originalaus `tex4ht` konverterio failo:

```
X:\texroot\2016\bin\win32\tex4ht_vtex.exe
```
 

### `4hspship.lua`

Naudojamas `callback`as `pre_output_filter`.

Po kiekvieno `glue` tipo `node`o įterpiamas `whatsit` `node`as (`\special`) su reikšme `"t4ht= "`.

Dabartinė būsena: kaip ir veikia, bet reikia daug rankinio testavimo &ndash;
`.uni` failus lyginti su pagamintais nekoreguotu `tex4ht` konverteriu ir tikrinti,
ar neatsirado žalingų skirtumų.

Saugyklos:

- šios saugyklos failai turi būti nuklonuoti, pvz., į lokaliai kompiliuojamo failo aplanko pakatalogį `styles/4hsp`:

```
mkdir styles
cd styles
git clone https://gitlab.vtex.vmt/mindaugas.piesina/4hsp.git
```

- į pakatalogį `styles/toktrc_common` papildomai klonuojami tokenų bibliotekos failai:

```
git clone https://gitlab.vtex.vmt/mindaugas.piesina/toktrc_common.git
```

- failas `styles/toktrc_common/toktrc.cfg` turi būti nukopijuotas į darbinį aplanką.

Naudojimas:

- `.tex` failas kompiliuojamas komanda:

```
vtex 2016 4ht iosmlatex foo.tex draft "-n" "" --lua=styles/4hsp/4hspship.lua
```

- `callback`ai inicijuojami komandomis:

```
\RequirePackage{luatexbase}
\directlua{
   luatexbase.add_to_callback('pre_output_filter', spship_insert_spaces, 'Insert tex4ht spaces')
   luatexbase.add_to_callback('stop_run', close_spship_log, 'Close 4hspship.log')
   }
```

- keliai iki pakatalogių `styles/4hsp` ir `styles/toktrc_common` turi būti nurodyti aplinkos kintamajame `LUA_PATH`:

```
set LUA_PATH=styles\4hsp\?.lua;styles\toktrc_common\?.lua;%LUA_PATH%
```
 
- pateiktas ir pakoreguotas kompiliavimo skriptas `iosmlatex.bat`, kurį galima naudoti, įsikopijavus lokaliai į kompiliuojamo failo aplanką;
anksčiau nurodytų komandų tada nebereikia.  

### `4hsp.lua`

 Naudojamas `callback`as `token_filter`.

Po kiekvieno `spacer` klasės `token`o bandom įterpinėt `\special{t4ht= }`, `\special{t4ht=\&\#32;}` ar kokią nors simbolinę makrokomandą ("@", "@sp@" ar "†"),
kuri po to .uni faile postprocesinimo metu keičiama į tarpus.

Dabartinė būsena &ndash; yra problemų:

- reikia naudoti tokenų `tracer`iu papildytą `luatex` kompiliatorių `toktrc`

- `\special` kimba teoremų apibrėžimuose (teoremos pavadinimo parametre), `\section` pavadinimo parametre --
`luatex` kompiliatorius tiesiog sustoja ir nieko nedaro, klaidos neišveda

- su tekstinėm makrokomandom geriau, kimba tik figūrose ir ties pirmu teoremų ar bibliografijos aplinkų tarpu;
su `toktrc` palaikančiu `luatex` kompiliatorium šitas situacijas pavyko išgaudyti

- kelių simbolių makrokomandos .uni faile suskyla į kelis gretimus identiškus (fontų) tagus, reikia postprocesinimo utilitos jų apjungimui atgal
