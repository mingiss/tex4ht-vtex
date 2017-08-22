/* -----------------------------------------------
 *
 * kpstdio.h
 *
 *  I/O tools
 *
 * Changelog:
 *  2013-04-04  mp  initial creation
 *  2013-10-29  mp  KpFileDesc and KpFileDescList split of TeXtrcFileDesc and TeXtrcClass
 *  2016-09-06  mp  migration of kpsgrp from tv to kplib
 *  2016-09-07  mp  kpfhook split
 *  2016-09-08  mp  migration of kpsgrm from tv to kplib
 *  2017-05-22  mp  build on Linux Mint 18.1 Serena 64
 *
 */

#ifndef KPSTDIO_INCLUDED
#define KPSTDIO_INCLUDED

// ------------------------ opcijos
// #define KPSTDIO_FULL_LOG // former TEXTRC_FULL_LOG

// ------------------------
#define KP_LOG_EXT ((const uchar *)".log")
#define KPTRC_LOG_SUFF ((const uchar *)".kptrc") // log file extension // former TEXTRC_LOG_EXT ".textrc"

#define NO_FILE_DESC (-1) // illegal file descriptor value for open() 

// #ifndef __WIN32__
// MS substitutes for flags used in _open() & co
// look files
//  /usr/include/bits/fcntl-linux.h
//  /usr/include/asm-generic/fcntl.h
//  /usr/include/x86_64-linux-gnu/bits/fcntl-linux.h
//  /usr/include/linux/coda.h
//  ../include/Net2/newsrc/sys/fcntl.h
//  ../include/mingw-w64/mingw-w64-headers/crt/fcntl.h
#ifndef _O_RDONLY
#define _O_RDONLY   O_RDONLY    // 0x0000
#endif
#ifndef _O_WRONLY
#define _O_WRONLY   O_WRONLY    // 0x0001
#endif
#ifndef _O_RDWR
#define _O_RDWR     O_RDWR      // 0x0002
#endif
#ifndef _O_CREAT
#define _O_CREAT    O_CREAT     // 0x0200   // 00100 /* not fcntl */    // 0x0100
#endif
#ifndef _O_APPEND
#define _O_APPEND   O_APPEND    // 0x0008   // 02000
#endif
#ifndef _O_TRUNC
#define _O_TRUNC    O_TRUNC     // 0x0400   // 01000 /* not fcntl */    // 0x0200   // 0x010
#endif
#ifndef _O_TEXT
// #define _O_TEXT O_TEXT
#define _O_TEXT     0x4000
#endif
#ifndef _O_BINARY
#define _O_BINARY   0x8000
#endif
// https://msdn.microsoft.com/en-us/library/aa822867(v=vs.85).aspx
#define FILE_READ_DATA      0x0001
#define FILE_WRITE_DATA     0x0002
#define FILE_APPEND_DATA    0x0004

// #define _wfopen fopen
FILE* __cdecl _wfopen(const wchar_t* filename, const wchar_t* mode);
int __cdecl _wopen(const wchar_t* filename, int oflag, ... /* int pmode */);
// #endif

#ifndef HAVE__FDOPEN
#define _fdopen fdopen
#endif

#ifndef HAVE__GET_OSFHANDLE
intptr_t __cdecl _get_osfhandle(int _FileHandle);
#endif

// --------------------------
extern PLAIN_C void FnameSplit // call to KpStdIo::TvFnameSplit()
(
    uchar *p_pszDiskBuf,
    uchar *p_pszPathBuf,
    uchar *p_pszFNameBuf,
    uchar *p_pszFTypeBuf,
    const uchar *p_pszFullName
);

// -------------------------------------- failų I/O traceris
// PLAIN_C wrapperiai į KpFileDesc ir KpFileDescList (*KpFileDescListPtr) metodus

#define KPADD_FOPEN(fname, fmode) kpadd_fopen(fname, fmode, __FILE__, __LINE__)
#define KPADD_WFOPEN(fname, fmode) kpadd_wfopen(fname, fmode, __FILE__, __LINE__)
#define KPADD_FDOPEN(fname, fd, fmode) kpadd_fdopen(fname, fd, fmode, __FILE__, __LINE__)
#define KPADD_OPEN(file, flag, mode) kpadd_open(file, flag, mode, __FILE__, __LINE__)
#define KPADD_WOPEN(file, flag, mode) kpadd_wopen(file, flag, mode, __FILE__, __LINE__)
#define KPADD_CreateFileA(file, access, share_mode, attrs, cr_disp, flags, temp_file) \
    kpadd_CreateFileA(file, access, share_mode, attrs, cr_disp, flags, temp_file, __FILE__, __LINE__)
#define KPADD_CreateFileW(file, access, share_mode, attrs, cr_disp, flags, temp_file) \
    kpadd_CreateFileW(file, access, share_mode, attrs, cr_disp, flags, temp_file, __FILE__, __LINE__)
#ifdef UNICODE
#define KPADD_CreateFile(file, access, share_mode, attrs, cr_disp, flags, temp_file) \
    kpadd_CreateFileW(file, access, share_mode, attrs, cr_disp, flags, temp_file, __FILE__, __LINE__)
#else
#define KPADD_CreateFile(file, access, share_mode, attrs, cr_disp, flags, temp_file) \
    kpadd_CreateFileA(file, access, share_mode, attrs, cr_disp, flags, temp_file, __FILE__, __LINE__)
#endif
#define KPADD_FOPEN_CHKIN(fhandle, fname, fmode) kpadd_fopen_chkin(fname, \
    kpadd_fmode_to_flags(fmode), fhandle, NO_FILE_DESC, 0, __FILE__, __LINE__)

#define KPADD_FCLOSE(fh) kpadd_fclose(fh, __FILE__, __LINE__)
#define KPADD_CLOSE(fd) kpadd_close(fd, __FILE__, __LINE__)
#define KPADD_CloseHandle(fh) kpadd_CloseHandle(fh, __FILE__, __LINE__)    

#define KPADD_FCLOSE_CHKIN(fhandle) kpadd_fclose_chkin(fhandle, NO_FILE_DESC, 0, __FILE__, __LINE__)
// #define KPADD_FGETC(fname, fmode) kpadd_fgetc(fname, fmode, __FILE__, __LINE__)

// converts fopen() style mode string to open() style flags
extern PLAIN_C KPADDSHARED int kpadd_fmode_to_flags(const uchar *p_pszOpenMode);
// converts _wfopen() style mode string to open() style flags
extern int kpadd_wfmode_to_flags(const WCHAR *p_pszOpenMode);
// converts CreateFile() dwDesiredAccess parameter to open() style flags
extern int kpadd_acc_to_flags(DWORD p_dwDesiredAccess);
// creates fopen() style mode string from open() flags parameter
// returned string should be free()'ed after use
extern uchar *kpadd_open_flags_to_str(int p_iFlags);

// input failo atidarymo hookai; sukuria nauja KpFileDesc objektą ir 
//      įtraukia i KpFileDescListPtr->m_pFileList
// fopen() wrapper
extern PLAIN_C KPADDSHARED FILE *kpadd_fopen(
    const char *p_pszFname, const char *p_pszOpenMode,
    const char *p_pszSrcFile, int p_iSrcLine);
// _wfopen() wrapper    
extern PLAIN_C KPADDSHARED FILE *kpadd_wfopen( 
    const WCHAR *p_pszFname, const WCHAR *p_pszOpenMode,
    const char *p_pszSrcFile, int p_iSrcLine);
// fdopen()/_fdopen() wrapper
extern PLAIN_C KPADDSHARED FILE *kpadd_fdopen(
    const char *p_pszFname, int p_iFileDesc, const char *p_pszOpenMode,
    const char *p_pszSrcFile, int p_iSrcLine);
// open()/_open() wrapper
extern PLAIN_C KPADDSHARED int kpadd_open(
    const char *p_pszFname, int p_iFlags, int p_iPerm,
    const char *p_pszSrcFile, int p_iSrcLine);
// _wopen() wrapper
extern PLAIN_C KPADDSHARED int kpadd_wopen(const WCHAR *p_pszFname, int p_iFlags, int p_iPerm,
    const char *p_pszSrcFile, int p_iSrcLine);
// CreateFile() wrappers    
extern PLAIN_C KPADDSHARED HANDLE kpadd_CreateFileA(const char *p_lpFileName,
    DWORD p_dwDesiredAccess, DWORD p_dwShareMode, LPSECURITY_ATTRIBUTES p_lpSecurityAttributes,
    DWORD p_dwCreationDisposition, DWORD p_dwFlagsAndAttributes, HANDLE p_hTemplateFile,
    const char *p_pszSrcFile, int p_iSrcLine);
extern PLAIN_C KPADDSHARED HANDLE kpadd_CreateFileW(const WCHAR *p_pszFileName,
    DWORD p_dwDesiredAccess, DWORD p_dwShareMode, LPSECURITY_ATTRIBUTES p_lpSecurityAttributes,
    DWORD p_dwCreationDisposition, DWORD p_dwFlagsAndAttributes, HANDLE p_hTemplateFile,
    const char *p_pszSrcFile, int p_iSrcLine);
// KpFileDesc objekto įtraukimas į KpFileDescListPtr->m_pFileList
extern PLAIN_C KPADDSHARED void kpadd_fopen_chkin(const char *p_pszFname, int p_iFlags,
    /* const */ FILE *p_pFile /* = NULL */, int p_iFileDesc /* = NO_FILE_DESC */, HANDLE p_hFile /* = 0 */,
    const char *p_pszSrcFile, int p_iSrcLine);
extern PLAIN_C KPADDSHARED void kpadd_wfopen_chkin(const TCHAR *p_pszFname, int p_iFlags,
    /* const */ FILE *p_pFile /* = NULL */, int p_iFileDesc /* = NO_FILE_DESC */, HANDLE p_hFile /* = 0 */,
    const char *p_pszSrcFile, int p_iSrcLine);
    
// failo uždarymo hookai; naikina KpFileDescListPtr->m_pFileList objektą
// fclose() wrapper
extern PLAIN_C KPADDSHARED int kpadd_fclose(FILE *p_pFile, 
    const char *p_pszSrcFile, int p_iSrcLine);
// tikslus fopen() wrapperis pakišimui vietoj fopen() adreso 
// Python: Objects/fileobject.c: PyFile_FromFile(), fill_file_fields(), PyFileObject::f_close 
extern PLAIN_C KPADDSHARED int kpadd_fclose_plain(FILE *p_pFile); 
// close()/_close() wrapper
extern PLAIN_C KPADDSHARED int kpadd_close(int p_iFileDesc, 
    const char *p_pszSrcFile, int p_iSrcLine);
// CloseHandle() wrapper    
extern PLAIN_C KPADDSHARED BOOL kpadd_CloseHandle(HANDLE p_hFile,
    const char *p_pszSrcFile, int p_iSrcLine);
// KpFileDesc objekto naikinimas iš KpFileDescListPtr->m_pFileList
extern PLAIN_C KPADDSHARED void kpadd_fclose_chkin(
    const FILE *p_pFile /* = NULL */, int p_iFileDesc /* = NO_FILE_DESC */, HANDLE p_hFile /* = 0 */,
    const char *p_pszSrcFile, int p_iSrcLine);


// --------------------------
#ifdef __cplusplus

// --------------------------
// failų aprašų klasės
// naudojamos luatex ir python failų I/O hookinimui

// failo aprašo objekto klasė
class KpFileDesc
{
public:
/* const */ FILE *m_pFile; // in case the file is fopen()'ed or fdopen()'ed
int m_iFileDesc; // in case the file is open()'ed
HANDLE m_hFile; // in case the file is CreateFile()'ed
uchar m_pszFileName[KP_MAX_FNAME_LEN + 1];
int m_iFlags; // open()/_open() style flags

#ifdef KPSTDIO_FULL_LOG
uchar m_pszLogFileName[KP_MAX_FNAME_LEN + 1];
#endif

int m_iCurLine; // current line number 1..n
int m_iCurLpos; // current line byte position

    KpFileDesc(void)  { InitMembers(); }
    KpFileDesc(const uchar *p_pszFileName, int p_iFlags,
        /* const */ FILE *p_pFile /* = NULL */, int p_iFileDesc /* = NO_FILE_DESC */, HANDLE p_hFile /* = 0 */);
    virtual void InitMembers(void);

    virtual ~KpFileDesc() {}

    virtual void PullData(const KpFileDesc *p_pDescObj); // kopijuoja duomenis iš *p_pDescObj į *this

    // TeXtrcFileDesc: išveda dabartinės eilutės paskutinio simbolio pozicijos pranešimą        
    virtual void LogLastCh(void) {}

    // rašo pranešimą į m_pszLogFileName
#ifdef KPSTDIO_FULL_LOG
    void PutLogMessage(const uchar *p_pszFmt, va_list p_Args);
    void PutLogMessage(const char *p_pszFmt, va_list p_Args)
        { PutLogMessage((const uchar *)p_pszFmt, p_Args); }
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
        PutLogMessage(p_pszFmt, argptr);
    }
#endif

};


// failų aprašų objektų sąrašo klasė
class KpFileDescList
{
public:
KpTreeEntry<KpFileDesc> *m_pFileList; // list of file descriptors, m_pFileList->m_lpRecord points to KpFileDesc object 

public:
    KpFileDescList(void);
    ~KpFileDescList();

    // kuria naują KpFileDesc (iš KpFileDesc paveldėtą) objektą pridėjimui prie m_pFileList
    // paveldėtos iš KpFileDescList klasės turi perimti šitą metodą, 
    //      jeigu m_pFileList nori naudoti kaip paveldėtų objektų sąrašą 
    virtual KpFileDesc *KpFileDescFactory(const uchar *p_pszFileName, int p_iFlags,
        /* const */ FILE *p_pFile /* = NULL */, int p_iFileDesc /* = NO_FILE_DESC */, HANDLE p_hFile /* = 0 */);

    // įtraukia naują failą i m_pFileList
    void RegNewFile(const uchar *p_pszFileName, int p_iFlags,
        /* const */ FILE *p_pFile /* = NULL */, int p_iFileDesc /* = NO_FILE_DESC */, HANDLE p_hFile /* = 0 */);
    void RegNewFile(const char *p_pszFileName, int p_iFlags,
        /* const */ FILE *p_pFile, int p_iFileDesc, HANDLE p_hFile)
        { RegNewFile((const uchar *)p_pszFileName, p_iFlags, p_pFile, p_iFileDesc, p_hFile); }

    // perrašo m_pFileList įrašą naujais duomenim
    // susiranda pagal p_pDescObj->m_pFile
    void UpdateFile(const KpFileDesc *p_pDescObj);

    // TODO: išmeta uždarytą failo deskriptorių is sąrašo m_pFileList
    void DelFile(const FILE *p_pFile /* = NULL */, int p_iFileDesc /* = NO_FILE_DESC */, HANDLE p_hFile /* = 0 */);
        
    // ieško p_pFile atitinkančio m_pFileList įrašo
    // NULL -- nerado
    // *pppNodePtr (jei ppNodePtr != NULL) grąžina rasto elemento rodyklės adresą, 
    //      kad tą rodyklę būtų galima pakoreguoti, pvz., elementą po to išmetant su DelFile()
    //      *pppNodePtr rodo i rasto elemento tėvo lauką m_pFirstChild arba į m_pFileList (vyriausio tėvo atveju) 
    //      nesekmės atveju *pppNodePtr rodo į jauniausio anūko m_pFirstChild, kurio reikšmė yra NULL
    // ieško pagal m_pFileList[].GetValue()->m_pFile
    KpFileDesc *FindFile(const FILE *p_pFile, KpTreeEntry<KpFileDesc> ***pppNodePtr = NULL); 
    // ieško pagal m_pFileList[].GetValue()->m_iFileDesc
    KpFileDesc *FindFileByDesc(int p_iFileDesc, KpTreeEntry<KpFileDesc> ***pppNodePtr = NULL); 
    // ieško pagal m_pFileList[].GetValue()->m_hFile
    KpFileDesc *FindFileByHandle(HANDLE p_hFile, KpTreeEntry<KpFileDesc> ***pppNodePtr = NULL); 
                                            
    // rašo pranešimą į p_pFile elemento m_pszLogFileName
#ifdef KPSTDIO_FULL_LOG
    void PutLogMessage(const FILE *p_pFile, const uchar *p_pszFmt, va_list p_Args);
    void PutLogMessage(const FILE *p_pFile, const char *p_pszFmt, va_list p_Args)
        { PutLogMessage(p_pFile, (const uchar *)p_pszFmt, p_Args); }
    void PutLogMessage(const FILE *p_pFile, const uchar *p_pszFmt, ...)
    {
va_list argptr;
        va_start(argptr, p_pszFmt);
        PutLogMessage(p_pFile, p_pszFmt, argptr);
    }
    void PutLogMessage(const FILE *p_pFile, const char *p_pszFmt, ...)
    {
va_list argptr;
        va_start(argptr, p_pszFmt);
        PutLogMessage(p_pFile, p_pszFmt, argptr);
    }
#endif

};


// pointer to the global KpFileDescList object
extern KpFileDescList *KpFileDescListPtr;


// --------------------------
// bendro pobūdžio statinės funkcijos
class KpStdIo
{
public:
   static void TvFnameSplit          // splits p_pszFullName to file name and file
   (                                 //    type parts p_pszFNameBuf, p_pszFTypeBuf.
      uchar *p_pszDiskBuf,            // p_pszDiskBuf, p_pszPathBuf and p_pszFNameBuf
      uchar *p_pszPathBuf,            //    must be not shorter than
      uchar *p_pszFNameBuf,           //    KP_MAX_FNAME_LEN + 1 bytes, p_pszFTypeBuf
      uchar *p_pszFTypeBuf,           //    - not shorter than KP_MAX_FTYPE_LEN + 1
      const uchar *p_pszFullName
   );

   static void TvFnameSplit          // splits p_lpszFullName to file name and file
   (                                 //    type parts p_lpszFNameBuf, p_lpszFTypeBuf.
      KpString& sDiskBuf,            // p_lpszDiskBuf, p_lpszPathBuf and p_lpszFNameBuf
      KpString& sPathBuf,            //    must be not shorter than
      KpString& sFNameBuf,           //    KP_MAX_FNAME_LEN + 1 bytes, p_lpszFTypeBuf
      KpString& sFTypeBuf,           //    - not shorter than KP_MAX_FTYPE_LEN + 1
      KpString sFullName      
   );
};

#endif // #ifdef __cplusplus

#endif // #ifndef KPSTDIO_INCLUDED
