------------------------------------------------------------------------------
-- tokinit.lua
--
--      Bendri toktrc paveldėtų projektų dalykai
--

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
