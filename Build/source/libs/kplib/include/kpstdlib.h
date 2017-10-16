/* -----------------------------------------------
 *
 * kpstdlib.h
 *
 *    common definitions for all KpLib driven projects
 *
 * Changelog:
 *  2013-02-22  mp  initial creation
 *  2013-10-31  mp  KPADDSHARED atkelti iš textrc.h
 *  2016-09-07  mp  migration of kpsgrp from tv to kplib
 *  2017-05-22  mp  build on Linux Mint 18.1 Serena 64
 *
 */

#ifndef KPSTDLIB_INCLUDED
#define KPSTDLIB_INCLUDED

#include "envir.h"

#include <stdarg.h>
#include <stdlib.h>
#ifdef __cplusplus
#include <string>
#endif

#ifdef _MSC_VER
#include <stdio.h>
#include <intrin.h>
#include <windows.h>
#include <WinDef.h>
#endif

#ifdef WIN32
#include <tchar.h>

#ifndef GWL_HINSTANCE
#define GWL_HINSTANCE (-6)
#endif
#endif

#ifdef __cplusplus
using namespace std;
#endif

// -------------------------------------- plain exportai
#ifdef MAKE_KPADD_SHARED
#   ifndef KPADD_SHARED
#       define KPADD_SHARED
#   endif
#endif

#ifndef KPADDSHARED
#   ifdef KPADD_SHARED
#       ifdef MAKE_KPADD_SHARED
#           ifndef __WIN32__
#               define KPADDSHARED __attribute__ ((visibility("default")))
#           else // #ifndef __WIN32__
#               define KPADDSHARED __declspec(dllexport)
#           endif
#       else // #ifdef MAKE_KPADD_SHARED
#           ifndef __WIN32__
#               define KPADDSHARED
#           else // #ifndef __WIN32__
#               define KPADDSHARED __declspec(dllimport)
#           endif
#       endif
#   else // #ifdef KPADD_SHARED
#       define KPADDSHARED
#   endif
#endif


// ========================================= kptt
#ifndef __WIN32__
// typedef char CHAR;
// typedef unsigned char UCHAR;
typedef unsigned long DWORD;
#endif
typedef unsigned char uchar;
typedef unsigned char u_char;

// typedef uchar *KpStrPtr;

// #ifndef _T
#ifndef __WIN32__
#define WCHAR wchar_t
// #ifdef _UNICODE
#ifdef UNICODE
#define _T(str) L##str
#define TCHAR wchar_t
#define LPCTSTR const wchar_t*
#else
#define _T(str) ((const uchar *)str)
#define TCHAR uchar
#define LPCTSTR const uchar*
#endif
#endif

// ------------------------------
#define Nul ((uchar)0)
#define Soh ((uchar)1)
#define Stx ((uchar)2)
#define Etx ((uchar)3)
#define Eot ((uchar)4)
#define Enq ((uchar)5)
#define Ack ((uchar)6)
#define Bel ((uchar)7)
#define Bs  ((uchar)('\b'))
#define Ht  ((uchar)('\t'))
#define Tab Ht
#define Lf  ((uchar)('\n'))
#define Vt ((uchar)('\v'))
#define Ff ((uchar)('\f'))
#define Cr ((uchar)('\r')) // 0x0D
#define So  ((uchar)016)
#define Si  ((uchar)017)
#define Dle ((uchar)020)
#define Dc1 ((uchar)021)
#define Dc2 ((uchar)022)
#define Dc3 ((uchar)023)
#define Dc4 ((uchar)024)
#define Nak ((uchar)025)
#define Syn ((uchar)026)
#define Etb ((uchar)027)
#define Can ((uchar)030)
#define Em  ((uchar)031) // 0x19
#define Sub ((uchar)032)
#define Esc ((uchar)033)
#define Fs  ((uchar)034)
#define Gs  ((uchar)035)
#define Rs  ((uchar)036)
#define Us  ((uchar)037)
#define Spc ((uchar)(' '))


// ----------------------------------
// TODO: apjungti abejus kalbų kodus

// ----------------------------------
// Languages for messages
// #define MsgLang – constant defined during compilation

typedef enum
{
   KpLangNo    = -1, // -1 - neapibrėžta – iMsgLangOff nustatom į KpLangEn
#define KpLangNo_p   (-1)

   KpLangEn,         // 0 - anglų
#define KpLangEn_p   0
   KpLangLt,         // 1 - lietuvių
#define KpLangLt_p   1
   KpLangPl_1250,    // 2 - lenkų Central European
#define KpLangPl_1250_p 2
   KpLangPl_1257,    // 3 - lenkų Windows Baltic
#define KpLangPl_1257_p 3
   KpLangRu_1251,    // 4 - rusų
#define KpLangRu_1251_p 4
   KpLangRu_0,       // 5 - rusų su angliškais mygtukų tekstais – kai regional Settings ne rusiški
#define KpLangRu_0_p 5

   KpNumOfLangs,
#define KpNumOfLangs_p 6

   KpLangRu    = 97, // 97 - išsitraukti iš registro Regional Setting'ų – KpLangRu_0 arba KpLangRu_1251 (jei rusiški)
#define KpLangRu_p   97
   KpLangPl    = 98, // 98 - išsitraukti iš registro Regional Setting'ų – KpLangPl_1250 arba KpLangPl_1257 (jei lietuviški / Baltic)
#define KpLangPl_p   98
   KpLangSel,        // 99 - išsitraukti iš registro Regional Setting'ų
#define KpLangSel_p  99

} KpLang;

#define KpNumOfLangs_2 KpNumOfLangs // masyvų riboms, padidinti kiekvieną kartą, pasikeitus kalbų skaičiui


// ----------------------------------
// Languages for SortMode
#define KP_LNG_LIT ('l')       // lithuanian, former TV_XE_LIT, (former #define Lit 1)
#define KP_LNG_LIX ('x')       // lithuanian sorting regardless of diacrytics, i.e., č==c, š==s, ž==z (for lzdsh.exe and main index generation)
#define KP_LNG_LIS ('s')       // lithuanian straigth sorting according to exact weights (for irregular form table generator - tvxmlecm.exe)
#define KP_LNG_ENG ('e')       // english, former TV_XE_ENG, (former #define Eng 0)
#define KP_LNG_GER ('v')       // german, former TV_XE_GER, former 'g'
#define KP_LNG_FRE ('f')       // french, former KP_LNG_FRA, TV_XE_FRA
#define KP_LNG_RUS ('r')       // russian, former TV_XE_RUS
#define KP_LNG_POL ('p')       // polish
#define KP_LNG_LAT ('n')       // latin

#define KP_LNG_NO  ('-')       // not applicable: text without any language specified, former TV_XE_NO
#define KP_LNG_UP  ('^')       // xml tags: language of the father tag should be inherited
#define KP_LNG_NA  ('@')       // not applicable: text not allowed; used for xml tags, excluded from index creation or non-text tags


// ========================================= KpLib
// KpLib initialization/destruction procedures for plain C projects
#ifdef __cplusplus
#define PLAIN_C "C"
#else 
#define PLAIN_C
#endif

extern PLAIN_C void KpInit(const uchar *ProdName, const void *pStackTop);  // pStackTop – caller stack top pointer,
extern PLAIN_C void KpClose(void);                  // usually pointer to some local variable of the main() function
                                                    // could be NULL

// ========================================= data types
// typedef enum
// {
//     False,
//     True
// } bool;


#ifndef WIN32
typedef int BOOL;
#endif

// #if defined(__MINGW32__) || defined(_MSC_VER)
#ifndef __cplusplus
typedef char bool;
#endif
// #endif

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
// #define TRUE 1
#define TRUE (!FALSE)
#endif


#ifndef __cplusplus
#ifndef true
#define true 1
#define false 0
#endif /* not true */
#endif /* not __cplusplus */

#define True ((bool)TRUE)
#define False ((bool)FALSE)

#if defined(__MINGW32__) && (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ <= 40401) // existed until mingw 4.4.1
#define va_list __VALIST 
#else
#   ifdef __GNUC__
#define va_list __gnuc_va_list 
#   endif
#endif
#ifndef va_start
#define va_start __builtin_va_start
#endif

#ifndef __WIN32__
#ifndef WIN32
typedef unsigned short u_short;
typedef unsigned int uint;
typedef unsigned int* UINT_PTR;
typedef long LONG;
typedef unsigned long ulong;
typedef unsigned long u_long;
#endif
#endif

//--------------------------- pointer processing
typedef void (*FuncPtr)(void);    /* funkcijos rodykles tipas */ // former Funpnt
#define Null ((FuncPtr)0)         /* nuline funkcijos rodykle */

#ifndef __WIN32__
#ifndef WIN32
#define FAR // far
#define WINAPI
typedef void* LPVOID;
#endif
#endif

#ifndef __WIN32__
#define __cdecl // _cdecl
#define __stdcall // _stdcall
#endif

typedef int (*CompareFuncPtr)(const void *pVal1, const void *pVal2);
      // lyginimo funkcijos rodyklės tipas, parametrai – lyginamų objektų adresai
      // naudojama, pvz., SearchTreeEntry(); pvz. – TvStrCmpStrict_(), KpCompareLong()
      // 0: *pVal1 == *pVal2
      // 1: *pVal1 > *pVal2
      // -1: *pVal1 > *pVal2

typedef int (*ComparePtrFuncPtr)(const void *ppVal1, const void *ppVal2);
      // lyginimo funkcijos rodyklės tipas, parametrai – lyginamų objektų adresų adresai
      // pvz. – TvStrPtrCmpStrict(), TvStrPtrCmpStrictRev()
      // 0: **ppVal1 == **ppVal2
      // 1: **ppVal1 > **ppVal2
      // -1: **ppVal1 > **ppVal2

// ========================================= file I/O
#ifndef PATH_MAX
#define PATH_MAX 512
#endif
#define KP_MAX_FNAME_LEN 260 // MAX_PATH // FILENAME_MAX // negalima keist/naudot neaiškios makrokomandos – pasikeis kpstart.ini dydis
#define KP_MAX_FTYPE_LEN KP_MAX_FNAME_LEN // 4  // negalima keist – pasikeis kpstart.ini dydis
#define KP_MAX_FILE_LIN_LEN 4096
#ifdef __WIN32__
#define KP_DIR_SEP '\\'
#define KP_DIR_SEP_STR (const uchar *)"\\"
#define KP_DIR_SEP_STR_0 "\\"
#define KP_EXE_EXT (const uchar *)"exe"
#else
#define KP_DIR_SEP '/'
#define KP_DIR_SEP_STR (const uchar *)"/"
#define KP_DIR_SEP_STR_0 "/"
#define KP_EXE_EXT (const uchar *)""
#endif
#define KP_EXT_SEP '.'
#define KP_EXT_SEP_STR (const uchar *)"."
#define KP_CUR_DIR_STR (const uchar *)"."

// ========================================= malloc
// #ifdef _MSC_VER
#ifndef KPATHSEA
extern PLAIN_C void *xmalloc(size_t size);
#endif
// #endif

#ifdef __cplusplus

#ifdef KP_ALLOC_TRACE
#define KP_ALLOC_SAFE
#endif

// -------------------------------------
// memory allocation control
// checks duplicate entries, deleting of non existing objects

#ifdef KP_ALLOC_SAFE

// entry of allocated object pointer
typedef struct
{
   const void *m_pAddress;
   bool m_bArrayFl;
} KpHeapEntry;

#define KP_HEAP_SIZE 10000 // size of heap pointers array; max number of simultaneously created objects

// heap testing class
class KpHeapClass
{
KpHeapEntry m_KpHeapArray[KP_HEAP_SIZE]; // array of currently allocated objects addresses
int m_iCurKpHeapIx; // current number of KpHeapArray elements

   int SearchHeapEntry(const void *pPtr); // -1 – did not find

public:
   KpHeapClass(void)
   {
      m_iCurKpHeapIx = 0;
   }

   void InsertHeapPtr(const void *pNewPtr, bool bArrayFl); // called by KP_NEW()
   HRESULT RemoveHeapPtr(const void *pDelPtr, bool bArrayFl); // called by KP_DELETE()
};

extern KpHeapClass KpHeap;

#endif // #ifdef KP_ALLOC_SAFE


// -------------
#ifdef KP_ALLOC_SAFE
#define KP_ALLOC_CHECK_DOUBLE_CALL(ptr) {{ KP_ASSERTW0((ptr) == NULL, KP_E_DOUBLE_CALL, null); }}
#define KP_ALLOC_INSERT_HEAP_PTR(ptr, arr_fl) {{ KpHeap.InsertHeapPtr(ptr, arr_fl); }}
#define KP_ALLOC_CHECK_REMOVE_HEAP_PTR(ptr, arr_fl) if (SUCCEEDED(KpHeap.RemoveHeapPtr(ptr, arr_fl)))
#else
#define KP_ALLOC_CHECK_DOUBLE_CALL(ptr)
#define KP_ALLOC_INSERT_HEAP_PTR(ptr, arr_fl)
#define KP_ALLOC_CHECK_REMOVE_HEAP_PTR(ptr, arr_fl)
#endif

#ifdef KP_ALLOC_TRACE
#define KP_ALLOC_TRACE_NEW_PTR(ptr, op) {{ KpError.PutLogMessage("KpAlloc:\t%08x\t%s\t%s\t%d", ptr, op, __FILE__, __LINE__); }}
#else
#define KP_ALLOC_TRACE_NEW_PTR(ptr, op) {}
#endif

// -------------------------------------
// object allocation
// KP_NEW(void &*ptr, (*constr)())
//    creates new object by calling the constructor constr
//    assigns new allocated object pointer to ptr
#define KP_NEW(ptr, constr) \
   {{ \
      KP_ALLOC_CHECK_DOUBLE_CALL(ptr); \
      (ptr) = new constr; \
      KP_ASSERT((ptr), KP_E_OUTOFMEM, null); \
      KP_ALLOC_TRACE_NEW_PTR(ptr, "new"); \
      KP_ALLOC_INSERT_HEAP_PTR(ptr, False); \
   }}

// without consistency check
#define KP_NEW0(ptr, constr) \
   {{ \
      KP_ALLOC_CHECK_DOUBLE_CALL(ptr); \
      (ptr) = new constr; \
      KP_ASSERT((ptr), KP_E_OUTOFMEM, null); \
   }}

// -------------------------------------
// object deleting
// KP_DELETE(void &*ptr)
//    if ptr != NULL deletes *ptr and clears ptr
#define KP_DELETE(ptr) \
   {{ \
      if (ptr) \
      { \
         KP_ALLOC_TRACE_NEW_PTR(ptr, "del"); \
         KP_ALLOC_CHECK_REMOVE_HEAP_PTR(ptr, False) delete (ptr); \
         (ptr) = NULL; \
	  } \
   }}

// without consistency check
#define KP_DELETE0(ptr) \
   {{ \
      if (ptr) \
      { \
         delete (ptr); \
         (ptr) = NULL; \
	  } \
   }}

// -------------------------------------
// array allocation
// KP_NEWA(void &ptr[], <scalar type>, int count)
//    creates new array
//    assigns new allocated array pointer to ptr
#define KP_NEWA(ptr, type, count) \
   {{ \
      KP_ALLOC_CHECK_DOUBLE_CALL(ptr); \
      (ptr) = new type[count]; \
      KP_ASSERT((ptr), KP_E_OUTOFMEM, null); \
      KP_ALLOC_TRACE_NEW_PTR(ptr, "new[]"); \
      KP_ALLOC_INSERT_HEAP_PTR(ptr, True); \
   }}


// -------------------------------------
// array deleting
// KP_DELETE(void &ptr[])
//    if ptr != NULL deletes *ptr and clears ptr
#define KP_DELETEA(ptr) \
   {{ \
      if (ptr) \
      { \
         KP_ALLOC_TRACE_NEW_PTR(ptr, "del[]"); \
         KP_ALLOC_CHECK_REMOVE_HEAP_PTR(ptr, True) delete [] (ptr); \
         (ptr) = NULL; \
	  } \
   }}

#endif // #ifdef __cplusplus


// ================================================== integer types and constants, math
#ifndef WIN32
typedef long LONG;
typedef unsigned long DWORD;
#endif

typedef unsigned int uint;
typedef unsigned long ulong;

#define MAX_UCHAR 0xFF
#if (!defined(__WIN32__)) || defined(__MINGW32__)
#define MAX_SHRT 0x7FFF // 32767 // SHRT_MAX
#ifndef MAX_INT
#define MAX_INT 0x7FFFFFFF // INT_MAX
#endif
#endif
#define MAX_LONG_HEX_DIGITS 8 /* num. of hex digits of MAXLONG */
#define MAX_LONG_DIGITS 11 /* num. of decimal digits of MAXLONG */

// max float
#define MAX_FLT (3.40282e+38) // FLT_MAX

#ifndef __MINGW32__
#define M_PI		3.14159265358979323846
#endif

// formats p_iVal as 16 bytes binary string
// p_lpszBinStrBuf[16 + 1]
void I2BinStr(uchar *p_lpszBinStrBuf, int p_iVal);

double NormAngle(double p_dAngle); // sukiša kampą į intervalą [-pi, pi)


// ================================================== date/time
#define WND_DATE_TEXT_LENGTH 40 // 30 // Windows: "Thu Aug  3 15:55:45 2006", HTTP: "Thu, 15 Jul 2004 16:29:04 GMT"


// ================================================== searching and sorting
#define KP_KWD_LEN 400 // negalima keist – pasikeis susijusių failų layout


// ================================================== OS related
#ifdef __cplusplus
extern string expandEnvironmentVariables(const string &input);
#endif


// ================================================== OS porting (Windows API <--> Linux)
#ifndef __WIN32__
#ifndef WIN32
// typedef unsigned long HINSTANCE;
#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
DECLARE_HANDLE(HINSTANCE);

// typedef unsigned long HANDLE;
typedef void* HANDLE;

typedef void* LPSECURITY_ATTRIBUTES;
#endif
#endif

#if defined(__WIN32__) || defined(WIN32)
// #ifdef WINDOWS
// #include <direct.h>
// #define GetCurrentDir _getcwd
#define GetCurrentDir(buf, len) GetCurrentDirectory(len, (LPSTR)buf)
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

// ----------------------------------------
#endif // #ifndef KPSTDLIB_INCLUDED
