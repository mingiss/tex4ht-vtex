/* -----------------------------
 * kpsort.cpp
 *      searching and sorting capabilities
 *      
 *  Changelog:
 *      2013-06-11  mp  initial creation
 *       
 */  


#include "envir.h"

#include <stdlib.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#ifdef __WIN32__
#include <windows.h>
#endif

using namespace std;

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpmsg.h"
#include "kperr.h"


// ================================================== sort order definition
int iCharWeigths[C_CharArrSize44] =
{
#include "KpCharWgt.cpp"
};


// --------------------------------------------------
int GetKwrdIndex(
    const uchar *p_pszKeywrd,
    const uchar *
#if (__GNUC__ != 5) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 0)
       const    // gcc 5.4.0 throws an error: duplicate ‘const’
#endif
            *p_ppszKeytable,
   const int p_iTabSize,
   bool p_bCaseSens,
   bool p_bWholeWords
)
{
int ix;
uchar kwd_str[KP_KWD_LEN + 1];
size_t ii;
int retv = TV_TG_NoKey;

    KP_ASSERT(p_pszKeywrd && p_ppszKeytable, E_INVALIDARG, null); 
    KP_ASSERT(strlen(p_pszKeywrd) < KP_KWD_LEN, KP_E_BUFFER_OVERFLOW, null);

    ix = 0;
    while
    (
        ((p_iTabSize < 0) || (ix < p_iTabSize)) &&
        ((p_iTabSize >= 0) || p_ppszKeytable[ix]) &&
        (retv == TV_TG_NoKey)
    )
    {
        strcpy(kwd_str, p_pszKeywrd);
        if (p_ppszKeytable[ix])
        {
            if (!p_bWholeWords)
            { 
                ii = strlen(p_ppszKeytable[ix]);
                KP_ASSERT(ii < KP_KWD_LEN, KP_E_BUFFER_OVERFLOW, null);
                kwd_str[ii] = Nul;
            }

            if (UcStrCmp(kwd_str, p_ppszKeytable[ix], False, KP_LNG_ENG, p_bCaseSens, False) == 0)
                retv = ix;
        }
         
        ix++;
    }

return(retv);
}

int GetKwrdIndexArr
(
   const uchar *p_pszKeywrd,
   const uchar *p_ppszKeytable,
   const int p_iTabSize,
   bool p_bCaseSens,
   bool p_bWholeWords,
   int p_iKeySize
)
{
int ix;
uchar kwd_str[KP_KWD_LEN + 1];
size_t ii;
int retv = TV_TG_NoKey;
const uchar *cur_kwd = p_ppszKeytable;

    KP_ASSERT(p_pszKeywrd && p_ppszKeytable, E_INVALIDARG, null); 
    KP_ASSERT(strlen(p_pszKeywrd) < KP_KWD_LEN, KP_E_BUFFER_OVERFLOW, null);
    KP_ASSERT(p_iKeySize > 1, E_INVALIDARG, null);

    ix = 0;
    while
    (
        ((p_iTabSize < 0) || (ix < p_iTabSize)) &&
        ((p_iTabSize >= 0) || *cur_kwd) &&
        (retv == TV_TG_NoKey)
    )
    {
        strcpy(kwd_str, p_pszKeywrd);
        if (*cur_kwd)
        {
            if (!p_bWholeWords)
            { 
                ii = strlen(cur_kwd);
                KP_ASSERT(ii < KP_KWD_LEN, KP_E_BUFFER_OVERFLOW, null);
                kwd_str[ii] = Nul;
            }

            if (UcStrCmp(kwd_str, cur_kwd, False, KP_LNG_ENG, p_bCaseSens, False) == 0)
                retv = ix;
        }
         
        cur_kwd += p_iKeySize;
        ix++;
    }

return(retv);
}
