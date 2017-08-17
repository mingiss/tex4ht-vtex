/* ==================================================
 *
 * kperrno.h
 *
 *    kp error codes
 *
 * 2013-02-22  mp  initial creation
 * 2016-09-05  mp  migration of kpsgrp from tv to kplib
 *
 */

// -------------------------------------------------
#ifndef KPERRNO_INCLUDED
#define KPERRNO_INCLUDED


// ================================================== return codes
#ifndef WIN32

typedef int HRESULT;

#define SUCCEEDED(Status) ((HRESULT)(Status) >= 0)
#define FAILED(Status) ((HRESULT)(Status)<0)

#define MAKE_HRESULT(s,f,c) ((HRESULT)(((unsigned long)(s)<<31)|((unsigned long)(f)<<16)|((unsigned long)(c))))

#define SEVERITY_SUCCESS 0
#define SEVERITY_ERROR 1
#define FACILITY_WINDOWS 8
#define FACILITY_STORAGE 3
#define FACILITY_RPC 1
#define FACILITY_WIN32 7
#define FACILITY_CONTROL 10
#define FACILITY_NULL 0
#define FACILITY_ITF 4
#define FACILITY_DISPATCH 2

// ok
#define S_OK         0 // (MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0))
// invalid parameter
#define E_INVALIDARG (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 1))
// feature not implemented yet
#define E_NOTIMPL    (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 2))
// out of memory
#define E_OUTOFMEMORY ((HRESULT)0x8007000E)
// illegal function call (at the moment)
#define E_UNEXPECTED ((HRESULT)0x8000FFFF)
#define E_NOINTERFACE ((HRESULT)0x80004002)
#define E_POINTER ((HRESULT)0x80004003)
#define E_HANDLE ((HRESULT)0x80070006)
// job cancelled
#define E_ABORT ((HRESULT)0x80004004)
#define E_FAIL ((HRESULT)0x80004005)
// Access denied
#define E_ACCESSDENIED ((HRESULT)0x80070005)
#define E_PENDING ((HRESULT)0x8000000A)
#define E_BUFFER_TOO_SMALL ((HRESULT)0x8007007A)

/*
http://research.microsoft.com/en-us/um/redmond/projects/invisible/iunknown.htm

See also AtomicDec IUnknown.QueryInterface IUnknown.AddRef
C++

UINT IUnknown::Release( void )

SCODE Constant
Generic success codes

S_OK 0x0    Generic all OK success used by all methods that return SCODEs.
S_FALSE 0x1    Generic secondary success, indicates last entry or similar.

MMLite error SCODE Constant
MMLite specific error codes

E_UNEXPECTED_ERROR 0x80060000    Object is in a state where the operation is not allowed.
E_OBJECT_NOT_INITIALIZED 0x80060001    Object is in a state where it is unable to service method call.
E_TIMED_OUT 0x80060003    Operation timed out and was not completed. In many cases this is intentional behavior and does not indicate any kind of failure.
E_ALREADY_RESERVED 0x8006000d    Memory region was already reserved. A region cannot be reserved twice.
E_NOT_RESERVED 0x8006000e    Memory region was not reserved. It must be reserved before mappings can be mapped to it.
E_ALREADY_COMMITTED 0x8006000f    A memory region already had a mapping and/or physical pages.
E_NOT_COMMITTED 0x80060010    Operation required a mapping but there was none.
E_TOO_MANY_CONTIGUOUS 0x80060012    The image has too many sections.
E_RESTART 0x80060014    Operation could not be completed atomically and must be restarted.
E_END_OF_DATA 0x80060015    Parser reached maximum content size.
E_PARSE_ERROR 0x80060016    Data format error.
E_SCHEMA_CHECK 0x80060017    Data format error.
E_WOULD_BLOCK 0x80060018    The method is done for now but ought to be restarted in the future.
E_PARSING_ERROR 0x80060020    Invalid input encountered
E_ERROR_RESPONSE_RECEIVED 0x80060021    Invalid input encountered
E_AUTHORIZATION_REQUIRED 0x80060022    The client authorization is lacking (e.g. HTTP 401).
E_NAME_NOT_FOUND E_PATH_NOT_FOUND    The name referred to did not exist in namespace.
E_OBJECT_NOT_FOUND E_ENTRY_NOT_FOUND    Lookup failed.
E_INVALID_METHOD E_INVALID_ORDINAL    Protocol error. Message referred to method not in schema.

MMLite success SCODE Constant
MMLite specific success codes

S_OUTATIME 0x60004    The previous constraint overran its estimate.
S_ALREADY_EXISTS 0x600b7    Entry already existed but was overwritten.
S_BUFFER_TOO_SMALL 0x6007a    The buffer provided was too small. This means usually the size of an out parameter of a method call. Nevertheless the call was completed and the return value was filled in up to the size.
S_NAME_SEARCH_INCOMPLETE 0x6007b    A symbolic link was encountered in the middle of a name resolution when NAME_SPACE_NOFOLLOW was set.
S_NO_RESPONSE 0x6007c    The application already sent a response or will send a response so the server should not do it.
S_MUST_REPLY 0x6007d    The application has generated a response and it should be forwarded to the server. Used by intermediaries that can handle data in either directions.
S_NO_MORE_ENTRIES S_FALSE    Last entry in namespace.

Ole32 SCODE Constant
OLE derived error codes

E_NOT_IMPLEMENTED 0x80040001    The method is not implementation by the server. Same as E_NOTIMPL in Ole.
E_NO_INTERFACE 0x80040002    The server does not support the given interface. In other words the Interface ID given to QueryInterface was not recognized. Same as E_NOINTERFACE in Ole.
E_FAIL 0x80040005    Generic catch-all failure.

Win32 SCODE Constant
Win32 derived error codes

E_FILE_NOT_FOUND 0x80070002    Specified name is not present in namespace.
E_PATH_NOT_FOUND 0x80070003    The name referred to did not exist in namespace.
E_ACCESS_DENIED 0x80070005    Access was denied. For example a write to a read-only file.
E_INVALID_HANDLE 0x80070006    Operation could not be completed because a required object was not available.
E_NOT_ENOUGH_MEMORY 0x80070008    Resource shortage.
E_WRITE_PROTECT 0x80070013    Disk was read-only.
E_BAD_UNIT 0x80070014    Disk error.
E_NOT_READY 0x80070015    Disk error. // "Įrenginys nėra pasirengęs" (PK910v/klaida_20120911_Algimantas_Lazauskas, bandant surasti My Documents su SHGetFolderPath())
E_CRC 0x80070017    Disk error.
E_DMA_FAILURE 0x80070018    Driver error.
E_SEEK 0x80070019    Disk error.
E_SECTOR_NOT_FOUND 0x8007001b    Disk error.
E_OUT_OF_STRUCTURES 0x80070054    Allocation from fixed size pool failed. Resource shortage.
E_INVALID_PARAMETER 0x80070057    A method argument had a value not allowed in call.
E_NULL_PARAMETER 0x80070058    A method argument had a value not allowed in call.
E_BUFFER_TOO_SMALL 0x8007007a    The buffer provided was too small. This means usually the size of an out parameter of a method call. The call could not be completed and the out parameters were not updated.
E_MOD_NOT_FOUND 0x8007007e    Module not found.
E_PROC_NOT_FOUND 0x8007007f    Method not found. DLL import was not found in export table.
E_INVALID_ORDINAL 0x800700b6    Method number out of range. DLL entry was not exported.
E_ALREADY_EXISTS 0x800700b7    Entry could not be created because it was already present.
E_INVALID_EXE_SIGNATURE 0x800700bf    Image could not be loaded for execution.
E_EXE_MARKED_INVALID 0x800700c0
E_BAD_EXE_FORMAT 0x800700c1    Image could not be loaded for execution.
E_LOCKED 0x800700d4
E_INCOMPATIBLE_VERSION 0x800700d8    An object's version is incompatible with another object, like between the loader and an executable image.
E_INVALID_ADDRESS 0x800701e7    Pointer argument was not within range.
E_IO_PENDING 0x800703e5    I/O in progress.
E_NOACCESS 0x800703e6
E_MEDIA_CHANGED 0x80070456    Disk error.
E_NO_MEDIA_IN_DRIVE 0x80070458    Disk error.
E_DLL_INIT_FAILED 0x8007045a    Image load failed.
E_FLOPPY_ID_MARK_NOT_FOUND 0x80070462    Disk error.
E_FLOPPY_WRONG_CYLINDER 0x80070463    Disk error.
E_FLOPPY_UNKNOWN_ERROR 0x80070464    Disk error.
E_FLOPPY_BAD_REGISTERS 0x80070465    Disk error.
E_DISK_RECALIBRATE_FAILED 0x80070466    Disk error.
E_DISK_OPERATION_FAILED 0x80070467    Disk error.
E_DISK_RESET_FAILED 0x80070468    Disk error.
E_INTERNAL_ERROR 0x8007054f    Should not happen.
E_ENTRY_NOT_FOUND 0x800706e1    Name was not found in namespace.
E_UNRECOGNIZED_MEDIA 0x800706f9    Disk error.
E_SIG_NOT_FOUND 0x80070715
E_DEVICE_IN_USE 0x80070964    Driver error. Exclusive access.
E_HTTP_ERROR 0x80070965    Driver error. Exclusive access.


WSA_INVALID_HANDLE6 
Specified event object handle is invalid.
An application attempts to use an event object, but the specified handle is not valid. Note that this error is returned by the operating system, so the error number may change in future releases of Windows.
 
 WSA_NOT_ENOUGH_MEMORY8 
Insufficient memory available.
An application used a Windows Sockets function that directly maps to a Windows function. The Windows function is indicating a lack of required memory resources. Note that this error is returned by the operating system, so the error number may change in future releases of Windows.
 
 WSA_INVALID_PARAMETER87 
One or more parameters are invalid.
An application used a Windows Sockets function which directly maps to a Windows function. The Windows function is indicating a problem with one or more parameters. Note that this error is returned by the operating system, so the error number may change in future releases of Windows.
 
 WSA_OPERATION_ABORTED995 
Overlapped operation aborted.
An overlapped operation was canceled due to the closure of the socket, or the execution of the SIO_FLUSH command in WSAIoctl. Note that this error is returned by the operating system, so the error number may change in future releases of Windows.
 
 WSA_IO_INCOMPLETE996 
Overlapped I/O event object not in signaled state.
The application has tried to determine the status of an overlapped operation which is not yet completed. Applications that use WSAGetOverlappedResult (with the fWait flag set to FALSE) in a polling mode to determine when an overlapped operation has completed, get this error code until the operation is complete. Note that this error is returned by the operating system, so the error number may change in future releases of Windows.
 
 WSA_IO_PENDING997 
Overlapped operations will complete later. 


The application has initiated an overlapped operation that cannot be completed immediately. A completion indication will be given later when the operation has been completed. Note that this error is returned by the operating system, so the error number may change in future releases of Windows.
 
 WSAEINTR10004 
Interrupted function call.
A blocking operation was interrupted by a call to WSACancelBlockingCall.
 
 WSAEBADF10009 
File handle is not valid.
The file handle supplied is not valid. 
 
 WSAEACCES10013 
Permission denied.
An attempt was made to access a socket in a way forbidden by its access permissions. An example is using a broadcast address for sendto without broadcast permission being set using setsockopt(SO_BROADCAST). 

Another possible reason for the WSAEACCES error is that when the bind function is called (on Windows NT 4.0 with SP4 and later), another application, service, or kernel mode driver is bound to the same address with exclusive access. Such exclusive access is a new feature of Windows NT 4.0 with SP4 and later, and is implemented by using the SO_EXCLUSIVEADDRUSE option.
 
 WSAEFAULT10014 
Bad address.
The system detected an invalid pointer address in attempting to use a pointer argument of a call. This error occurs if an application passes an invalid pointer value, or if the length of the buffer is too small. For instance, if the length of an argument, which is a sockaddr structure, is smaller than the sizeof(sockaddr).
 
 WSAEINVAL10022 
Invalid argument.
Some invalid argument was supplied (for example, specifying an invalid level to the setsockopt function). In some instances, it also refers to the current state of the socket—for instance, calling accept on a socket that is not listening.
 
 WSAEMFILE10024 
Too many open files.
Too many open sockets. Each implementation may have a maximum number of socket handles available, either globally, per process, or per thread.
 
 WSAEWOULDBLOCK10035 
Resource temporarily unavailable.
This error is returned from operations on nonblocking sockets that cannot be completed immediately, for example recv when no data is queued to be read from the socket. It is a nonfatal error, and the operation should be retried later. It is normal for WSAEWOULDBLOCK to be reported as the result from calling connect on a nonblocking SOCK_STREAM socket, since some time must elapse for the connection to be established.
 
 WSAEINPROGRESS10036 
Operation now in progress.
A blocking operation is currently executing. Windows Sockets only allows a single blocking operation—per- task or thread—to be outstanding, and if any other function call is made (whether or not it references that or any other socket) the function fails with the WSAEINPROGRESS error.
 
 WSAEALREADY10037 
Operation already in progress.
An operation was attempted on a nonblocking socket with an operation already in progress—that is, calling connect a second time on a nonblocking socket that is already connecting, or canceling an asynchronous request (WSAAsyncGetXbyY) that has already been canceled or completed.
 
 WSAENOTSOCK10038 
Socket operation on nonsocket.
An operation was attempted on something that is not a socket. Either the socket handle parameter did not reference a valid socket, or for select, a member of an fd_set was not valid.
 
 WSAEDESTADDRREQ10039 
Destination address required.
A required address was omitted from an operation on a socket. For example, this error is returned if sendto is called with the remote address of ADDR_ANY.
 
 WSAEMSGSIZE10040 
Message too long.
A message sent on a datagram socket was larger than the internal message buffer or some other network limit, or the buffer used to receive a datagram was smaller than the datagram itself.
 
 WSAEPROTOTYPE10041 
Protocol wrong type for socket.
A protocol was specified in the socket function call that does not support the semantics of the socket type requested. For example, the ARPA Internet UDP protocol cannot be specified with a socket type of SOCK_STREAM.
 
 WSAENOPROTOOPT10042 
Bad protocol option.
An unknown, invalid or unsupported option or level was specified in a getsockopt or setsockopt call.
 
 WSAEPROTONOSUPPORT10043 
Protocol not supported.
The requested protocol has not been configured into the system, or no implementation for it exists. For example, a socket call requests a SOCK_DGRAM socket, but specifies a stream protocol.
 
 WSAESOCKTNOSUPPORT10044 
Socket type not supported.
The support for the specified socket type does not exist in this address family. For example, the optional type SOCK_RAW might be selected in a socket call, and the implementation does not support SOCK_RAW sockets at all.
 
 WSAEOPNOTSUPP10045 
Operation not supported.
The attempted operation is not supported for the type of object referenced. Usually this occurs when a socket descriptor to a socket that cannot support this operation is trying to accept a connection on a datagram socket.
 
 WSAEPFNOSUPPORT10046 
Protocol family not supported.
The protocol family has not been configured into the system or no implementation for it exists. This message has a slightly different meaning from WSAEAFNOSUPPORT. However, it is interchangeable in most cases, and all Windows Sockets functions that return one of these messages also specify WSAEAFNOSUPPORT.
 
 WSAEAFNOSUPPORT10047 
Address family not supported by protocol family.
An address incompatible with the requested protocol was used. All sockets are created with an associated address family (that is, AF_INET for Internet Protocols) and a generic protocol type (that is, SOCK_STREAM). This error is returned if an incorrect protocol is explicitly requested in the socket call, or if an address of the wrong family is used for a socket, for example, in sendto.
 
 WSAEADDRINUSE10048 
Address already in use.
Typically, only one usage of each socket address (protocol/IP address/port) is permitted. This error occurs if an application attempts to bind a socket to an IP address/port that has already been used for an existing socket, or a socket that was not closed properly, or one that is still in the process of closing. For server applications that need to bind multiple sockets to the same port number, consider using setsockopt (SO_REUSEADDR). Client applications usually need not call bind at all—connect chooses an unused port automatically. When bind is called with a wildcard address (involving ADDR_ANY), a WSAEADDRINUSE error could be delayed until the specific address is committed. This could happen with a call to another function later, including connect, listen, WSAConnect, or WSAJoinLeaf.
 
 WSAEADDRNOTAVAIL10049 
Cannot assign requested address.
The requested address is not valid in its context. This normally results from an attempt to bind to an address that is not valid for the local computer. This can also result from connect, sendto, WSAConnect, WSAJoinLeaf, or WSASendTo when the remote address or port is not valid for a remote computer (for example, address or port 0).
 
 WSAENETDOWN10050 
Network is down.
A socket operation encountered a dead network. This could indicate a serious failure of the network system (that is, the protocol stack that the Windows Sockets DLL runs over), the network interface, or the local network itself.
 
 WSAENETUNREACH10051 
Network is unreachable.
A socket operation was attempted to an unreachable network. This usually means the local software knows no route to reach the remote host.
 
 WSAENETRESET10052 
Network dropped connection on reset.
The connection has been broken due to keep-alive activity detecting a failure while the operation was in progress. It can also be returned by setsockopt if an attempt is made to set SO_KEEPALIVE on a connection that has already failed.
 
 WSAECONNABORTED10053 
Software caused connection abort.
An established connection was aborted by the software in your host computer, possibly due to a data transmission time-out or protocol error.
 
 WSAECONNRESET10054 
Connection reset by peer.
An existing connection was forcibly closed by the remote host. This normally results if the peer application on the remote host is suddenly stopped, the host is rebooted, the host or remote network interface is disabled, or the remote host uses a hard close (see setsockopt for more information on the SO_LINGER option on the remote socket). This error may also result if a connection was broken due to keep-alive activity detecting a failure while one or more operations are in progress. Operations that were in progress fail with WSAENETRESET. Subsequent operations fail with WSAECONNRESET.
 
 WSAENOBUFS10055 
No buffer space available.
An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full.
 
 WSAEISCONN10056 
Socket is already connected.
A connect request was made on an already-connected socket. Some implementations also return this error if sendto is called on a connected SOCK_DGRAM socket (for SOCK_STREAM sockets, the to parameter in sendto is ignored) although other implementations treat this as a legal occurrence.
 
 WSAENOTCONN10057 
Socket is not connected.
A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using sendto) no address was supplied. Any other type of operation might also return this error—for example, setsockopt setting SO_KEEPALIVE if the connection has been reset.
 
 WSAESHUTDOWN10058 
Cannot send after socket shutdown.
A request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call. By calling shutdown a partial close of a socket is requested, which is a signal that sending or receiving, or both have been discontinued.
 
 WSAETOOMANYREFS10059 
Too many references.
Too many references to some kernel object.
 
 WSAETIMEDOUT10060 
Connection timed out.
A connection attempt failed because the connected party did not properly respond after a period of time, or the established connection failed because the connected host has failed to respond.
 
 WSAECONNREFUSED10061 
Connection refused.
No connection could be made because the target computer actively refused it. This usually results from trying to connect to a service that is inactive on the foreign host—that is, one with no server application running.
 
 WSAELOOP10062 
Cannot translate name.
Cannot translate a name.
 
 WSAENAMETOOLONG10063 
Name too long.
A name component or a name was too long.
 
 WSAEHOSTDOWN10064 
Host is down.
A socket operation failed because the destination host is down. A socket operation encountered a dead host. Networking activity on the local host has not been initiated. These conditions are more likely to be indicated by the error WSAETIMEDOUT.
 
 WSAEHOSTUNREACH10065 
No route to host.
A socket operation was attempted to an unreachable host. See WSAENETUNREACH.
 
 WSAENOTEMPTY10066 
Directory not empty.
Cannot remove a directory that is not empty.
 
 WSAEPROCLIM10067 
Too many processes.
A Windows Sockets implementation may have a limit on the number of applications that can use it simultaneously. WSAStartup may fail with this error if the limit has been reached.
 
 WSAEUSERS10068 
User quota exceeded.
Ran out of user quota. 
 
 WSAEDQUOT10069 
Disk quota exceeded.
Ran out of disk quota. 
 
 WSAESTALE10070 
Stale file handle reference.
The file handle reference is no longer available. 
 
 WSAEREMOTE10071 
Item is remote.
The item is not available locally. 
 
 WSASYSNOTREADY10091 
Network subsystem is unavailable.
This error is returned by WSAStartup if the Windows Sockets implementation cannot function at this time because the underlying system it uses to provide network services is currently unavailable. Users should check:
•That the appropriate Windows Sockets DLL file is in the current path.
•That they are not trying to use more than one Windows Sockets implementation simultaneously. If there is more than one Winsock DLL on your system, be sure the first one in the path is appropriate for the network subsystem currently loaded.
•The Windows Sockets implementation documentation to be sure all necessary components are currently installed and configured correctly.
 
 WSAVERNOTSUPPORTED10092 
Winsock.dll version out of range.
The current Windows Sockets implementation does not support the Windows Sockets specification version requested by the application. Check that no old Windows Sockets DLL files are being accessed.
 
 WSANOTINITIALISED10093 
Successful WSAStartup not yet performed.
Either the application has not called WSAStartup or WSAStartup failed. The application may be accessing a socket that the current active task does not own (that is, trying to share a socket between tasks), or WSACleanup has been called too many times.
 
 WSAEDISCON10101 
Graceful shutdown in progress.
Returned by WSARecv and WSARecvFrom to indicate that the remote party has initiated a graceful shutdown sequence.
 
 WSAENOMORE10102 
No more results.
No more results can be returned by the WSALookupServiceNext function.
 
 WSAECANCELLED10103 
Call has been canceled.
A call to the WSALookupServiceEnd function was made while this call was still processing. The call has been canceled.
 
 WSAEINVALIDPROCTABLE10104 
Procedure call table is invalid.
The service provider procedure call table is invalid. A service provider returned a bogus procedure table to Ws2_32.dll. This is usually caused by one or more of the function pointers being NULL.
 
 WSAEINVALIDPROVIDER10105 
Service provider is invalid.
The requested service provider is invalid. This error is returned by the WSCGetProviderInfo and WSCGetProviderInfo32 functions if the protocol entry specified could not be found. This error is also returned if the service provider returned a version number other than 2.0.
 
 WSAEPROVIDERFAILEDINIT10106 
Service provider failed to initialize.
The requested service provider could not be loaded or initialized. This error is returned if either a service provider's DLL could not be loaded (LoadLibrary failed) or the provider's WSPStartup or NSPStartup function failed.
 
 WSASYSCALLFAILURE10107 
System call failure.
A system call that should never fail has failed. This is a generic error code, returned under various conditions. 

Returned when a system call that should never fail does fail. For example, if a call to WaitForMultipleEvents fails or one of the registry functions fails trying to manipulate the protocol/namespace catalogs.

Returned when a provider does not return SUCCESS and does not provide an extended error code. Can indicate a service provider implementation error.
 
 WSASERVICE_NOT_FOUND10108 
Service not found.
No such service is known. The service cannot be found in the specified name space.
 
 WSATYPE_NOT_FOUND10109 
Class type not found.
The specified class was not found.
 
 WSA_E_NO_MORE10110 
No more results.
No more results can be returned by the WSALookupServiceNext function.
 
 WSA_E_CANCELLED10111 
Call was canceled.
A call to the WSALookupServiceEnd function was made while this call was still processing. The call has been canceled.
 
 WSAEREFUSED10112 
Database query was refused.
A database query failed because it was actively refused.
 
 WSAHOST_NOT_FOUND11001 
Host not found.
No such host is known. The name is not an official host name or alias, or it cannot be found in the database(s) being queried. This error may also be returned for protocol and service queries, and means that the specified name could not be found in the relevant database.
 
 WSATRY_AGAIN11002 
Nonauthoritative host not found.
This is usually a temporary error during host name resolution and means that the local server did not receive a response from an authoritative server. A retry at some time later may be successful.
 
 WSANO_RECOVERY11003 
This is a nonrecoverable error.
This indicates that some sort of nonrecoverable error occurred during a database lookup. This may be because the database files (for example, BSD-compatible HOSTS, SERVICES, or PROTOCOLS files) could not be found, or a DNS request was returned by the server with a severe error.
 
 WSANO_DATA11004 
Valid name, no data record of requested type.
The requested name is valid and was found in the database, but it does not have the correct associated data being resolved for. The usual example for this is a host name-to-address translation attempt (using gethostbyname or WSAAsyncGetHostByName) which uses the DNS (Domain Name Server). An MX record is returned but no A record—indicating the host itself exists, but is not directly reachable.
 
 WSA_QOS_RECEIVERS11005 
QoS receivers.
At least one QoS reserve has arrived.
 
 WSA_QOS_SENDERS11006 
QoS senders.
At least one QoS send path has arrived.
 
 WSA_QOS_NO_SENDERS11007 
No QoS senders.
There are no QoS senders.
 
 WSA_QOS_NO_RECEIVERS11008 
QoS no receivers.
There are no QoS receivers.
 
 WSA_QOS_REQUEST_CONFIRMED11009 
QoS request confirmed.
The QoS reserve request has been confirmed.
 
 WSA_QOS_ADMISSION_FAILURE11010 
QoS admission error.
A QoS error occurred due to lack of resources.
 
 WSA_QOS_POLICY_FAILURE11011 
QoS policy failure.
The QoS request was rejected because the policy system couldn't allocate the requested resource within the existing policy. 
 
 WSA_QOS_BAD_STYLE11012 
QoS bad style.
An unknown or conflicting QoS style was encountered.
 
 WSA_QOS_BAD_OBJECT11013 
QoS bad object.
A problem was encountered with some part of the filterspec or the provider-specific buffer in general.
 
 WSA_QOS_TRAFFIC_CTRL_ERROR11014 
QoS traffic control error.
An error with the underlying traffic control (TC) API as the generic QoS request was converted for local enforcement by the TC API. This could be due to an out of memory error or to an internal QoS provider error. 
 
 WSA_QOS_GENERIC_ERROR11015 
QoS generic error.
A general QoS error.
 
 WSA_QOS_ESERVICETYPE11016 
QoS service type error.
An invalid or unrecognized service type was found in the QoS flowspec.
 
 WSA_QOS_EFLOWSPEC11017 
QoS flowspec error.
An invalid or inconsistent flowspec was found in the QOS structure.
 
 WSA_QOS_EPROVSPECBUF11018 
Invalid QoS provider buffer.
An invalid QoS provider-specific buffer.
 
 WSA_QOS_EFILTERSTYLE11019 
Invalid QoS filter style.
An invalid QoS filter style was used.
 
 WSA_QOS_EFILTERTYPE11020 
Invalid QoS filter type.
An invalid QoS filter type was used.
 
 WSA_QOS_EFILTERCOUNT11021 
Incorrect QoS filter count.
An incorrect number of QoS FILTERSPECs were specified in the FLOWDESCRIPTOR.
 
 WSA_QOS_EOBJLENGTH11022 
Invalid QoS object length.
An object with an invalid ObjectLength field was specified in the QoS provider-specific buffer.
 
 WSA_QOS_EFLOWCOUNT11023 
Incorrect QoS flow count.
An incorrect number of flow descriptors was specified in the QoS structure.
 
 WSA_QOS_EUNKOWNPSOBJ11024 
Unrecognized QoS object.
An unrecognized object was found in the QoS provider-specific buffer.
 
 WSA_QOS_EPOLICYOBJ11025 
Invalid QoS policy object.
An invalid policy object was found in the QoS provider-specific buffer.
 
 WSA_QOS_EFLOWDESC11026 
Invalid QoS flow descriptor.
An invalid QoS flow descriptor was found in the flow descriptor list.
 
 WSA_QOS_EPSFLOWSPEC11027 
Invalid QoS provider-specific flowspec.
An invalid or inconsistent flowspec was found in the QoS provider-specific buffer.
 
 WSA_QOS_EPSFILTERSPEC11028 
Invalid QoS provider-specific filterspec.
An invalid FILTERSPEC was found in the QoS provider-specific buffer.
 
 WSA_QOS_ESDMODEOBJ11029 
Invalid QoS shape discard mode object.
An invalid shape discard mode object was found in the QoS provider-specific buffer.
 
 WSA_QOS_ESHAPERATEOBJ11030 
Invalid QoS shaping rate object.
An invalid shaping rate object was found in the QoS provider-specific buffer.
 
 WSA_QOS_RESERVED_PETYPE11031 
Reserved policy QoS element type.
A reserved policy element was found in the QoS provider-specific buffer.
 
*/
#endif // #ifndef WIN32

#ifdef _MSC_VER
#define E_BUFFER_TOO_SMALL ((HRESULT)0x8007007a)
#endif

// Object is busy
// The method can't proceed since a resource needed is currently in use but this ought to be restarted in the future.
#define E_OBJECT_BUSY ((HRESULT)0x80060019L)


// --------------------------------------------------------
// out of memory
#define KP_E_OUTOFMEM         E_OUTOFMEMORY  // (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 +  0x01))
// double unget
#define KP_E_DOUBLE_UNGET     (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 +  0x02))
// file not found
#define KP_E_FILE_NOT_FOUND   (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 +  0x03))
// unable to create file
#define KP_E_DIR_ERROR        (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 +  0x04))
// file error
#define KP_E_FERROR           (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 +  0x05))
// internal error
#define KP_E_SYSTEM_ERROR     (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 +  0x06))
// unexpected end of input file
#define KP_E_EOF              (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 +  0x07))
// unexpected input file format
#define KP_E_FILE_FORMAT      (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 +  0x08))
// no file open
#define KP_E_NO_FILE          (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 +  0x09))
// unknown character
#define KP_E_UNKN_CHR         (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x0a))
// external error
#define KP_E_COMMAND_ERROR    (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x0b))
// buffer overflow
// #define KP_E_BUFFER_OVERFLOW  (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x0c))
#define KP_E_BUFFER_OVERFLOW  E_BUFFER_TOO_SMALL
// font undefined
#define KP_E_FONT_UNDEF       (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x0d))
// keyword not found
#define KP_E_KWD_NOT_FOUND    (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x0e))
// unknown OS version
#define KP_E_UNKNOWN_SYSTEM   (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x0f))
// illegal registration code
#define KP_E_ILL_CODE         (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x10))
// job cancelled
#define KP_E_CANCEL           E_ABORT  // (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x011))
// duplicated call to function, illegal recursion etc.
#define KP_E_DOUBLE_CALL      E_PENDING // (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x012))
// timeout when waiting for answer
#define KP_E_TIMEOUT          (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x013))
// object not found
#define KP_E_OBJ_NOT_FOUND    (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x014))
// no connection
#define KP_E_NO_CONN          (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x015))
// transfer error
#define KP_E_TRANS_ERR        (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x016))
// registration refused
#define KP_E_REFUSED          (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x017))
// Access denied
#define KP_E_ACCESS_DENIED    E_ACCESSDENIED    // (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x018))
// illegal character
#define KP_E_ILL_CHR          (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x019))
// skip next operation - return code, not error
#define KP_E_SKIP             (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x01a))
// division by zero
#define KP_E_DIV_ZERO         (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x01b))
// negative sqrt() parameter
#define KP_E_ILLMATHARG       (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x01c)) // former KP_E_IRRAC
// illegal function call
#define KP_E_ILLFUNC          (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x01d))
// program not installed
#define KP_E_NOTINST          (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x01e))
// unexpected message format
#define KP_E_MSG_FORMAT       (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x01f))
// obsolete function
#define KP_E_OBSOLETE         (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x020))
// help, forgot an password, etc
#define KP_E_HELP             (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x021))
// negative answer from called function / received IP message
// bendras klaidos kodas visiems neigiamiams HTTP atsakymams; norint konkretinti – KpErrorProcClass::TranslFromHTTP_RetCode(KpSocket::m_iRetCode)
#define KP_E_NEG_ANSW         (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x022))
// file changed // pvz., užsikrėtė virusu
#define KP_E_FILE_CHANGED     (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x023))
// formuojamas diagnostinis pranešimas
#define KP_S_DIAG_MSG         (MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_ITF, 0x200 + 0x100 + 0x024))
// Neteisingas e-pašto adresas
#define KP_E_BAD_EMAIL        (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x025))
// programa baigta išsiloginimo procedūra
#define KP_S_LOGOFF           (MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_ITF, 0x200 + 0x100 + 0x026))
// operacija atlikta sėkmingai (naudojama išėjimui iš dialogų)
#define KP_S_DONE             (MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_ITF, 0x200 + 0x100 + 0x027))
// licence expired
#define KP_E_EXPIRED          (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x028))
// memory fault
// #define KP_E_MEMORY_FAULT     (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x029))
// arithmetic overflow
// #define KP_E_ARITHM_OVERFL    (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x02a))
// unhandled exception
#define KP_E_UNHANDLED_EXCEPTION  (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 + 0x02b))
// unexpected data format
#define KP_E_DATA_FORMAT      (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 +  0x2c))
// database error
#define KP_E_DBERROR          (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 +  0x2d))
// error during text encoding (not limited to KP_E_ILL_CHR, could be KP_E_BUFFER_OVERFLOW, for instance) 
#define KP_E_ENCODING         (MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 +  0x2e))

// =========================================
// interaktyvių pranešimų tipai kpwindow.cpp: KpMsgOut()
//
typedef enum
{
    KP_MB_OK,
    KP_MB_GERAI,
    KP_MB_TESTI,
    KP_MB_BAIGTI,
    KP_MB_OK_CANCEL,
    KP_MB_GERAI_ATSAUKTI,
    KP_MB_TESTI_ATSAUKTI,
    KP_MB_YES_NO,
    KP_MB_TAIP_NE,
    KP_MB_GERAI_ATSAUKTI_PAMIRSAU,
    KP_MB_NONE, // tik išveda pranešimą be mygtukų ir iškart grįžta
} KpMsgTypes;


#endif // #ifndef KPERRNO_INCLUDED
