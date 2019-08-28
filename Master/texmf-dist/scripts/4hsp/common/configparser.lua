-----------------------------------
-- INI failu parsinimo modulis
--
-- Changelog:
--      2013-11-08  mp  trimmed spaces, comments, default section
--      2013-11-14  mp  lowercase keys
--
-----------------------------------

local ConfigParser = {};

function ConfigParser.load(fileName)
        local file = assert(io.open(fileName, 'r'), 
                            'Nepavyko atidaryti failo: ' .. fileName);
        local data = {};
        local section = "default";
        data[section] = {};

    	for line in file:lines() do

           -- sekcijos atpazinimas
           local tmpSection = line:match('^%s-%[([^%[%]]+)%]%s*$');
           if tmpSection then
              section = tmpSection:lower()
              data[section] = data[section] or {};
           end
           
           -- konfiguracijos nuskaitymas
           local param, value = line:match('^%s-([%w|_]+)%s-=%s*([^#]*).-$');
           if (param and value) then
              param = param:lower()
              value = value:match('(.-)%s*$');
              -- int arba bool vertes
              if tonumber(value) then
                 value = tonumber(value);
              elseif (value:lower() == 'yes') or (value:lower() == 'true') then
                 value = true;
              elseif (value:lower() == 'no') or (value:lower() == 'false') then
                 value = false;
              end

              data[section][param] = value;
           end
    	end
    	file:close();
	return data;
end



return ConfigParser;

