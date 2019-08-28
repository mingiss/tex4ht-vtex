------------------------------------------------------------------------------
-- tokinit.lua
--
--      Bendri toktrc paveldėtų projektų dalykai
--

-----------------------------
-- konfigūracinio failo parsinimo modulis
ConfigParser = require "configparser"

-----------------------------
-- globalios konstantos

-- TeX'ą laužiančių simbolių kodai; reikia, jei naudojam \directlua{}
tab_chr = string.char(9)            -- "\t"
eol_chr = string.char(10)           -- "\n"
cr_chr = string.char(10)            -- "\r"
hash_chr = string.char(35)          -- "#"
perc_chr = string.char(37)          -- "%"
bslash_chr = string.char(92)        -- "\\"
underscore_chr = string.char(95)    -- "_"

-- konstantos *_cmd -- komandų kodai, command code,
--      pirmo tokeno lentelės elemento tok[1] reikšmės
relax_cmd = 0               -- \relax
spacer_cmd = 10             -- spacer " "
letter_cmd = 11             -- letter
other_char_cmd = 12         -- other_char
char_given_cmd = 72         -- char_given
assign_int_cmd = 78         -- assign_int
left_brace_cmd = 1          -- left_brace "{"
right_brace_cmd = 2         -- right_brace "}"
math_shift_cmd = 3          -- math_shift "$"
tab_mark_cmd = 4            -- tab_mark "&"
sup_mark_cmd = 7            -- sup_mark "^"
sub_mark_cmd = 8            -- sub_mark "_"
extension_cmd = 59          -- \special
begin_group_cmd = 61        -- begin_group \begingroup
end_group_cmd = 62          -- end_group \endgroup
call_cmd = 126              -- call
long_call_cmd = 127         -- long_call
outer_call_cmd = 128        -- outer_call
long_outer_call_cmd = 129   -- long_outer_call
undefined_cs_cmd = 116      -- undefined_cs
cs_name_cmd = 122           -- cs_name \csname
end_cs_name_cmd = 69        -- end_cs_name \endcsname
let_cmd = 107               -- let \let \futurelet
def_cmd = 110               -- def \def \edef \gdef \xdef
shorthand_def_cmd = 108     -- shorthand_def \chardef \countdef
mac_param_cmd = 6           -- mac_param "#"


----------------------------------
-- konfigūracinio failo vardas
toktrc_cfg_fname = "toktrc.cfg"

----------------------------------
-- toktrc.cfg parametrų lentelė
--      konfigūracijos parametras mypar pasiekiamas per
--          cfgt["default"]["mypar"] arba cfgt.default.mypar
cfgt = {}

-------------
-- toktrc.cfg parametrų leistinos reikšmės

cfgv = {}
cfgv["mainfilename"]    = {true, false}
cfgv["tracelevel"]      = {"filter", "tracer", "internal"}
cfgv["tracefilename"]   = {true, false}
cfgv["alltokens"]       = {true, "calls", false}
cfgv["tracetokcnt"]     = {"all", "listed", "none"}
cfgv["tracelpos"]       = {true, false}
cfgv["tracetcmd"]       = {true, false}
cfgv["tracecmdname"]    = {true, false}
cfgv["tracetchcode"]    = {true, false}
cfgv["tracetext"]       = {true, false}
cfgv["tracetid"]        = {true, false}
cfgv["tracegrplev"]     = {true, false}
cfgv["tracemathmode"]   = {true, false}
cfgv["traceixlev"]      = {true, false}
cfgv["tracefont"]       = {"full", true, false}
cfgv["tracepage"]       = {true, false}
cfgv["traceenv"]        = {true, false}
cfgv["expandmacros"]    = {true, false}


------------------------------------------------------------------------
-- checks, whether table contains an element
-- @param table, elem
-- @return is_present   true, if elem is present in the table
------------------------------------------------------------------------
function table.contains(table, element)
  for _, value in pairs(table) do
    if value == element then
      return true
    end
  end
  return false
end


---------------------------------------------------------------
-- table length function
-- for compatibility between Lua 4.0 ant 5.2
-- not the same as conventional table size concept (table.getn(tab) (?) or #tab) in Lua
--      (count of elements between tab["1"] and first nil element, iterating sequentionally through elements with numeric indices)
-- table field tab.n could be used for setting fixed length of the table
-- @param tab -- table
-- @return table length (either value of tab.n or value of maximal numeric index)
---------------------------------------------------------------
--    function getn(tab)
--        if type(tab.n) == "number" then return tab.n end
--        local max = 0
--        for ix, _ in pairs(tab) do
--            if type(ix) == "number" and ix > max then max = ix end
--        end
--        return max
--    end

------------------------------------------------------------------------
-- konfigūracinio failo toktrc.cfg parsinimas į konfigūracijos
--      lentelę cfgt[][]
------------------------------------------------------------------------
function parse_cfg()

    --------------------
    cfgt = ConfigParser.load(toktrc_cfg_fname)

    -- cfgt.default.mainfilename = "./\currfilename"
    cfgt.default.mainfilename = cfgt.default.mainfilename:lower()

    for par, val in pairs(cfgt.default) do
        if (not cfgv[par]) then
            texio.write_nl("! toktrc.lua: Unknown keyword in file " ..
                toktrc_cfg_fname .. ": " .. par .. " = " ..
                tostring(val))
        else
            if ((par ~= "mainfilename") and
                (not table.contains(cfgv[par], val))) then
                texio.write_nl(
                    "! toktrc.lua: Unknown keyword value in file " ..
                    toktrc_cfg_fname .. ": " .. par .. " = " ..
                    tostring(val))
            end
        end
    end

    if (cfgt.default.tracetokcnt == "none") then
        cfgt.default.tracetokcnt = nil end

    if (not cfgt.default.tracelevel) then
        cfgt.default.tracelevel = "tracer" end
end


------------------------------------------------------------------------
-- atidaro log failą, grąžina atidaryto failo objektą;
-- @param log_fsuff     log failo vardo priesaga
--                          ("toktrc.log", "used.log", etc.)
-- @return logfile      atidaryto log failo objektas
------------------------------------------------------------------------
function open_log_file(log_fsuff)
    local log_fname = cfgt.default.mainfilename
    if (log_fname == "")
    then
--           log_fname = "./\currfilename" 
--           log_fname = log_fname .. "." .. log_fsuff
        log_fname = log_fsuff
    else
        log_fname = log_fname .. "." .. log_fsuff
    end
    local logfile = io.open(log_fname, "w")

return(logfile)
end


------------------------------------------------------------------------
-- papildo sudėtinių išvedamų laukų reikšmes nauju elementu
-- @param out_str   einamoji sudėtinio lauko reikšmė -- stringas, kurio
--                      laukeliai atskirti slešais '/'
-- @param app_str   naujo laukelio stringas
-- @return out_str  grąžinama apjungta reikšmė
------------------------------------------------------------------------
function append_str_elem(out_str, app_str)
    local new_app = app_str
    if (new_app == nil) then new_app = "" end

    return(out_str .. "/" .. new_app)
end


------------------------------------------------------------------------
-- suformuoja indeksų gylių išvedimo eilutę
-- naudoja ix_levs[] ir num_of_ix_levs
-- @return ix_lev_str   slešais '/' suskirstytas indeksų gylių stringas
------------------------------------------------------------------------
function format_ix_lev_str()
    local ix_lev_str = ""

    if (num_of_ix_levs == 0)
    then
        ix_lev_str = "0"
    else
        for ii = 1, num_of_ix_levs do
            local add_elem = true

            if (ii < num_of_ix_levs)
            then
                if (ix_levs[ii][1] * ix_levs[ii + 1][1] > 0)
                then
                    -- gretimi lygmenys to paties ženklo
                    add_elem = false -- neišvedinėjam
                end
            end

           if (add_elem)
           then
                if (ix_lev_str == "")
                then
                    ix_lev_str = ix_levs[ii][1]
                else ix_lev_str = append_str_elem(ix_lev_str,
                                        ix_levs[ii][1])
                end
           end
        end
    end

    return(ix_lev_str)
end


------------------------------------------------------------------------
-- suformuoja fonto objekto hasho išvedimo stringą
-- @param font_obj      iš font.fonts[] gauta fonto elementų hash lentelė
-- @return fstr         slešais '/' suskirstytas fonto elementų stringas
------------------------------------------------------------------------
function format_font_str(font_obj)
    local fstr = ""

    if (font_obj == nil)
    then
        if (cfgt.default.tracefont == "full")
        then
            fstr = "////0/10/0/0////////10///unknown/unknown//0/////////0/"
        else
            fstr = "/10/10"
        end
    else
        fstr = font_obj["name"]

        if (cfgt.default.tracefont == "full")
        then
            -- visiems ""
            fstr = append_str_elem(fstr, font_obj["area"])

            fstr = append_str_elem(fstr, "") -- TODO: font_obj["used"])
            fstr = append_str_elem(fstr, "") -- TODO: font_obj["characters"])
            fstr = append_str_elem(fstr, font_obj["checksum"])
        end
        
        local design_size = font_obj["designsize"]
        if (design_size == nil)
        then 
            design_size = 10.
        else
            design_size = design_size * 10. / 655360.
        end
       fstr = append_str_elem(fstr, design_size)

        if (cfgt.default.tracefont == "full")
        then
            fstr = append_str_elem(fstr, font_obj["direction"])
            fstr = append_str_elem(fstr, font_obj["encodingbytes"])

            -- visiems ""
            fstr = append_str_elem(fstr, font_obj["encodingname"])

            fstr = append_str_elem(fstr, "") -- TODO: font_obj["fonts"])

            -- visiems ""
            fstr = append_str_elem(fstr, font_obj["psname"])

            -- visiems ""
            fstr = append_str_elem(fstr, font_obj["fullname"])

            fstr = append_str_elem(fstr, font_obj["header"])
            fstr = append_str_elem(fstr, font_obj["hyphenchar"])
            fstr = append_str_elem(fstr, "") -- TODO: font_obj["parameters"])

        end -- if (cfgt.default.tracefont == "full")

        local size = font_obj["size"] 
        if (size == nil)
        then
            size = design_size 
        else
            size = size * 10. / 655360.
        end
        fstr = append_str_elem(fstr, size)

        if (cfgt.default.tracefont == "full")
        then
            fstr = append_str_elem(fstr, font_obj["skewchar"])

            -- visiems "real", matyt, galima atsekti virtualius
            fstr = append_str_elem(fstr, font_obj["type"])

            -- visiems "unknown"
            fstr = append_str_elem(fstr, font_obj["format"])

            fstr = append_str_elem(fstr, font_obj["embedding"])

            -- visiems ""
            fstr = append_str_elem(fstr, font_obj["filename"])
                                
            fstr = append_str_elem(fstr, font_obj["tounicode"])

            -- visiems ""
            fstr = append_str_elem(fstr, font_obj["stretch"])
            
            -- visiems ""
            fstr = append_str_elem(fstr, font_obj["shrink"])
        
            fstr = append_str_elem(fstr, font_obj["step"])
            fstr = append_str_elem(fstr, font_obj["auto_expand"])

            -- visiems ""
            fstr = append_str_elem(fstr, font_obj["expansion_factor"])

            -- visiems ""
            fstr = append_str_elem(fstr, font_obj["attributes"])

            fstr = append_str_elem(fstr, font_obj["cache"])
            fstr = append_str_elem(fstr, "") -- TODO: font_obj["nomath"])

            -- visiems "0"
            fstr = append_str_elem(fstr, font_obj["slant"])
            
            fstr = append_str_elem(fstr, font_obj["extent"])

        end -- if (cfgt.default.tracefont == "full")

    end -- else -- if (font_obj == nil)

    return(fstr)
end


------------------------------------------------------------------------
-- nematomų simbolių kodų formateris
-- @param csname        -- stringas su tekstu ir simbolių kodais
-- @return csname_out   -- grąžinamas simbolis (jei matomas ASCII) ar suformatuotas kodo tekstas (jei nematomas)
------------------------------------------------------------------------
function cvt_out(csname)
    local csname_out
    csname_out = ""

    for  ii = 1, string.len(csname)
    do
        local out_ch
        out_ch = string.byte(csname, ii)

        if ((out_ch <= 32) or (out_ch > 126))
        then
            csname_out = csname_out ..
                string.format("<" .. perc_chr .. "d>", out_ch)
        else
            csname_out = csname_out .. string.char(out_ch)
        end
    end

    return(csname_out)
end


---------------------------------------------------------------
-- tabuliacijos logo lentelės stulpelių išlyginimui
-- @param value     -- išvedamos stulpelio reikšmės stringas
-- @param max_tabs  -- max. tabuliacijų skaičius, kurį stulpelio reikšmė gali užimti (stulpelio plotis tabuliacijomis)
-- @return          -- grąžinamas stringas su tabuliacijomis papildymui iki stulpelio pločio
---------------------------------------------------------------
tab_wdt = 4 -- tabuliacijos plotis simboliais

tabs_len = 10
tabs = tab_chr
for ii = 2, tabs_len do
    tabs = tabs .. tab_chr
end

function tabs_allign(value, max_tabs)
    val_len = 0
    if (value ~= nil) then val_len = value:len() end
    return(tabs:sub(math.floor(val_len / tab_wdt + tabs_len - max_tabs)))
end


----------------------------------------------------
-- pradžia, inicializacija

parse_cfg() -- skaitom toktrc.cfg

-------------------------------------
-- išorinių funkcijų prijungimas

-- čia kad kpadd.so ieškotų ne per kpathsea, o per sistemą iš /usr/lib
--      package.searchers[2] = package.searchers[3]
-- nepadeda, o ir nebereikia -- paleidimo faile nustatom
--      # CLUAINPUTS=/usr/lib
--      LUA_CPATH="/usr/local/texlive/2010/bin/x86_64-linux/kpadd.so"
-- prijungiam kpadd.so/kpadd.dll; iškviečia TeXtrcClass::LuaOpen()
require("kpadd")

-- galima ir pavienėm funkcijom, tada kpadd.so ieško ne per kpathsea
--  get_cur_lnum = package.loadlib("kpadd.so", "get_cur_lnum")
--  if not(get_cur_lnum) then
--      texio.write_nl("! toktrc.lua: Error on kpadd.so:get_cur_lnum")
--  else texio.write_nl("toktrc.lua: kpadd.so:get_cur_lnum prijungtas")
--  end

--  get_cur_lpos = package.loadlib("kpadd.so", "get_cur_lpos")
--  if not(get_cur_lpos) then
--      texio.write_nl("! toktrc.lua: Error on kpadd.so:get_cur_lpos")
--  else texio.write_nl("toktrc.lua: kpadd.so:get_cur_lpos prijungtas")
--  end

--  get_cur_fname = package.loadlib("kpadd.so", "get_cur_fname")
--  if not(get_cur_fname) then
--      texio.write_nl("! toktrc.lua: Error on kpadd.so:get_cur_fname")
--  else texio.write_nl("toktrc.lua: kpadd.so:get_cur_fname prijungtas")
--  end
