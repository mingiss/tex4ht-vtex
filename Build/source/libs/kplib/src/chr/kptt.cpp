#include <stdint.h>
#include <assert.h>
#include "kpstdlib.h"
#include "kptt.h"

void
encode_utf16_pair(int character, UniChar units[2]) // (uint32_t character, uint16_t *units)
{
    unsigned int code;
    assert(0x10000 <= character && character <= 0x10FFFF);
    code = (character - 0x10000);
    units[0] = 0xD800 | (code >> 10);
    units[1] = 0xDC00 | (code & 0x3FF);
}

unsigned int // uint32_t
decode_utf16_pair(const UniChar units[2]) // (uint16_t *units)
{
    unsigned int /* uint32_t */ code;
    assert(0xD800 <= units[0] && units[0] <= 0xDBFF);
    assert(0xDC00 <= units[1] && units[1] <= 0xDFFF);
    code = 0x10000;
    code += (units[0] & 0x03FF) << 10;
    code += (units[1] & 0x03FF);
    return code;
}

void Utf16ToUniStr(const UniStr& Utf16_str, UniStr& Uni_str)
{
    Uni_str.clear();
    for (UniStr::const_iterator is = Utf16_str.begin(); is != Utf16_str.end(); is++)
    {
        if ((*is >= 0xD800) && (*is <= 0xDBFF))
        {
            UniChar units[2];
            units[0] = *is++;
            assert(is != Utf16_str.end());
            assert((*is >= 0xDC00) && (*is <= 0xDFFF));
            units[1] = *is;
            Uni_str.push_back(decode_utf16_pair(units));
        }
        else
            Uni_str.push_back(*is);
    }
}
