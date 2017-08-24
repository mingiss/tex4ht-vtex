/* -----------------------------------------------
 *
 * kpwindow.cpp
 *
 *    Win32 windows
 *
 * 2013-04-11  mp  initial creation
 *
 */

#include "envir.h"
#include "kpstdlib.h"

#ifdef __WIN32__

#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#ifdef __WIN32__
#include <windows.h>
#include <wincon.h>
#endif

using namespace std;

#include "res_com.h"
#include "kperrno.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpmsg.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpcapp.h"


// ------------------------------------------
HINSTANCE KpCommonApp::m_hInstance = NULL;
HWND KpCommonApp::m_hWndParent = NULL;

int KpCommonApp::m_iWndCaptionHgt = KPW_WND_CAPTION_HGT_INI;
int KpCommonApp::m_iWndMenuHgt = KPW_WND_MENU_HGT_INI;
int KpCommonApp::m_iWndBorderWdt = KPW_WND_BORDER_WDT_INI;


void KpCommonApp::InitWindowPars(void)
{
#ifndef MSVC_EXPRESS

WNDCLASSEX wcx;
HWND test_wnd = NULL;
RECT cli_rect;
RECT wnd_rect;
HMENU menu = NULL;

// ---------------------------------
    wcx.hInstance     = m_hInstance;
    wcx.lpszClassName = TEXT("KPTEST"),
    wcx.lpfnWndProc   = DefWindowProc;
    wcx.style         = CS_DBLCLKS;
    wcx.cbSize        = sizeof(WNDCLASSEX);
    wcx.hIcon         = LoadIcon(m_hInstance, IDI_APPLICATION);
                                // MAKEINTRESOURCE(IDI_APPLICATION));
    wcx.hIconSm       = LoadIcon(m_hInstance, IDI_APPLICATION);
                                // MAKEINTRESOURCE(IDI_APPLICATION));
    wcx.hCursor       = LoadCursor(0, IDC_ARROW);
    wcx.lpszMenuName  = 0;
    wcx.cbClsExtra    = 0;
    wcx.cbWndExtra    = 0;
    wcx.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    KP_ASSERTW0(RegisterClassEx(&wcx), KP_E_SYSTEM_ERROR, GetLastError());

// ---------------------------------
    test_wnd = CreateWindowEx
    (
        0,              // DWORD dwExStyle,
            // extended window style
        TEXT("KPTEST"),       // LPCTSTR lpClassName,
        TEXT("KpTest"),       // LPCTSTR lpWindowName,
            // pointer to window name
        WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX |WS_THICKFRAME
//          |WS_MINIMIZE
#ifdef Debug
//          |WS_VISIBLE
#endif
            , // |WS_BORDER|WS_POPUP, // DWORD dwStyle,
                // window style
        200, // CW_USEDEFAULT, // int x,
            // horizontal position of window
        200, // CW_USEDEFAULT, // int y,
            // vertical position of window
        200, // CW_USEDEFAULT, // int nWidth,
            // window width
        200, // CW_USEDEFAULT, // int nHeight,
            // window height
        HWND_DESKTOP,  // HWND hWndParent,
            // handle to parent or owner window
        NULL,          // HMENU hMenu,
            // handle to menu, or child-window identifier
        m_hInstance, // HINSTANCE hInstance,
        NULL           // LPVOID lpParam
            // pointer to window-creation data
    );
    KP_ASSERT(test_wnd, KP_E_SYSTEM_ERROR, GetLastError());

// --------------------------------
    KP_ASSERT(GetClientRect(test_wnd, &cli_rect),
                        KP_E_SYSTEM_ERROR, GetLastError());
    KP_ASSERT(GetWindowRect(test_wnd, &wnd_rect),
                        KP_E_SYSTEM_ERROR, GetLastError());
    m_iWndBorderWdt = ((wnd_rect.right - wnd_rect.left) -
                        (cli_rect.right - cli_rect.left)) / 2;
    m_iWndCaptionHgt = ((wnd_rect.bottom - wnd_rect.top) -
        (cli_rect.bottom - cli_rect.top)) - 2 * m_iWndBorderWdt;

    if (test_wnd) ::DestroyWindow(test_wnd);
    test_wnd=NULL;

// ------------------------------- menu
    menu = CreateMenu();
    KP_ASSERT(menu, KP_E_SYSTEM_ERROR, GetLastError());

    KP_ASSERT(AppendMenu(menu, MF_STRING, KP_ID_FILE, TEXT("File")),
                                        KP_E_SYSTEM_ERROR, GetLastError());

// ---------------------------------
    test_wnd = CreateWindowEx
    (
        0,              // DWORD dwExStyle,
            // extended window style
        TEXT("KPTEST"),       // LPCTSTR lpClassName,
        TEXT("KpTest"),       // LPCTSTR lpWindowName,
            // pointer to window name
        WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX |WS_THICKFRAME
//       |WS_MINIMIZE
#ifdef Debug
//       |WS_VISIBLE
#endif
            , // |WS_BORDER|WS_POPUP, // DWORD dwStyle,
                // window style
         200, // CW_USEDEFAULT, // int x,
            // horizontal position of window
         200, // CW_USEDEFAULT, // int y,
            // vertical position of window
         200, // CW_USEDEFAULT, // int nWidth,
            // window width
         200, // CW_USEDEFAULT, // int nHeight,
            // window height
         HWND_DESKTOP,  // HWND hWndParent,
            // handle to parent or owner window
         menu,          // HMENU hMenu,
            // handle to menu, or child-window identifier
         m_hInstance,   // HINSTANCE hInstance,
         NULL           // LPVOID lpParam
            // pointer to window-creation data
    );
    KP_ASSERT(test_wnd, KP_E_SYSTEM_ERROR, GetLastError());

// --------------------------------
    KP_ASSERT(GetClientRect(test_wnd, &cli_rect), KP_E_SYSTEM_ERROR,
                                                            GetLastError());
    KP_ASSERT(GetWindowRect(test_wnd, &wnd_rect), KP_E_SYSTEM_ERROR,
                                                            GetLastError());
    m_iWndMenuHgt = ((wnd_rect.bottom - wnd_rect.top) -
        (cli_rect.bottom - cli_rect.top)) -
        2 * m_iWndBorderWdt - m_iWndCaptionHgt;

    if (test_wnd) ::DestroyWindow(test_wnd);
    test_wnd=NULL;

#endif // #ifndef MSVC_EXPRESS
}


// ------------------------------------------
void KpCommonApp::KpInitWindows(HINSTANCE p_hInstance)
{
// -----------------
#ifdef __WIN32__
    if (p_hInstance)
    {
        m_hInstance = p_hInstance;
        m_hWndParent = HWND_DESKTOP;
    }
    else
    {
//      m_hInstance = GetModuleHandle(NULL);

#ifndef KP_CONSOLE
#error Not a console application
#endif
    // TODO: GetConsoleWindow() veikia tik su MinGW 4.6.2 iš MSYS,
    //      nėra MinGW 4.4.1 iš CodeBlocks 10.05
        m_hWndParent = GetConsoleWindow(); // = HWND_DESKTOP; 
        KP_ASSERT(m_hWndParent, KP_E_SYSTEM_ERROR,
            "Not a console application, "
            "proper instance handle should be provided");
#ifndef _WIN64
        m_hInstance = (HINSTANCE)GetWindowLong(m_hWndParent, GWL_HINSTANCE);
#endif
// printf("KpCommonApp::KpInitWindows(): %lx %lx\n", m_hInstance,
//                                                      m_hWndParent);

#if FALSE
    char cur_title[KP_MAX_FNAME_LEN + 1];
        KP_ASSERT(GetConsoleTitle(cur_title, KP_MAX_FNAME_LEN),
                                                KP_E_SYSTEM_ERROR, null);
        KP_ASSERTW0(SetConsoleTitle("zzzz"), KP_E_SYSTEM_ERROR,
                GetLastError()); // (const char *)KpError.m_lpszProdName);
        m_hWndParent = FindWindow(NULL, "zzzz");
            // (const char *)KpError.m_lpszProdName);
//      SetConsoleTitle(cur_title);
        m_hInstance = (HINSTANCE)GetWindowLong(m_hWndParent, GWL_HINSTANCE);
// printf("KpCommonApp::KpInitWindows(): %lx %lx\n", m_hInstance,
//                                                      m_hWndParent);
#endif
    }
#endif

// -----------------
#ifdef MsgLang
#   if (MsgLang == KpLangNo_p)
        m_iMsgLangOff = KpLangEn;

#   elif (MsgLang == KpLangSel_p)
        KP_THROW(E_NOTIMPL, null);

#   elif ((MsgLang == KpLangEn_p) || (MsgLang == KpLangLt_p) ||
        (MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p) ||
        (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))
            m_iMsgLangOff = (KpLang)MsgLang;

#   elif ((MsgLang == KpLangPl_p) || (MsgLang == KpLangRu_p))
#       ifdef __WIN32__
HRESULT retc = S_OK;
HKEY key = NULL;
LONG retw = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                        "SYSTEM\\CurrentControlSet\\Control\\Nls\\CodePage",
                        0, KEY_QUERY_VALUE, &key);
        KP_ASSERTW(retw == ERROR_SUCCESS, KP_E_KWD_NOT_FOUND, retw);
        KP_ASSERTW(key, KP_E_SYSTEM_ERROR, null);

DWORD buf_len = KP_KWD_LEN;
unsigned char key_buf[KP_KWD_LEN + 1];
        if (SUCCEEDED(retc))
        {
DWORD val_type;
            retw = RegQueryValueEx(key, "ACP", NULL, &val_type, key_buf,
                                                                    &buf_len);
            KP_ASSERTW(retw == ERROR_SUCCESS, KP_E_KWD_NOT_FOUND, retw);
            KP_ASSERTW(val_type == REG_SZ, KP_E_KWD_NOT_FOUND, retw);
        }
        if (SUCCEEDED(retc))
        {
            key_buf[buf_len] = Nul;
            CutInitTrailSpcs(key_buf);
#       if (MsgLang == KpLangPl_p)
                if (strcmp(key_buf, "1257") == 0) iMsgLangOff = KpLangPl_1257;
                else /* if (strcmp(key_buf, "1250") == 0) */
                                        iMsgLangOff = KpLangPl_1250;

#       elif (MsgLang == KpLangRu_p)
                if (strcmp(key_buf, "1251") == 0) iMsgLangOff = KpLangRu_1251;
                else iMsgLangOff = KpLangRu_0;

#       else
                KP_THROW(E_INVALIDARG, null);
#       endif
        }
        if (key) RegCloseKey(key);
        key = NULL;
#       else // #       ifdef __WIN32__
        KP_THROW(E_INVALIDARG, null);
#       endif

#   else
        KP_THROW(E_INVALIDARG, null);
        break;

#   endif // #  elif ((MsgLang == KpLangPl_p) || (MsgLang == KpLangRu_p))

#endif // #ifdef MsgLang

    KP_ASSERT((m_iMsgLangOff >= 0) && (m_iMsgLangOff < KpNumOfLangs),
                                                    KP_E_SYSTEM_ERROR, null);

// -------------
    InitWindowPars();
}


// ----------------------------------------
#ifdef KP_WINDOWED
void KpDrawLine(HDC p_hDC, int p_iX1, int p_iY1, int p_iX2, int p_iY2,
                                                            COLORREF p_lColor)
{
HRESULT retc = S_OK;
HPEN pen = NULL;

    pen = CreatePen(PS_SOLID, 1, p_lColor);
    KP_ASSERTW(pen, KP_E_SYSTEM_ERROR, GetLastError());

    KP_ASSERTW(SelectObject(p_hDC, pen), KP_E_SYSTEM_ERROR, GetLastError());

    KP_ASSERTW(MoveToEx(p_hDC, p_iX1, p_iY1, NULL), KP_E_SYSTEM_ERROR,
                                                        GetLastError());

    KP_ASSERTW(LineTo(p_hDC, p_iX2, p_iY2), KP_E_SYSTEM_ERROR, GetLastError());

    if(pen) KP_ASSERTW(DeleteObject(pen), KP_E_SYSTEM_ERROR, GetLastError());
    pen = NULL;
}
#endif


#ifdef KP_WINDOWED
void KpDrawRect(HDC p_hDC, int p_iX1, int p_iY1, int p_iX2, int p_iY2,
                                                            COLORREF p_lColor)
{
    KpDrawLine(p_hDC, p_iX1, p_iY1, p_iX2, p_iY1, p_lColor);
    KpDrawLine(p_hDC, p_iX2, p_iY1, p_iX2, p_iY2, p_lColor);
    KpDrawLine(p_hDC, p_iX2, p_iY2, p_iX1, p_iY2, p_lColor);
    KpDrawLine(p_hDC, p_iX1, p_iY2, p_iX1, p_iY1, p_lColor);
}
#endif


// ----------------------------
extern HRESULT KpMsgOut(const unsigned char *p_lpszOutStr,
                            LPCTSTR /* p_lpszIconID */, KpMsgTypes /* p_iMsgType */)
{
#ifdef KP_WINDOWED
// TODO:
#else
cout << p_lpszOutStr << endl;
#endif

return S_OK;
}

#endif // #ifdef __WIN32__
