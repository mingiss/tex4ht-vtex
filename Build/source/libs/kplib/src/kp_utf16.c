/* -----------------------------
 * utf16.c
 * encoding high codes to utf-16
 */

#include <stdlib.h>
#include <assert.h>
#include <string.h>

// #include "mem.h"
#include "kp_utf16.h"

unsigned int* uni32_2_utf16(unsigned long ucode, int* p_ucnt)
{
    unsigned int* tounicode = NULL;
    int ucnt = 0;

    assert(p_ucnt);

    if (ucode <= 0x10FFFF)
    {
        if (ucode >= 0x10000L)
        {
            ucnt = 2;
            tounicode = malloc(ucnt * sizeof(*tounicode)); // NEW(ucnt, unsigned int);
            assert(tounicode);
            ucode -= 0x10000L;
            tounicode[0] = 0xD800 | ((ucode >> 10) & 0x3FF);
            tounicode[1] = 0xDC00 | (ucode & 0x3FF);
        }
        else
        {
            ucnt = 1;
            tounicode = malloc(ucnt * sizeof(*tounicode)); // NEW(ucnt, unsigned int);
            assert(tounicode);
            tounicode[0] = ucode;
        }
    }

    *p_ucnt = ucnt;
    return (tounicode);
}
