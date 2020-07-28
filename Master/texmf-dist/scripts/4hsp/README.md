## `tex4ht` scripts for inserting of explicit spaces

Used for eliminating problems of heuristic space recognition of `tex4ht`.
`tex4ht` converter recognizes spaces by means of measuring geometric intervals between text elements in `.dvi` file of the document layout. 
When that interval exceeds some certain threshold, the `xml` space is generated.
The algorithm doesn't function ideally, there are situations with excess or missing spaces &ndash;
for example, spaces in the middle of the words or stuck words. 

The problem was intended to solve by modifications of `tex4ht` converter &ndash; two additional command line switches have been implemented:

- `-r` &ndash; correction of the space recognition threshold &ndash; the switch should be followed by the percentage value of the correction factor;

- `-n` &ndash; switch off the space recognition. In this case the `.tex` file should be compiled using one of the scripts provided in this repo.

Look the main `README` file in this repository:

https://github.com/mingiss/tex4ht-vtex/blob/master/README.md

Built executables of the updated converter are stored in the folder `Master` of this repository.
 

### `4hspship.lua`

The script uses the `LuaTeX` callback `pre_output_filter`.
It inserts the `whatsit` (`\special`) node with the value `"t4ht= "`
after each `glue` or `kern` node (corresponding to real spaces in the source file).

Using:

- files of this folder could be copied to the local folder of the `.tex` file being compiled;

- the header of the `.tex` file should be supplemented with the command 

```
    \RequirePackage{4hspship}
```

- resulting `XML` file should be extracted using modified converter `tex4ht_vtex` with space recognition switched off:

```
    tex4ht_vtex foo -n
```
