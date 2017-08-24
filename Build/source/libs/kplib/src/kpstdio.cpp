/* ---------------------------------------------------
 *
 * kpstdio.cpp
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

// --------------------------------------
#include "envir.h"

#include <string.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#ifdef _MSC_VER
#include <io.h>
#endif
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
#include "kptree.h"
#include "kpstdio.h"


void FnameSplit
(
    uchar *p_pszDiskBuf,
    uchar *p_pszPathBuf,
    uchar *p_pszFNameBuf,
    uchar *p_pszFTypeBuf,
    const uchar *p_pszFullName
)
{
    KpStdIo::TvFnameSplit(p_pszDiskBuf, p_pszPathBuf, p_pszFNameBuf, p_pszFTypeBuf, p_pszFullName);
}


// --------------------------
// KpStdIo

void KpStdIo::TvFnameSplit
(
KpString& sDiskBuf,
KpString& sPathBuf,
KpString& sFNameBuf,
KpString& sFTypeBuf,
KpString sFullName
)
{
    // TODO: perdaryt per KpString::Split()
uchar disk[KP_MAX_FNAME_LEN + 1];
uchar path[KP_MAX_FNAME_LEN + 1];
uchar fname[KP_MAX_FNAME_LEN + 1];
uchar ftype[KP_MAX_FNAME_LEN + 1];
    TvFnameSplit(disk, path, fname, ftype, sFullName.c_str());
    sDiskBuf = disk;
    sPathBuf = path;
    sFNameBuf = fname;
    sFTypeBuf = ftype;
}

void KpStdIo::TvFnameSplit
(
uchar *p_pszDiskBuf,
uchar *p_pszPathBuf,
uchar *p_pszFNameBuf,
uchar *p_pszFTypeBuf,
const uchar *p_pszFullName
)
{
    KP_ASSERT(p_pszDiskBuf && p_pszPathBuf && p_pszFNameBuf &&
        p_pszFTypeBuf && p_pszFullName, E_INVALIDARG, null);

    KP_ASSERT(strlen(p_pszFullName) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, p_pszFullName);

uchar str_buf[KP_MAX_FNAME_LEN + 1];
    strcpy(str_buf, p_pszFullName);

uchar *disk_ptr;
uchar *path_ptr;
uchar *fnam_ptr;
uchar *typ_ptr;
uchar *pnts;
    disk_ptr = pnts = path_ptr = fnam_ptr = typ_ptr = str_buf;

    do
    {
      if (*pnts == ':') path_ptr = pnts + 1;
      if ((*pnts == '\\') || (*pnts == '/')) fnam_ptr = pnts + 1;
      if (*pnts == '.') typ_ptr = pnts;
      pnts++;
    } while (*pnts);

// type
    if (typ_ptr <= fnam_ptr) typ_ptr=(uchar *)"";
    else *(typ_ptr++) = Nul;

    KP_ASSERT(strlen(typ_ptr) < KP_MAX_FTYPE_LEN, KP_E_BUFFER_OVERFLOW, null);
    strcpy(p_pszFTypeBuf, typ_ptr);

// fname
    if (fnam_ptr < path_ptr) fnam_ptr = path_ptr;
    KP_ASSERT(strlen(fnam_ptr) < KP_MAX_FTYPE_LEN, KP_E_BUFFER_OVERFLOW, null);
    strcpy(p_pszFNameBuf, fnam_ptr);

// path
    if (fnam_ptr == path_ptr) strcpy(p_pszPathBuf, KP_CUR_DIR_STR);
    else /* if (fnam_ptr > path_ptr) */
    {
        *fnam_ptr-- = Nul;
        if ((*fnam_ptr=='\\') || (*fnam_ptr=='/')) *fnam_ptr = Nul;
        else KP_THROW(KP_E_SYSTEM_ERROR, null);

        KP_ASSERT(strlen(path_ptr) < KP_MAX_FTYPE_LEN, KP_E_BUFFER_OVERFLOW, null);
        strcpy(p_pszPathBuf, path_ptr);
    }

// disk
    *path_ptr = Nul;
    KP_ASSERT(strlen(disk_ptr) < KP_MAX_FTYPE_LEN, KP_E_BUFFER_OVERFLOW, null);
    strcpy(p_pszDiskBuf, disk_ptr);
}


// --------------------------------------
#ifndef __WIN32__
FILE* _wfopen(const wchar_t * /* filename */, const wchar_t * /* mode */)
{
    KP_ERROR(E_NOTIMPL, null);
return NULL;
}

int _wopen(const wchar_t * /* filename */, int /* oflag */, ... /* int pmode */)
{
    KP_ERROR(E_NOTIMPL, null);
    return 0;
}
#endif

#ifndef HAVE__GET_OSFHANDLE
intptr_t __cdecl _get_osfhandle(int /* _FileHandle */)
{
    KP_ERROR(E_NOTIMPL, null);
return 0;
}
#endif

// --------------------------------------
uchar *fgetss(uchar *buf, int maxnum, FILE *fil)
{
uchar *retstr, *pntc;

    retstr = NULL;
    fgets((char *)buf, maxnum, fil);
    if ((!feof(fil)) && (!ferror(fil)))
    {
        pntc = strchr(buf, Cr);
        if (pntc)
            *pntc = Nul;
        pntc = strchr(buf, Lf);
        if (pntc)
            *pntc=Nul;
        retstr = buf;
    }

return(retstr);
}

// -------------------------------------- File I/O traceris
// *KpFileDescListPtr metodų PLAIN_C wrapperiai

int kpadd_fmode_to_flags(const uchar *p_pszOpenMode)
{
    KP_ASSERT(p_pszOpenMode, E_INVALIDARG, null);
int fflags = 0;
    if (strchr(
#if (__GNUC__ == 5) && (__GNUC_MINOR__ == 4) && (__GNUC_PATCHLEVEL__ == 0)
        (uchar *)
#endif
            p_pszOpenMode, 'r')) fflags |= _O_RDONLY;
    if (strchr(
#if (__GNUC__ == 5) && (__GNUC_MINOR__ == 4) && (__GNUC_PATCHLEVEL__ == 0)
        (uchar *)
#endif
            p_pszOpenMode, 'w'))
    {
        if (fflags & _O_RDONLY) fflags = (fflags & ~_O_RDONLY) | _O_RDWR | _O_CREAT;
        else fflags |= _O_WRONLY | _O_CREAT;
    }
    if (strchr(
#if (__GNUC__ == 5) && (__GNUC_MINOR__ == 4) && (__GNUC_PATCHLEVEL__ == 0)
        (uchar *)
#endif
            p_pszOpenMode, 'a')) fflags = (fflags & ~(_O_RDONLY | _O_RDWR | _O_CREAT)) | _O_WRONLY | _O_APPEND;
    if (strchr(
#if (__GNUC__ == 5) && (__GNUC_MINOR__ == 4) && (__GNUC_PATCHLEVEL__ == 0)
        (uchar *)
#endif
            p_pszOpenMode, 'b')) fflags |= _O_BINARY;
    else fflags |= _O_TEXT;

return(fflags);
}


int kpadd_wfmode_to_flags(const WCHAR *p_pszOpenMode)
{
    KP_ASSERT(p_pszOpenMode, E_INVALIDARG, null);
int fflags = 0;
    if (wcschr(p_pszOpenMode, 'r')) fflags |= _O_RDONLY;
    if (wcschr(p_pszOpenMode, 'w'))
    {
        if (fflags & _O_RDONLY) fflags = (fflags & ~_O_RDONLY) | _O_RDWR | _O_CREAT;
        else fflags |= _O_WRONLY | _O_CREAT;
    }
    if (wcschr(p_pszOpenMode, 'a')) fflags = (fflags & ~(_O_RDONLY | _O_RDWR | _O_CREAT)) | _O_WRONLY | _O_APPEND;
    if (wcschr(p_pszOpenMode, 'b')) fflags |= _O_BINARY;
    else fflags |= _O_TEXT;

return(fflags);
}


int kpadd_acc_to_flags(DWORD p_dwDesiredAccess)
{
int fflags = 0;
    if (p_dwDesiredAccess & FILE_READ_DATA) fflags |= _O_RDONLY;
    if (p_dwDesiredAccess & FILE_WRITE_DATA)  
    {
        if (fflags & _O_RDONLY) fflags = (fflags & ~_O_RDONLY) | _O_RDWR | _O_CREAT;
        else fflags |= _O_WRONLY | _O_CREAT;
    }
    if (p_dwDesiredAccess & FILE_APPEND_DATA) fflags = (fflags & ~(_O_RDONLY | _O_RDWR | _O_CREAT)) | _O_WRONLY | _O_APPEND;
    fflags |= _O_BINARY;

return(fflags);
}


uchar *kpadd_open_flags_to_str(int p_iFlags)
{
uchar *fmode = null;
    KP_NEWA(fmode, uchar, 20);
    fmode[0] = Nul;

    if (p_iFlags & _O_RDONLY) strcat(fmode, "r");
    if (p_iFlags & (_O_WRONLY | _O_CREAT | _O_TRUNC | _O_RDWR)) strcat(fmode, "w");
    if (p_iFlags & _O_APPEND) strcat(fmode, "a");
    if (p_iFlags & _O_BINARY) strcat(fmode, "b");

return(fmode);
}


FILE *kpadd_fopen(const char *p_pszFname, const char *p_pszOpenMode,
    const char *p_pszSrcFile, int p_iSrcLine)
{
FILE *ret_file = NULL;

    try
    {
        KP_ASSERT(p_pszFname, E_INVALIDARG, null);
        KP_ASSERT(p_pszOpenMode, E_INVALIDARG, null);

    uchar *fmode = null;
        KP_NEWA(fmode, uchar, strlen(p_pszOpenMode) + 10);
        strcpy(fmode, p_pszOpenMode);
        if(strchr(fmode, 'b') == null) strcat(fmode, "b"); // atidarinėjam visada binary mode, į tekstą vers I/O wrapperiai

        ret_file = fopen(p_pszFname, (const char *)fmode);

    int fflags = kpadd_fmode_to_flags((const uchar *)p_pszOpenMode);
        kpadd_fopen_chkin(p_pszFname, fflags, ret_file, NO_FILE_DESC, 0, p_pszSrcFile, p_iSrcLine);

        KP_DELETEA(fmode);
    }
    KP_CATCH_ALL; 

return(ret_file); 
}


FILE *kpadd_wfopen(
    const WCHAR *
#if defined(__WIN32__) && defined(UNICODE)
        p_pszFname
#endif
    , const WCHAR *
#if defined(__WIN32__) && defined(UNICODE)
        p_pszOpenMode
#endif
    , const char *
#if defined(__WIN32__) && defined(UNICODE)
        p_pszSrcFile
#endif
    , int
#if defined(__WIN32__) && defined(UNICODE)
        p_iSrcLine
#endif
    )
{
FILE *ret_file = NULL;

    try
    {
#if (!defined(__WIN32__)) || (!defined(UNICODE))
        KP_ASSERT(false, E_NOTIMPL, null);
#else
        KP_ASSERT(p_pszFname, E_INVALIDARG, null);
        KP_ASSERT(p_pszOpenMode, E_INVALIDARG, null);

    TCHAR *fmode = NULL;
        KP_NEWA(fmode, TCHAR, wcslen(p_pszOpenMode) + 10);
        wcscpy(fmode, p_pszOpenMode);
        if(wcschr(fmode, _T('b'))) wcscat(fmode, _T("b")); // atidarinėjam visada binary mode, į tekstą vers I/O wrapperiai

        ret_file = _wfopen(p_pszFname, fmode);

    int fflags = kpadd_wfmode_to_flags(p_pszOpenMode);
        kpadd_wfopen_chkin(p_pszFname, fflags, ret_file, NO_FILE_DESC, NULL, p_pszSrcFile, p_iSrcLine);

        KP_DELETEA(fmode);
#endif
    }
    KP_CATCH_ALL; 

return(ret_file); 
}


FILE *kpadd_fdopen(const char *p_pszFname, int p_iFileDesc, const char *p_pszOpenMode,
    const char *p_pszSrcFile, int p_iSrcLine)
{
FILE *ret_file = NULL;

    try
    {
        KP_ASSERT(p_pszFname, E_INVALIDARG, null);
        KP_ASSERT(p_pszOpenMode, E_INVALIDARG, null);

    uchar *fmode = null;
        KP_NEWA(fmode, uchar, strlen(p_pszOpenMode) + 10);
        strcpy(fmode, p_pszOpenMode);
        if(strchr(fmode, 'b') == null) strcat(fmode, "b"); // atidarinėjam visada binary mode, į tekstą vers I/O wrapperiai

        ret_file = fdopen(p_iFileDesc, (const char *)fmode);

    int fflags = kpadd_fmode_to_flags((const uchar *)p_pszOpenMode);
        kpadd_fopen_chkin(p_pszFname, fflags, ret_file, p_iFileDesc, 0, p_pszSrcFile, p_iSrcLine);

        KP_DELETEA(fmode);
    }
    KP_CATCH_ALL;

return(ret_file);
}


int kpadd_open(const char *p_pszFname, int p_iFlags, int p_iPerm,
    const char *p_pszSrcFile, int p_iSrcLine)
{
int ret_fdesc = NO_FILE_DESC;

    try
    {
        KP_ASSERT(p_pszFname, E_INVALIDARG, null);

    int fflags = (p_iFlags & ~_O_TEXT) | _O_BINARY; // atidarinėjam visada binary mode, į tekstą vers I/O wrapperiai
        ret_fdesc = _open(p_pszFname, fflags, p_iPerm);

        kpadd_fopen_chkin(p_pszFname, p_iFlags, NULL, ret_fdesc, 0, p_pszSrcFile, p_iSrcLine);
    }
    KP_CATCH_ALL;

return(ret_fdesc);
}


int kpadd_wopen(
    const WCHAR *
#if defined(__WIN32__) && defined(UNICODE)
        p_pszFname
#endif
    , int
#if defined(__WIN32__) && defined(UNICODE)
        p_iFlags
#endif
    , int
#if defined(__WIN32__) && defined(UNICODE)
        p_iPerm
#endif
    , const char *
#if defined(__WIN32__) && defined(UNICODE)
        p_pszSrcFile
#endif
    , int
#if defined(__WIN32__) && defined(UNICODE)
        p_iSrcLine
#endif
    )
{
int ret_fdesc = NO_FILE_DESC;

    try
    {
#if (!defined(__WIN32__)) || (!defined(UNICODE))
        KP_ASSERT(false, E_NOTIMPL, null);
#else
        KP_ASSERT(p_pszFname, E_INVALIDARG, null);

    int fflags = (p_iFlags & ~_O_TEXT) | _O_BINARY; // atidarinėjam visada binary mode, į tekstą vers I/O wrapperiai
        ret_fdesc = _wopen(p_pszFname, fflags, p_iPerm);

        kpadd_wfopen_chkin(p_pszFname, p_iFlags, NULL, ret_fdesc, NULL, p_pszSrcFile, p_iSrcLine);
#endif
    }
    KP_CATCH_ALL;

return(ret_fdesc);
}


HANDLE kpadd_CreateFileA(
    const char *
#ifdef __WIN32__
        p_lpFileName
#endif
    , DWORD
#ifdef __WIN32__
        p_dwDesiredAccess
#endif
    , DWORD
#ifdef __WIN32__
        p_dwShareMode
#endif
    , LPSECURITY_ATTRIBUTES
#ifdef __WIN32__
        p_lpSecurityAttributes
#endif
    , DWORD
#ifdef __WIN32__
        p_dwCreationDisposition
#endif
    , DWORD
#ifdef __WIN32__
        p_dwFlagsAndAttributes
#endif
    , HANDLE
#ifdef __WIN32__
        p_hTemplateFile
#endif
    , const char *
#ifdef __WIN32__
        p_pszSrcFile
#endif
    , int
#ifdef __WIN32__
        p_iSrcLine
#endif
    )
{
HANDLE retv = 0;

    try
    {
#ifndef __WIN32__
        KP_ASSERT(false, E_NOTIMPL, null);
#else
        retv = CreateFileA(p_lpFileName, p_dwDesiredAccess, p_dwShareMode, p_lpSecurityAttributes,
            p_dwCreationDisposition, p_dwFlagsAndAttributes, p_hTemplateFile);

    int fflags = kpadd_acc_to_flags(p_dwDesiredAccess);
        kpadd_fopen_chkin(p_lpFileName, fflags, NULL, NO_FILE_DESC, retv,
            p_pszSrcFile, p_iSrcLine);
#endif
    }
    KP_CATCH_ALL;

return(retv);
}


HANDLE kpadd_CreateFileW(
    const WCHAR *
#if defined(__WIN32__) && defined(UNICODE)
        p_lpFileName
#endif
    , DWORD
#if defined(__WIN32__) && defined(UNICODE)
        p_dwDesiredAccess
#endif
    , DWORD
#if defined(__WIN32__) && defined(UNICODE)
        p_dwShareMode
#endif
    , LPSECURITY_ATTRIBUTES
#if defined(__WIN32__) && defined(UNICODE)
        p_lpSecurityAttributes
#endif
    , DWORD
#if defined(__WIN32__) && defined(UNICODE)
        p_dwCreationDisposition
#endif
    , DWORD
#if defined(__WIN32__) && defined(UNICODE)
        p_dwFlagsAndAttributes
#endif
    , HANDLE
#if defined(__WIN32__) && defined(UNICODE)
        p_hTemplateFile
#endif
    , const char *
#if defined(__WIN32__) && defined(UNICODE)
        p_pszSrcFile
#endif
    , int
#if defined(__WIN32__) && defined(UNICODE)
        p_iSrcLine
#endif
    )
{
HANDLE retv = 0;

    try
    {
#if (!defined(__WIN32__)) || (!defined(UNICODE))
        KP_ASSERT(false, E_NOTIMPL, null);
#else
        retv = CreateFileW(p_lpFileName, p_dwDesiredAccess, p_dwShareMode, p_lpSecurityAttributes,
            p_dwCreationDisposition, p_dwFlagsAndAttributes, p_hTemplateFile);

    int fflags = kpadd_acc_to_flags(p_dwDesiredAccess);
        kpadd_wfopen_chkin(p_lpFileName, fflags, NULL, NO_FILE_DESC, retv,
            p_pszSrcFile, p_iSrcLine);
#endif
    }
    KP_CATCH_ALL;

return(retv);
}


void kpadd_wfopen_chkin(
    const TCHAR * /* p_pszFname */, int p_iFlags, /* const */ FILE *p_pFile, int p_iFileDesc, HANDLE p_hFile,
    const char *p_pszSrcFile, int p_iSrcLine)
{
    try
    {
#ifndef __WIN32__
        KP_ASSERT(false, E_NOTIMPL, null);
#endif
    uchar fname_utf8[KP_MAX_FNAME_LEN + 1];
        // TODO: konvertuoti p_pszFname į UTF-8
        KP_THROW(E_NOTIMPL, null);

        kpadd_fopen_chkin((const char *)fname_utf8, p_iFlags, p_pFile, p_iFileDesc, p_hFile,
            p_pszSrcFile, p_iSrcLine);
    }
    KP_CATCH_ALL;
}


void kpadd_fopen_chkin(const char *p_pszFname, int p_iFlags,
    /* const */ FILE *p_pFile, int p_iFileDesc, HANDLE p_hFile,
    const char *
#ifdef Debug
        p_pszSrcFile
#endif
    , int
#ifdef Debug
        p_iSrcLine
#endif
    )
{
    try
    {
        KP_ASSERT(KpFileDescListPtr, E_POINTER, null);

        KpFileDescListPtr->RegNewFile((const uchar *)p_pszFname, p_iFlags,
            p_pFile, p_iFileDesc, p_hFile);
#ifdef KPSTDIO_FULL_LOG
        KpFileDescListPtr->PutLogMessage(p_pFile, "Opened: %s", p_pszFname);
#endif

#ifdef Debug
uchar str_buf[KP_MAX_FILE_LIN_LEN + 1];    
        sprintf((char *)str_buf,
#ifdef _WIN64
            ".... kpstdio: kpadd_fopen_chkin(\"%s\") %x; %llx; %d; %llx; file: %s line: %d\n",
#else
            ".... kpstdio: kpadd_fopen_chkin(\"%s\") %x; %lx; %d; %lx; file: %s line: %d\n",
#endif
                p_pszFname, p_iFlags,
                (unsigned long
#ifdef _WIN64
                    long
#endif
                        )p_pFile,
                p_iFileDesc,
                (unsigned long
#ifdef _WIN64
                    long
#endif
                        )p_hFile,
                p_pszSrcFile, p_iSrcLine);
//      cout << endl << str_buf;
        puts("\n"); puts((const char *)str_buf);
        KpError.PutLogMessage(str_buf);
//      KpError.StackDump();
#endif
    }
    KP_CATCH_ALL;
}


int kpadd_fclose(FILE *p_pFile, const char *p_pszSrcFile, int p_iSrcLine)
{
    kpadd_fclose_chkin(p_pFile, NO_FILE_DESC, 0, p_pszSrcFile, p_iSrcLine);
return(fclose(p_pFile));
}


int kpadd_fclose_plain(FILE *p_pFile)
{
return(kpadd_fclose(p_pFile, __FILE__, __LINE__));
}


int kpadd_close(int p_iFileDesc, const char *p_pszSrcFile, int p_iSrcLine)
{
int retv = -1;

    try
    {
        retv = close(p_iFileDesc);

        kpadd_fclose_chkin(NULL, p_iFileDesc, 0, p_pszSrcFile, p_iSrcLine);
    }
    KP_CATCH_ALL; 

return(retv);
}


BOOL kpadd_CloseHandle(
    HANDLE
#ifdef __WIN32__
        p_hFile
#endif
    , const char *
#ifdef __WIN32__
        p_pszSrcFile
#endif
    , int
#ifdef __WIN32__
        p_iSrcLine
#endif
    )
{
BOOL retv = False;

    try
    {
#ifndef __WIN32__
        KP_ASSERT(false, E_NOTIMPL, null);
#else
        retv = CloseHandle(p_hFile);

        kpadd_fclose_chkin(NULL, NO_FILE_DESC, p_hFile, p_pszSrcFile, p_iSrcLine);
#endif
    }
    KP_CATCH_ALL;

return(retv);
}


void kpadd_fclose_chkin(const FILE *p_pFile, int p_iFileDesc, HANDLE p_hFile,
    const char *p_pszSrcFile, int p_iSrcLine)
{
    try
    {
        KP_ASSERT(KpFileDescListPtr, E_POINTER, null);

uchar str_buf[KP_MAX_FILE_LIN_LEN + 1];
        sprintf((char *)str_buf,
#ifdef _WIN64
            ".... kpstdio: kpadd_fclose_chkin(%llx, %d, %llx); file: %s line: %d\n",
#else
            ".... kpstdio: kpadd_fclose_chkin(%lx, %d, %lx); file: %s line: %d\n",
#endif
            (unsigned long
#ifdef _WIN64
                long
#endif
                    )p_pFile,
            p_iFileDesc,
            (unsigned long
#ifdef _WIN64
                long
#endif
                    )p_hFile, p_pszSrcFile, p_iSrcLine);

#ifdef KPSTDIO_FULL_LOG
        KpFileDescListPtr->PutLogMessage(p_pFile, "Closed");
#endif
        KpFileDescListPtr->DelFile(p_pFile, p_iFileDesc, p_hFile);

#ifdef Debug
//      cout << endl << str_buf;
        puts("\n"); puts((const char *)str_buf);

        KpError.PutLogMessage(str_buf);
//      KpError.StackDump();
#endif
    }
    KP_CATCH_ALL;
}


// -----------------------------------------
// KpFileDesc

void KpFileDesc::InitMembers(void)
{
#ifdef Debug
#ifdef _WIN64
printf(".... kpstdio: KpFileDesc::InitMembers(%llx)\n", (unsigned long long)this);
#else
printf(".... kpstdio: KpFileDesc::InitMembers(%lx)\n", (unsigned long)this);
#endif
#endif

    m_pFile = NULL;
    m_iFileDesc = NO_FILE_DESC;
    m_hFile = 0;

    m_pszFileName[0] = Nul;
    m_iFlags = 0;

#ifdef KPSTDIO_FULL_LOG
    m_pszLogFileName[0] = Nul;
#endif

    m_iCurLine = 0;
    m_iCurLpos = 0;
}


KpFileDesc::KpFileDesc(const uchar *p_pszFileName, int p_iFlags,
    /* const */ FILE *p_pFile, int p_iFileDesc, HANDLE p_hFile)
{
    InitMembers();

    // ------
    KP_ASSERT((p_pFile != NULL)  || (p_iFileDesc != NO_FILE_DESC) || (p_hFile != 0),
        E_INVALIDARG, null);
    KP_ASSERT(p_pszFileName, E_INVALIDARG, null);

    m_pFile = p_pFile;
    m_iFileDesc = p_iFileDesc;
    m_hFile = p_hFile;

    // -------
    if (m_pFile)
    {
    int fd = fileno(m_pFile);
        if (m_iFileDesc == NO_FILE_DESC) m_iFileDesc = fd;
        KP_ASSERTW0(m_iFileDesc == fd, E_INVALIDARG, null);
    }

#ifdef __WIN32__
    if (m_iFileDesc != NO_FILE_DESC)
    {
    HANDLE fh = (HANDLE)_get_osfhandle(m_iFileDesc);
        if (m_hFile == 0) m_hFile = fh;
        KP_ASSERTW0(m_hFile == fh, E_INVALIDARG, null);
    }
#endif

    // ------
    KP_ASSERT(strlen(p_pszFileName) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null);
    strcpy(m_pszFileName, p_pszFileName);

    strlwr(m_pszFileName);

    // ------
    m_iFlags = p_iFlags;

    // ------
#ifdef KPSTDIO_FULL_LOG
uchar disk[KP_MAX_FNAME_LEN + 1];
uchar path[KP_MAX_FNAME_LEN + 1];
uchar fname[KP_MAX_FNAME_LEN + 1];
uchar ftype[KP_MAX_FNAME_LEN + 1];
    KpStdIo::TvFnameSplit(disk, path, fname, ftype, m_pszFileName);

    KP_ASSERT(strlen(fname) + 1 + strlen(ftype) + strlen(KPTRC_LOG_SUFF) + strlen(KP_LOG_EXT) <=
        KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null);
    strcpy(m_pszLogFileName, fname);
    strcat(m_pszLogFileName, ".");
    strcat(m_pszLogFileName, ftype);
    strcat(m_pszLogFileName, KPTRC_LOG_SUFF);
    strcat(m_pszLogFileName, KP_LOG_EXT);

    remove((const char *)m_pszLogFileName);
#endif
}


// -----------------------------------------
void KpFileDesc::PullData(const KpFileDesc *p_pDescObj)
{
    KP_ASSERT(p_pDescObj, E_INVALIDARG, null);

    m_pFile = p_pDescObj->m_pFile;
    strcpy(m_pszFileName, p_pDescObj->m_pszFileName);
#ifdef KPSTDIO_FULL_LOG
    strcpy(m_pszLogFileName, p_pDescObj->m_pszLogFileName);
#endif
}


// -----------------------------------------
#ifdef KPSTDIO_FULL_LOG
void KpFileDesc::PutLogMessage(const uchar *p_pszFmt, va_list p_Args)
{
uchar *out_str = null;
    KP_NEWA(out_str, uchar, KP_MAX_FILE_LIN_LEN + strlen(p_pszFmt) * 10 + 1);
    vsprintf((char *)out_str, (const char *)p_pszFmt, p_Args);
    strcat(out_str, "\n");

FILE *log_file = fopen((const char *)m_pszLogFileName, "a");
    KP_ASSERT(log_file != NULL, KP_E_DIR_ERROR, m_pszLogFileName);

    fputs((const char *)out_str, log_file);

    fclose(log_file);

    KP_DELETEA(out_str);
}
#endif



// -----------------------------------------
// KpFileDescList

KpFileDescList *KpFileDescListPtr = NULL;

KpFileDescList::KpFileDescList(void)
{
#ifdef Debug
    KpError.PutLogMessage("KpFileDescList::KpFileDescList()");
#endif
    m_pFileList = NULL;
}


KpFileDescList::~KpFileDescList()
{
// ----------------
#ifdef Debug
    KpError.PutLogMessage("KpFileDescList::~KpFileDescList()");
#endif

KpTreeEntry<KpFileDesc> *cur_entry = m_pFileList;
    while (cur_entry != NULL)
    {
KpFileDesc *desc_ptr = cur_entry->GetValue();
        KP_ASSERT(desc_ptr != NULL, E_POINTER, null);
#ifdef Debug
        KpError.PutLogMessage("KpFileDescList::~KpFileDescList(): deleting object: %s", desc_ptr->m_pszFileName);
#endif
        desc_ptr->LogLastCh();

        cur_entry = cur_entry->GetFirstChild();
    }

// ----------------
    KP_DELETE(m_pFileList);
}


// -----------------------------------------
KpFileDesc *KpFileDescList::KpFileDescFactory(const uchar *p_pszFileName, int p_iFlags,
    /* const */ FILE *p_pFile, int p_iFileDesc, HANDLE p_hFile)
{
#ifdef Debug
    KpError.PutLogMessage("KpFileDescList::KpFileDescFactory()");
#endif

KpFileDesc *desc_obj_ptr = NULL;
    KP_NEW(desc_obj_ptr, KpFileDesc(p_pszFileName, p_iFlags,
        p_pFile, p_iFileDesc, p_hFile));

return(desc_obj_ptr);
}


// -----------------------------------------
void KpFileDescList::RegNewFile(const uchar *p_pszFileName, int p_iFlags,
    /* const */ FILE *p_pFile, int p_iFileDesc, HANDLE p_hFile)
{
HRESULT retc = S_OK;
KpFileDesc *desc_obj_ptr = NULL;
    if(p_pFile) desc_obj_ptr = FindFile(p_pFile);
    if(p_iFileDesc != NO_FILE_DESC) desc_obj_ptr = FindFileByDesc(p_iFileDesc);
    if(p_hFile) desc_obj_ptr = FindFileByHandle(p_hFile);
    KP_ASSERTW(desc_obj_ptr == NULL, KP_E_DOUBLE_CALL, p_pszFileName);
    if(FAILED(retc))
    {
        KpError.PutLogMessage(
#ifdef _WIN64
            "KpFileDescList::RegNewFile(): failas jau yra: %llx %d %llx %s",
#else
            "KpFileDescList::RegNewFile(): failas jau yra: %lx %d %lx %s",
#endif
            (unsigned long
#ifdef _WIN64
                long
#endif
                    )p_pFile, p_iFileDesc,
            (unsigned long
#ifdef _WIN64
                long
#endif
                    )p_hFile, desc_obj_ptr->m_pszFileName);
        DelFile(p_pFile, p_iFileDesc, p_hFile);
    }

    desc_obj_ptr = KpFileDescFactory(p_pszFileName, p_iFlags, p_pFile, p_iFileDesc, p_hFile);

KpTreeEntry<KpFileDesc> *new_node = NULL;
    KP_NEW(new_node, KpTreeEntry<KpFileDesc>(desc_obj_ptr, NULL));

    if (m_pFileList == NULL) m_pFileList = new_node;
    else m_pFileList->PutToEnd(new_node);
    new_node = NULL;
}


// -----------------------------------------
void KpFileDescList::DelFile(const FILE *p_pFile, int p_iFileDesc, HANDLE p_hFile)
{
uchar out_str[MAX_LONG_HEX_DIGITS + 10];
    sprintf((char *)out_str,
#ifdef _WIN64
        "%llx", (unsigned long long)p_pFile);
#else
        "%lx", (unsigned long)p_pFile);
#endif

HRESULT retc = S_OK;
KpTreeEntry<KpFileDesc> **node_ptr_ptr = NULL;
KpFileDesc *desc_obj_ptr = NULL;
    if(p_pFile) desc_obj_ptr = FindFile(p_pFile, &node_ptr_ptr);
    if(p_iFileDesc != NO_FILE_DESC) desc_obj_ptr = FindFileByDesc(p_iFileDesc, &node_ptr_ptr);
    if(p_hFile) desc_obj_ptr = FindFileByHandle(p_hFile, &node_ptr_ptr);
    KP_ASSERTW(desc_obj_ptr != NULL, KP_E_NO_FILE, out_str);
    if (SUCCEEDED(retc))
    {
        desc_obj_ptr->LogLastCh();

        KP_ASSERT(node_ptr_ptr != NULL, KP_E_NO_FILE, out_str);
        KP_ASSERT(*node_ptr_ptr != NULL, KP_E_NO_FILE, out_str);

        KpTreeEntry<KpFileDesc>::DeleteKpTreeBros(node_ptr_ptr);
    }
}


// -----------------------------------------
KpFileDesc *KpFileDescList::FindFile(const FILE *p_pFile, KpTreeEntry<KpFileDesc> ***pppNodePtr)
{
KpFileDesc *desc_obj_ptr = NULL;

    if (pppNodePtr != NULL) *pppNodePtr = &m_pFileList;
KpTreeEntry<KpFileDesc> *cur_entry = m_pFileList;

    while (cur_entry != NULL)
    {
KpFileDesc *desc_ptr = cur_entry->GetValue();
        KP_ASSERT(desc_ptr != NULL, E_POINTER, null);
        if (desc_ptr->m_pFile == p_pFile)
        {
            desc_obj_ptr = desc_ptr; 
            break;
        }

        if (pppNodePtr != NULL) *pppNodePtr = &(cur_entry->m_pFirstChild);
        cur_entry = cur_entry->GetFirstChild();
    }

return(desc_obj_ptr);
}


KpFileDesc *KpFileDescList::FindFileByDesc(int p_iFileDesc, KpTreeEntry<KpFileDesc> ***pppNodePtr)
{
KpFileDesc *desc_obj_ptr = NULL;

    if (pppNodePtr != NULL) *pppNodePtr = &m_pFileList;
KpTreeEntry<KpFileDesc> *cur_entry = m_pFileList;

    while (cur_entry != NULL)
    {
KpFileDesc *desc_ptr = cur_entry->GetValue();
        KP_ASSERT(desc_ptr != NULL, E_POINTER, null);
        if (desc_ptr->m_iFileDesc == p_iFileDesc)
        {
            desc_obj_ptr = desc_ptr; 
            break;
        }

        if (pppNodePtr != NULL) *pppNodePtr = &(cur_entry->m_pFirstChild);
        cur_entry = cur_entry->GetFirstChild();
    }

return(desc_obj_ptr);
}


KpFileDesc *KpFileDescList::FindFileByHandle(HANDLE p_hFile, KpTreeEntry<KpFileDesc> ***pppNodePtr)
{
KpFileDesc *desc_obj_ptr = NULL;

    if (pppNodePtr != NULL) *pppNodePtr = &m_pFileList;
KpTreeEntry<KpFileDesc> *cur_entry = m_pFileList;

    while (cur_entry != NULL)
    {
KpFileDesc *desc_ptr = cur_entry->GetValue();
        KP_ASSERT(desc_ptr != NULL, E_POINTER, null);
        if (desc_ptr->m_hFile == p_hFile)
        {
            desc_obj_ptr = desc_ptr; 
            break;
        }

        if (pppNodePtr != NULL) *pppNodePtr = &(cur_entry->m_pFirstChild);
        cur_entry = cur_entry->GetFirstChild();
    }

return(desc_obj_ptr);
}


// -----------------------------------------
void KpFileDescList::UpdateFile(const KpFileDesc *p_pDescObj)
{
HRESULT retc = S_OK;

    KP_ASSERT(p_pDescObj, E_INVALIDARG, null);

KpFileDesc *desc_obj_ptr = NULL;
KpTreeEntry<KpFileDesc> *cur_entry = m_pFileList;
    while (cur_entry != NULL)
    {
        desc_obj_ptr = cur_entry->GetValue();
        KP_ASSERT(desc_obj_ptr != NULL, E_POINTER, null);

        if (desc_obj_ptr->m_pFile == p_pDescObj->m_pFile)
        {
            // radom – deskriptorių updeitinam, o desc_obj_ptr paliekam nustatytą
            desc_obj_ptr->PullData(p_pDescObj);
            break;
        }
        else
        {
            // neradom – valom desc_obj_ptr
            desc_obj_ptr = NULL;
        }

        cur_entry = cur_entry->GetFirstChild();
    }

    KP_ASSERTW(desc_obj_ptr != NULL, KP_E_NO_FILE, null); // neradom
}


// -----------------------------------------
#ifdef KPSTDIO_FULL_LOG
void KpFileDescList::PutLogMessage(const FILE *p_pFile, const uchar *p_pszFmt, va_list p_Args)
{
HRESULT retc = S_OK;
uchar out_str[MAX_LONG_HEX_DIGITS + 10];
    sprintf((char *)out_str, "%lx", p_pFile);
KpFileDesc *desc_obj_ptr = FindFile(p_pFile);
    KP_ASSERTW(desc_obj_ptr != NULL, KP_E_NO_FILE, out_str);
    if (FAILED(retc)) KpError.PutLogMessage(p_pszFmt, p_Args);
    else
        desc_obj_ptr->PutLogMessage(p_pszFmt, p_Args);
}
#endif
