------------------------------------------------------------------------------
--  4hsp.lua
--      tex4hp tarpų \special generatorius
--      kiekvienam reikšminiam tarpui sugeneruoja komandą \special{}
--      kad tex4hp nereikėtų užsiiminėti tarpų atpažinimu pagal layout'o intervalus
--
--      Scenarijus aktyvuojamas LuaTex kompiliatoriaus iškvietimo komandoje
--          pridėjus parinktį --lua=4hsp.lua
--      Pvz.:
--          luatex.exe --fmt=lualatex --progname=latex --lua=4hsp.lua foo.tex
--
--  2017  Mindaugas Piešina, mindaugas.piesina@vtex.lt
--
--  Changelog:
--      2017-05-17  mp  initial implementation as token_filter.inc
--      2017-05-18  mp  4hsp.lua, \special{t4ht=\&\#32;}
--      2017-05-19  mp  \special{t4ht= }
--      2017-05-19  mp  attempt to filter actual file tokens using open_read_file callback
--      2017-07-14  mp  using luatex with toktrc add-on
--      2017-07-25  mp  using luatex with toktrc add-on
--
-- TODO:
--      endlines (\par) as spaces too; combined spaces / endlines to single space
--
--      <paraclass="nopar"> suvalgo tarpą tago viduje, turi būti <para class="nopar">
--
--      lygint normalizuotus rezultatus
--
--      reikia ilgesnės kakos, kokio nors @sp@
--          @ neužtenka, nes @ ir taip reikia tekste (emailams)
--          tada reikia postprocesinimo toolo, apjungiančio gretimus identiškus tagus -- ilgos kakos pabyra į kelis pasikartojančius tagus
--
--      arba kokio unicodinio nenaudojamo simbolio
--          kaip įvest -- dabar kažkur susivalgo ar į kažką konvertuojasi
--
--      patyrinėt, kodėl netinka \special
--
--      stack for storing status (cur_cmd / cur_cmd_csname / cur_cmd_grp_lev / cur_par_val / cur_par_val_str / cur_status / cur_cmd_par_num)
--          for nested command parameters (when parameters consist of other commands with parameters)
--
--      nesuveikia cur_cmd_par_num > cur_status -- komandos parametrus skanuoja iki cur_grp_lev grįžimo į pradinį cur_cmd_grp_lev (\begin{multicolumns}{2})
--          tada bus blogai, jei grįžimo iš vis nėra -- tekstas po komandos vėl figūriniuose skliaustuose
--
------------------------------------------------------------------------------

-------------------------------
-- Definitions
-------------------------------

local tokqueue = {}         -- queue for posponed generated tokens; elements -- token triples of {tcmd, tchcode, tid}

-- paskutinė skanavimo būsena
local last_cur_lnum = 0     -- einamosios input failo eilutės nr.
local last_cur_lpos = 0     -- einamosios input failo eilutės pozicija

local spc_cnt = 0
local first_space = false   -- first space of theorem body

local cur_grp_lev = 0       -- group level counter -- tex.currentgrouplevel

local cmds = {}             -- list of defined commands; keys -- command csnames, elements -- numbers of parameters
cmds["begin"] = 1           -- parameter #1: name of the environment
cmds["end"] = 1             -- parameter #1: name of the environment
cmds["newtheorem"] = 2      -- parameters: #1: name, #2: title

local cur_status = 0        -- current scanner status --  order number of current parameter of cur_cmd
local cur_cmd_grp_lev = 0   -- group level at cmd name reading phase
local cur_cmd = nil         -- token triple of command currently scanned -- {tcmd, tchcode, tid}
local cur_cmd_csname = ""
local cur_cmd_par_num = 0   -- total number of parameters of command currently being scanned
local cur_par_val = {}      -- current parameter value as token array; elements -- token triples of {tcmd, tchcode, tid}
local cur_par_val_str = ""  -- parameter value string representation

local envs = {}             -- stack of environments; elements - environment name strings

local theorems = {}         -- list of theorems; elements -- theorem names

------------------------------------------------
-- returns true when stack envs contains environment value
function belongs_to(list, value)
    for _, elem in pairs(list)
    do
        if (value == elem)
        then
            return true
        end
    end
    return false
end

---------------------------------------------------------------
-- "token_filter" calback'o funkcija
-- ties tarpais įterpinėja \special{t4ht= }
-- @param token.get_next() -- eilinis tex tokenas iš input srauto
-- @return tok -- gražinamas eilinis tokenas -- iš srauto ar iš generavimo eilės tokqueue
---------------------------------------------------------------
function token_filter_callback()
    local tok

    local is_space = false
    local inserted = false
    local ins_warn = ""

    if (#tokqueue > 0)
    then
        tok = tokqueue[1]
        table.remove(tokqueue, 1)
        inserted = true
        ins_warn = "!!!"
    else
        tok = token.get_next()
    end

    local tcmd = tok[1] -- tokeno simbolio klasė
    local tchcode = tok[2] -- tokeno simbolio kodas
    local tid = tok[3] -- tokeno id
    local csname = token.csname_name(tok)
    local cmdname = token.command_name(tok)

    local cur_fname = get_cur_fname() -- einamojo input failo vardas
    local cur_lnum = get_cur_lnum()   -- einamosios input failo eilutės nr.
    local cur_lpos = get_cur_lpos()   -- einamosios input failo eilutės pozicija

    -------------------------------------------------
    -- tikrinam, ar reikia procesinti
    local proceed = false

    -- tikrinam mainfilename
    -- cfgt.default.mainfilename == "" atveju suveiks -- rezultatas bus 1
    local fname_ix = cur_fname:find(cfgt.default.mainfilename)
    if (fname_ix)
    then 
        if (fname_ix == 1)
        then
            -- atmetam tuos, kur mainfilename yra tik dalis cur_fname
            --      failo vardo (fname_ix > 1)
            proceed = true -- failo vardas sutampa tiksliai 
        else
            if (cur_fname:sub(fname_ix - 1, fname_ix - 1) == "/")
            then
                -- cur_fname yra substringas "/" .. cfgt.default.mainfilename
                proceed = true
            end
        end
    end

    -- ar pasikeitė pagrindinio failo pozicija? 
    if (proceed)
    then
        -- "top_token_tracer" callback'ui pagrindinio failo požymį
        -- tikrinti reikia tik alltokens = Calls atveju
--      if (cfgt.default.alltokens ~= true)
--      then -- "no" or "calls"
            -- procesinam, tik jei pasikeitė einamojo failo būsena --
            --      pagal tai atpažįstam perėjimą prie naujo tokeno pagrindiniam faile
            if ((cur_lnum == last_cur_lnum) and
                (cur_lpos == last_cur_lpos))
            then
                proceed = false
            end
--      end
    end

    ------------------
    -- group level
--  cur_grp_lev = tex.currentgrouplevel
    if (proceed)
    then
        if (tcmd == left_brace_cmd) then cur_grp_lev = cur_grp_lev + 1 end
        if (tcmd == right_brace_cmd) then cur_grp_lev = cur_grp_lev - 1 end
    end

    ------------------
    -- textual representation of tchcode
    local char_code = 0
    local csname_tmp = ""
    if
    (
        (tcmd == spacer_cmd) or
        (tcmd == letter_cmd) or
        (tcmd == other_char_cmd) or
        (tcmd == char_given_cmd) or
        (tcmd == left_brace_cmd) or
        (tcmd == right_brace_cmd) or
        (tcmd == math_shift_cmd) or
        (tcmd == tab_mark_cmd) or
        (tcmd == sup_mark_cmd) or
        (tcmd == sub_mark_cmd) or
        (tcmd == mac_param_cmd)
    )
    then
        if (tchcode < 256)
        then
            csname_tmp = string.char(tchcode)
        else
            csname_tmp = string.format("<??? " .. perc_chr .. "d>", tchcode)
        end
        char_code = tchcode
    end

    local csname_out = ""
    csname_out = cvt_out(csname_tmp)

    ----------------------------------------
    -- procesinam
    if (proceed and not inserted)
    then
        ---------------------------
        -- environment scanning
        if (cur_status > 0)
        then
            table.insert(cur_par_val, toc)
            cur_par_val_str = cur_par_val_str .. csname_out

            if (cur_grp_lev == cur_cmd_grp_lev)
            then
                -- baigiam eilinio parametro skanavimą
                if (cur_cmd_csname == "begin") and (cur_status == 1)
                then
                    -- atidarom aplinką
                    table.insert(envs, cur_par_val_str)

                    if ((belongs_to(theorems, cur_par_val_str)) or (cur_par_val_str == "{thebibliography}"))
                    then
                        first_space = true
                    end
                end

                if (cur_cmd_csname == "end") and (cur_status == 1)
                then
                    if (#envs < 1)
                    then
                        print ("Error: trying to close unopened environment " .. cur_par_val_str)
                    else
                        if (envs[#envs] ~= cur_par_val_str)
                        then
                            print ("Error: trying to close environment " .. cur_par_val_str .. " when inside of environment " .. envs[#envs])
                        else
                            -- uždarom
                            table.remove(envs, #envs)
                        end
                    end
                end

                if (cur_cmd_csname == "newtheorem") and (cur_status == 1) and (cur_par_val_str ~= "*")
                then
                    -- pildom teoremų sąrašą
                    table.insert(theorems, cur_par_val_str)
                end

                if (cur_cmd_par_num > cur_status)
                then
                    -- TODO: process starred commands
                    if ((cur_status ~= 1) or (cur_par_val_str ~= "*"))
                    then
                        -- kitas parametras
                        cur_status = cur_status + 1
                    end
                else
                    -- parametrai baigėsi
                    -- grįžtam į bazinę būseną
                    cur_status = 0
                    cur_cmd = nil
                    cur_cmd_csname = ""
                    cur_cmd_par_num = 0
                    cur_cmd_grp_lev = 0
                end
                cur_par_val = {}
                cur_par_val_str = ""
            end
        end

        if ((cur_status == 0) and (cmds[csname] ~= nil))
        then
            cur_cmd = tok
            cur_cmd_csname = csname
            cur_cmd_par_num = cmds[csname]
            cur_cmd_grp_lev = cur_grp_lev

            cur_par_val = {}
            cur_par_val_str = ""
            if (cur_cmd_par_num > cur_status) then cur_status = cur_status + 1 end
        end

        local cur_env = ""
        if (#envs > 0) then cur_env = envs[#envs] end

        --------------------------
        -- insertion of spaces
        if (tcmd == spacer_cmd)
        then
            is_space = true
            spc_cnt = spc_cnt + 1
        end


        if (is_space) and
            (belongs_to(envs, "{document}") or
                (cur_cmd_csname == "newtheorem")) and -- teoremų pavadinimai
-- čia lūžta, jei \special
--          (spc_cnt ~= 15) and -- \newtheorem*{maintheorem*}{Main Theorem}
--          (spc_cnt ~= 141) and (spc_cnt ~= 142) and (spc_cnt ~= 143) and -- \section{Introduction and main result}
-- čia lūžta, jei '@' ir 'x'
            (not first_space) and -- pirmas tarpas iškart po \begin{maintheorem*} ar \begin{thebibliography}{18}
            (not belongs_to(envs, "{figure}"))
        then

            if (false)
            then
-- \special{t4ht= }
-- 59  3   14076       0   special extension
-- TODO: išsitraukti tchcode (3) ir tid (14076) pagal macro vardą ("special")
                table.insert(tokqueue, {extension_cmd, 3, 14076})
-- 1   123 0   {   0       left_brace
                table.insert(tokqueue, {left_brace_cmd, string.byte("{", 1), 0})
-- 11  116 0   t   0       letter
                table.insert(tokqueue, {letter_cmd, string.byte("t", 1), 0})
-- 12  52  0   4   0       other_char
                table.insert(tokqueue, {other_char_cmd, string.byte("4", 1), 0})
-- 11  104 0   h   0       letter
                table.insert(tokqueue, {letter_cmd, string.byte("h", 1), 0})
-- 11  116 0   t   0       letter
                table.insert(tokqueue, {letter_cmd, string.byte("t", 1), 0})
-- 12  61  0   =   0       other_char
                table.insert(tokqueue, {other_char_cmd, string.byte("=", 1), 0})
-- 10  32  0   <32>    1       spacer
                table.insert(tokqueue, {spacer_cmd, string.byte(" ", 1), 0})
-- 2   125 0   }   0       right_brace
                table.insert(tokqueue, {right_brace_cmd, string.byte("}", 1), 0})
            end

            if (false)
            then
-- \special{t4ht=\&\#32;}
-- 59	3	14076		special	extension	0	0		0
-- TODO: išsitraukti tchcode (3) ir tid (14076) pagal macro vardą ("special")
                table.insert(tokqueue, {extension_cmd, 3, 14076})
-- 1	123	0	{		left_brace	0	0		0
                table.insert(tokqueue, {left_brace_cmd, string.byte("{", 1), 0})
-- 11	116	0	t		letter	0	0		0
                table.insert(tokqueue, {letter_cmd, string.byte("t", 1), 0})
-- 12	52	0	4		other_char	0	0		0
                table.insert(tokqueue, {other_char_cmd, string.byte("4", 1), 0})
-- 11	104	0	h		letter	0	0		0
                table.insert(tokqueue, {letter_cmd, string.byte("h", 1), 0})
-- 11	116	0	t		letter	0	0		0
                table.insert(tokqueue, {letter_cmd, string.byte("t", 1), 0})
-- 12	61	0	=		other_char	0	0		0
                table.insert(tokqueue, {other_char_cmd, string.byte("=", 1), 0})
-- 72	38	40	&	&	char_given	0	0		0
-- TODO: išsitraukti tid (40) pagal macro vardą ("&")
--                      table.insert(tokqueue, {char_given_cmd, string.byte("&", 1), 40})
                table.insert(tokqueue, {other_char_cmd, string.byte("&", 1), 0})
-- \# praleidžiam, paliekam tik jo skleidimą '#'
-- 126	257505	37		#	call	0	0		0
-- 12	35	0	#		other_char	0	0		0
                table.insert(tokqueue, {other_char_cmd, string.byte("#", 1), 0})
-- 12	51	0	3		other_char	0	0		0
                table.insert(tokqueue, {other_char_cmd, string.byte("3", 1), 0})
-- 12	50	0	2		other_char	0	0		0
                table.insert(tokqueue, {other_char_cmd, string.byte("2", 1), 0})
-- 12	59	0	;		other_char	0	0		0
                table.insert(tokqueue, {other_char_cmd, string.byte(";", 1), 0})
-- 2	125	0	}		right_brace	0	0		0
                table.insert(tokqueue, {right_brace_cmd, string.byte("}", 1), 0})
            end

            if (false)
            then
-- &#32;
                table.insert(tokqueue, {char_given_cmd, string.byte("&", 1), 40}) -- šitą kažkas suvalgo, iki *.uni failo nenueina
                table.insert(tokqueue, {other_char_cmd, string.byte("#", 1), 0})
                table.insert(tokqueue, {other_char_cmd, string.byte("3", 1), 0})
                table.insert(tokqueue, {other_char_cmd, string.byte("2", 1), 0})
                table.insert(tokqueue, {other_char_cmd, string.byte(";", 1), 0})
            end

            if (true)
            then
                table.insert(tokqueue, {other_char_cmd, string.byte("@", 1), 0})
--                  table.insert(tokqueue, {other_char_cmd, string.byte("#", 1), 0})
--                  table.insert(tokqueue, {other_char_cmd, string.byte("#", 1), 0})
--                  table.insert(tokqueue, {letter_cmd, string.byte("x", 1), 0})
           end

            if (false)
            then
-- \zzz
--                  table.insert(tokqueue, {call_cmd, ???, 0})
            end

-- ․
-- ⁕
-- †
            if (false)
            then
-- ·
                table.insert(tokqueue, {other_char_cmd, string.byte("·", 1), 0})
           end

        end

        if (is_space) then first_space = false end

    end -- if (proceed and not inserted)

    if (proceed or inserted)
    then
        local cmd_par_num = -1
        if (cmds[csname] ~= nil)
        then
            cmd_par_num = cmds[csname]
        end

        logfile:write(
            tcmd, tabs_allign(tostring(tcmd), 2),
            char_code, tabs_allign(tostring(char_code), 2),
            tid, tabs_allign(tostring(tid), 2),
            csname_out, tabs_allign(csname_out, 4),
            csname, tabs_allign(csname, 4),
            cmdname, tabs_allign(cmdname, 4),
            cur_fname, tabs_allign(cur_fname, 4),
            cur_lnum, tab_chr,
            cur_lpos, tab_chr,
            spc_cnt, tabs_allign(tostring(spc_cnt), 2),
            tostring(is_space), tab_chr,
            tostring(inserted), tab_chr,
            ins_warn, tab_chr,
            #tokqueue, tab_chr)

        for _, env in pairs(envs)
        do
            logfile:write(env, tab_chr)
        end
        logfile:write("||", tab_chr)

        for _, tt in pairs(tokqueue)
        do
            logfile:write(tt[2], tab_chr)
        end

        logfile:write(eol_chr)

        last_cur_lnum = cur_lnum
        last_cur_lpos = cur_lpos

    end -- if (proceed)

    return tok
end

-------------------------------
-- Darbo pabaigos callback'as
-------------------------------
function stop_run_callback()
    logfile:close()
end

-------------------------------
-- Initiation
-------------------------------
require("tokinit")

logfile = io.open("4hsp.log", "w")

callback.register("token_filter", token_filter_callback)
callback.register("stop_run", stop_run_callback)
