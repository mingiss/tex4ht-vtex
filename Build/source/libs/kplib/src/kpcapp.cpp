/* -----------------------------------------------
 *
 * kpcapp.cpp
 *
 *  common application
 *
 * Changelog:
 *  2013-04-04  mp  initial creation
 *  2013-04-11  mp  Pirmas imgcmp buildas
 *  2013-04-12  mp  StackDump() fix
 *  2013-04-23  mp  Pridėtas kptree.cpp
 *  2013-04-23  mp  Testuojam kpfwrap su imgcmp
 *  2013-04-24  mp  KpFWrapFileDesc::LineInput()
 *  2013-05-22  mp  __WIN32__
 *  2013-05-28  mp  SetProd(); KP_CATCH_ALL
 *  2013-06-07  mp  drti split to dvread, dvisp & drtim
 *  2013-06-10  mp  pirmas drtim suobjektinimas
 *  2013-06-19  mp  ImgCmp
 *  2013-06-20  mp  imgcmp FreeImage_Load()
 *  2013-06-26  mp  dvi2ht: zodziu apjungimas i spanus
 *  2013-07-02  mp  dvi2ht: fontai
 *  2013-07-15  mp  UCHAR --> uchar
 *  2013-07-16  mp  ImgCmp: m_hWndHandle = CreateWindowEx()
 *  2013-07-18  mp  console + window
 *  2013-09-06  mp  imgcmp langas juda
 *  2013-09-06  mp  imgcmp img ctrl
 *  2013-10-21  mp  srchunifonts iteratorius per failus
 *  2013-10-21  mp  kpfrtyp.cpp
 *  2017-05-22  mp  build on Linux Mint 18.1 Serena 64
 *
 */

#include "envir.h"
#include "ProjData.h"

#include <vector>
#include <string>
#include <stdio.h>
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
#include "kpcapp.h"


// ----------------------------------
KpLang KpCommonApp::m_iMsgLangOff = KpLangEn;


// ----------------------------------
KpCommonApp::KpCommonApp(const uchar *p_pszProdName, int p_iProdVer)
{
    m_iMsgLangOff = KpLangEn;
#ifdef __WIN32__
    m_hInstance = NULL;
    m_hWndHandle = NULL;
    m_hWndParent = NULL; 
#endif

    m_pszAppName[0] = Nul;

    SetProd(p_pszProdName, p_iProdVer);

    m_pszCmdLine[0] = Nul;
    KP_ASSERT(p_pszProdName, E_INVALIDARG, null);
    KP_ASSERT(strlen(KP_CUR_DIR_STR) + strlen(KP_DIR_SEP_STR) + strlen(p_pszProdName) + strlen(KP_EXT_SEP_STR) + strlen(KP_EXE_EXT) 
        <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, p_pszProdName);
    strcpy(m_pszCmdLine, KP_CUR_DIR_STR); 
    strcat(m_pszCmdLine, KP_DIR_SEP_STR); 
    strcat(m_pszCmdLine, p_pszProdName);
    strcat(m_pszCmdLine, KP_EXT_SEP_STR); 
    strcat(m_pszCmdLine, KP_EXE_EXT);

    strncpy(m_pszProdDate, PROJ_DATE, KP_MAX_FNAME_LEN);
    m_pszProdDate[KP_MAX_FNAME_LEN] = Nul;

    m_pStackTop = NULL;
}


// ----------------------------------
KpCommonApp::~KpCommonApp(void){}


// ----------------------------------
void KpCommonApp::Init(
    HINSTANCE
#ifdef __WIN32__
        p_hInstance
        #endif
            , const uchar *p_pszCmdLine, const void *p_pStackTop)
{
#ifdef __WIN32__
    KpInitWindows(p_hInstance);
#endif

    KP_ASSERT(p_pszCmdLine, E_POINTER, null);
    strncpy(m_pszCmdLine, p_pszCmdLine, KP_MAX_FNAME_LEN);
    m_pszCmdLine[KP_MAX_FNAME_LEN] = Nul;

    m_pStackTop = p_pStackTop;

static uchar log_fname[KP_MAX_FNAME_LEN + 1];
    KpError.GetLogFileName(log_fname);
    remove((const char *)log_fname);
}


// ----------------------------------
void KpCommonApp::SetProd(const uchar *p_pszProdName, int p_iProdVer)
{
    KP_ASSERT(p_pszProdName, E_INVALIDARG, null);
    KpError.SetProdName(p_pszProdName);
    m_iProdVer = p_iProdVer;
}


// ----------------------------------
void KpCommonApp::GetAppName(uchar *p_pszNameBuf)
{
    KP_ASSERT(p_pszNameBuf, E_INVALIDARG, null);

    if (m_pszAppName[0])
        strcpy(p_pszNameBuf, m_pszAppName); // tik pirmą kartą būna teisingas kelias, paskui nustatau SetCurrentDirectory() ir santykinis kelias išsiderina
    else
    {
    uchar *pnts = m_pszCmdLine;

    static uchar name_buf_tmp[KP_MAX_FNAME_LEN + 1];
        if (*pnts != '\"')
        {
            strncpy(name_buf_tmp, pnts, KP_MAX_FNAME_LEN);
            name_buf_tmp[KP_MAX_FNAME_LEN] = Nul;
            
            pnts = const_cast<uchar *>(strchr(name_buf_tmp, Spc));
        }
        else
        {
            strncpy(name_buf_tmp, pnts + 1, KP_MAX_FNAME_LEN);
            name_buf_tmp[KP_MAX_FNAME_LEN] = Nul;
            pnts = strchr(name_buf_tmp, '\"');
        }
        if (pnts) *pnts = Nul;

#ifdef __WIN32__
#ifdef UNICODE
// TODO: get full unicode path
        strcpy(p_pszNameBuf, name_buf_tmp);
#else
DWORD ll = 0L;
        ll = GetFullPathName((const char *)name_buf_tmp, KP_MAX_FNAME_LEN, (char *)p_pszNameBuf, NULL);
//      KP_ASSERT(ll > 0L, KP_E_SYSTEM_ERROR, GetLastError());
        KP_ASSERTW0(ll < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null);
        p_pszNameBuf[KP_MAX_FNAME_LEN] = Nul;
#endif
#else
// TODO Linux: get full path
        strcpy(p_pszNameBuf, name_buf_tmp);
#endif
        strcpy(m_pszAppName, p_pszNameBuf);
    }
}


// ----------------------------------
void KpCommonApp::Pause(void)
{
    fputs("Press Enter ...", stderr);
    getchar();
}
