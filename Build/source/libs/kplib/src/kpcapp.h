/* -----------------------------------------------
 *
 * kpcapp.cpp
 *
 *    common application
 *
 * 2013-04-04  mp  initial creation
 *
 */

#ifndef KPCAPP_INCLUDED
#define KPCAPP_INCLUDED

#ifdef __cplusplus

class KpCommonApp
{
public:
    int m_iProdVer;
    uchar m_pszProdDate[KP_MAX_FNAME_LEN + 1];

    const void *m_pStackTop;

    uchar m_pszAppName[KP_MAX_FNAME_LEN + 1]; // full path to the executable

#ifdef __WIN32__
    static HINSTANCE m_hInstance;   // nustatomas KpInitWindows(), po to Init()

    static HWND m_hWndParent; // parent window: either desktop or console 
    HWND m_hWndHandle; // main program window

    // nustatomi InitWindowPars()
    static int m_iWndCaptionHgt;
    static int m_iWndMenuHgt;
    static int m_iWndBorderWdt;
#endif

    uchar m_pszCmdLine[KP_MAX_FNAME_LEN + 1]; // command line

    static KpLang m_iMsgLangOff; // member, set by KpInitWindows() // nupjautas iki KpNumOfLangs, galima naudoti masyvų indeksams

// --------------   
    KpCommonApp(const uchar *p_pszProdName, int p_iProdVer);
    virtual ~KpCommonApp(void);

    virtual void Init(HINSTANCE p_hInstance, const uchar *p_pszCmdLine, const void *p_pStackTop);  // pStackTop – caller stack top pointer,
    virtual void Close(void){}                                  // usually pointer to some local variable of the main() function
                                                                // could be NULL
#ifdef __WIN32__
    static void InitWindowPars(void); // iškviečiamas KpInitWindows()    
    static void KpInitWindows(HINSTANCE p_hInstance); // iškviečiamas konstruktoriaus
#endif

   
    void SetProd(const uchar *p_pszProdName, int p_iProdVer); // sets value of KpError.m_pszProdName[] and m_iProdVer
    
    void GetAppName(uchar *p_pszNameBuf);
                     // gets filename of application currently running
                     // at first call sets m_pszAppName[]
                     // pszNameBuf[KP_MAX_FNAME_LEN + 1]

    static void Pause(void); // panašiai kaip system("pause") laukia enterio iš stdin
};

extern KpCommonApp *KpApp;

#endif // #ifdef __cplusplus
#endif // #ifndef KPCAPP_INCLUDED
