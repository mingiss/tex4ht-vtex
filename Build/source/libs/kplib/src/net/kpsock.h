/*
 * kpsock.h
 *
 *    Win32 sockets
 *
 * 2013-12-16  mp  initial creation
 * 2016-09-06  mp  migration of kpsgrp from tv to kplib
 *
 *  TODO:
 *      p_bThrowError parametrus kelt į KpSocket metodą m_bThrowErrors
 */


#ifndef kpsock_included
#define kpsock_included


//---------------------
#ifndef __WIN32__
typedef struct in_addr {
  union {
    struct {
      u_char s_b1,s_b2,s_b3,s_b4;
    } S_un_b;
    struct {
      u_short s_w1,s_w2;
    } S_un_w;
    u_long S_addr;
  } S_un;
} IN_ADDR, *PIN_ADDR, FAR *LPIN_ADDR;

#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define SOCK_RAW 3
#define SOCK_RDM 4
#define SOCK_SEQPACKET 5

typedef UINT_PTR SOCKET;
#endif

#define KPSOCK_BLOCK_TIMEOUT 5

#define KP_IPADDR_LOCAL_HOST ((const uchar *)"127.0.0.1")
#define KP_INADDR_LOOPBACK  0x0100007f  // sisteminis  atbulas:
                                        //      INADDR_LOOPBACK 0x7f000001

#define KP_IPADDR_BROADCAST ((const uchar *)"255.255.255.255")

#define KP_MIN_USER_PORT 10000
#define KP_UDP_PORT_OFFSET 100


//---------------------
typedef enum
{
    NO_PROT,

    HTTP_PROT,
    FTP_PROT,
    HTTPS_PROT,
    SMTP_PROT,

    NUM_OF_PROTS

} Protocols;

#define NUM_OF_PROTS_2 NUM_OF_PROTS


//---------------------
typedef struct
{
    uchar m_lpszServerName[KP_MAX_FNAME_LEN + 1]; // remote IP address or
                                                  //    server name

    IN_ADDR m_Addr;     // resolved remote IP address
    Protocols m_iProtocol;
    int m_iPort;
    uchar m_lpszFileName[KP_MAX_FNAME_LEN + 1]; // remote file name with
                                                //      possible query string
    uchar m_lpszServerNameUnres[KP_MAX_FNAME_LEN + 1]; // remote IP address as
                            // got from the message header, before Resolve()
} PackedUrl;


typedef struct
{
    uchar m_lpszVarName[KP_KWD_LEN + 1];
    uchar m_lpszVarData[KP_MAX_FILE_LIN_LEN + 1];
}
PostVarRec;


//---------------------
// HTTP pranešimo (requesto/atsakymo su/be papildomų duomenų gabalų) tipai
typedef enum
{
    HTTP_MSG_TYPE_UNKNOWN,  // 0

// request'ai:
    HTTP_REQUEST_UNKNOWN,   // 1    // HTTP_GET_REQUEST arba HTTP_POST_REQUEST
    HTTP_GET_REQUEST,       // 2
    HTTP_POST_REQUEST,      // 3

// post duomenys:
    HTTP_POST_DATA_SEGM,    // 4    // paprastas duomenų gabaliukas
    HTTP_POST_SUBDATA_SEGM, // 5    // POST duomenų gabalas, kurio viduje yra
        //      kiti gabaliukai,
        // pradeda naują rekursyvinę POST_DATA_CHUNK seka su nauja boundary=

// atsakymas:
    HTTP_REPLY,             // 6  // atsakymas i requestą

    NUM_OF_HTTP_MSG_TYPES   // 7

} HttpMsgTypes; // taip pat ir headerių tipai

#define NUM_OF_HTTP_MSG_TYPES_1 NUM_OF_HTTP_MSG_TYPES


//---------------------
// HTTP header tags
typedef enum
{
    KPSOCK_HDTAG_None = (-1),

    KPSOCK_HDTAG_Date,
    KPSOCK_HDTAG_Server,
    KPSOCK_HDTAG_SetCookie,
    KPSOCK_HDTAG_LastModified,
    KPSOCK_HDTAG_XPoweredBy,
    KPSOCK_HDTAG_ETag,
    KPSOCK_HDTAG_AcceptRanges,
    KPSOCK_HDTAG_ContentLength,
    KPSOCK_HDTAG_TransferEncoding,
    KPSOCK_HDTAG_Connection,
    KPSOCK_HDTAG_KeepAlive,
    KPSOCK_HDTAG_ContentType,
    KPSOCK_HDTAG_ContentEncoding,
    KPSOCK_HDTAG_Host,
    KPSOCK_HDTAG_UserAgent,
    KPSOCK_HDTAG_Accept,
    KPSOCK_HDTAG_AcceptLanguage,
    KPSOCK_HDTAG_AcceptEncoding,
    KPSOCK_HDTAG_AcceptCharset,
    KPSOCK_HDTAG_Pragma,
    KPSOCK_HDTAG_CacheControl,
    KPSOCK_HDTAG_Referer,
    KPSOCK_HDTAG_IfModifiedSince,
    KPSOCK_HDTAG_IfNoneMatch,
    KPSOCK_HDTAG_ContentDisposition,
    KPSOCK_HDTAG_ContentTransferEncoding,
    KPSOCK_HDTAG_TE,
    KPSOCK_HDTAG_UA_CPU,
    KPSOCK_HDTAG_Location,
    KPSOCK_HDTAG_AcrobatVersion,
    KPSOCK_HDTAG_Expires,
    KPSOCK_HDTAG_ContentDescription,
    KPSOCK_HDTAG_Vary,
    KPSOCK_HDTAG_X_UA_Compatible,
    KPSOCK_HDTAG_X_Environment,
    KPSOCK_HDTAG_X_Origin_Server,
    KPSOCK_HDTAG_Link,
    KPSOCK_HDTAG_X_Robots_Tag,
    KPSOCK_HDTAG_P3P_Tag,
    KPSOCK_HDTAG_X_TransKey,
    KPSOCK_HDTAG_X_RE_Ref,
    KPSOCK_HDTAG_X_RE_PROXY_CMP,
    KPSOCK_HDTAG_X_Cnection,
    KPSOCK_HDTAG_X_SmartBan_URL,
    KPSOCK_HDTAG_X_SmartBan_Host,
    KPSOCK_HDTAG_X_Varnish,
    KPSOCK_HDTAG_Age,
    KPSOCK_HDTAG_Via,
    KPSOCK_HDTAG_X_Varnish_Hostname,
    KPSOCK_HDTAG_X_Varnish_Cache,
    KPSOCK_HDTAG_X_Highwire_SessionId,
    KPSOCK_HDTAG_X_Highwire_RequestId,
    KPSOCK_HDTAG_X_Firenze_Processing_Time,
    KPSOCK_HDTAG_X_Firenze_Processing_Times,
    KPSOCK_HDTAG_X_HighWire_Preview_Mode,
    KPSOCK_HDTAG_X_Content_Type_Options,
    KPSOCK_HDTAG_X_Frame_Options,
    KPSOCK_HDTAG_X_XSS_Protection,
    KPSOCK_HDTAG_Alternate_Protocol,

    KPSOCK_NUM_OF_HDTAGS

} KpSockHdTag;

#define KPSOCK_NUM_OF_HDTAGS_4 KPSOCK_NUM_OF_HDTAGS


//---------------------
typedef enum
{
    NORMAL_HTTP_TR_MODE,    // visi duomenys vienu gabalu

    HTTP_TR_CHUNK_MODE,     // tuščia eilutė prieš kiekvieną gabaliuką
        // po to - viena eilutė - segmento ilgis - šešioliktainis skaičius
        // pabaiga - segmentas su ilgiu 0

    NUM_OF_HTTP_TR_MODES

} HttpTransferModes;

#define NUM_OF_HTTP_TR_MODES_1 NUM_OF_HTTP_TR_MODES


//---------------------
#define HTTP_PORT 80
#define HTTP_PORT_ALT 8080
#define HTTPS_PORT 443
#define FTP_PORT 21
#define SMTP_PORT 25

#define HTTP_GET_REQUEST_CMD (const uchar *)"GET"
#define HTTP_POST_REQUEST_CMD (const uchar *)"POST"

#define KPSOCK_URL_HTTP_PREFIX ((const uchar *)"http://")
#define KPSOCK_URL_FTP_PREFIX ((const uchar *)"ftp://")

#define KPSOCK_HTTP_HDR_PREFIX "HTTP/1.1"

#define KPSOCK_FAKED_USER_AGENT ((const uchar *)"Mozilla/5.0 (Windows; U; Windows NT 5.0; en-US; rv:1.8.0.6) Gecko/20060728 Firefox/1.5.0.6")

//---------------------
#define HTTP_GET_REQ_TPL_MAIN ((const uchar *)\
    "%s %s HTTP/1.1\r\n" \
    "Host: %s%s\r\n"          /* 127.0.0.1:80 */ \
    "User-Agent: %s\r\n"       /* Mozilla/5.0 (Windows; U; Win98; en-US; rv:1.4) Gecko/20030624 Netscape/7.1 (ax) */ \
    "Accept: */*\r\n" \
    "Accept-Language: lt\r\n"  /* en-us,en;q=0.5 */ \
    "Accept-Encoding: identity\r\n" /* "Accept-Encoding: deflate\r\n" */ /* "Accept-Encoding: none\r\n" */ /* gzip,deflate */ \
    "Accept-Charset: utf-8\r\n"  /* ISO-8859-13 */ /* ISO-8859-1,utf-8;q=0.7,*;q=0.7 */ \
    "Keep-Alive: 300\r\n" \
    "Connection: keep-alive\r\n" \
    "\r\n")

#define HTTP_GET_REQ_TPL_TEXT ((const uchar *)\
    "%s %s HTTP/1.1\r\n" \
    "Host: %s%s\r\n"          /* 127.0.0.1:80 */ \
    "User-Agent: %s\r\n"       /* Mozilla/5.0 (Windows; U; Win98; en-US; rv:1.4) Gecko/20030624 Netscape/7.1 (ax) */ \
    "Accept: text/*\r\n" \
    "Accept-Language: lt\r\n"  /* en-us,en;q=0.5 */ \
    "Accept-Encoding: identity\r\n" /* "Accept-Encoding: deflate\r\n" */ /* "Accept-Encoding: none\r\n" */ /* gzip,deflate */ \
    "Accept-Charset: utf-8\r\n"  /* ISO-8859-13 */ /* ISO-8859-1,utf-8;q=0.7,*;q=0.7 */ \
    "Keep-Alive: 300\r\n" \
    "Connection: keep-alive\r\n" \
    "\r\n")

#define HTTP_GET_REQ_TPL_BIN ((const uchar *)\
    "%s %s HTTP/1.1\r\n" \
    "Host: %s%s\r\n"          /* 127.0.0.1:80 */ \
    "User-Agent: %s\r\n"       /* Mozilla/5.0 (Windows; U; Win98; en-US; rv:1.4) Gecko/20030624 Netscape/7.1 (ax) */ \
    "Accept: */*\r\n" \
/*  "Accept-Language: lt\r\n" */ /* en-us,en;q=0.5 */ \
    "Accept-Encoding: identity\r\n" /* "Accept-Encoding: deflate\r\n" */ /* "Accept-Encoding: none\r\n" */ /* gzip,deflate */ \
/*  "Accept-Charset: utf-8\r\n" */  /* ISO-8859-13 */ /* ISO-8859-1,utf-8;q=0.7,*;q=0.7 */ \
    "Keep-Alive: 300\r\n" \
    "Connection: keep-alive\r\n" \
    "\r\n")

#define HTTP_POST_REQ_TPL ((const uchar *) \
    "%s %s HTTP/1.1\r\n"       /* POST /diag.php HTTP/1.1 */ \
    "Host: %s%s\r\n"          /* Host: www.tev.lt:80 */ \
    "User-Agent: %s\r\n"       /* User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1) */ \
    "Accept: */*\r\n" \
    "Content-Length: %ld\r\n" \
    "Cache-Control: no-cache\r\n" \
    "Accept-Language: lt\r\n" \
    "UA-CPU: x86\r\n" \
    "Accept-Encoding: none\r\n" /* Accept-Encoding: gzip, deflate */ \
    "Connection: Keep-Alive\r\n")

// Tado Acrobato POST pranesimu kepure
#define HTTP_POST_REQ_TPL_ACRO ((unsigned char *) \
    "%s %s HTTP/1.1\r\n"       /* POST / HTTP/1.1 */ \
    "Host: %s%s\r\n"          /* 127.0.0.1:80 */ \
    "User-Agent: %s\r\n"       /* AcroForms */ \
    "Accept: */*\r\n" \
    "Content-Type: application/x-www-form-urlencoded\r\n" \
    "Content-Length: %ld\r\n" \
    "Cache-Control: no-cache\r\n" \
    "\r\n")

#define HTTP_POST_REQ_TAIL_TPL ((const uchar *) \
    "Referer: http://%s%s\r\n" /* Referer: http://www.tev.lt/diag.php */ \
    "Content-Type: multipart/form-data; boundary=%s\r\n" /* Content-Type: multipart/form-data; boundary=----------------------tv689907.tmp */ \
    "\r\n")

#define HTTP_POST_HDR_TPL ((const uchar *)\
    "Content-Type: multipart/form-data; boundary=%s" /* ---------------------------287452692419072 */ \
    "Content-Length: %d"       /* 242 */ \
    "\r\n")

#define HTTP_DATA_HDR_TPL ((const uchar *)\
    "HTTP/%1.1f %d %s\r\n"     /* 1.1 200 OK */ \
    "Date: %s\r\n"             /* Mon, 19 Jul 2004 06:43:58 GMT */ \
    "Server: %s\r\n"           /* Apache/1.3.26 (Unix) mod_gzip/1.3.19.1a mod_throttle/3.1.2 */ \
    "Last-Modified: %s\r\n"    /* Thu, 15 Jul 2004 16:29:04 GMT */ \
    "ETag: \"%s\"\r\n"         /* 23-40f6b0d0 */ \
    "Accept-Ranges: %s\r\n"    /* bytes */ \
    "Content-Length: %d\r\n"   /* 35 */ \
    "Connection: close\r\n" \
    "Content-Type: %s\r\n"     /* text/plain */ \
    "\r\n")

#define HTTP_CONT_HDR_TPL ((const uchar *)\
    "HTTP/%1.1f %d %s\r\n"     /* 1.1 100 Continue */ \
    "Date: %s\r\n"             /* Mon, 19 Jul 2004 06:43:58 GMT */ \
    "Server: %s\r\n"           /* Apache/1.3.26 (Unix) mod_gzip/1.3.19.1a mod_throttle/3.1.2 */ \
    "Last-Modified: %s\r\n"    /* Thu, 15 Jul 2004 16:29:04 GMT */ \
    "ETag: \"%s\"\r\n"         /* 23-40f6b0d0 */ \
    "Keep-Alive: %d\r\n"       /* 300 */ \
    "Connection: keep-alive\r\n" \
    "\r\n")

#define HTTP_NOTIF_HDR_TPL ((const uchar *)\
    "HTTP/%1.1f %d %s\r\n"     /* 1.1 404 File not found */ \
    "Date: %s\r\n"             /* Mon, 19 Jul 2004 06:43:58 GMT */ \
    "Server: %s\r\n"           /* Apache/1.3.26 (Unix) mod_gzip/1.3.19.1a mod_throttle/3.1.2 */ \
    "Last-Modified: %s\r\n"    /* Thu, 15 Jul 2004 16:29:04 GMT */ \
    "ETag: \"%s\"\r\n"         /* 23-40f6b0d0 */ \
    "Connection: close\r\n" \
    "\r\n")

#define MIN_HTTP_HDR_LEN (min(min(strlen(HTTP_DATA_HDR_TPL), strlen(HTTP_CONT_HDR_TPL)), strlen(HTTP_NOTIF_HDR_TPL)))

#define MAX_HTTP_HDR_LEN ((100L * 1024) + 1)

#define VAR_POST_BUF_LEN 4000 // max. GetPostVars() duomenų kiekis

#define MIN_HTTP_POST_HDR_LEN (strlen(HTTP_POST_HDR_TPL))

#define KPSOCK_RCVBUF_CHUNK_SIZE KP_MAX_FILE_LIN_LEN

// TODO: sinchronizuoti su kpsock.py KpHttpResponse.m_status_text
//          ir KpErrorProcClass::FormatErrorMessageHTTP()
#define HTTP_ANSW_OK 200                // 200 OK
#define HTTP_ANSW_MOVED 301             // 301 Moved Permanently
#define HTTP_ANSW_FOUND 302             // 302 Found
#define HTTP_ANSW_TEMP_MOVED 302        // 302 Moved Temporarily
#define HTTP_ANSW_OTHER 303             // 303 See Other
#define HTTP_ANSW_TEMP_REDIR 307        // 307 Temporary Redirect
#define HTTP_ANSW_FILE_NOT_FOUND 404
#define HTTP_ANSW_CONTINUE 100
#define HTTP_ANSW_CONFLICT 409
#define HTTP_ANSW_GATEWAY 502

// TODO: contentus migruoti iš content_types.py
#define KPSOCK_DEF_CONT_TYPE ((const uchar *)"text/html")

#define KPSOCK_POST_MULTIPART_TAG ((const uchar *)"multipart/form-data;")
#define KPSOCK_POST_BOUNDARY_TAG ((const uchar *)"boundary=")
#define KPSOCK_POST_FORM_TAG ((const uchar *)"form-data;")
#define KPSOCK_POST_CTRL_NAME_TAG ((const uchar *)"name=")
#define KPSOCK_POST_FILE_TAG ((const uchar *)"file;")
#define KPSOCK_POST_ATT_TAG ((const uchar *)"attachment;")
#define KPSOCK_POST_FNAME_TAG ((const uchar *)"filename=")
#define KPSOCK_POST_BIN_TAG ((const uchar *)"binary")


//--------------------- asinchroninis porto klausymas
class KpSocket;

// parametrai RecvFromProc()
typedef struct{
    KpSocket *m_This;
    unsigned char *m_pBuf;
    long *m_plBufLen;
    bool m_bThrowError;
    DWORD m_iCallersThreadId;
} RecvFromProcPars;

// KpSocket::RecvFromAsynch() threado procedura
/* extern */ DWORD WINAPI RecvFromProc(
    LPVOID p_lpParameter // rodyklė į RecvFromProcPars
    );

//---------------------
class KpSocket
{
    SOCKET m_hSocket; // main socket
    SOCKET m_hAccSock;   // accepted socked for server applications

public:
    static const uchar *ProtocolNames[NUM_OF_PROTS];
        // URI prefixes actually
    static int DefPorts[NUM_OF_PROTS]; // default ports

    static const uchar *KpsockMsgTypes[NUM_OF_HTTP_MSG_TYPES];
    static const uchar *KpsockTagNames[KPSOCK_NUM_OF_HDTAGS+1]; // gale NULL
    static const bool KpsockTagOccurences[KPSOCK_NUM_OF_HDTAGS][NUM_OF_HTTP_MSG_TYPES];

    static const uchar *TransferModeNames[NUM_OF_HTTP_TR_MODES];

// priimamo paketo atributai, užpildo ScanHdr()
    HttpMsgTypes m_iMsgType;
    int m_iRetCode;             // 200 OK etc.

    uchar m_lpszRetMsg[KP_MAX_FILE_LIN_LEN /* MAX_HTTP_HDR_LEN */ + 1];
        // klaidos pranešimas ištrauktas iš HTTP headerio, tekstas einantis po
        //      200, 404

    uchar m_lpszLocation[KP_MAX_FILE_LIN_LEN + 1]; // Location:
        // redirectintiems linkams
    long m_lContLen;            // Content-Length:
    HttpTransferModes m_iTrMode;   // Transfer-Encoding:
    uchar m_lpszBoundary[KP_MAX_FILE_LIN_LEN /* MAX_HTTP_HDR_LEN */ + 2 + 1];
        // riba tarp POST duomenų segmentų
    uchar m_lpszEndBoundary[KP_MAX_FILE_LIN_LEN /* MAX_HTTP_HDR_LEN */ + 4 + 1];
        // paskutinio POST duomenų segmento galas
    uchar m_lpszCtrlName[KP_KWD_LEN + 1];

    uchar *m_lpszHdrBuf; // [MAX_HTTP_HDR_LEN + 1];

    PackedUrl m_PackedUrl;

    int m_iLocalPort;

    long m_lRestChunkLength; // RcvHttpMsg() dabar skaitomo chunk likęs ilgis,
        // jei netilpo į pBuf[]; reikia iškvietinėti RcvHttpRest(), kol
        // perskaitytas ilgis bus 0L
//  long m_lNextChunkLength; // sekančio neperskaityto chunk ilgis, kai
        // pasibaigia RcvHttpMsg() buferis, tokiu atveju iškvietinėti
        // RcvHttpRest(), kol perskaitytas ilgis bus 0L

    uchar *m_lpszChunkPos;   // GetChunkLength()/GetChunk() skaitymo pozicija
        // buferyje m_lpszHdrBuf[]
    long m_lChunkRest; // GetChunkLength()/GetChunk() baitų skaičius nuo
        // m_lpszChunkPos iki paskutiniu GetByte() perskaitytų baitų masyvo
        // skaičiaus buferyje m_lpszHdrBuf[]

// -------------------
    KpSocket(int p_iSockType = SOCK_STREAM); // creates m_hSocket
        // p_iSockType gali būti SOCK_STREAM arba SOCK_DGRAM
    ~KpSocket();

// -------------------
    static HRESULT TestIP(const uchar *p_lpszIpAddr);
        // grąžina E_INVALIDARG jei blogas formatas, pranešimų neišveda

// -------------------
// client routines
    HRESULT Resolve(const uchar *p_lpszUrl,
        bool p_bThrowError = False  // False - doesn't throw errors,
                            // error code will be returned as a result instead
        );
        // saves resolved server address, protocol, port and file name to
        //      m_PackedUrl

    HRESULT Connect(bool p_bThrowError = False);
        // connects m_hSocket to m_lAddr

    static void PutMsgFirewall(const uchar *p_lpszMsgFmt);
        // message to the user about possibly blocking firewall

// server routines
    HRESULT Bind(int p_iPort, unsigned long p_lAddr,
                                        bool p_bThrowError = False);
        // binds m_hSocket to localhost:p_iPort for listening
        // p_lAddr: ADDR_ANY, INADDR_LOOPBACK
    HRESULT Listen(bool p_bThrowError = False);
        // switches m_hSocket to listening status, waits for incoming messages
    HRESULT Accept(bool p_bThrowError = False);
        // accepts incomming through m_hSocket message to the
        // new socket m_hAccSock; fills m_PackedUrl

// ---------------------- lowest level, datagramm broadcast
    HRESULT SendTo(const uchar *p_pBuf, long p_lBufLen,
                                                bool p_bThrowError = False);
        // siunčia adresu m_PackedUrl.m_Addr.S_un.S_addr

    HRESULT RecvFromAsynch(uchar *p_pBuf, long *p_plBufLen,
                                                bool p_bThrowError = False);
        // neblokuojantis, laukia KPSOCK_BLOCK_TIMEOUT sec.
        // paleidžia RecvFromProc atskiram threade
    HRESULT RecvFrom(uchar *p_pBuf, long *p_plBufLen,
                                            bool p_bThrowError = False);
        // *p_plBufLen įeinant turi turėti buferio max ilgį,
        //          išeinant grąžinamas priimtų baitų skaičius
        // m_PackedUrl.m_Addr.S_un.S_addr ir m_PackedUrl.lpszServerName
        //      užpildomas priimto pranešimo siuntėjo adresu –
        //      jeigu reikia dar broadcastinti, m_PackedUrl.m_Addr.S_un.S_addr
        //      vėl turi būti nustatytas į INADDR_BROADCAST

// ---------------------- low level, stream sockets
    HRESULT SendMsg(const uchar *p_pBuf, long p_lBufLen,
                                            bool p_bThrowError = False);
    HRESULT SendStr(const uchar *p_lpszBuf, bool p_bThrowError = False);
    HRESULT SendStr(const char *p_lpszBuf, bool p_bThrowError = False);

    HRESULT ReceiveMsg(uchar *p_pBuf,
            long *p_plRead,     // on entering *p_plRead must be filled with
                                //      length of p_pBuf
            bool p_bSingleMsg,  // True - expected length of message unknown,
                                //      receive only one block as header
            bool p_bThrowError = False);
        

    HRESULT GetChar(uchar *p_pcInChar, bool p_bThrowError = False);
        // actually ReceiveMsg(p_pcInChar, &1, True, p_bThrowError);
        // grąžina KP_E_EOF jei negavo

    HRESULT GetCharD(uchar *p_pcInChar, bool p_bThrowError = False);
        // įvykdo GetChar();
        // dekrementuoja m_lContLen, jei ne 0
        // jei dekrementavus pasiekia 0, duoda KP_E_EOF
        // naudojamas POST duomenų headeriams (HTTP_POST_DATA_SEGM)
        //    ir patiems duomenims

    HRESULT GetLine(uchar *p_lpszStrBuf, int p_iBufLen,
                                        bool p_bThrowError = False);
        // GetCharD() iki eilutės pabaigos

private:
// ------------- methods used for RcvHttpMsg()
    HRESULT GetByte                 // read character through m_lpszHdrBuf[]
    (                               // uses m_lpszChunkPos and m_lChunkRest
        uchar *p_pcInCh,            // character to read
        bool p_bThrowError = False
    );

    HRESULT UnGetByte               // unget character to m_lpszHdrBuf[]
    (                               // uses m_lpszChunkPos and m_lChunkRest
        uchar p_cInCh,              // character to unget
        bool p_bThrowError = False
    );

    HRESULT GetChunk                // get HTTP chunk through m_lpszHdrBuf[]
    (                               // uses m_lpszChunkPos and m_lChunkRest
        long p_lChunkLength,
        uchar **p_ppOutBufPtr,      // pointer of current byte in pBuf
        uchar *p_pBuf,              // output buffer itself
        long p_lBufLen,             // size of pBuf
        bool p_bFullChunk = True,   // False – skaitomas tik gabalas chunk'o
            // nuo einamosios pozicijos, nereikia suvalgyt chunko uodegoje
            // esančių Cr/Lf
        bool p_bThrowError = False
    );

    HRESULT GetChunkLength      // get HTTP chunk length from chunk header
                                //      in current position of m_lpszHdrBuf[]
    (                           // uses m_lpszChunkPos and m_lChunkRest
        long *p_plChunkLength,  // scanned HTTP chunk length
        bool p_bThrowError = False
    );

public:
// ------------------------------ HTTP level
    static bool IsHTTPdataMsg(int p_iHTTP_RetCode);
    static bool IsHTTPcontinueMsg(int p_iHTTP_RetCode);
    static bool IsHTTPerrorMsg(int p_iHTTP_RetCode);

// ------------------------------
    HRESULT SendHttpRequest(
        const uchar *p_lpszRequest,
            // HTTP_GET_REQUEST_CMD/HTTP_POST_REQUEST_CMD ("GET"/"POST")
        const uchar *p_lpszArg = null,
            // failo vardas, jei null – imamas m_PackedUrl.m_lpszFileName
        bool p_bFakeAgent = False, // ar apsimetinėti Mozilla
        bool p_bUsePort = True, // ar nurodyti portą po serverio adreso
        long p_lSimplyPostMsgLen = 0L,
        bool p_bAcroPostMsg = True,
        const uchar *p_lpszPostBoundary = (const uchar *)"",
        const uchar *p_lpszHTTP_Template = HTTP_GET_REQ_TPL_MAIN,
        bool p_bThrowError = False);

    HRESULT ReceiveHdr(HttpMsgTypes p_iMsgType, long *p_plRead,
                                                bool p_bThrowError = False);
        // priima iki tuščios eilutės į m_lpszHdrBuf
        // gale prideda Nul
        // *plRead pradžioj nustatyti nereikia
        // plRead gali būti NULL
        // iMsgType HTTP_MSG_TYPE_UNKNOWN, HTTP_POST_DATA_SEGM arba HTTP_REPLY

    HRESULT ScanHdrFileName(uchar **p_plpszHdrPtrPtr, // ScanHdr() paprogramė
                                            bool p_bThrowError = False);
    HRESULT ScanHdr(
        HttpMsgTypes p_iInitMsgType,    // HTTP_MSG_TYPE_UNKNOWN,
                                        // HTTP_POST_DATA_SEGM arba HTTP_REPLY
        bool p_bThrowError = False);
        // skanuoja m_lpszHdrBuf turinį
        // užpildo memberius:
        //      m_iMsgType, m_iRetCode, m_lContLen, m_iTrMode, m_lpszBoundary,
        //          m_lpszEndBoundary
        //      TODO: užpildyt m_lpszRetMsg
        // jei priimta be klaidų, bet yra neigiamas HTTP atsakymas, klaidos
        //      nemeta bet kokiu atveju (nepriklausomai nuo p_bThrowError),
        //      bet grąžina klaidos kodą KP_E_NEG_ANSW

    HRESULT RcvHdr(HttpMsgTypes p_iInitMsgType, bool p_bThrowError = False);
        // ReceiveHdr() + ScanHdr()
        // jei priimta be klaidų, bet yra neigiamas HTTP atsakymas, klaidos
        //      nemeta bet kokiu atveju (nepriklausomai nuo p_bThrowError),
        //      bet grąžina klaidos kodą KP_E_NEG_ANSW

    HRESULT RcvHttpRequest(bool p_bThrowError = False)
        { return(RcvHdr(HTTP_REQUEST_UNKNOWN, p_bThrowError)); }
        // GET /favicon.ico HTTP/1.1
        // POST /friends.htm HTTP/1.1
        // the same as RcvHdr()
        // receives and scans HTTP request header from newly accepted socket
        // fills m_PackedUrl structure, destroys data previously filled by
        //      Accept()
        
    HRESULT RcvHttpMsg(uchar *p_pBuf, long *p_plRead,
        bool p_bRcvHdr = True,  // False – RcvHdr() neiškviečia (naudojam,
            //  kai jau būna priimtas anksčiau, tik paties (chunked) pranešimo
            //  kūno priėmimui)
        bool p_bThrowError = False);
        // HTTP/1.1 200 OK
        // on entering *p_plRead must be filled with the length of p_pBuf
        // scans and skips HTTP header RcvHdr()
        // TODO: o gal ir visus GetByte() ir Co keist i GetChar()?
        // jei priimta be klaidų, bet yra neigiamas HTTP atsakymas, klaidos
        //      nemeta bet kokiu atveju (nepriklausomai nuo p_bThrowError),
        //      bet grąžina klaidos kodą KP_E_NEG_ANSW
        // jei pasibaigia p_pBuf, sustoja po eilinio chunk ilgio perskaitymo,
        //      užpildo m_lNextChunkLength ir grįžta
        // po to reikia iškvietinėti RcvHttpRest(), kol perskaitytas ilgis
        //      bus 0L
        // TODO: problema, jei HTTP chunk ilgis pasitaikys didesnis, negu
        //      p_pBuf ilgis, kažką daryt – dalint eilinį chunk gabalais

    HRESULT RcvHttpRest(uchar *p_pBuf, long *p_plRead,
                                        bool p_bThrowError = False);
        // tęsia RcvHttpMsg() pradėtą pranešimo siuntimą
        // iškvietinėti, kol *plRead grąžins 0L

    HRESULT RcvHttpMsgAlloc(uchar **p_ppBuf, long *p_plRead,
                    bool p_bRcvHdr = True, bool p_bThrowError = False);
        // RcvHttpMsg() su dinaminiu buferio išskyrimu;
        // *p_ppBuf įeinant turi būti NULL, *p_plRead bet koks
        // jei iš pirmo karto nepataiko išskirt užtektinai, buferį didina ir
        //      iškvietinėja RcvHttpRest()

    HRESULT SendHttpMsg(const uchar *p_lpszMsg, 
        const uchar *p_lpszFileType = KPSOCK_DEF_CONT_TYPE,
            // parameter for HTTP tag Content-Type:
            //    text/plain
            //    text/html; charset=ISO-8859-1
            //    image/jpeg
        int p_iHTTP_RetCode = HTTP_ANSW_OK,
            // look KpErrorClass::FormatErrorMessageHTTP()
        bool p_bThrowError = False);
        
    HRESULT GetPostVars(KpTreeEntry<PostVarRec> **p_pVarList,
                                        bool p_bThrowError = False);
        // priima POST metodu atsiųstų kintamųjų reikšmes
        // kintamųjų reikšmės tik po vieną eilutę,
        // duomenys siunčiami tik vieno lygmens struktura
        //      netinka trečio tipo pranešimas (žr. GetPostVars() realizaciją)
        // TODO: perdaryt rekursiškai - lokalus headerio buferis,
        //      kai gauna naują boundary
        //      Content-Type: multipart/mixed; boundary=BbC04y
        //      iškviečia save rekursiškai su ta nauja boundary,
        //      po to grįžta tęsti blokų su sena boundary
};

#endif
