------------------------------------------------------------------------------
--  4hspship.lua
--      generator of tex4hp \special's for output of explicit spaces
--      the version of processing the node list right before the ship out -- uses the pre_output_filter callback
--      inserts the whatsit nodes (verbatim \special{} commands with space content) right after each glue and kern node
--      for possibility tex4ht heuristic spaces recognition algorithm to be switched off
--
--      The script is activated including the wrapper style 4hspship.sty to the source .tex document:
--            \RequirePackage{4hspship}
--
--  2017  Mindaugas Piešina, mindaugas.piesina@vtex.lt
--
--  Changelog:
--      2017-07-26  mp  initial implementation
--      2020-06-10  mp  tested and deployed
--
--  TODO:
--      - there are multiple glue nodes, generating several spaces instead of one
--      - processing of node tree uses recursion, the big one could cause stack overflow
--          implementation could be moved to the another callback post_linebreak_filter -- 
--            at that stage nodes are placed to linear lists
--       - glues with the width = 1 appear on the very begin of the table row, producing double spaces
--          it seems there is no problem with that -- spaces are cleared using xslt transformations anyway  
--
------------------------------------------------------------------------------

require('tokinit')

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

        sp_str = nil
        if (node_type == 'glue')
        then
            width, stretch, shrink, stretch_order, shrink_order = node.getglue(cur_node)
            if (width > 0)
            then
                -- sp_str = '&#32;' -- not good -- entities are inserted into the tag itself:
                                    -- <math&#32;xmlns="http://www.w3.org/1998/Math/MathML">
                sp_str = ' '
            end
        else
            if ((node_type == 'kern') and (cur_node.kern > 0) and
                (cur_node.subtype == 1)) -- userkern
            then
                -- if (cur_node.kern >= 1000000) -- approximate threshold for \; -- \thickmuskip
                if (cur_node.kern > 0)
                then
                    -- sp_str = '&#32;'
                    sp_str = ' '
                -- else
                --    sp_str = '&#x2009;' -- thin space; kern threshold should be much less than 1000000
                end                       -- no need at the moment -- thin spaces are converted directly to &#x2009;
            end
        end

        if (sp_str)
        then
            sp_node = node.new(node.id('whatsit'), 3)
            sp_node.data = 't4ht=' .. sp_str

            sp_node.prev = cur_node
            sp_node.next = cur_node.next
            cur_node.next = sp_node

            cur_node = sp_node.next
        else
            cur_node = cur_node.next
        end
    end
end


function spship_insert_spaces(head, groupcode, size, packtype, maxdepth, direction)

    ins_sp(head)

    return true
end
