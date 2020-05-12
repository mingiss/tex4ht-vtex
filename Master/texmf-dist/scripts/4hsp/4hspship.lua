------------------------------------------------------------------------------
--  4hspship.lua
--      tex4hp tarpų \special generatorius prieš node'ų sąrašo shipout'ą
--      naudoja pre_output_filter callbacką
--      po kiekvieno glue node'o prilipdo po whatsit tipo node (komandą \special{}) su tarpu ar entity &#32;
--      kad tex4hp nereikėtų užsiiminėti tarpų atpažinimu pagal layout'o intervalus
--
--      Scenarijus aktyvuojamas LuaTex kompiliatoriaus iškvietimo komandoje
--          pridėjus parinktį --lua=4hspship.lua
--      Pvz.:
--          luatex.exe --fmt=lualatex --progname=latex --lua=4hspship.lua foo.tex
--
--  2017  Mindaugas Piešina, mindaugas.piesina@vtex.lt
--
--  Changelog:
--      2017-07-26  mp  initial implementation
--
--  TODO:
--      - yra dubliuotų glue node'ų, dabar įsiterps keli tarpai iš eilės
--      - ar visi glue reiškia tarpus?
--      - kern'ams gal irgi reikia?
--      - node medis apdorojamas rekursiškai, jei jis bus gilus, gali persipildyti stekas
--          išbandyt post_linebreak_filter callback'ą -- jame node'ai panašu kad vienmačiai
--          žr. https://gitlab.vtex.lt/texgr/tex4ht-v2/blob/withspaces/1_fontspec/styles/addspaces.lua
--
------------------------------------------------------------------------------

-------------------------------
-- įterpia whatsit tipo node (\special) su reikšme 't4ht= ' ar 't4ht=&#32;' po kiekvieno glue tipo node
--      &#32; negerai, nes jie įsiterpia ir tagų viduje tarp tago vardo ir atributų: <math&#32;xmlns="http://www.w3.org/1998/Math/MathML">
-------------------------------
function ins_sp(head)
    local cur_node = head
    while (cur_node)
    do
        local node_id = cur_node.id
        local node_type = node.type(node_id)

        if (node_type == 'hlist') or (node_type == 'vlist')
        then
            ins_sp(cur_node.head)
        end

        if (node_type == 'glue')
        then
        
            width, stretch, shrink, stretch_order, shrink_order = node.getglue(cur_node)
            if (width > 0)
            then
                sp_node = node.new(node.id('whatsit'), 3)
                -- sp_node.data = 't4ht=&#32;'
                sp_node.data = 't4ht= '
    
                sp_node.prev = cur_node
                sp_node.next = cur_node.next
                cur_node.next = sp_node
    
                cur_node = sp_node.next
            else
                cur_node = cur_node.next
            end
        else
            cur_node = cur_node.next
        end
    end
end


---------------------------------------------------------------
-- 'pre_output_filter' calback'o funkcija
-- ties glue įterpinėja \special{t4ht= }
---------------------------------------------------------------
function spship_insert_spaces(head, groupcode, size, packtype, maxdepth, direction)

    -- įterpiam
    ins_sp(head)

    -- loginam
    local cur_node = head
    while (cur_node)
    do
        local node_id = cur_node.id
        local node_type = node.type(node_id)

        logfile:write(
            node_type, tab_chr,
--          node_id, tab_chr,
            cur_node.subtype, tab_chr -- ,
--          node.type(cur_node.subtype), tab_chr
            )

        if (node_type ~= 'whatsit')
        then
            for _, fld in pairs(node.fields(node_id))
            do
                logfile:write(fld, tab_chr)
            end
        end
        logfile:write('||', tab_chr)

        for _, fld in pairs(node.fields(node_id, cur_node.subtype))
        do
            logfile:write(fld, tab_chr)
        end
        logfile:write('||', tab_chr)

--      if cur_node.attr
--      then
--          logfile:write('attr:', cur_node.attr, tab_chr)
--      end

        if (node_type == 'whatsit')
        then
            local dta = cur_node.data
            if (type(dta) == 'string')
            then
                logfile:write(dta, tab_chr)
            elseif (type(dta) == 'table')
            then
                logfile:write('[')
                for _, fld in pairs(dta)
                do
                    if (type(fld) == 'string')
                    then
                        logfile:write(fld, tab_chr)
                    elseif (type(fld) == 'table')
                    then
                        logfile:write('[')
                        for _, fld1 in pairs(fld)
                        do
                            logfile:write(fld1, tab_chr)
                        end
                        logfile:write(']')
                    end
                end
                logfile:write(']')
            end
        end

        if (node_type == 'hlist') or (node_type == 'vlist')
        then
            local cur_subnode = cur_node.head
            while cur_subnode
            do
                local subnode_id = cur_subnode.id
                local subnode_type = node.type(subnode_id)

                logfile:write(subnode_type, tab_chr)

                cur_subnode = cur_subnode.next
            end
        end


        logfile:write(eol_chr)

        cur_node = cur_node.next
    end

    logfile:write(eol_chr)

    return true
end

-------------------------------
-- Darbo pabaigos callback'as
-------------------------------
function close_spship_log()
    logfile:close()
end

-------------------------------
-- Initiation
-------------------------------
-- package.path = './styles' .. package.path
require('tokinit')

logfile = io.open('4hspship.log', 'w')

-- conflicts with luatexbase.add_to_callback('pre_output_filter',...) in dgbook.cls 
-- callback.register('pre_output_filter', spship_insert_spaces)
-- callback.register('stop_run', close_spship_log)

-- should be registered using                                                            
-- \RequirePackage{luatexbase}
-- \directlua{
--    luatexbase.add_to_callback('pre_output_filter', spship_insert_spaces, 'Insert tex4ht spaces')
--    luatexbase.add_to_callback('stop_run', close_spship_log, 'Close 4hspship.log')
--    }
