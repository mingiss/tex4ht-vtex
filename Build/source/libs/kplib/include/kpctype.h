/* ----------------------------------------------------
 *
 * kpctype.h
 *
 *  type conversations & character processing for KP C++ projects
 *
 * Changelog:
 *  2017-05-22  mp  build on Linux Mint 18.1 Serena 64
 *
 */

#ifndef KPCTYPE_INCLUDED
#define KPCTYPE_INCLUDED

#include "kperrno.h"
#include "kpstdlib.h"

// ---------------------------------------
// predefined spec. character strings
// TODO: kelt į KpCtype klasę
extern uchar pszSpaces[];
extern uchar pszEols[];
extern uchar pszSpcEol[];
extern uchar pszSpcEolNotNBSP[];
extern uchar pszSpcEolNotTabNotFF[];

extern uchar pszSpCharsSpcEol[]; // "/.,- \t\r\n"  // characters ignored by sorting/searching
                                 //    former lpszSpChars

// ----------------------
extern bool KpIsDigit(KpChar p_uiCh);

// ----------------------
// gcc 5.4.0 does not distinguish between a pointer to const and const pointer
extern HRESULT TestAllowed(const uchar *p_pszCheckString, const uchar *p_pszCharsAllowed);
    // tests, whether p_pszCheckString contains
    //    only characters from p_pszCharsAllowed
    // returns KP_E_UNKN_CHR in case of failure

// ----------------------
extern bool KpIsNumber(const uchar *p_pszString);
    // tests whether p_pszString is decimal integer number

extern bool KpIsHexNum(const uchar *p_pszHexString);
    // tests whether p_pszHexString is hex number
extern bool KpIsOctNum(const uchar *p_pszOctString);
    // tests whether p_pszOctString is octal number
extern bool KpIsRomNum(const uchar *p_pszString);
    // tests whether p_pszString is roman number

#endif // #ifndef KPCTYPE_INCLUDED

