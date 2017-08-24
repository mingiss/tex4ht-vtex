/* -----------------------------------------------
 *
 * kpwindow.h
 *
 *    Win32 windows
 *
 * 2013-07-16  mp  initial creation
 *
 */

#ifndef KPWINDOW_INCLUDED
#define KPWINDOW_INCLUDED

#ifdef __WIN32__

// ----------------------------
#define KPW_WND_CAPTION_HGT_INI 26
#define KPW_WND_BORDER_WDT_INI 4
#define KPW_WND_MENU_HGT_INI 20

// ----------------------------
extern void KpDrawLine(HDC p_hDC, int p_iX1, int p_iY1, int p_iX2, int p_iY2,
                                                            COLORREF p_iColor);
extern void KpDrawRect(HDC p_hDC, int p_iX1, int p_iY1, int p_iX2, int p_iY2,
                                                            COLORREF p_lColor);

// ----------------------------
extern HRESULT KpMsgOut(const unsigned char *p_lpszOutStr,
                                LPCTSTR p_lpszIconID, KpMsgTypes p_iMsgType);
#endif // #ifdef __WIN32__

#endif // #ifndef KPWINDOW_INCLUDED
