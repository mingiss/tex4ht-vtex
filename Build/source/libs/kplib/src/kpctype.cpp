/* -----------------------------------------------
 *
 * kpctype.cpp
 *
 *  type conversations & character processing for KP C++ projects
 *
 * Changelog:
 *  2017-05-22  mp  build on Linux Mint 18.1 Serena 64
 *
 */

// ======================================= definitions
#include "envir.h"

#include <vector>
#include <string>
#include <ctype.h>
#include <iostream>
#ifdef __WIN32__
#include <windows.h>
#endif

using namespace std;

#include "kperrno.h"
#include "kpstdlib.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpmsg.h"
#include "kperr.h"


// -------------------------------------------
// predefined spec. character strings
uchar pszSpaces[] = " \t\xA0"; // C_NBSP
uchar pszEols[] =   "\r\n";      // "\r\n\f";
uchar pszSpcEol[] = " \t\xA0\r\n"; // C_NBSP // " \t\r\n\f";
uchar pszSpcEolNotNBSP[] = " \t\r\n";
uchar pszSpcEolNotTabNotFF[] = " \r\n";

uchar pszSpCharsSpcEol[] = "/.,- \t\r\n";


// --------------------------------------------------
bool KpIsDigit(KpChar p_uiCh)
{
bool retv = False;

   switch(p_uiCh)
   {
      case C_0:
      case C_1:
      case C_2:
      case C_3:
      case C_4:
      case C_5:
      case C_6:
      case C_7:
      case C_8:
      case C_9:
         retv = True;
         break;
   }

return(retv);
}


// --------------------------------------------------
// gcc 5.4.0 does not distinguish between a pointer to const and const pointer
HRESULT TestAllowed(const uchar *p_pszCheckString, const uchar *p_pszCharsAllowed)
{
HRESULT retc = S_OK;

    KP_ASSERT(p_pszCheckString, E_INVALIDARG, null);
    KP_ASSERT(p_pszCharsAllowed, E_INVALIDARG, null);

#if (__GNUC__ != 5) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 0)
const
#endif
    uchar *pntc =
#if (__GNUC__ == 5) || (__GNUC_MINOR__ == 4) || (__GNUC_PATCHLEVEL__ == 0)
        (uchar *)
#endif
            p_pszCheckString;

    while ((*pntc) && SUCCEEDED(retc))
        if (strchr(
#if (__GNUC__ == 5) || (__GNUC_MINOR__ == 4) || (__GNUC_PATCHLEVEL__ == 0)
                (uchar *)
#endif
                    p_pszCharsAllowed, *pntc++) == NULL)
            retc = KP_E_UNKN_CHR;

return(retc);
}


// ----------------------------
bool KpIsNumber(const uchar *p_pszString)
{
bool retv = True;

    KP_ASSERT(p_pszString, E_INVALIDARG, null);

uchar *buf = null;
    KP_NEWA(buf, uchar, strlen(p_pszString) + 1);
    strcpy(buf, p_pszString);
    KpStripLeading(buf);

// gcc 5.4.0 does not distinguish between a pointer to const and const pointer
#if (__GNUC__ != 5) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 0)
const
#endif
    uchar *pntc = buf;

    if (*pntc == Nul) retv = False;
    else
        while ((*pntc) && retv)
            if (!isdigit(*pntc++))
            {
                retv = False;
                break;
            }

   KP_DELETEA(buf);

return(retv);
}


bool KpIsHexNum(const uchar *p_pszHexString)
{
return (SUCCEEDED(TestAllowed(p_pszHexString, (const uchar *)"0123456789ABCDEFabcdef")));
}


bool KpIsOctNum(const uchar *p_pszOctString)
{
return (SUCCEEDED(TestAllowed(p_pszOctString, (const uchar *)"01234567")));
}


bool KpIsRomNum(const uchar *p_pszRomanString)
{
return (SUCCEEDED(TestAllowed(p_pszRomanString, (const uchar *)"IVXLCM")));
}
