/* ----------------------------------------------
 *
 * kperr.h
 *
 *    error handling
 *
 * 2013-02-22  mp  initial creation
 *
 */

#ifndef KPERR_INCLUDED
#define KPERR_INCLUDED

#include <stdlib.h>

// ---------------------------------------- assertions
// KP_ASSERT[W[0]](bool p_bCond, HRESULT p_lhErrCode, uchar *p_pszMsg);
// KP_ASSERT[F][W[F][0]](bool p_bCond, HRESULT p_lhErrCode, uchar *p_pszFmt, ...);
//    assertion, whether p_bCond is kept
//    definitions of possible p_lhErrCode's given in kperrno.h
//    p_pszMsg / p_pszFmt could be null
//    in place of p_pszMsg return code from GetLastError() could be used as well
//
// severe error – throws an exception if p_bCond not kept
#ifdef KP_CPP
#define KP_ASSERT(p_bCond, p_lhErrCode, p_pszMsg) {{ if (!(p_bCond)){ KP_THROW(p_lhErrCode, p_pszMsg); } }}
#define KP_ASSERTF(p_bCond, p_lhErrCode, p_pszFmt, ...) {{ if (!(p_bCond)){ \
    KP_NEWA(out_str, uchar, KP_MAX_FILE_LIN_LEN + strlen(p_pszFmt) * 10 + 1000); \
    sprintf(out_str, p_pszFmt, __VA_ARGS__); \
    KP_THROW(p_lhErrCode, out_str); \
    KP_DELETEA(out_str); /* čia jau nebeateis */ \
    } }}
#else
#define KP_ASSERT(p_bCond, p_lhErrCode, p_pszMsg) {{ if (!(p_bCond)){ KP_ERROR(p_lhErrCode, p_pszMsg); exit(p_lhErrCode); } }}
#define KP_ASSERTF(p_bCond, p_lhErrCode, p_pszFmt, ...) {{ if (!(p_bCond)){ KP_ERRORF(p_lhErrCode, p_pszFmt, __VA_ARGS__); exit(p_lhErrCode); } }}
#endif

// local fault – puts warning to the log file and sets local variable retc (HRESULT retc)
#define KP_ASSERTW(p_bCond, p_lhErrCode, p_pszMsg) {{ if (SUCCEEDED(retc)) if (!(p_bCond)){ KP_WARNING(p_lhErrCode, p_pszMsg); retc = p_lhErrCode; } }}
#define KP_ASSERTWF(p_bCond, p_lhErrCode, p_pszFmt, ...) {{ if (SUCCEEDED(retc)) if (!(p_bCond)){ KP_WARNINGF(p_lhErrCode, p_pszFmt, __VA_ARGS__); retc = p_lhErrCode; } }}
// the same as KP_ASSERTW, but does not bother with retc
#define KP_ASSERTW0(p_bCond, p_lhErrCode, p_pszMsg) {{ if (!(p_bCond)){ KP_WARNING(p_lhErrCode, p_pszMsg); } }}
#define KP_ASSERTWF0(p_bCond, p_lhErrCode, p_pszFmt, ...) {{ if (!(p_bCond)){ KP_WARNINGF(p_lhErrCode, p_pszFmt, __VA_ARGS__); } }}

// conditional local fault – depending on p_bThrowError puts warning or throws an error
#define KP_ASSERTQ(p_bCond, p_lhErrCode, p_pszMsg, p_bThrowError) {{ \
    if (p_bThrowError){ KP_ASSERT(p_bCond, p_lhErrCode, p_pszMsg) } \
    else { KP_ASSERTW(p_bCond, p_lhErrCode, p_pszMsg) } }}

#ifdef __cplusplus
// ---------------------------------------- exceptions
#define KP_THROW(p_lhErrCode, p_pszMsg) {{ throw(new KpException(p_lhErrCode, p_pszMsg, (const uchar *)__FILE__, __LINE__)); }}

// KP_CATCH(const std::exception &p_rExc);
// KP_CATCH(KpException &p_rKpExc);
#define KP_CATCH(p_KpExc) {{ KpError.Catch(p_KpExc); }}
#endif
#define KP_CATCH_ALL \
    catch(const KpException *p_pKpExc) \
    { \
        KP_CATCH(*p_pKpExc); \
    } \
    catch(const std::exception &p_rExc) \
    { \
        KP_CATCH(p_rExc); \
    } \
    catch(...) \
    { \
        KP_ERROR(KP_E_UNHANDLED_EXCEPTION, null); \
    }


// ---------------------------------------- error messages
#ifdef __cplusplus
#define KP_ERROR(p_lhErrCode, p_pszMsg) {{ KpError.OutputErrorMessage(p_lhErrCode, /* (const uchar *) */ p_pszMsg, True, (const uchar *)__FILE__, __LINE__); }}
#define KP_ERRORF(p_lhErrCode, p_pszFmt, ...) {{ KpError.OutputErrorMessage(p_lhErrCode, (const uchar *)p_pszFmt, True, (const uchar *)__FILE__, __LINE__, __VA_ARGS__); }}
#define KP_WARNING(p_lhErrCode, p_pszMsg) {{ KpError.OutputErrorMessage(p_lhErrCode, /* (const uchar *) */ p_pszMsg, False, (const uchar *)__FILE__, __LINE__); }}
#define KP_WARNINGF(p_lhErrCode, p_pszFmt, ...) {{ KpError.OutputErrorMessage(p_lhErrCode, (const uchar *)p_pszFmt, False, (const uchar *)__FILE__, __LINE__, __VA_ARGS__); }}
#define KP_TRACE(...) {{ KpError.PutLogMessage((const char *)__VA_ARGS__); }}
#else
#define KP_ERROR(p_lhErrCode, p_pszMsg) {{ KpOutputErrorMessage(p_lhErrCode, /* (const uchar *) */ p_pszMsg, True, (const uchar *)__FILE__, __LINE__); }}
#define KP_ERRORF(p_lhErrCode, p_pszFmt, ...) {{ KpOutputErrorMessage(p_lhErrCode, (const uchar *)p_pszFmt, True, (const uchar *)__FILE__, __LINE__, __VA_ARGS__); }}
#define KP_WARNING(p_lhErrCode, p_pszMsg) {{ KpOutputErrorMessage(p_lhErrCode, /* (const uchar *) */ p_pszMsg, False, (const uchar *)__FILE__, __LINE__); }}
#define KP_WARNINGF(p_lhErrCode, p_pszFmt, ...) {{ KpOutputErrorMessage(p_lhErrCode, (const uchar *)p_pszFmt, False, (const uchar *)__FILE__, __LINE__, __VA_ARGS__); }}
#define KP_TRACE(...) {{ KpPutLogMessage((const char *)__VA_ARGS__); }}
#endif



#ifdef __cplusplus
class KpException : public std::exception
{
public:
   // KpErrorClass::OutputErrorMessage() parametrai
   HRESULT m_lhErrCode;
   uchar m_pszMsg[KP_MAX_FILE_LIN_LEN + 1];
   LONG m_lWindowsErrorCode;
   uchar m_pszSourceFile[KP_MAX_FNAME_LEN + 1];
   int m_iSourceLine;

   KpException
   (
      HRESULT p_lhRetc,
      const uchar *p_pszMessageText,
      const uchar *p_pszSourceFile,
      int p_iSourceLine
   ){ Constructor(p_lhRetc, p_pszMessageText, 0L, p_pszSourceFile, p_iSourceLine); }

   KpException
   (
      HRESULT p_lhRetc,
      const char *p_pszMessageText,
      const uchar *p_pszSourceFile,
      int p_iSourceLine
   ){ Constructor(p_lhRetc, (const uchar *)p_pszMessageText, 0L, p_pszSourceFile, p_iSourceLine); }

   KpException
   (
      HRESULT p_lhRetc,
      KpString& p_rsMessageText,
      const uchar *p_pszSourceFile,
      int p_iSourceLine
   ){ Constructor(p_lhRetc, p_rsMessageText.c_str(), 0L, p_pszSourceFile, p_iSourceLine); }

   KpException
   (
      HRESULT p_lhRetc,
      LONG p_lWindowsErrorCode, // return value of GetLastError() etc.
      const uchar *p_pszSourceFile,
      int p_iSourceLine
   ){ Constructor(p_lhRetc, null, p_lWindowsErrorCode, p_pszSourceFile, p_iSourceLine); }

   void Constructor
   (
      HRESULT p_lhRetc,
      const uchar *p_pszMessageText,
      LONG p_lWindowsErrorCode,
      const uchar *p_pszSourceFile,
      int p_iSourceLine
   );
};


// ----------------------------------------
class KpErrorClass
{
public:
    uchar m_pszProdName[KP_MAX_FNAME_LEN + 1];

    static
#if (__GNUC__ != 5) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 0)
        const
#endif
            uchar *m_pszaKpMessages[NumOfKpMessages][KpNumOfLangs];

//  volatile int m_iInsideOfStackDump; // StackDump() recursion avoiding semaphore
    volatile int m_iInsideOfPutLogMessage; // PutLogMessage() recursion avoiding semaphore

    HRESULT m_lhLastRetc;
    uchar m_pszLastMessageText[KP_MAX_FILE_LIN_LEN + 1];
    uchar m_pszLastSourceFile[KP_MAX_FNAME_LEN + 1];
    int m_iLastSourceLine;

    bool m_bOutMsg;

    KpErrorClass(const uchar *p_pszProdName, bool p_bOutMsg);

    void SetProdName(const uchar *p_pszNameBuf); // p_pszNameBuf[KP_MAX_FNAME_LEN + 1]
    void GetProdName(uchar *p_pszNameBuf); // p_pszNameBuf[KP_MAX_FNAME_LEN + 1]
    const uchar *GetProdNamePtr(void); // grąžina m_pszProdName, taigi, ne ilgesnis už KP_MAX_FNAME_LEN

//  void StackDump(void);

    void GetLogFileName(uchar *p_pszLogFNameBuf); // p_pszLogFNameBuf[KP_MAX_FNAME_LEN + 1];
    void EncodeLogBuf(uchar *p_pBuffer, int p_iDataLen);

// --------------------
    void PutLogMessage(const uchar *p_pszFmt, va_list Args);
    void PutLogMessage(const uchar *p_pszFmt, ...)
    {
va_list argptr;
        va_start(argptr, p_pszFmt);
        PutLogMessage(p_pszFmt, argptr);
    }
    void PutLogMessage(const char *p_pszFmt, ...)
    {
va_list argptr;
        va_start(argptr, p_pszFmt);
        PutLogMessage((const uchar *)p_pszFmt, argptr);
    }

// --------------------
    void SendDiagMsg
    (
        const uchar *p_pszMessageText,  // pranešimas klientui
        bool p_bSevereError,            // jei False – ne klaida, o tiesiog diag. msg siuntimas,
                                        //    formuoti atitinkamą ikoną ir kepurės tekstą
        const uchar *p_pszAddMessage    // papildomas pranešimas apie klaidos kodą ir src failą,
                                        //    klientui nerodomas, siunčiamas helpdeskui
    );

// --------------------
    static void FormatErrorMessage
    (
        const HRESULT p_lhRetc,
        uchar *p_pszMsg
    );                         // generates the error message
                               // p_pszMsg is used to return back the error text, must
                               //    be not shorter, than KP_MAX_FILE_LIN_LEN bytes
                               // must be defined locally for processing special errors of application

    static HRESULT FormatSystemErrorMessage
    (
        LONG p_lWindowsErrorCode,
        uchar *p_pszMsg,
        bool p_bFullFormat
    );
    static uchar *FormatSystemErrorMessage(LONG p_lWindowsErrorCode);
                               // formats windows system error message
                               // bFullFormat == False - tik lietuviškas pranešimas
                               // p_pszMsg is used to return back the error text, must
                               //    be not shorter, than KP_MAX_FILE_LIN_LEN bytes

    static const uchar *FormatErrorMessageHTTP(int p_iHTTP_RetCode);
    static int TranslToHTTP_RetCode(HRESULT p_lRetc); // verčia KP klaidos kodą KP_E_... į HTTP atsakymo kodą HTTP_ANSW_...
    static HRESULT TranslFromHTTP_RetCode(int p_iHTTP_RetCode); // verčia HTTP atsakymo kodą HTTP_ANSW_... į KP klaidos kodą KP_E_...

// --------------------
    void OutputErrorMessage          // outputs error message; calls FormatErrorMessage()
    (
        HRESULT p_lhRetc,
        const uchar *p_pszFmt,    // explanational error text / message format string
        bool p_bSevereError,      // True - pranešimas išvedamas ne tik į log failą, bet ir į ekraną su galimybe išsiųsti diagnostinį pranešimą
        const uchar *p_pszSourceFile,
        int p_iSourceLine,
        ...
    );

    void OutputErrorMessage
    (
        HRESULT p_lhRetc,
        const char *p_pszFmt,
        bool p_bSevereError,
        const uchar *p_pszSourceFile,
        int p_iSourceLine,
        ...
    ){ va_list argptr; va_start(argptr, p_iSourceLine); OutputErrorMessage(p_lhRetc, (const uchar *)p_pszFmt, p_bSevereError, p_pszSourceFile, p_iSourceLine, argptr); }

    void OutputErrorMessage
    (
        HRESULT p_lhRetc,
        LONG p_lWindowsErrorCode, // return value of GetLastError() etc.
        bool p_bSevereError,
        const uchar *p_pszSourceFile,
        int p_iSourceLine
    ){ OutputErrorMessage(p_lhRetc, (const char *)FormatSystemErrorMessage(p_lWindowsErrorCode), p_bSevereError, p_pszSourceFile, p_iSourceLine); };

// --------------------
    void Catch(const std::exception &p_rExc);
};

// should be defined locally in main module of the project
// for kplib drived projects defined in kpstdlib.cpp
extern KpErrorClass KpError;

#endif // #ifdef __cplusplus

// call to KpError.OutputErrorMessage()
extern PLAIN_C void KpOutputErrorMessage
(
    HRESULT p_lhRetc,
    const uchar *p_pszFmt,
    bool p_bSevereError,
    const uchar *p_pszSourceFile,
    int p_iSourceLine,
    ...
);

// call to KpError.FormatSystemErrorMessage()
extern PLAIN_C uchar *KpFormatSystemErrorMessage(LONG p_lWindowsErrorCode);

// call to KpError.PutLogMessage()
extern PLAIN_C void KpPutLogMessage(const uchar *p_pszFmt, ...);


// call to KpError.GetProdName() and KpApp->GetAppName()
// returns char string not longer than KP_MAX_FNAME_LEN
extern PLAIN_C const uchar *KpGetProdName(void);
// extern String program;  /* name of dvread program */
#define program KpGetProdName() // definition for dvread.c, etc.

// ----------------------------------------
#endif // #ifndef KPERR_INCLUDED
