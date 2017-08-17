// -----------------------------------------
// kpmsg_en.h
// programos paleidimo aplikaciju pranesimai
// angl� kalba
//

#ifndef KPMSG_EN_INCLUDED
#define KPMSG_EN_INCLUDED

// --------------------------------------- common kp messages

#if TRUE // ((MsgLang == KpLangEn_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangEn_p))

#define KP_MSG_TITLE_EN             ((MSG_TYPE)"Message")
#define KP_INPUT_TITLE_EN           ((MSG_TYPE)"Input")

#define KP_MSG_YES_EN               ((MSG_TYPE)"Yes")
#define KP_MSG_TAIP_EN              KP_MSG_YES_EN
#define KP_MSG_NO_EN                ((MSG_TYPE)"No")
#define KP_MSG_NE_EN                KP_MSG_NO_EN
#define KP_MSG_OK_EN                ((MSG_TYPE)"OK")
#define KP_MSG_GERAI_EN             KP_MSG_OK_EN
#define KP_MSG_CANCEL_EN            ((MSG_TYPE)"Cancel")
#define KP_MSG_ATSAUKTI_EN          KP_MSG_CANCEL_EN
#define KP_MSG_TESTI_EN             ((MSG_TYPE)"Continue")
#define KP_MSG_BAIGTI_EN            ((MSG_TYPE)"Finish")
#define KP_MSG_PAMIRSAU_SLAPTAZODI_EN ((MSG_TYPE)"Forgot password")

#define KP_MSG_ERROR_EN             ((MSG_TYPE)"Error")
#define KP_MSG_WARNING_EN           ((MSG_TYPE)"Warning")
#define KP_MSG_FILE_LINE_EN         ((MSG_TYPE)", error: %lx, file: %s, line: %d")
#define KP_MSG_ENTRY_ID_EN          ((MSG_TYPE)", Entry Id:%ld")
#define KP_MSG_ENTRY_EN             ((MSG_TYPE)", Entry: %s")

#define KP_MSG_NO_STANDARD_PROG_EN  ((MSG_TYPE)"Standard program not set to open given file type")
#define KP_MSG_WND_NOT_FOUND_EN     ((MSG_TYPE)"Window not found")
#define KP_MSG_PID_NOT_FOUND_EN     ((MSG_TYPE)"PID not found")
#define KP_MSG_NO_SOCKET_EN         ((MSG_TYPE)"Socket not created yet")
#define KP_MSG_SOCK_UNRESOLVED_EN   ((MSG_TYPE)"Server address not resolved yet")

#define KP_MSG_ERR_OK_EN            ((MSG_TYPE)"Operation ended successfully")
#define KP_MSG_INVALIDARG_EN        ((MSG_TYPE)"Invalid parameter")
#define KP_MSG_NOTIMPL_EN           ((MSG_TYPE)"Feature not implemented yet")
#define KP_MSG_UNEXPECTED_EN        ((MSG_TYPE)"Unexpected interface call") // Interface call result: Unexpected error
#define KP_MSG_FERROR_EN            ((MSG_TYPE)"File I/O error")
#define KP_MSG_SYSTEM_ERROR_EN      ((MSG_TYPE)"Internal error")
#define KP_MSG_EOF_EN               ((MSG_TYPE)"Unexpected end of input file")
#define KP_MSG_FILE_FORMAT_EN       ((MSG_TYPE)"Unexpected input file format")
#define KP_MSG_FILE_NOT_FOUND_EN    ((MSG_TYPE)"File not found")
#define KP_MSG_DIR_ERROR_EN         ((MSG_TYPE)"Unable to create file")
#define KP_MSG_OUTOFMEM_EN          ((MSG_TYPE)"Out of memory")
#define KP_MSG_NO_FILE_EN           ((MSG_TYPE)"No file open")
#define KP_MSG_DOUBLE_UNGET_EN      ((MSG_TYPE)"Double unget")
#define KP_MSG_UNKN_CHR_EN          ((MSG_TYPE)"Unknown character")
#define KP_MSG_COMMAND_ERROR_EN     ((MSG_TYPE)"External error")
#define KP_MSG_BUFFER_OVERFLOW_EN   ((MSG_TYPE)"Buffer overflow")
#define KP_MSG_FONT_UNDEF_EN        ((MSG_TYPE)"Font undefined")
#define KP_MSG_KWD_NOT_FOUND_EN     ((MSG_TYPE)"Keyword not found")
#define KP_MSG_UNKNOWN_SYSTEM_EN    ((MSG_TYPE)"Unknown OS version")
// #define KP_MSG_ILL_CODE_EN          ((MSG_TYPE)"Illegal registration code")
#define KP_MSG_ILL_CODE_EN          ((MSG_TYPE)"Illegal activation code")
#define KP_MSG_CANCELLED_EN         ((MSG_TYPE)"Job cancelled")
#define KP_MSG_DOUBLE_CALL_EN       ((MSG_TYPE)"Double call")
#define KP_MSG_TIMEOUT_EN           ((MSG_TYPE)"Timeout")
#define KP_MSG_OBJ_NOT_FOUND_EN     ((MSG_TYPE)"Object not found")
#define KP_MSG_NO_CONN_EN           ((MSG_TYPE)"No connection")

#define KP_MSG_TRANS_ERR_EN         ((MSG_TYPE)"Transfer error")
#define KP_MSG_TRANS_ERR_1_EN       ((MSG_TYPE)"Transfer error, repeat the download procedure, please")

// #define KP_MSG_REFUSED_EN           ((MSG_TYPE)"Registration refused")
#define KP_MSG_REFUSED_EN           ((MSG_TYPE)"Activation refused")
#define KP_MSG_ACCESS_DENIED_EN     ((MSG_TYPE)"Access denied")
#define KP_MSG_ILLEGAL_CHARACTER_EN ((MSG_TYPE)"Unexpected character")
#define KP_MSG_DIV_ZERO_EN          ((MSG_TYPE)"Division by zero")
#define KP_MSG_ILLMATHARG_EN        ((MSG_TYPE)"Illegal math argument")
#define KP_MSG_ILLFUNC_EN           ((MSG_TYPE)"Illegal function call")
                                    
// #define KP_MSG_NOTINST_EN        ((MSG_TYPE)"Program not yet installed or installation is damaged, repeat the installation procedure again, please")
#define KP_MSG_NOTINST_EN           ((MSG_TYPE)"Product not yet installed or its installation is damaged, repeat the installation procedure again, please")
#define KP_MSG_NOTINST_S_EN         ((MSG_TYPE)"Product �%s� not yet installed or its installation is damaged, repeat the installation procedure again, please")
#define KP_MSG_NOTINST_DELETE_EN    ((MSG_TYPE)"Product not yet installed or its installation is damaged. Delete the product and repeat the installation procedure again, please.")

#define KP_MSG_MSG_FORMAT_EN        ((MSG_TYPE)"Illegal message format")
#define KP_MSG_OBSOLETE_EN          ((MSG_TYPE)"Obsolete function call")

// #define KP_MSG_ERROR_HELP_EN     ((MSG_TYPE)".  Technical support by e-mail %s   For further information look file %s")
#define KP_MSG_ERROR_HELP_EN        ((MSG_TYPE)".  Ask for technical support by e-mail at address %s")
#define KP_MSG_ERROR_HELP_REST_EN   ((MSG_TYPE)"   Attach file %s from your desktop to the message.")

#define KP_MSG_WSAEACCES_EN         ((MSG_TYPE)"Permission denied")
#define KP_MSG_WSAEADDRINUSE_EN     ((MSG_TYPE)"Address already in use")
#define KP_MSG_WSAEADDRNOTAVAIL_EN  ((MSG_TYPE)"Cannot assign requested address")
#define KP_MSG_WSAEAFNOSUPPORT_EN   ((MSG_TYPE)"Address family not supported by protocol family")
#define KP_MSG_WSAEALREADY_EN       ((MSG_TYPE)"Operation already in progress")
#define KP_MSG_WSAECONNABORTED_EN   ((MSG_TYPE)"Software caused connection abort")
#define KP_MSG_WSAECONNREFUSED_EN   ((MSG_TYPE)"Connection refused")
#define KP_MSG_WSAECONNRESET_EN     ((MSG_TYPE)"Connection reset by peer")
#define KP_MSG_WSAEDESTADDRREQ_EN   ((MSG_TYPE)"Destination address required")
#define KP_MSG_WSAEFAULT_EN         ((MSG_TYPE)"Bad address")
#define KP_MSG_WSAEHOSTDOWN_EN      ((MSG_TYPE)"Host is down")
#define KP_MSG_WSAEHOSTUNREACH_EN   ((MSG_TYPE)"No route to host")
#define KP_MSG_WSAEINPROGRESS_EN    ((MSG_TYPE)"Operation now in progress")
#define KP_MSG_WSAEINTR_EN          ((MSG_TYPE)"Interrupted function call")
#define KP_MSG_WSAEINVAL_EN         ((MSG_TYPE)"Invalid argument")
#define KP_MSG_WSAEISCONN_EN        ((MSG_TYPE)"Socket is already connected")
#define KP_MSG_WSAEMFILE_EN         ((MSG_TYPE)"Too many open files")
#define KP_MSG_WSAEMSGSIZE_EN       ((MSG_TYPE)"Message too long")
#define KP_MSG_WSAENETDOWN_EN       ((MSG_TYPE)"Network is down")
#define KP_MSG_WSAENETRESET_EN      ((MSG_TYPE)"Network dropped connection on reset")
#define KP_MSG_WSAENETUNREACH_EN    ((MSG_TYPE)"Network is unreachable")
#define KP_MSG_WSAENOBUFS_EN        ((MSG_TYPE)"No buffer space available")
#define KP_MSG_WSAENOPROTOOPT_EN    ((MSG_TYPE)"Bad protocol option")
#define KP_MSG_WSAENOTCONN_EN       ((MSG_TYPE)"Socket is not connected")
#define KP_MSG_WSAENOTSOCK_EN       ((MSG_TYPE)"Socket operation on non-socket")
#define KP_MSG_WSAEOPNOTSUPP_EN     ((MSG_TYPE)"Operation not supported")
#define KP_MSG_WSAEPFNOSUPPORT_EN   ((MSG_TYPE)"Protocol family not supported")
#define KP_MSG_WSAEPROCLIM_EN             ((MSG_TYPE)"Too many processes")
#define KP_MSG_WSAEPROTONOSUPPORT_EN      ((MSG_TYPE)"Protocol not supported")
#define KP_MSG_WSAEPROTOTYPE_EN           ((MSG_TYPE)"Protocol wrong type for socket")
#define KP_MSG_WSAESHUTDOWN_EN            ((MSG_TYPE)"Cannot send after socket shutdown")
#define KP_MSG_WSAESOCKTNOSUPPORT_EN      ((MSG_TYPE)"Socket type not supported")
#define KP_MSG_WSAETIMEDOUT_EN            ((MSG_TYPE)"Connection timed out")
#define KP_MSG_WSATYPE_NOT_FOUND_EN       ((MSG_TYPE)"Class type not found")
#define KP_MSG_WSAEWOULDBLOCK_EN          ((MSG_TYPE)"Resource temporarily unavailable")
#define KP_MSG_WSAHOST_NOT_FOUND_EN       ((MSG_TYPE)"Host not found")
#define KP_MSG_WSA_INVALID_HANDLE_EN      ((MSG_TYPE)"Specified event object handle is invalid")
#define KP_MSG_WSA_INVALID_PARAMETER_EN   ((MSG_TYPE)"One or more parameters are invalid")
#define KP_MSG_WSAINVALIDPROCTABLE_EN     ((MSG_TYPE)"Invalid procedure table from service provider")
#define KP_MSG_WSAINVALIDPROVIDER_EN      ((MSG_TYPE)"Invalid service provider version number")
#define KP_MSG_WSA_IO_INCOMPLETE_EN       ((MSG_TYPE)"Overlapped I/O event object not in signaled state")
#define KP_MSG_WSA_IO_PENDING_EN          ((MSG_TYPE)"Overlapped operations will complete later")

#define KP_MSG_WSA_NOT_ENOUGH_MEMORY_EN   ((MSG_TYPE)"Insufficient memory available")
#define KP_MSG_WSANOTINITIALISED_EN       ((MSG_TYPE)"Successful WSAStartup not yet performed")
#define KP_MSG_WSANO_DATA_EN              ((MSG_TYPE)"Valid name, no data record of requested type")
#define KP_MSG_WSANO_RECOVERY_EN          ((MSG_TYPE)"this is a non-recoverable error")
#define KP_MSG_WSAPROVIDERFAILEDINIT_EN   ((MSG_TYPE)"Unable to initialize a service provider")
#define KP_MSG_WSASYSCALLFAILURE_EN       ((MSG_TYPE)"System call failure")
#define KP_MSG_WSASYSNOTREADY_EN          ((MSG_TYPE)"Network subsystem is unavailable")
#define KP_MSG_WSATRY_AGAIN_EN            ((MSG_TYPE)"Non-authoritative host not found")
#define KP_MSG_WSAVERNOTSUPPORTED_EN      ((MSG_TYPE)"WINSOCK.DLL version out of range")
#define KP_MSG_WSAEDISCON_EN              ((MSG_TYPE)"Graceful shutdown in progress")
#define KP_MSG_WSA_OPERATION_ABORTED_EN   ((MSG_TYPE)"Overlapped operation aborted")

#define KP_MSG_OUT_OF_MEM_RES_EN          ((MSG_TYPE)"The operating system is out of memory or resources")
#define KP_MSG_ERROR_FILE_NOT_FOUND_EN    ((MSG_TYPE)"The file specified was not found")
#define KP_MSG_ERROR_PATH_NOT_FOUND_EN    ((MSG_TYPE)"The path specified was not found")
#define KP_MSG_ERROR_BAD_FORMAT_EN        ((MSG_TYPE)"The .exe file is invalid (non-Win32(r) .exe or error in .exe image)")
#define KP_MSG_SE_ERR_ACCESSDENIED_EN     ((MSG_TYPE)"The operating system denied access to the specified file")
#define KP_MSG_SE_ERR_ASSOCINCOMPLETE_EN  ((MSG_TYPE)"The file name association is incomplete or invalid")
#define KP_MSG_SE_ERR_DDEBUSY_EN          ((MSG_TYPE)"The DDE transaction could not be completed because other DDE transactions were being processed")
#define KP_MSG_SE_ERR_DDEFAIL_EN          ((MSG_TYPE)"The DDE transaction failed")
#define KP_MSG_SE_ERR_DDETIMEOUT_EN       ((MSG_TYPE)"The DDE transaction could not be completed because the request timed out")
#define KP_MSG_SE_ERR_DLLNOTFOUND_EN      ((MSG_TYPE)"The specified dynamic-link library was not found")
#define KP_MSG_SE_ERR_FNF_EN              ((MSG_TYPE)"The specified file was not found")
#define KP_MSG_SE_ERR_NOASSOC_EN          ((MSG_TYPE)"There is no application associated with the given file name extension")
#define KP_MSG_SE_ERR_OOM_EN              ((MSG_TYPE)"There was not enough memory to complete the operation")
#define KP_MSG_SE_ERR_PNF_EN              ((MSG_TYPE)"The specified path was not found")
#define KP_MSG_SE_ERR_SHARE_EN            ((MSG_TYPE)"A sharing violation occurred")

#define KP_MSG_FIRST_TIME_ADMIN_EN        ((MSG_TYPE)"Starting the program first time administrator\n rights are necessary. Run the program again as privileged user.")
#define KP_MSG_NOW_NOT_ADMIN_EN           KP_MSG_NOT_ADMIN
#define KP_MSG_NOT_ADMIN_EN               ((MSG_TYPE)"Run the program again as ordinary user")
#define KP_MSG_COPY_FILE_ACCESS_DENIED_EN ((MSG_TYPE)"Unsuccessfull file copy operation, run the program again as privileged user")

#define KP_PROGRESS_TITLE_EN              ((MSG_TYPE)"Wait...")
#define KP_MSG_DELETING_FILE_EN           ((MSG_TYPE)"Deleting file %s.%s...")
#define KP_MSG_COPYING_EN                 ((MSG_TYPE)"Copying file...")
#define KP_MSG_COPYING_FILE_EN            ((MSG_TYPE)"Copying file %s.%s...")
#define KP_MSG_COPYING_DIR_EN             ((MSG_TYPE)"Copying folder %s.%s...")

#define KP_MSG_DOWNLOADING_EN             ((MSG_TYPE)"Downloading file...")
#define KP_MSG_DOWNLOADING_FILE_EN        ((MSG_TYPE)"Downloading file %s.%s...")

#define KP_MSG_NEG_ANSW_EN                ((MSG_TYPE)"Negative responce")

#define KP_MSG_UNABLE_TO_EXECUTE_EN       ((MSG_TYPE)"Unable to execute command %s - check installed components of the system")

#define KP_MSG_FLASH_PLAYER_INSTALL_EN    ((MSG_TYPE)"Macromedia Flash player will be installed. Follow setup instructions.")

#define KP_MSG_FILE_CHANGED_EN            ((MSG_TYPE)"File has been changed")

#define KP_MSG_ALL_FILES_EN               ((MSG_TYPE)"All files (*.*)") // "Visi failai (*.*)"
#define KP_MSG_SAVE_AS_EN                 ((MSG_TYPE)"Save As") // "�ra�yti kaip"

#define KP_MSG_FILE_EXISTS_EN             ((MSG_TYPE)"File %s already exists, overwrite?") // "Failas %s jau yra, perra�yti?"

#define KP_MSG_DIAG_MSG_EN                ((MSG_TYPE)"Error report preparation")
#define KP_MSG_DIAG_MSG_TITLE_EN          ((MSG_TYPE)"Error report")

#if FALSE
#define KP_MSG_DIAG_MSG_EXPL_EN           ((MSG_TYPE)"To send error report to the producer, fill following fields and press " \
                                                                  "button \"Continue\". The message about computer configuration, product " \
                                                                  "and the error will be sent by internet to the server of the product " \
                                                                  "manufacturer. If you will not be contacted in certain period of time, " \
                                                                  "ask for assistance by e-mail %s")
#endif
// #define KP_MSG_DIAG_MSG_EXPL_EN        ((MSG_TYPE)"In order to send error report to the producer, you could fill following fields.")
#define KP_MSG_DIAG_MSG_EXPL_EN           ((MSG_TYPE)"In case you have problems by using this produkt, you can send error report to the producer. Fill in following fields.")
#define KP_MSG_DIAG_MSG_EXPL1_EN          ((MSG_TYPE)"If you are agreed to send the error report, click the button �Send�, otherwise � �Cancel�.")
#define KP_MSG_DIAG_MSG_EXPL2_EN          ((MSG_TYPE)"In order to send error report to the producer, fill the field with your e-mail address and click the button �Send�.")

#define KP_MSG_DIAG_MSG_EMAIL_PROMPT_EN   ((MSG_TYPE)"Your e-mail address:")
#define KP_MSG_DIAG_MSG_COMMENTS_PROMPT_EN ((MSG_TYPE)"Your comments about circumstances when the error is appearing:")
#define KP_MSG_DIAG_MSG_FILE_PROMPT_EN    ((MSG_TYPE)"Additional file to send to the producer\n(copy of the display picture, for example):")

#define KP_MSG_BAD_EMAIL_ADDRESS_EN       ((MSG_TYPE)"E-mail address incorrect")

#define KP_MSG_DIAG_MSG_SEL_FILE_EN       ((MSG_TYPE)"Choose file to send")

#define KP_MSG_DIAG_MSG_SUCCEEDED_EN      ((MSG_TYPE)"Error report sent successfully")

#define KP_MSG_SIUSTI_EN                  ((MSG_TYPE)"Send")

#define KP_MSG_FIREWALL_EN                ((MSG_TYPE)"Access to the internet rejected. Check your firewall settings � try to add %s to the list of programs with allowed internet access.")

#define KP_MSG_POINTER_EN                 ((MSG_TYPE)"Bad pointer")

#define KP_MSG_LOG_STARTED_EN             ((MSG_TYPE)"Start logging to file %s")
#define KP_MSG_CONS_TITLE_EN              ((MSG_TYPE)"%s: Console")

#define KP_MSG_UNHANDLED_EXCEPTION_EN     ((MSG_TYPE)"Unhandled exception")

#define KP_MSG_DATA_FORMAT_EN			((MSG_TYPE)"Unrecognized data format")
#define KP_MSG_DBERROR_EN				((MSG_TYPE)"Database error")

#endif // #if ((MsgLang == KpLangEn_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangEn_p))

#endif // #ifndef KPMSG_EN_INCLUDED
