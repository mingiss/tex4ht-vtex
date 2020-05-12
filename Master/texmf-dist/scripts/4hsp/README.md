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
https://github.com/mingiss/tex4ht-vtex
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

Naudojimas:

- šio pakatalogio failai nukopijuojami, pvz., į lokaliai kompiliuojamo failo aplanko pakatalogį `styles/4hsp`:

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

- kelias iki pakatalogio `styles/4hsp` turi būti nurodytas aplinkos kintamajame `LUA_PATH`:

```
set LUA_PATH=styles\4hsp\?.lua;%LUA_PATH%
```
