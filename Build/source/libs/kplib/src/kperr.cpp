/* -----------------------------------------------
 *
 * kperr.cpp
 *
 *    error processing, debug tools
 *
 * 2013-04-04  mp  initial creation
 *
 */

#include "envir.h"

#ifdef _MSC_VER
#define _WINSOCKAPI_ // kad neinkliudintų winsock.h – pjaunasi po to su ws2def.h (inkliudinamas iš WinSock2.h)
#endif

#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#ifdef __WIN32__
#include <windows.h>
#ifdef __MINGW32__
#include <ddk\ntapi.h>
#endif
#ifdef _MSC_VER
#include <WinSock2.h>
#endif
#endif

using namespace std;

#include "kperrno.h"
#include "kpstdlib.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kptree.h"
#include "kpmsg.h"
#include "kpmsg_en.h"
#if (MsgLang == KpLangLt_p) || (MsgLang == KpLangSel_p)
#   include "kpmsg_lt.h"
#endif
#if (MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_p)
#   include "kpmsg_pl_1250.h"
#endif
#if (MsgLang == KpLangPl_1257_p) || (MsgLang == KpLangPl_p)
#   include "kpmsg_pl_1257.h"
#endif
#if (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p) || (MsgLang == KpLangRu_p)
#   include "kpmsg_ru.h"
#endif
#include "kperr.h"
#include "kpstdio.h"
#include "kpsock.h"
#include "kpcapp.h"

using namespace std;


// ------------------------------------ bendri kp programų pranešimai
#if (__GNUC__ != 5) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 0)
const
#endif
    uchar *KpErrorClass::m_pszaKpMessages[NumOfKpMessages_25][KpNumOfLangs_2] =
{
    { KP_MSG_TITLE_EN,                    KP_MSG_TITLE_LT,                    KP_MSG_TITLE_PL_1250,                     KP_MSG_TITLE_PL_1257,                     KP_MSG_TITLE_RU,                    KP_MSG_TITLE_EN,                    }, // "Pranešimas"
    { KP_INPUT_TITLE_EN,                  KP_INPUT_TITLE_LT,                  KP_INPUT_TITLE_PL_1250,                   KP_INPUT_TITLE_PL_1257,                   KP_INPUT_TITLE_RU,                  KP_INPUT_TITLE_EN,                  }, // "Įvedimas"

    { KP_MSG_TAIP_EN,                     KP_MSG_TAIP_LT,                     KP_MSG_TAIP_PL_1250,                      KP_MSG_TAIP_PL_1257,                      KP_MSG_TAIP_RU,                     KP_MSG_TAIP_EN,                     }, // "Taip"
    { KP_MSG_YES_EN,                      KP_MSG_YES_LT,                      KP_MSG_YES_PL_1250,                       KP_MSG_YES_PL_1257,                       KP_MSG_YES_RU,                      KP_MSG_YES_EN,                      }, // KP_MSG_TAIP
    { KP_MSG_NE_EN,                       KP_MSG_NE_LT,                       KP_MSG_NE_PL_1250,                        KP_MSG_NE_PL_1257,                        KP_MSG_NE_RU,                       KP_MSG_NE_EN,                       }, // "Ne"
    { KP_MSG_NO_EN,                       KP_MSG_NO_LT,                       KP_MSG_NO_PL_1250,                        KP_MSG_NO_PL_1257,                        KP_MSG_NO_RU,                       KP_MSG_NO_EN,                       }, // KP_MSG_NE
    { KP_MSG_GERAI_EN,                    KP_MSG_GERAI_LT,                    KP_MSG_GERAI_PL_1250,                     KP_MSG_GERAI_PL_1257,                     KP_MSG_GERAI_RU,                    KP_MSG_GERAI_EN,                    }, // "Gerai"
    { KP_MSG_OK_EN,                       KP_MSG_OK_LT,                       KP_MSG_OK_PL_1250,                        KP_MSG_OK_PL_1257,                        KP_MSG_OK_RU,                       KP_MSG_OK_EN,                       }, // KP_MSG_GERAI
    { KP_MSG_ATSAUKTI_EN,                 KP_MSG_ATSAUKTI_LT,                 KP_MSG_ATSAUKTI_PL_1250,                  KP_MSG_ATSAUKTI_PL_1257,                  KP_MSG_ATSAUKTI_RU,                 KP_MSG_ATSAUKTI_EN,                 }, // "Atšaukti"
    { KP_MSG_CANCEL_EN,                   KP_MSG_CANCEL_LT,                   KP_MSG_CANCEL_PL_1250,                    KP_MSG_CANCEL_PL_1257,                    KP_MSG_CANCEL_RU,                   KP_MSG_CANCEL_EN,                   }, // KP_MSG_ATSAUKTI
    { KP_MSG_TESTI_EN,                    KP_MSG_TESTI_LT,                    KP_MSG_TESTI_PL_1250,                     KP_MSG_TESTI_PL_1257,                     KP_MSG_TESTI_RU,                    KP_MSG_TESTI_EN,                    }, // "Toliau"
    { KP_MSG_BAIGTI_EN,                   KP_MSG_BAIGTI_LT,                   KP_MSG_BAIGTI_PL_1250,                    KP_MSG_BAIGTI_PL_1257,                    KP_MSG_BAIGTI_RU,                   KP_MSG_BAIGTI_EN,                   }, // "Baigti"
    { KP_MSG_PAMIRSAU_SLAPTAZODI_EN,      KP_MSG_PAMIRSAU_SLAPTAZODI_LT,      KP_MSG_PAMIRSAU_SLAPTAZODI_PL_1250,       KP_MSG_PAMIRSAU_SLAPTAZODI_PL_1257,       KP_MSG_PAMIRSAU_SLAPTAZODI_RU,      KP_MSG_PAMIRSAU_SLAPTAZODI_EN,      }, // "Pamiršau slaptažodį"

    { KP_MSG_ERROR_EN,                    KP_MSG_ERROR_LT,                    KP_MSG_ERROR_PL_1250,                     KP_MSG_ERROR_PL_1257,                     KP_MSG_ERROR_RU,                    KP_MSG_ERROR_RU,                    }, // "Klaida"
    { KP_MSG_WARNING_EN,                  KP_MSG_WARNING_LT,                  KP_MSG_WARNING_PL_1250,                   KP_MSG_WARNING_PL_1257,                   KP_MSG_WARNING_RU,                  KP_MSG_WARNING_RU,                  }, // "Perspėjimas"
    { KP_MSG_FILE_LINE_EN,                KP_MSG_FILE_LINE_LT,                KP_MSG_FILE_LINE_PL_1250,                 KP_MSG_FILE_LINE_PL_1257,                 KP_MSG_FILE_LINE_RU,                KP_MSG_FILE_LINE_RU,                }, // ", failas:%s, eilutė:%d"
    { KP_MSG_ENTRY_ID_EN,                 KP_MSG_ENTRY_ID_LT,                 KP_MSG_ENTRY_ID_PL_1250,                  KP_MSG_ENTRY_ID_PL_1257,                  KP_MSG_ENTRY_ID_RU,                 KP_MSG_ENTRY_ID_RU,                 }, // ", Įrašo nr.:%ld"
    { KP_MSG_ENTRY_EN,                    KP_MSG_ENTRY_LT,                    KP_MSG_ENTRY_PL_1250,                     KP_MSG_ENTRY_PL_1257,                     KP_MSG_ENTRY_RU,                    KP_MSG_ENTRY_RU,                    }, // ", Įrašas: %s"

    { KP_MSG_NO_STANDARD_PROG_EN,         KP_MSG_NO_STANDARD_PROG_LT,         KP_MSG_NO_STANDARD_PROG_PL_1250,          KP_MSG_NO_STANDARD_PROG_PL_1257,          KP_MSG_NO_STANDARD_PROG_RU,         KP_MSG_NO_STANDARD_PROG_RU,         }, // "Nerasta programa skirta atverti šio tipo failus"
    { KP_MSG_WND_NOT_FOUND_EN,            KP_MSG_WND_NOT_FOUND_LT,            KP_MSG_WND_NOT_FOUND_PL_1250,             KP_MSG_WND_NOT_FOUND_PL_1257,             KP_MSG_WND_NOT_FOUND_RU,            KP_MSG_WND_NOT_FOUND_RU,            }, // "Langas nerastas"
    { KP_MSG_PID_NOT_FOUND_EN,            KP_MSG_PID_NOT_FOUND_LT,            KP_MSG_PID_NOT_FOUND_PL_1250,             KP_MSG_PID_NOT_FOUND_PL_1257,             KP_MSG_PID_NOT_FOUND_RU,            KP_MSG_PID_NOT_FOUND_RU,            }, // "Nerastas proceso identifikatorius"
    { KP_MSG_NO_SOCKET_EN,                KP_MSG_NO_SOCKET_LT,                KP_MSG_NO_SOCKET_PL_1250,                 KP_MSG_NO_SOCKET_PL_1257,                 KP_MSG_NO_SOCKET_RU,                KP_MSG_NO_SOCKET_RU,                }, // "Jungtis dar nesukurta"
    { KP_MSG_SOCK_UNRESOLVED_EN,          KP_MSG_SOCK_UNRESOLVED_LT,          KP_MSG_SOCK_UNRESOLVED_PL_1250,           KP_MSG_SOCK_UNRESOLVED_PL_1257,           KP_MSG_SOCK_UNRESOLVED_RU,          KP_MSG_SOCK_UNRESOLVED_RU,          }, // "Tarnybinės stoties adresas dar nesurastas"

    { KP_MSG_ERR_OK_EN,                   KP_MSG_ERR_OK_LT,                   KP_MSG_ERR_OK_PL_1250,                    KP_MSG_ERR_OK_PL_1257,                    KP_MSG_ERR_OK_RU,                   KP_MSG_ERR_OK_RU,                   }, // "Operacija atlikta sėkmingai" // !!!
    { KP_MSG_INVALIDARG_EN,               KP_MSG_INVALIDARG_LT,               KP_MSG_INVALIDARG_PL_1250,                KP_MSG_INVALIDARG_PL_1257,                KP_MSG_INVALIDARG_RU,               KP_MSG_INVALIDARG_RU,               }, // "Neteisingi parametrai"
    { KP_MSG_NOTIMPL_EN,                  KP_MSG_NOTIMPL_LT,                  KP_MSG_NOTIMPL_PL_1250,                   KP_MSG_NOTIMPL_PL_1257,                   KP_MSG_NOTIMPL_RU,                  KP_MSG_NOTIMPL_RU,                  }, // "Priedas neįdiegtas"
    { KP_MSG_UNEXPECTED_EN,               KP_MSG_UNEXPECTED_LT,               KP_MSG_UNEXPECTED_PL_1250,                KP_MSG_UNEXPECTED_PL_1257,                KP_MSG_UNEXPECTED_RU,               KP_MSG_UNEXPECTED_RU,               }, // "Netikėtas kreipinys į sąsają"
    { KP_MSG_FERROR_EN,                   KP_MSG_FERROR_LT,                   KP_MSG_FERROR_PL_1250,                    KP_MSG_FERROR_PL_1257,                    KP_MSG_FERROR_RU,                   KP_MSG_FERROR_RU,                   }, // "Failo skaitymo/rašymo klaida"
    { KP_MSG_SYSTEM_ERROR_EN,             KP_MSG_SYSTEM_ERROR_LT,             KP_MSG_SYSTEM_ERROR_PL_1250,              KP_MSG_SYSTEM_ERROR_PL_1257,              KP_MSG_SYSTEM_ERROR_RU,             KP_MSG_SYSTEM_ERROR_RU,             }, // "Klaida sistemoje"
    { KP_MSG_EOF_EN,                      KP_MSG_EOF_LT,                      KP_MSG_EOF_PL_1250,                       KP_MSG_EOF_PL_1257,                       KP_MSG_EOF_RU,                      KP_MSG_EOF_RU,                      }, // "Neteisinga failo pabaiga"
    { KP_MSG_FILE_FORMAT_EN,              KP_MSG_FILE_FORMAT_LT,              KP_MSG_FILE_FORMAT_PL_1250,               KP_MSG_FILE_FORMAT_PL_1257,               KP_MSG_FILE_FORMAT_RU,              KP_MSG_FILE_FORMAT_RU,              }, // "Neteisingas failo formatas"
    { KP_MSG_FILE_NOT_FOUND_EN,           KP_MSG_FILE_NOT_FOUND_LT,           KP_MSG_FILE_NOT_FOUND_PL_1250,            KP_MSG_FILE_NOT_FOUND_PL_1257,            KP_MSG_FILE_NOT_FOUND_RU,           KP_MSG_FILE_NOT_FOUND_RU,           }, // "Failas nerastas"
    { KP_MSG_DIR_ERROR_EN,                KP_MSG_DIR_ERROR_LT,                KP_MSG_DIR_ERROR_PL_1250,                 KP_MSG_DIR_ERROR_PL_1257,                 KP_MSG_DIR_ERROR_RU,                KP_MSG_DIR_ERROR_RU,                }, // "Nepavyko atverti/sukurti failo"
    { KP_MSG_OUTOFMEM_EN,                 KP_MSG_OUTOFMEM_LT,                 KP_MSG_OUTOFMEM_PL_1250,                  KP_MSG_OUTOFMEM_PL_1257,                  KP_MSG_OUTOFMEM_RU,                 KP_MSG_OUTOFMEM_RU,                 }, // "Trūksta atminties"
    { KP_MSG_NO_FILE_EN,                  KP_MSG_NO_FILE_LT,                  KP_MSG_NO_FILE_PL_1250,                   KP_MSG_NO_FILE_PL_1257,                   KP_MSG_NO_FILE_RU,                  KP_MSG_NO_FILE_RU,                  }, // "Failas neatvertas"
    { KP_MSG_DOUBLE_UNGET_EN,             KP_MSG_DOUBLE_UNGET_LT,             KP_MSG_DOUBLE_UNGET_PL_1250,              KP_MSG_DOUBLE_UNGET_PL_1257,              KP_MSG_DOUBLE_UNGET_RU,             KP_MSG_DOUBLE_UNGET_RU,             }, // "Dvigubas įvedimo grąžinimas"
    { KP_MSG_UNKN_CHR_EN,                 KP_MSG_UNKN_CHR_LT,                 KP_MSG_UNKN_CHR_PL_1250,                  KP_MSG_UNKN_CHR_PL_1257,                  KP_MSG_UNKN_CHR_RU,                 KP_MSG_UNKN_CHR_RU,                 }, // "Neatpažintas simbolis"
    { KP_MSG_COMMAND_ERROR_EN,            KP_MSG_COMMAND_ERROR_LT,            KP_MSG_COMMAND_ERROR_PL_1250,             KP_MSG_COMMAND_ERROR_PL_1257,             KP_MSG_COMMAND_ERROR_RU,            KP_MSG_COMMAND_ERROR_RU,            }, // "Išorinė klaida"
    { KP_MSG_BUFFER_OVERFLOW_EN,          KP_MSG_BUFFER_OVERFLOW_LT,          KP_MSG_BUFFER_OVERFLOW_PL_1250,           KP_MSG_BUFFER_OVERFLOW_PL_1257,           KP_MSG_BUFFER_OVERFLOW_RU,          KP_MSG_BUFFER_OVERFLOW_RU,          }, // "Persipildė buferis"
    { KP_MSG_FONT_UNDEF_EN,               KP_MSG_FONT_UNDEF_LT,               KP_MSG_FONT_UNDEF_PL_1250,                KP_MSG_FONT_UNDEF_PL_1257,                KP_MSG_FONT_UNDEF_RU,               KP_MSG_FONT_UNDEF_RU,               }, // "Neapibrėžtas šriftas"
    { KP_MSG_KWD_NOT_FOUND_EN,            KP_MSG_KWD_NOT_FOUND_LT,            KP_MSG_KWD_NOT_FOUND_PL_1250,             KP_MSG_KWD_NOT_FOUND_PL_1257,             KP_MSG_KWD_NOT_FOUND_RU,            KP_MSG_KWD_NOT_FOUND_RU,            }, // "Raktinis žodis nerastas"
    { KP_MSG_UNKNOWN_SYSTEM_EN,           KP_MSG_UNKNOWN_SYSTEM_LT,           KP_MSG_UNKNOWN_SYSTEM_PL_1250,            KP_MSG_UNKNOWN_SYSTEM_PL_1257,            KP_MSG_UNKNOWN_SYSTEM_RU,           KP_MSG_UNKNOWN_SYSTEM_RU,           }, // "Operacinė sistema neatpažinta"
    { KP_MSG_ILL_CODE_EN,                 KP_MSG_ILL_CODE_LT,                 KP_MSG_ILL_CODE_PL_1250,                  KP_MSG_ILL_CODE_PL_1257,                  KP_MSG_ILL_CODE_RU,                 KP_MSG_ILL_CODE_RU,                 }, // "Klaidingas registracijos kodas"
    { KP_MSG_CANCELLED_EN,                KP_MSG_CANCELLED_LT,                KP_MSG_CANCELLED_PL_1250,                 KP_MSG_CANCELLED_PL_1257,                 KP_MSG_CANCELLED_RU,                KP_MSG_CANCELLED_RU,                }, // "Operacija nutraukta"
    { KP_MSG_DOUBLE_CALL_EN,              KP_MSG_DOUBLE_CALL_LT,              KP_MSG_DOUBLE_CALL_PL_1250,               KP_MSG_DOUBLE_CALL_PL_1257,               KP_MSG_DOUBLE_CALL_RU,              KP_MSG_DOUBLE_CALL_RU,              }, // "Dvigubas iškvietimas"
    { KP_MSG_TIMEOUT_EN,                  KP_MSG_TIMEOUT_LT,                  KP_MSG_TIMEOUT_PL_1250,                   KP_MSG_TIMEOUT_PL_1257,                   KP_MSG_TIMEOUT_RU,                  KP_MSG_TIMEOUT_RU,                  }, // "Viršytas laukimo laikas"
    { KP_MSG_OBJ_NOT_FOUND_EN,            KP_MSG_OBJ_NOT_FOUND_LT,            KP_MSG_OBJ_NOT_FOUND_PL_1250,             KP_MSG_OBJ_NOT_FOUND_PL_1257,             KP_MSG_OBJ_NOT_FOUND_RU,            KP_MSG_OBJ_NOT_FOUND_RU,            }, // "Objektas nerastas"
    { KP_MSG_NO_CONN_EN,                  KP_MSG_NO_CONN_LT,                  KP_MSG_NO_CONN_PL_1250,                   KP_MSG_NO_CONN_PL_1257,                   KP_MSG_NO_CONN_RU,                  KP_MSG_NO_CONN_RU,                  }, // "Nėra ryšio"

    { KP_MSG_TRANS_ERR_EN,                KP_MSG_TRANS_ERR_LT,                KP_MSG_TRANS_ERR_PL_1250,                 KP_MSG_TRANS_ERR_PL_1257,                 KP_MSG_TRANS_ERR_RU,                KP_MSG_TRANS_ERR_RU,                }, // "Perdavimo klaida"
    { KP_MSG_TRANS_ERR_1_EN,              KP_MSG_TRANS_ERR_1_LT,              KP_MSG_TRANS_ERR_1_PL_1250,               KP_MSG_TRANS_ERR_1_PL_1257,               KP_MSG_TRANS_ERR_1_RU,              KP_MSG_TRANS_ERR_1_RU,              }, // "Ryšio klaida, pakartokite siuntimo procedūrą"

    { KP_MSG_REFUSED_EN,                  KP_MSG_REFUSED_LT,                  KP_MSG_REFUSED_PL_1250,                   KP_MSG_REFUSED_PL_1257,                   KP_MSG_REFUSED_RU,                  KP_MSG_REFUSED_RU,                  }, // "Registracija atmesta"
    { KP_MSG_ACCESS_DENIED_EN,            KP_MSG_ACCESS_DENIED_LT,            KP_MSG_ACCESS_DENIED_PL_1250,             KP_MSG_ACCESS_DENIED_PL_1257,             KP_MSG_ACCESS_DENIED_RU,            KP_MSG_ACCESS_DENIED_RU,            }, // "Neleista prisijungti"
    { KP_MSG_ILLEGAL_CHARACTER_EN,        KP_MSG_ILLEGAL_CHARACTER_LT,        KP_MSG_ILLEGAL_CHARACTER_PL_1250,         KP_MSG_ILLEGAL_CHARACTER_PL_1257,         KP_MSG_ILLEGAL_CHARACTER_RU,        KP_MSG_ILLEGAL_CHARACTER_RU,        }, // "Neleistinas simbolis"
    { KP_MSG_DIV_ZERO_EN,                 KP_MSG_DIV_ZERO_LT,                 KP_MSG_DIV_ZERO_PL_1250,                  KP_MSG_DIV_ZERO_PL_1257,                  KP_MSG_DIV_ZERO_RU,                 KP_MSG_DIV_ZERO_RU,                 }, // "Dalyba iš nulio"
    { KP_MSG_ILLMATHARG_EN,               KP_MSG_ILLMATHARG_LT,               KP_MSG_ILLMATHARG_PL_1250,                KP_MSG_ILLMATHARG_PL_1257,                KP_MSG_ILLMATHARG_RU,               KP_MSG_ILLMATHARG_RU,               }, // "Neleistinas matematinės funkcijos argumentas" // "Šaknis iš neigiamo skaičiaus"
    { KP_MSG_ILLFUNC_EN,                  KP_MSG_ILLFUNC_LT,                  KP_MSG_ILLFUNC_PL_1250,                   KP_MSG_ILLFUNC_PL_1257,                   KP_MSG_ILLFUNC_RU,                  KP_MSG_ILLFUNC_RU,                  }, // "Neleistina operacija" // illegal function call (at the moment)

    { KP_MSG_NOTINST_EN,                  KP_MSG_NOTINST_LT,                  KP_MSG_NOTINST_PL_1250,                   KP_MSG_NOTINST_PL_1257,                   KP_MSG_NOTINST_RU,                  KP_MSG_NOTINST_RU,                  }, // "Programa neįdiegta arba diegimas sugedo, pakartokite diegimo procedūrą"
    { KP_MSG_NOTINST_S_EN,                KP_MSG_NOTINST_S_LT,                KP_MSG_NOTINST_S_PL_1250,                 KP_MSG_NOTINST_S_PL_1257,                 KP_MSG_NOTINST_S_RU,                KP_MSG_NOTINST_S_RU,                }, // "Produktas „%s“ neįdiegtas arba jo diegimas sugedo, pakartokite diegimo procedūrą"
    { KP_MSG_NOTINST_DELETE_EN,           KP_MSG_NOTINST_DELETE_LT,           KP_MSG_NOTINST_DELETE_PL_1250,            KP_MSG_NOTINST_DELETE_PL_1257,            KP_MSG_NOTINST_DELETE_RU,           KP_MSG_NOTINST_DELETE_RU,           }, // "Produktas neįdiegtas arba jo diegimas sugedo, produktą panaikinkite ir pakartokite diegimo procedūrą"

    { KP_MSG_MSG_FORMAT_EN,               KP_MSG_MSG_FORMAT_LT,               KP_MSG_MSG_FORMAT_PL_1250,                KP_MSG_MSG_FORMAT_PL_1257,                KP_MSG_MSG_FORMAT_RU,               KP_MSG_MSG_FORMAT_RU,               }, // "Neteisingas pranešimo formatas"
    { KP_MSG_OBSOLETE_EN,                 KP_MSG_OBSOLETE_LT,                 KP_MSG_OBSOLETE_PL_1250,                  KP_MSG_OBSOLETE_PL_1257,                  KP_MSG_OBSOLETE_RU,                 KP_MSG_OBSOLETE_RU,                 }, // "Pasenusi funkcija"
    { KP_MSG_ERROR_HELP_EN,               KP_MSG_ERROR_HELP_LT,               KP_MSG_ERROR_HELP_PL_1250,                KP_MSG_ERROR_HELP_PL_1257,                KP_MSG_ERROR_HELP_RU,               KP_MSG_ERROR_HELP_RU,               }, // ".  Dėl techninės pagalbos kreipkitės elektroniniu paštu, adresu %s"
    { KP_MSG_ERROR_HELP_REST_EN,          KP_MSG_ERROR_HELP_REST_LT,          KP_MSG_ERROR_HELP_REST_PL_1250,           KP_MSG_ERROR_HELP_REST_PL_1257,           KP_MSG_ERROR_HELP_REST_RU,          KP_MSG_ERROR_HELP_REST_RU,          }, // "   Prie laiško prikabinkite failą %s"
    { KP_MSG_WSAEACCES_EN,                KP_MSG_WSAEACCES_LT,                KP_MSG_WSAEACCES_PL_1250,                 KP_MSG_WSAEACCES_PL_1257,                 KP_MSG_WSAEACCES_RU,                KP_MSG_WSAEACCES_RU,                }, // "Teisės nesuteiktos"
    { KP_MSG_WSAEADDRINUSE_EN,            KP_MSG_WSAEADDRINUSE_LT,            KP_MSG_WSAEADDRINUSE_PL_1250,             KP_MSG_WSAEADDRINUSE_PL_1257,             KP_MSG_WSAEADDRINUSE_RU,            KP_MSG_WSAEADDRINUSE_RU,            }, // "Adresas jau naudojamas"
    { KP_MSG_WSAEADDRNOTAVAIL_EN,         KP_MSG_WSAEADDRNOTAVAIL_LT,         KP_MSG_WSAEADDRNOTAVAIL_PL_1250,          KP_MSG_WSAEADDRNOTAVAIL_PL_1257,          KP_MSG_WSAEADDRNOTAVAIL_RU,         KP_MSG_WSAEADDRNOTAVAIL_RU,         }, // "Prašomas adresas negali būti priskirtas"
    { KP_MSG_WSAEAFNOSUPPORT_EN,          KP_MSG_WSAEAFNOSUPPORT_LT,          KP_MSG_WSAEAFNOSUPPORT_PL_1250,           KP_MSG_WSAEAFNOSUPPORT_PL_1257,           KP_MSG_WSAEAFNOSUPPORT_RU,          KP_MSG_WSAEAFNOSUPPORT_RU,          }, // "Adresų šeimos grupė nepalaikoma protokolo"
    { KP_MSG_WSAEALREADY_EN,              KP_MSG_WSAEALREADY_LT,              KP_MSG_WSAEALREADY_PL_1250,               KP_MSG_WSAEALREADY_PL_1257,               KP_MSG_WSAEALREADY_RU,              KP_MSG_WSAEALREADY_RU,              }, // "Operacija jau vykdoma"
    { KP_MSG_WSAECONNABORTED_EN,          KP_MSG_WSAECONNABORTED_LT,          KP_MSG_WSAECONNABORTED_PL_1250,           KP_MSG_WSAECONNABORTED_PL_1257,           KP_MSG_WSAECONNABORTED_RU,          KP_MSG_WSAECONNABORTED_RU,          }, // "Programa iššaukė ryšio nutraukimą"
    { KP_MSG_WSAECONNREFUSED_EN,          KP_MSG_WSAECONNREFUSED_LT,          KP_MSG_WSAECONNREFUSED_PL_1250,           KP_MSG_WSAECONNREFUSED_PL_1257,           KP_MSG_WSAECONNREFUSED_RU,          KP_MSG_WSAECONNREFUSED_RU,          }, // "Susijungimas atmestas"
    { KP_MSG_WSAECONNRESET_EN,            KP_MSG_WSAECONNRESET_LT,            KP_MSG_WSAECONNRESET_PL_1250,             KP_MSG_WSAECONNRESET_PL_1257,             KP_MSG_WSAECONNRESET_RU,            KP_MSG_WSAECONNRESET_RU,            }, // "Sujungimas nutrauktas"
    { KP_MSG_WSAEDESTADDRREQ_EN,          KP_MSG_WSAEDESTADDRREQ_LT,          KP_MSG_WSAEDESTADDRREQ_PL_1250,           KP_MSG_WSAEDESTADDRREQ_PL_1257,           KP_MSG_WSAEDESTADDRREQ_RU,          KP_MSG_WSAEDESTADDRREQ_RU,          }, // "Būtinas kreipties adresas"
    { KP_MSG_WSAEFAULT_EN,                KP_MSG_WSAEFAULT_LT,                KP_MSG_WSAEFAULT_PL_1250,                 KP_MSG_WSAEFAULT_PL_1257,                 KP_MSG_WSAEFAULT_RU,                KP_MSG_WSAEFAULT_RU,                }, // "Neteisingas adresas"
    { KP_MSG_WSAEHOSTDOWN_EN,             KP_MSG_WSAEHOSTDOWN_LT,             KP_MSG_WSAEHOSTDOWN_PL_1250,              KP_MSG_WSAEHOSTDOWN_PL_1257,              KP_MSG_WSAEHOSTDOWN_RU,             KP_MSG_WSAEHOSTDOWN_RU,             }, // "Serveris laikinai neveikia"
    { KP_MSG_WSAEHOSTUNREACH_EN,          KP_MSG_WSAEHOSTUNREACH_LT,          KP_MSG_WSAEHOSTUNREACH_PL_1250,           KP_MSG_WSAEHOSTUNREACH_PL_1257,           KP_MSG_WSAEHOSTUNREACH_RU,          KP_MSG_WSAEHOSTUNREACH_RU,          }, // "Serveris nepasiekiamas"
    { KP_MSG_WSAEINPROGRESS_EN,           KP_MSG_WSAEINPROGRESS_LT,           KP_MSG_WSAEINPROGRESS_PL_1250,            KP_MSG_WSAEINPROGRESS_PL_1257,            KP_MSG_WSAEINPROGRESS_RU,           KP_MSG_WSAEINPROGRESS_RU,           }, // "Operacija vykdoma"
    { KP_MSG_WSAEINTR_EN,                 KP_MSG_WSAEINTR_LT,                 KP_MSG_WSAEINTR_PL_1250,                  KP_MSG_WSAEINTR_PL_1257,                  KP_MSG_WSAEINTR_RU,                 KP_MSG_WSAEINTR_RU,                 }, // "Funkcija nutraukta"
    { KP_MSG_WSAEINVAL_EN,                KP_MSG_WSAEINVAL_LT,                KP_MSG_WSAEINVAL_PL_1250,                 KP_MSG_WSAEINVAL_PL_1257,                 KP_MSG_WSAEINVAL_RU,                KP_MSG_WSAEINVAL_RU,                }, // "Neteisingi parametrai"
    { KP_MSG_WSAEISCONN_EN,               KP_MSG_WSAEISCONN_LT,               KP_MSG_WSAEISCONN_PL_1250,                KP_MSG_WSAEISCONN_PL_1257,                KP_MSG_WSAEISCONN_RU,               KP_MSG_WSAEISCONN_RU,               }, // "Susijungimas jau įvykęs"
    { KP_MSG_WSAEMFILE_EN,                KP_MSG_WSAEMFILE_LT,                KP_MSG_WSAEMFILE_PL_1250,                 KP_MSG_WSAEMFILE_PL_1257,                 KP_MSG_WSAEMFILE_RU,                KP_MSG_WSAEMFILE_RU,                }, // "Perdaug atvertų failų"
    { KP_MSG_WSAEMSGSIZE_EN,              KP_MSG_WSAEMSGSIZE_LT,              KP_MSG_WSAEMSGSIZE_PL_1250,               KP_MSG_WSAEMSGSIZE_PL_1257,               KP_MSG_WSAEMSGSIZE_RU,              KP_MSG_WSAEMSGSIZE_RU,              }, // "Perdaug ilgas pranešimas"
    { KP_MSG_WSAENETDOWN_EN,              KP_MSG_WSAENETDOWN_LT,              KP_MSG_WSAENETDOWN_PL_1250,               KP_MSG_WSAENETDOWN_PL_1257,               KP_MSG_WSAENETDOWN_RU,              KP_MSG_WSAENETDOWN_RU,              }, // "Tinklas neveikia"
    { KP_MSG_WSAENETRESET_EN,             KP_MSG_WSAENETRESET_LT,             KP_MSG_WSAENETRESET_PL_1250,              KP_MSG_WSAENETRESET_PL_1257,              KP_MSG_WSAENETRESET_RU,             KP_MSG_WSAENETRESET_RU,             }, // "Atsijungė nuo tinklo"
    { KP_MSG_WSAENETUNREACH_EN,           KP_MSG_WSAENETUNREACH_LT,           KP_MSG_WSAENETUNREACH_PL_1250,            KP_MSG_WSAENETUNREACH_PL_1257,            KP_MSG_WSAENETUNREACH_RU,           KP_MSG_WSAENETUNREACH_RU,           }, // "Tinklas nepasiekiamas"
    { KP_MSG_WSAENOBUFS_EN,               KP_MSG_WSAENOBUFS_LT,               KP_MSG_WSAENOBUFS_PL_1250,                KP_MSG_WSAENOBUFS_PL_1257,                KP_MSG_WSAENOBUFS_RU,               KP_MSG_WSAENOBUFS_RU,               }, // "Trūksta vietos buferyje"
    { KP_MSG_WSAENOPROTOOPT_EN,           KP_MSG_WSAENOPROTOOPT_LT,           KP_MSG_WSAENOPROTOOPT_PL_1250,            KP_MSG_WSAENOPROTOOPT_PL_1257,            KP_MSG_WSAENOPROTOOPT_RU,           KP_MSG_WSAENOPROTOOPT_RU,           }, // "Neteisinga protokolo parinktis"
    { KP_MSG_WSAENOTCONN_EN,              KP_MSG_WSAENOTCONN_LT,              KP_MSG_WSAENOTCONN_PL_1250,               KP_MSG_WSAENOTCONN_PL_1257,               KP_MSG_WSAENOTCONN_RU,              KP_MSG_WSAENOTCONN_RU,              }, // "Sujungimas nepavyko"
    { KP_MSG_WSAENOTSOCK_EN,              KP_MSG_WSAENOTSOCK_LT,              KP_MSG_WSAENOTSOCK_PL_1250,               KP_MSG_WSAENOTSOCK_PL_1257,               KP_MSG_WSAENOTSOCK_RU,              KP_MSG_WSAENOTSOCK_RU,              }, // "Socket operation on non-socket"
    { KP_MSG_WSAEOPNOTSUPP_EN,            KP_MSG_WSAEOPNOTSUPP_LT,            KP_MSG_WSAEOPNOTSUPP_PL_1250,             KP_MSG_WSAEOPNOTSUPP_PL_1257,             KP_MSG_WSAEOPNOTSUPP_RU,            KP_MSG_WSAEOPNOTSUPP_RU,            }, // "Operacija negali būti atlikta"
    { KP_MSG_WSAEPFNOSUPPORT_EN,          KP_MSG_WSAEPFNOSUPPORT_LT,          KP_MSG_WSAEPFNOSUPPORT_PL_1250,           KP_MSG_WSAEPFNOSUPPORT_PL_1257,           KP_MSG_WSAEPFNOSUPPORT_RU,          KP_MSG_WSAEPFNOSUPPORT_RU,          }, // "Protokolo šeima nepalaikoma"
    { KP_MSG_WSAEPROCLIM_EN,              KP_MSG_WSAEPROCLIM_LT,              KP_MSG_WSAEPROCLIM_PL_1250,               KP_MSG_WSAEPROCLIM_PL_1257,               KP_MSG_WSAEPROCLIM_RU,              KP_MSG_WSAEPROCLIM_RU,              }, // "Perdaug procesų"
    { KP_MSG_WSAEPROTONOSUPPORT_EN,       KP_MSG_WSAEPROTONOSUPPORT_LT,       KP_MSG_WSAEPROTONOSUPPORT_PL_1250,        KP_MSG_WSAEPROTONOSUPPORT_PL_1257,        KP_MSG_WSAEPROTONOSUPPORT_RU,       KP_MSG_WSAEPROTONOSUPPORT_RU,       }, // "Protokolas nepalaikomas"
    { KP_MSG_WSAEPROTOTYPE_EN,            KP_MSG_WSAEPROTOTYPE_LT,            KP_MSG_WSAEPROTOTYPE_PL_1250,             KP_MSG_WSAEPROTOTYPE_PL_1257,             KP_MSG_WSAEPROTOTYPE_RU,            KP_MSG_WSAEPROTOTYPE_RU,            }, // "Neteisingas protokolo sujungimo tipas"
    { KP_MSG_WSAESHUTDOWN_EN,             KP_MSG_WSAESHUTDOWN_LT,             KP_MSG_WSAESHUTDOWN_PL_1250,              KP_MSG_WSAESHUTDOWN_PL_1257,              KP_MSG_WSAESHUTDOWN_RU,             KP_MSG_WSAESHUTDOWN_RU,             }, // "Siuntimas nebegalimas, sujungimas nutrauktas"
    { KP_MSG_WSAESOCKTNOSUPPORT_EN,       KP_MSG_WSAESOCKTNOSUPPORT_LT,       KP_MSG_WSAESOCKTNOSUPPORT_PL_1250,        KP_MSG_WSAESOCKTNOSUPPORT_PL_1257,        KP_MSG_WSAESOCKTNOSUPPORT_RU,       KP_MSG_WSAESOCKTNOSUPPORT_RU,       }, // "Sujungimo tipas nepalaikomas"
    { KP_MSG_WSAETIMEDOUT_EN,             KP_MSG_WSAETIMEDOUT_LT,             KP_MSG_WSAETIMEDOUT_PL_1250,              KP_MSG_WSAETIMEDOUT_PL_1257,              KP_MSG_WSAETIMEDOUT_RU,             KP_MSG_WSAETIMEDOUT_RU,             }, // "Viršytas maksimalus sujungimo laukimo laikas"
    { KP_MSG_WSATYPE_NOT_FOUND_EN,        KP_MSG_WSATYPE_NOT_FOUND_LT,        KP_MSG_WSATYPE_NOT_FOUND_PL_1250,         KP_MSG_WSATYPE_NOT_FOUND_PL_1257,         KP_MSG_WSATYPE_NOT_FOUND_RU,        KP_MSG_WSATYPE_NOT_FOUND_RU,        }, // "Klasės tipas nerastas"
    { KP_MSG_WSAEWOULDBLOCK_EN,           KP_MSG_WSAEWOULDBLOCK_LT,           KP_MSG_WSAEWOULDBLOCK_PL_1250,            KP_MSG_WSAEWOULDBLOCK_PL_1257,            KP_MSG_WSAEWOULDBLOCK_RU,           KP_MSG_WSAEWOULDBLOCK_RU,           }, // "Šaltinis laikinai nepasiekiamas"
    { KP_MSG_WSAHOST_NOT_FOUND_EN,        KP_MSG_WSAHOST_NOT_FOUND_LT,        KP_MSG_WSAHOST_NOT_FOUND_PL_1250,         KP_MSG_WSAHOST_NOT_FOUND_PL_1257,         KP_MSG_WSAHOST_NOT_FOUND_RU,        KP_MSG_WSAHOST_NOT_FOUND_RU,        }, // "Serveris nerastas"
    { KP_MSG_WSA_INVALID_HANDLE_EN,       KP_MSG_WSA_INVALID_HANDLE_LT,       KP_MSG_WSA_INVALID_HANDLE_PL_1250,        KP_MSG_WSA_INVALID_HANDLE_PL_1257,        KP_MSG_WSA_INVALID_HANDLE_RU,       KP_MSG_WSA_INVALID_HANDLE_RU,       }, // "Klaidingas objekto valdiklis" // "Klaidingas pasirinkto įvykio objekto valdiklis"
    { KP_MSG_WSA_INVALID_PARAMETER_EN,    KP_MSG_WSA_INVALID_PARAMETER_LT,    KP_MSG_WSA_INVALID_PARAMETER_PL_1250,     KP_MSG_WSA_INVALID_PARAMETER_PL_1257,     KP_MSG_WSA_INVALID_PARAMETER_RU,    KP_MSG_WSA_INVALID_PARAMETER_RU,    }, // "Neteisingi parametrai" // "Neteisingi vienas ar daugiau parametrų"
    { KP_MSG_WSAINVALIDPROCTABLE_EN,      KP_MSG_WSAINVALIDPROCTABLE_LT,      KP_MSG_WSAINVALIDPROCTABLE_PL_1250,       KP_MSG_WSAINVALIDPROCTABLE_PL_1257,       KP_MSG_WSAINVALIDPROCTABLE_RU,      KP_MSG_WSAINVALIDPROCTABLE_RU,      }, // "Klaidinga procedūrų lentelė"
    { KP_MSG_WSAINVALIDPROVIDER_EN,       KP_MSG_WSAINVALIDPROVIDER_LT,       KP_MSG_WSAINVALIDPROVIDER_PL_1250,        KP_MSG_WSAINVALIDPROVIDER_PL_1257,        KP_MSG_WSAINVALIDPROVIDER_RU,       KP_MSG_WSAINVALIDPROVIDER_RU,       }, // "Neteisingas tiekėjo kodas"
    { KP_MSG_WSA_IO_INCOMPLETE_EN,        KP_MSG_WSA_IO_INCOMPLETE_LT,        KP_MSG_WSA_IO_INCOMPLETE_PL_1250,         KP_MSG_WSA_IO_INCOMPLETE_PL_1257,         KP_MSG_WSA_IO_INCOMPLETE_RU,        KP_MSG_WSA_IO_INCOMPLETE_RU,        }, // "Persikloja įvesties/išvesties įvykiai"
    { KP_MSG_WSA_IO_PENDING_EN,           KP_MSG_WSA_IO_PENDING_LT,           KP_MSG_WSA_IO_PENDING_PL_1250,            KP_MSG_WSA_IO_PENDING_PL_1257,            KP_MSG_WSA_IO_PENDING_RU,           KP_MSG_WSA_IO_PENDING_RU,           }, // "Persiklojančios operacijos bus atliktos vėliau"

    { KP_MSG_WSA_NOT_ENOUGH_MEMORY_EN,    KP_MSG_WSA_NOT_ENOUGH_MEMORY_LT,    KP_MSG_WSA_NOT_ENOUGH_MEMORY_PL_1250,     KP_MSG_WSA_NOT_ENOUGH_MEMORY_PL_1257,     KP_MSG_WSA_NOT_ENOUGH_MEMORY_RU,    KP_MSG_WSA_NOT_ENOUGH_MEMORY_RU,    }, // "Nepakanka atminties"
    { KP_MSG_WSANOTINITIALISED_EN,        KP_MSG_WSANOTINITIALISED_LT,        KP_MSG_WSANOTINITIALISED_PL_1250,         KP_MSG_WSANOTINITIALISED_PL_1257,         KP_MSG_WSANOTINITIALISED_RU,        KP_MSG_WSANOTINITIALISED_RU,        }, // "Tinklo posistemis neaktyvuotas"
    { KP_MSG_WSANO_DATA_EN,               KP_MSG_WSANO_DATA_LT,               KP_MSG_WSANO_DATA_PL_1250,                KP_MSG_WSANO_DATA_PL_1257,                KP_MSG_WSANO_DATA_RU,               KP_MSG_WSANO_DATA_RU,               }, // "Vardas teisingas, tačiau nėra reikiamo tipo duomenų"
    { KP_MSG_WSANO_RECOVERY_EN,           KP_MSG_WSANO_RECOVERY_LT,           KP_MSG_WSANO_RECOVERY_PL_1250,            KP_MSG_WSANO_RECOVERY_PL_1257,            KP_MSG_WSANO_RECOVERY_RU,           KP_MSG_WSANO_RECOVERY_RU,           }, // "Nepataisoma klaida"
    { KP_MSG_WSAPROVIDERFAILEDINIT_EN,    KP_MSG_WSAPROVIDERFAILEDINIT_LT,    KP_MSG_WSAPROVIDERFAILEDINIT_PL_1250,     KP_MSG_WSAPROVIDERFAILEDINIT_PL_1257,     KP_MSG_WSAPROVIDERFAILEDINIT_RU,    KP_MSG_WSAPROVIDERFAILEDINIT_RU,    }, // "Negalima inicializuoti paslaugos tiekėjo"
    { KP_MSG_WSASYSCALLFAILURE_EN,        KP_MSG_WSASYSCALLFAILURE_LT,        KP_MSG_WSASYSCALLFAILURE_PL_1250,         KP_MSG_WSASYSCALLFAILURE_PL_1257,         KP_MSG_WSASYSCALLFAILURE_RU,        KP_MSG_WSASYSCALLFAILURE_RU,        }, // "Sistemos kreipinio klaida"
    { KP_MSG_WSASYSNOTREADY_EN,           KP_MSG_WSASYSNOTREADY_LT,           KP_MSG_WSASYSNOTREADY_PL_1250,            KP_MSG_WSASYSNOTREADY_PL_1257,            KP_MSG_WSASYSNOTREADY_RU,           KP_MSG_WSASYSNOTREADY_RU,           }, // "Tinklo posistemė nepasiekiama"
    { KP_MSG_WSATRY_AGAIN_EN,             KP_MSG_WSATRY_AGAIN_LT,             KP_MSG_WSATRY_AGAIN_PL_1250,              KP_MSG_WSATRY_AGAIN_PL_1257,              KP_MSG_WSATRY_AGAIN_RU,             KP_MSG_WSATRY_AGAIN_RU,             }, // "Neautorizuotas serveris nerastas"
    { KP_MSG_WSAVERNOTSUPPORTED_EN,       KP_MSG_WSAVERNOTSUPPORTED_LT,       KP_MSG_WSAVERNOTSUPPORTED_PL_1250,        KP_MSG_WSAVERNOTSUPPORTED_PL_1257,        KP_MSG_WSAVERNOTSUPPORTED_RU,       KP_MSG_WSAVERNOTSUPPORTED_RU,       }, // "Netinka WINSOCK.DLL versija"
    { KP_MSG_WSAEDISCON_EN,               KP_MSG_WSAEDISCON_LT,               KP_MSG_WSAEDISCON_PL_1250,                KP_MSG_WSAEDISCON_PL_1257,                KP_MSG_WSAEDISCON_RU,               KP_MSG_WSAEDISCON_RU,               }, // "Pradėtas tvarkingas išjungimas" // "Pradėtas gracingas išjungimas"
    { KP_MSG_WSA_OPERATION_ABORTED_EN,    KP_MSG_WSA_OPERATION_ABORTED_LT,    KP_MSG_WSA_OPERATION_ABORTED_PL_1250,     KP_MSG_WSA_OPERATION_ABORTED_PL_1257,     KP_MSG_WSA_OPERATION_ABORTED_RU,    KP_MSG_WSA_OPERATION_ABORTED_RU,    }, // "Persiklojanti operacija nutraukta"

    { KP_MSG_OUT_OF_MEM_RES_EN,           KP_MSG_OUT_OF_MEM_RES_LT,           KP_MSG_OUT_OF_MEM_RES_PL_1250,            KP_MSG_OUT_OF_MEM_RES_PL_1257,            KP_MSG_OUT_OF_MEM_RES_RU,           KP_MSG_OUT_OF_MEM_RES_RU,           }, // "Operacinei sistemai trūksta atminties"
    { KP_MSG_ERROR_FILE_NOT_FOUND_EN,     KP_MSG_ERROR_FILE_NOT_FOUND_LT,     KP_MSG_ERROR_FILE_NOT_FOUND_PL_1250,      KP_MSG_ERROR_FILE_NOT_FOUND_PL_1257,      KP_MSG_ERROR_FILE_NOT_FOUND_RU,     KP_MSG_ERROR_FILE_NOT_FOUND_RU,     }, // "Nurodytas failas nerastas"
    { KP_MSG_ERROR_PATH_NOT_FOUND_EN,     KP_MSG_ERROR_PATH_NOT_FOUND_LT,     KP_MSG_ERROR_PATH_NOT_FOUND_PL_1250,      KP_MSG_ERROR_PATH_NOT_FOUND_PL_1257,      KP_MSG_ERROR_PATH_NOT_FOUND_RU,     KP_MSG_ERROR_PATH_NOT_FOUND_RU,     }, // "Nurodytas kelias iki failų nerastas"
    { KP_MSG_ERROR_BAD_FORMAT_EN,         KP_MSG_ERROR_BAD_FORMAT_LT,         KP_MSG_ERROR_BAD_FORMAT_PL_1250,          KP_MSG_ERROR_BAD_FORMAT_PL_1257,          KP_MSG_ERROR_BAD_FORMAT_RU,         KP_MSG_ERROR_BAD_FORMAT_RU,         }, // "Pasirinktas .exe failas sugadintas"
    { KP_MSG_SE_ERR_ACCESSDENIED_EN,      KP_MSG_SE_ERR_ACCESSDENIED_LT,      KP_MSG_SE_ERR_ACCESSDENIED_PL_1250,       KP_MSG_SE_ERR_ACCESSDENIED_PL_1257,       KP_MSG_SE_ERR_ACCESSDENIED_RU,      KP_MSG_SE_ERR_ACCESSDENIED_RU,      }, // "Operacinė sistema uždraudė prisijungimą prie reikiamų failų"
    { KP_MSG_SE_ERR_ASSOCINCOMPLETE_EN,   KP_MSG_SE_ERR_ASSOCINCOMPLETE_LT,   KP_MSG_SE_ERR_ASSOCINCOMPLETE_PL_1250,    KP_MSG_SE_ERR_ASSOCINCOMPLETE_PL_1257,    KP_MSG_SE_ERR_ASSOCINCOMPLETE_RU,   KP_MSG_SE_ERR_ASSOCINCOMPLETE_RU,   }, // "Failo sąryšis su programa nepilnas arba neteisingas"
    { KP_MSG_SE_ERR_DDEBUSY_EN,           KP_MSG_SE_ERR_DDEBUSY_LT,           KP_MSG_SE_ERR_DDEBUSY_PL_1250,            KP_MSG_SE_ERR_DDEBUSY_PL_1257,            KP_MSG_SE_ERR_DDEBUSY_RU,           KP_MSG_SE_ERR_DDEBUSY_RU,           }, // "DDE transakcija negali būti baigta, nes kitos DDE transakcijos dar vykdomos"
    { KP_MSG_SE_ERR_DDEFAIL_EN,           KP_MSG_SE_ERR_DDEFAIL_LT,           KP_MSG_SE_ERR_DDEFAIL_PL_1250,            KP_MSG_SE_ERR_DDEFAIL_PL_1257,            KP_MSG_SE_ERR_DDEFAIL_RU,           KP_MSG_SE_ERR_DDEFAIL_RU,           }, // "DDE transakcija nutraukta"
    { KP_MSG_SE_ERR_DDETIMEOUT_EN,        KP_MSG_SE_ERR_DDETIMEOUT_LT,        KP_MSG_SE_ERR_DDETIMEOUT_PL_1250,         KP_MSG_SE_ERR_DDETIMEOUT_PL_1257,         KP_MSG_SE_ERR_DDETIMEOUT_RU,        KP_MSG_SE_ERR_DDETIMEOUT_RU,        }, // "DDE transakcija negali būti baigta, nes neužteko nurodyto laukimo laiko"
    { KP_MSG_SE_ERR_DLLNOTFOUND_EN,       KP_MSG_SE_ERR_DLLNOTFOUND_LT,       KP_MSG_SE_ERR_DLLNOTFOUND_PL_1250,        KP_MSG_SE_ERR_DLLNOTFOUND_PL_1257,        KP_MSG_SE_ERR_DLLNOTFOUND_RU,       KP_MSG_SE_ERR_DLLNOTFOUND_RU,       }, // "Nurodyta dinaminė biblioteka nerasta"
    { KP_MSG_SE_ERR_FNF_EN,               KP_MSG_SE_ERR_FNF_LT,               KP_MSG_SE_ERR_FNF_PL_1250,                KP_MSG_SE_ERR_FNF_PL_1257,                KP_MSG_SE_ERR_FNF_RU,               KP_MSG_SE_ERR_FNF_RU,               }, // "Nurodytas failas nerastas"
    { KP_MSG_SE_ERR_NOASSOC_EN,           KP_MSG_SE_ERR_NOASSOC_LT,           KP_MSG_SE_ERR_NOASSOC_PL_1250,            KP_MSG_SE_ERR_NOASSOC_PL_1257,            KP_MSG_SE_ERR_NOASSOC_RU,           KP_MSG_SE_ERR_NOASSOC_RU,           }, // "Nerasta programa skirta atverti šio tipo failus"
    { KP_MSG_SE_ERR_OOM_EN,               KP_MSG_SE_ERR_OOM_LT,               KP_MSG_SE_ERR_OOM_PL_1250,                KP_MSG_SE_ERR_OOM_PL_1257,                KP_MSG_SE_ERR_OOM_RU,               KP_MSG_SE_ERR_OOM_RU,               }, // "Nepakanka atminties atlikti operacijai"
    { KP_MSG_SE_ERR_PNF_EN,               KP_MSG_SE_ERR_PNF_LT,               KP_MSG_SE_ERR_PNF_PL_1250,                KP_MSG_SE_ERR_PNF_PL_1257,                KP_MSG_SE_ERR_PNF_RU,               KP_MSG_SE_ERR_PNF_RU,               }, // "Nurodytas kelias nerastas"
    { KP_MSG_SE_ERR_SHARE_EN,             KP_MSG_SE_ERR_SHARE_LT,             KP_MSG_SE_ERR_SHARE_PL_1250,              KP_MSG_SE_ERR_SHARE_PL_1257,              KP_MSG_SE_ERR_SHARE_RU,             KP_MSG_SE_ERR_SHARE_RU,             }, // "Dalijimosi klaida"

    { KP_MSG_FIRST_TIME_ADMIN_EN,         KP_MSG_FIRST_TIME_ADMIN_LT,         KP_MSG_FIRST_TIME_ADMIN_PL_1250,          KP_MSG_FIRST_TIME_ADMIN_PL_1257,          KP_MSG_FIRST_TIME_ADMIN_RU,         KP_MSG_FIRST_TIME_ADMIN_RU,         }, // "Programą paleidžiant pirmą kartą, reikalingos\n administratoriaus teisės. Paleiskite programą iš naujo administratoriaus teisėmis."
    { KP_MSG_NOW_NOT_ADMIN_EN,            KP_MSG_NOW_NOT_ADMIN_LT,            KP_MSG_NOW_NOT_ADMIN_PL_1250,             KP_MSG_NOW_NOT_ADMIN_PL_1257,             KP_MSG_NOW_NOT_ADMIN_RU,            KP_MSG_NOW_NOT_ADMIN_RU,            }, // KP_MSG_NOT_ADMIN // "Dabar programą paleiskite dar kartą paprasto vartotojo teisėmis"
    { KP_MSG_NOT_ADMIN_EN,                KP_MSG_NOT_ADMIN_LT,                KP_MSG_NOT_ADMIN_PL_1250,                 KP_MSG_NOT_ADMIN_PL_1257,                 KP_MSG_NOT_ADMIN_RU,                KP_MSG_NOT_ADMIN_RU,                }, // "Programą paleiskite iš naujo paprasto vartotojo teisėmis"
    { KP_MSG_COPY_FILE_ACCESS_DENIED_EN,  KP_MSG_COPY_FILE_ACCESS_DENIED_LT,  KP_MSG_COPY_FILE_ACCESS_DENIED_PL_1250,   KP_MSG_COPY_FILE_ACCESS_DENIED_PL_1257,   KP_MSG_COPY_FILE_ACCESS_DENIED_RU,  KP_MSG_COPY_FILE_ACCESS_DENIED_RU,  }, // "Failo nukopijuoti nepavyko, programą paleiskite iš naujo administratoriaus teisėmis"

    { KP_PROGRESS_TITLE_EN,               KP_PROGRESS_TITLE_LT,               KP_PROGRESS_TITLE_PL_1250,                KP_PROGRESS_TITLE_PL_1257,                KP_PROGRESS_TITLE_RU,               KP_PROGRESS_TITLE_EN,               }, // "Palaukite..." // naudojamas kaip progress langelio antraštė
    { KP_MSG_DELETING_FILE_EN,            KP_MSG_DELETING_FILE_LT,            KP_MSG_DELETING_FILE_PL_1250,             KP_MSG_DELETING_FILE_PL_1257,             KP_MSG_DELETING_FILE_RU,            KP_MSG_DELETING_FILE_RU,            }, // "Naikinamas failas %s.%s..."
    { KP_MSG_COPYING_EN,                  KP_MSG_COPYING_LT,                  KP_MSG_COPYING_PL_1250,                   KP_MSG_COPYING_PL_1257,                   KP_MSG_COPYING_RU,                  KP_MSG_COPYING_RU,                  }, // "Kopijuojamas failas..."
    { KP_MSG_COPYING_DIR_EN,              KP_MSG_COPYING_DIR_LT,              KP_MSG_COPYING_DIR_PL_1250,               KP_MSG_COPYING_DIR_PL_1257,               KP_MSG_COPYING_DIR_RU,              KP_MSG_COPYING_DIR_RU,              }, // "Kopijuojamas aplankas %s.%s..."
    { KP_MSG_COPYING_FILE_EN,             KP_MSG_COPYING_FILE_LT,             KP_MSG_COPYING_FILE_PL_1250,              KP_MSG_COPYING_FILE_PL_1257,              KP_MSG_COPYING_FILE_RU,             KP_MSG_COPYING_FILE_RU,             }, // "Kopijuojamas failas %s.%s..."

    { KP_MSG_NEG_ANSW_EN,                 KP_MSG_NEG_ANSW_LT,                 KP_MSG_NEG_ANSW_PL_1250,                  KP_MSG_NEG_ANSW_PL_1257,                  KP_MSG_NEG_ANSW_RU,                 KP_MSG_NEG_ANSW_RU,                 }, // "Neigiamas atsakymas"

    { KP_MSG_UNABLE_TO_EXECUTE_EN,        KP_MSG_UNABLE_TO_EXECUTE_LT,        KP_MSG_UNABLE_TO_EXECUTE_PL_1250,         KP_MSG_UNABLE_TO_EXECUTE_PL_1257,         KP_MSG_UNABLE_TO_EXECUTE_RU,        KP_MSG_UNABLE_TO_EXECUTE_RU,        }, // "Komandos %s įvykdyti negaliu – patikrinkite, ar teisingai įdiegėte visus sistemos komponentus"

    { KP_MSG_FLASH_PLAYER_INSTALL_EN,     KP_MSG_FLASH_PLAYER_INSTALL_LT,     KP_MSG_FLASH_PLAYER_INSTALL_PL_1250,      KP_MSG_FLASH_PLAYER_INSTALL_PL_1257,      KP_MSG_FLASH_PLAYER_INSTALL_RU,     KP_MSG_FLASH_PLAYER_INSTALL_RU,     }, // "Dabar bus įdiegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus."

    { KP_MSG_FILE_CHANGED_EN,             KP_MSG_FILE_CHANGED_LT,             KP_MSG_FILE_CHANGED_PL_1250,              KP_MSG_FILE_CHANGED_PL_1257,              KP_MSG_FILE_CHANGED_RU,             KP_MSG_FILE_CHANGED_RU,             }, // "Failas pasikeitė"

    { KP_MSG_ALL_FILES_EN,                KP_MSG_ALL_FILES_LT,                KP_MSG_ALL_FILES_PL_1250,                 KP_MSG_ALL_FILES_PL_1257,                 KP_MSG_ALL_FILES_RU,                KP_MSG_ALL_FILES_RU,                }, // "Visi failai (*.*)"
    { KP_MSG_SAVE_AS_EN,                  KP_MSG_SAVE_AS_LT,                  KP_MSG_SAVE_AS_PL_1250,                   KP_MSG_SAVE_AS_PL_1257,                   KP_MSG_SAVE_AS_RU,                  KP_MSG_SAVE_AS_RU,                  }, // "Įrašyti kaip"

    { KP_MSG_FILE_EXISTS_EN,              KP_MSG_FILE_EXISTS_LT,              KP_MSG_FILE_EXISTS_PL_1250,               KP_MSG_FILE_EXISTS_PL_1257,               KP_MSG_FILE_EXISTS_RU,              KP_MSG_FILE_EXISTS_RU,              }, // "Failas %s jau yra, perrašyti?"

    { KP_MSG_DIAG_MSG_EN,                 KP_MSG_DIAG_MSG_LT,                 KP_MSG_DIAG_MSG_PL_1250,                  KP_MSG_DIAG_MSG_PL_1257,                  KP_MSG_DIAG_MSG_RU,                 KP_MSG_DIAG_MSG_RU,                 }, // "Formuojamas diagnostinis pranešimas"
    { KP_MSG_DIAG_MSG_TITLE_EN,           KP_MSG_DIAG_MSG_TITLE_LT,           KP_MSG_DIAG_MSG_TITLE_PL_1250,            KP_MSG_DIAG_MSG_TITLE_PL_1257,            KP_MSG_DIAG_MSG_TITLE_RU,           KP_MSG_DIAG_MSG_TITLE_EN,           }, // "Diagnostinis pranešimas"
    { KP_MSG_DIAG_MSG_EXPL_EN,            KP_MSG_DIAG_MSG_EXPL_LT,            KP_MSG_DIAG_MSG_EXPL_PL_1250,             KP_MSG_DIAG_MSG_EXPL_PL_1257,             KP_MSG_DIAG_MSG_EXPL_RU,            KP_MSG_DIAG_MSG_EXPL_RU,            }, // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite pateiktus laukus. Pranešimas apie kompiuterio konfigūraciją, produktą bei klaidos pobūdį bus išsiųstas internetu į produkto gamintojo tarnybinę stotį. Jei po kurio laiko su Jumis nebus susisiekta Jūsų nurodytu pašto adresu, kreipkitės adresu %s")
    { KP_MSG_DIAG_MSG_EMAIL_PROMPT_EN,    KP_MSG_DIAG_MSG_EMAIL_PROMPT_LT,    KP_MSG_DIAG_MSG_EMAIL_PROMPT_PL_1250,     KP_MSG_DIAG_MSG_EMAIL_PROMPT_PL_1257,     KP_MSG_DIAG_MSG_EMAIL_PROMPT_RU,    KP_MSG_DIAG_MSG_EMAIL_PROMPT_RU,    }, // "Jūsų e-pašto adresas:")
    { KP_MSG_DIAG_MSG_COMMENTS_PROMPT_EN, KP_MSG_DIAG_MSG_COMMENTS_PROMPT_LT, KP_MSG_DIAG_MSG_COMMENTS_PROMPT_PL_1250,  KP_MSG_DIAG_MSG_COMMENTS_PROMPT_PL_1257,  KP_MSG_DIAG_MSG_COMMENTS_PROMPT_RU, KP_MSG_DIAG_MSG_COMMENTS_PROMPT_RU, }, // "Komentarai apie klaidos atsiradimo aplinkybes:")
    { KP_MSG_DIAG_MSG_FILE_PROMPT_EN,     KP_MSG_DIAG_MSG_FILE_PROMPT_LT,     KP_MSG_DIAG_MSG_FILE_PROMPT_PL_1250,      KP_MSG_DIAG_MSG_FILE_PROMPT_PL_1257,      KP_MSG_DIAG_MSG_FILE_PROMPT_RU,     KP_MSG_DIAG_MSG_FILE_PROMPT_RU,     }, // "Papildomas failas, kurį norėtumėte nusiųsti (pvz., ekrano kopijos paveikslėlis):")

    { KP_MSG_BAD_EMAIL_ADDRESS_EN,        KP_MSG_BAD_EMAIL_ADDRESS_LT,        KP_MSG_BAD_EMAIL_ADDRESS_PL_1250,         KP_MSG_BAD_EMAIL_ADDRESS_PL_1257,         KP_MSG_BAD_EMAIL_ADDRESS_RU,        KP_MSG_BAD_EMAIL_ADDRESS_RU,        }, // "Neteisingas e-pašto adresas"

    { KP_MSG_DIAG_MSG_SEL_FILE_EN,        KP_MSG_DIAG_MSG_SEL_FILE_LT,        KP_MSG_DIAG_MSG_SEL_FILE_PL_1250,         KP_MSG_DIAG_MSG_SEL_FILE_PL_1257,         KP_MSG_DIAG_MSG_SEL_FILE_RU,        KP_MSG_DIAG_MSG_SEL_FILE_EN,        }, // "Pasirinkite siunčiamą failą"

    { KP_MSG_DIAG_MSG_SUCCEEDED_EN,       KP_MSG_DIAG_MSG_SUCCEEDED_LT,       KP_MSG_DIAG_MSG_SUCCEEDED_PL_1250,        KP_MSG_DIAG_MSG_SUCCEEDED_PL_1257,        KP_MSG_DIAG_MSG_SUCCEEDED_RU,       KP_MSG_DIAG_MSG_SUCCEEDED_RU,       }, // "Diagnostinis pranešimas nusiųstas sėkmingai"

    { KP_MSG_DIAG_MSG_EXPL1_EN,           KP_MSG_DIAG_MSG_EXPL1_LT,           KP_MSG_DIAG_MSG_EXPL1_PL_1250,            KP_MSG_DIAG_MSG_EXPL1_PL_1257,            KP_MSG_DIAG_MSG_EXPL1_RU,           KP_MSG_DIAG_MSG_EXPL1_RU,           }, // "Jei norite siųsti diagnostinį pranešimą, spragtelėkite „Siųsti“, jei ne – „Atšaukti“."
    { KP_MSG_SIUSTI_EN,                   KP_MSG_SIUSTI_LT,                   KP_MSG_SIUSTI_PL_1250,                    KP_MSG_SIUSTI_PL_1257,                    KP_MSG_SIUSTI_RU,                   KP_MSG_SIUSTI_EN,                   }, // "Siųsti"
    { KP_MSG_DIAG_MSG_EXPL2_EN,           KP_MSG_DIAG_MSG_EXPL2_LT,           KP_MSG_DIAG_MSG_EXPL2_PL_1250,            KP_MSG_DIAG_MSG_EXPL2_PL_1257,            KP_MSG_DIAG_MSG_EXPL2_RU,           KP_MSG_DIAG_MSG_EXPL2_RU,           }, // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite Jūsų e-pašto adreso lauką ir spragtelėkite mygtuką „Siųsti“."

    { KP_MSG_DOWNLOADING_EN,              KP_MSG_DOWNLOADING_LT,              KP_MSG_DOWNLOADING_PL_1250,               KP_MSG_DOWNLOADING_PL_1257,               KP_MSG_DOWNLOADING_RU,              KP_MSG_DOWNLOADING_RU,              }, // "Siunčiamas failas..."
    { KP_MSG_DOWNLOADING_FILE_EN,         KP_MSG_DOWNLOADING_FILE_LT,         KP_MSG_DOWNLOADING_FILE_PL_1250,          KP_MSG_DOWNLOADING_FILE_PL_1257,          KP_MSG_DOWNLOADING_FILE_RU,         KP_MSG_DOWNLOADING_FILE_RU,         }, // "Siunčiamas failas %s.%s..."

    { KP_MSG_FIREWALL_EN,                 KP_MSG_FIREWALL_LT,                 KP_MSG_FIREWALL_PL_1250,                  KP_MSG_FIREWALL_PL_1257,                  KP_MSG_FIREWALL_RU,                 KP_MSG_FIREWALL_RU,                 }, // "Neleista prisijungti prie interneto. Patikrinkite Jūsų ugniasienės parinktis – pabandykite įtraukti %s į sąrašą programų, kurioms leidžiama kreiptis į internetą."

    { KP_MSG_POINTER_EN,                  KP_MSG_POINTER_LT,                  KP_MSG_POINTER_PL_1250,                   KP_MSG_POINTER_PL_1257,                   KP_MSG_POINTER_RU,                  KP_MSG_POINTER_RU,                  }, // "Bloga rodyklė"

    { KP_MSG_LOG_STARTED_EN,              KP_MSG_LOG_STARTED_LT,              KP_MSG_LOG_STARTED_PL_1250,               KP_MSG_LOG_STARTED_PL_1257,               KP_MSG_LOG_STARTED_RU,              KP_MSG_LOG_STARTED_RU,              }, // "Žurnalas išvedamas ir į failą %s"
    { KP_MSG_CONS_TITLE_EN,               KP_MSG_CONS_TITLE_LT,               KP_MSG_CONS_TITLE_PL_1250,                KP_MSG_CONS_TITLE_PL_1257,                KP_MSG_CONS_TITLE_RU,               KP_MSG_CONS_TITLE_RU,               }, // "%s: Pranešimų žurnalas"

    { KP_MSG_UNHANDLED_EXCEPTION_EN,      KP_MSG_UNHANDLED_EXCEPTION_LT,      KP_MSG_UNHANDLED_EXCEPTION_PL_1250,       KP_MSG_UNHANDLED_EXCEPTION_PL_1257,       KP_MSG_UNHANDLED_EXCEPTION_RU,      KP_MSG_UNHANDLED_EXCEPTION_RU,      }, // "Neapdorojamas trūkis"

    { KP_MSG_DATA_FORMAT_EN,              KP_MSG_DATA_FORMAT_LT,              KP_MSG_DATA_FORMAT_PL_1250,               KP_MSG_DATA_FORMAT_PL_1257,               KP_MSG_DATA_FORMAT_RU,              KP_MSG_DATA_FORMAT_RU,              }, // "Neteisingas duomenų formatas"
    { KP_MSG_DBERROR_EN,                  KP_MSG_DBERROR_LT,                  KP_MSG_DBERROR_PL_1250,                   KP_MSG_DBERROR_PL_1257,                   KP_MSG_DBERROR_RU,                  KP_MSG_DBERROR_RU,                  }, // "Duomenų bazės klaida"
};


// ---------------------
// KpException

// ---------------------
void KpException::Constructor
(
   HRESULT p_lhErrCode,
   const uchar *p_pszMsg,
   LONG p_lWindowsErrorCode,
   const uchar *p_pszSourceFile,
   int p_iSourceLine
)
{
   m_lhErrCode = p_lhErrCode;

   m_pszMsg[0] = Nul;
   if (p_pszMsg)
   {
      strncpy(m_pszMsg, p_pszMsg, KP_MAX_FILE_LIN_LEN);
      m_pszMsg[KP_MAX_FILE_LIN_LEN] = Nul;
   }

   m_lWindowsErrorCode = p_lWindowsErrorCode;

   m_pszSourceFile[0] = Nul;
   if (p_pszSourceFile)
   {
      strncpy(m_pszSourceFile, p_pszSourceFile, KP_MAX_FNAME_LEN);
      m_pszSourceFile[KP_MAX_FNAME_LEN] = Nul;
   }

   m_iSourceLine = p_iSourceLine;
}


// ---------------------
// KpErrorClass

// ---------------------
KpErrorClass::KpErrorClass(const uchar *p_pszProdName, bool p_bOutMsg)
{
//  m_iInsideOfStackDump = 0;
    m_iInsideOfPutLogMessage = 0;

    m_lhLastRetc = S_OK;
    m_pszLastMessageText[0] = Nul;
    m_pszLastSourceFile[0] = Nul;
    m_iLastSourceLine = 0;

    m_pszProdName[0] = Nul;

    KP_ASSERT(p_pszProdName, E_INVALIDARG, null);
    strncpy(m_pszProdName, p_pszProdName, KP_MAX_FNAME_LEN);
    m_pszProdName[KP_MAX_FNAME_LEN] = Nul;

    m_bOutMsg = p_bOutMsg;
}


// ----------------------------------
void KpErrorClass::GetProdName(uchar *p_pszNameBuf)
{
    KP_ASSERT(p_pszNameBuf, E_INVALIDARG, null);
    strcpy(p_pszNameBuf, m_pszProdName);
}

const uchar *KpErrorClass::GetProdNamePtr(void)
{
return(m_pszProdName);
}

const uchar *KpGetProdName(void)
{
return(KpError.GetProdNamePtr());
}


// ----------------------------------
void KpErrorClass::SetProdName(const uchar *p_pszNameBuf)
{
    KP_ASSERT(p_pszNameBuf, E_INVALIDARG, null);
    KP_ASSERT(strlen(p_pszNameBuf) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null);
    strcpy(m_pszProdName, p_pszNameBuf);
}


// ---------------------
void KpErrorClass::FormatErrorMessage
(
const HRESULT p_lhRetc,
unsigned char *p_pszMsg
)
{
   if (p_pszMsg)
   {
// gcc 5.4.0 does not distinguish between a pointer to const and const pointer
#if (__GNUC__ != 5) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 0)
   const
#endif
        uchar *msgptr = (
#if (__GNUC__ != 5) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 0)
            const
#endif
                uchar *)"";

      switch(p_lhRetc)
      {
         case S_OK:                 msgptr = KP_MSG_ERR_OK; break;
         case E_INVALIDARG:         msgptr = KP_MSG_INVALIDARG; break;
         case E_NOTIMPL:            msgptr = KP_MSG_NOTIMPL; break;
         case E_UNEXPECTED:         msgptr = KP_MSG_UNEXPECTED; break;
//       case E_NOINTERFACE:
         case E_POINTER:            msgptr = KP_MSG_POINTER; break;
//       case E_HANDLE:
//       case E_FAIL:
// TODO: case E_OBJECT_BUSY:        msgptr = KP_MSG_OBJBUSY; break;
         case KP_E_FERROR:          msgptr = KP_MSG_FERROR; break;
         case KP_E_SYSTEM_ERROR:    msgptr = KP_MSG_SYSTEM_ERROR; break;
         case KP_E_EOF:             msgptr = KP_MSG_EOF; break;
         case KP_E_FILE_FORMAT:     msgptr = KP_MSG_FILE_FORMAT; break;
         case KP_E_FILE_NOT_FOUND:  msgptr = KP_MSG_FILE_NOT_FOUND; break;
         case KP_E_DIR_ERROR:       msgptr = KP_MSG_DIR_ERROR; break;
         case KP_E_OUTOFMEM:        msgptr = KP_MSG_OUTOFMEM; break;
         case KP_E_NO_FILE:         msgptr = KP_MSG_NO_FILE; break;
         case KP_E_DOUBLE_UNGET:    msgptr = KP_MSG_DOUBLE_UNGET; break;
         case KP_E_UNKN_CHR:        msgptr = KP_MSG_UNKN_CHR; break;
         case KP_E_COMMAND_ERROR:   msgptr = KP_MSG_COMMAND_ERROR; break;
         case KP_E_BUFFER_OVERFLOW: msgptr = KP_MSG_BUFFER_OVERFLOW; break;
         case KP_E_FONT_UNDEF:      msgptr = KP_MSG_FONT_UNDEF; break;
         case KP_E_KWD_NOT_FOUND:   msgptr = KP_MSG_KWD_NOT_FOUND; break;
         case KP_E_UNKNOWN_SYSTEM:  msgptr = KP_MSG_UNKNOWN_SYSTEM; break;
         case KP_E_ILL_CODE:        msgptr = KP_MSG_ILL_CODE; break;
         case KP_E_CANCEL:          msgptr = KP_MSG_CANCELLED; break;
         case KP_E_DOUBLE_CALL:     msgptr = KP_MSG_DOUBLE_CALL; break;
         case KP_E_TIMEOUT:         msgptr = KP_MSG_TIMEOUT; break;
         case KP_E_OBJ_NOT_FOUND:   msgptr = KP_MSG_OBJ_NOT_FOUND; break;
         case KP_E_NO_CONN:         msgptr = KP_MSG_NO_CONN; break;
         case KP_E_TRANS_ERR:       msgptr = KP_MSG_TRANS_ERR; break;
         case KP_E_REFUSED:         msgptr = KP_MSG_REFUSED; break;
         case KP_E_ACCESS_DENIED:   msgptr = KP_MSG_ACCESS_DENIED; break;
         case KP_E_ILL_CHR:         msgptr = KP_MSG_ILLEGAL_CHARACTER; break;
         case KP_E_DIV_ZERO:        msgptr = KP_MSG_DIV_ZERO; break;
         case KP_E_ILLMATHARG:      msgptr = KP_MSG_ILLMATHARG; break;
         case KP_E_ILLFUNC:         msgptr = KP_MSG_ILLFUNC; break;
         case KP_E_NOTINST:         msgptr = KP_MSG_NOTINST; break;
         case KP_E_MSG_FORMAT:      msgptr = KP_MSG_MSG_FORMAT; break;
         case KP_E_OBSOLETE:        msgptr = KP_MSG_OBSOLETE; break;
         case KP_E_NEG_ANSW:        msgptr = KP_MSG_NEG_ANSW; break;
         case KP_E_FILE_CHANGED:    msgptr = KP_MSG_FILE_CHANGED; break;
         case KP_S_DIAG_MSG:        msgptr = KP_MSG_DIAG_MSG; break;
         case KP_E_BAD_EMAIL:       msgptr = KP_MSG_BAD_EMAIL_ADDRESS; break;
         case KP_E_UNHANDLED_EXCEPTION:
                                    msgptr = KP_MSG_UNHANDLED_EXCEPTION; break;
         case KP_E_DATA_FORMAT:     msgptr = KP_MSG_DATA_FORMAT; break;
         case KP_E_DBERROR:         msgptr = KP_MSG_DBERROR; break;
      }

      strncpy(p_pszMsg, msgptr, KP_MAX_FILE_LIN_LEN);
      p_pszMsg[KP_MAX_FILE_LIN_LEN] = Nul;
   }
}


// ---------------------
HRESULT KpErrorClass::FormatSystemErrorMessage
(
long p_lWindowsErrorCode,
uchar *p_pszMsg,
bool
#ifdef __WIN32__
    p_bFullFormat
#endif
)
{
HRESULT retc = S_OK;
// gcc 5.4.0 does not distinguish between a pointer to const and const pointer
#if (__GNUC__ != 5) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 0)
const
#endif
    uchar *msg0 = null;
uchar *msg1 = null;
#if (__GNUC__ != 5) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 0)
const
#endif
    uchar *msg = null;
uchar *pnts;
uchar str_buf[MAX_LONG_DIGITS + 20];
    str_buf[0] = Nul;
int ii;

    KP_ASSERT(p_pszMsg, E_INVALIDARG, null);

    if (SUCCEEDED(retc)) p_pszMsg[0] = Nul;

    if (p_lWindowsErrorCode)
    {
        switch(p_lWindowsErrorCode)
        {
#ifdef __WIN32__
        case WSAEACCES:               msg0=KP_MSG_WSAEACCES; break;
        case WSAEADDRINUSE:           msg0=KP_MSG_WSAEADDRINUSE; break;
        case WSAEADDRNOTAVAIL:        msg0=KP_MSG_WSAEADDRNOTAVAIL; break;
        case WSAEAFNOSUPPORT:         msg0=KP_MSG_WSAEAFNOSUPPORT; break;
        case WSAEALREADY:             msg0=KP_MSG_WSAEALREADY; break;
        case WSAECONNABORTED:         msg0=KP_MSG_WSAECONNABORTED; break;
        case WSAECONNREFUSED:         msg0=KP_MSG_WSAECONNREFUSED; break;
        case WSAECONNRESET:           msg0=KP_MSG_WSAECONNRESET; break;
        case WSAEDESTADDRREQ:         msg0=KP_MSG_WSAEDESTADDRREQ; break;
        case WSAEFAULT:               msg0=KP_MSG_WSAEFAULT; break;
        case WSAEHOSTDOWN:            msg0=KP_MSG_WSAEHOSTDOWN; break;
        case WSAEHOSTUNREACH:         msg0=KP_MSG_WSAEHOSTUNREACH; break;
        case WSAEINPROGRESS:          msg0=KP_MSG_WSAEINPROGRESS; break;
        case WSAEINTR:                msg0=KP_MSG_WSAEINTR; break;
        case WSAEINVAL:               msg0=KP_MSG_WSAEINVAL; break;
        case WSAEISCONN:              msg0=KP_MSG_WSAEISCONN; break;
        case WSAEMFILE:               msg0=KP_MSG_WSAEMFILE; break;
        case WSAEMSGSIZE:             msg0=KP_MSG_WSAEMSGSIZE; break;
        case WSAENETDOWN:             msg0=KP_MSG_WSAENETDOWN; break;
        case WSAENETRESET:            msg0=KP_MSG_WSAENETRESET; break;
        case WSAENETUNREACH:          msg0=KP_MSG_WSAENETUNREACH; break;
        case WSAENOBUFS:              msg0=KP_MSG_WSAENOBUFS; break;
        case WSAENOPROTOOPT:          msg0=KP_MSG_WSAENOPROTOOPT; break;
        case WSAENOTCONN:             msg0=KP_MSG_WSAENOTCONN; break;
        case WSAENOTSOCK:             msg0=KP_MSG_WSAENOTSOCK; break;
        case WSAEOPNOTSUPP:           msg0=KP_MSG_WSAEOPNOTSUPP; break;
        case WSAEPFNOSUPPORT:         msg0=KP_MSG_WSAEPFNOSUPPORT; break;
        case WSAEPROCLIM:             msg0=KP_MSG_WSAEPROCLIM; break;
        case WSAEPROTONOSUPPORT:      msg0=KP_MSG_WSAEPROTONOSUPPORT; break;
        case WSAEPROTOTYPE:           msg0=KP_MSG_WSAEPROTOTYPE; break;
        case WSAESHUTDOWN:            msg0=KP_MSG_WSAESHUTDOWN; break;
        case WSAESOCKTNOSUPPORT:      msg0=KP_MSG_WSAESOCKTNOSUPPORT; break;
        case WSAETIMEDOUT:            msg0=KP_MSG_WSAETIMEDOUT; break;
        case WSATYPE_NOT_FOUND:       msg0=KP_MSG_WSATYPE_NOT_FOUND; break;
        case WSAEWOULDBLOCK:          msg0=KP_MSG_WSAEWOULDBLOCK; break;
        case WSAHOST_NOT_FOUND:       msg0=KP_MSG_WSAHOST_NOT_FOUND; break;
        case WSA_INVALID_HANDLE:      msg0=KP_MSG_WSA_INVALID_HANDLE; break;
        case WSA_INVALID_PARAMETER:   msg0=KP_MSG_WSA_INVALID_PARAMETER; break;
//      case WSAINVALIDPROCTABLE:     msg0=KP_MSG_WSAINVALIDPROCTABLE; break;
//      case WSAINVALIDPROVIDER:      msg0=KP_MSG_WSAINVALIDPROVIDER; break;
        case WSA_IO_INCOMPLETE:       msg0=KP_MSG_WSA_IO_INCOMPLETE; break;
        case WSA_IO_PENDING:          msg0=KP_MSG_WSA_IO_PENDING; break;
// tas pat, kaip SE_ERR_OOM
//      case WSA_NOT_ENOUGH_MEMORY:   msg0=KP_MSG_WSA_NOT_ENOUGH_MEMORY; break;
        case WSANOTINITIALISED:       msg0=KP_MSG_WSANOTINITIALISED; break;
        case WSANO_DATA:              msg0=KP_MSG_WSANO_DATA; break;
        case WSANO_RECOVERY:          msg0=KP_MSG_WSANO_RECOVERY; break;
//      case WSAPROVIDERFAILEDINIT:   msg0=KP_MSG_WSAPROVIDERFAILEDINIT; break;
        case WSASYSCALLFAILURE:       msg0=KP_MSG_WSASYSCALLFAILURE; break;
        case WSASYSNOTREADY:          msg0=KP_MSG_WSASYSNOTREADY; break;
        case WSATRY_AGAIN:            msg0=KP_MSG_WSATRY_AGAIN; break;
        case WSAVERNOTSUPPORTED:      msg0=KP_MSG_WSAVERNOTSUPPORTED; break;
        case WSAEDISCON:              msg0=KP_MSG_WSAEDISCON; break;
        case WSA_OPERATION_ABORTED:   msg0=KP_MSG_WSA_OPERATION_ABORTED; break;

//      switch((int)hErrorCode)
//      {
// !!! case 0:                      msg0=KP_MSG_OUT_OF_MEM_RES; break;
        case ERROR_FILE_NOT_FOUND:    msg0=KP_MSG_ERROR_FILE_NOT_FOUND; break;
        case ERROR_PATH_NOT_FOUND:    msg0=KP_MSG_ERROR_PATH_NOT_FOUND; break;
        case ERROR_BAD_FORMAT:        msg0=KP_MSG_ERROR_BAD_FORMAT; break;
        case SE_ERR_ACCESSDENIED:     msg0=KP_MSG_SE_ERR_ACCESSDENIED; break;
        case SE_ERR_ASSOCINCOMPLETE:  msg0=KP_MSG_SE_ERR_ASSOCINCOMPLETE; break;
        case SE_ERR_DDEBUSY:          msg0=KP_MSG_SE_ERR_DDEBUSY; break;
        case SE_ERR_DDEFAIL:          msg0=KP_MSG_SE_ERR_DDEFAIL; break;
        case SE_ERR_DDETIMEOUT:       msg0=KP_MSG_SE_ERR_DDETIMEOUT; break;
        case SE_ERR_DLLNOTFOUND:      msg0=KP_MSG_SE_ERR_DLLNOTFOUND; break;
//      case SE_ERR_FNF:              msg0=KP_MSG_SE_ERR_FNF; break;
        case SE_ERR_NOASSOC:          msg0=KP_MSG_SE_ERR_NOASSOC; break;
        case SE_ERR_OOM:              msg0=KP_MSG_SE_ERR_OOM; break;
//      case SE_ERR_PNF:              msg0=KP_MSG_SE_ERR_PNF; break;
        case SE_ERR_SHARE:            msg0=KP_MSG_SE_ERR_SHARE; break;

// klaidos iš­ GetAdaptersAddresses(), naudojama KpSocket::Bind()
//      case ERROR_ADDRESS_NOT_ASSOCIATED:  "DHCP lease information was available."
//      case ERROR_BUFFER_OVERFLOW:         "The buffer size indicated by the SizePointer parameter is too small to hold the adapter information or the AdapterAddresses parameter is NULL. The SizePointer parameter returned points to the required size of the buffer to hold the adapter information."
//      case ERROR_INVALID_PARAMETER:       "One of the parameters is invalid. This error is returned for any of the following conditions: the SizePointer parameter is NULL, the Address parameter is not AF_INET, AF_INET6, or AF_UNSPEC, or the address information for the parameters requested is greater than ULONG_MAX."
//      case ERROR_NOT_ENOUGH_MEMORY:       "Insufficient memory resources are available to complete the operation."
//      case ERROR_NO_DATA:                 "No addresses were found for the requested parameters."

// FindFirstFile(), FindNextFile(), FindClose()
//      case ERROR_NO_MORE_FILES:
#endif
        default: msg0 = null; break;
        }

        msg = null;
#ifdef __WIN32__
#ifdef UNICODE
// TODO:
#else
        if ((msg0 == null) || p_bFullFormat) if(FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_IGNORE_INSERTS |
            FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, p_lWindowsErrorCode, 0,
            (char *)&msg, 0, NULL) == 0)
        {
            msg = null; // nesuformavo
        }
#endif
#endif
//      if ((msg0 == null) && (msg == null))
        {
            sprintf((char *)str_buf, " %ld", p_lWindowsErrorCode);
//          msg0 = str_buf;
        }

    } // if (p_lWindowsErrorCode)

    if ((msg0 || msg || str_buf[0]) && SUCCEEDED(retc))
    {
        ii = 20;
        if (msg0) ii += strlen(msg0);
        if (msg) ii += strlen(msg);
        ii += strlen(str_buf);

//      KP_NEWA(msg1, unsigned char, ii + 1); // isvieciamas ir is KP_NEWA(), gali uzsiciklint
        msg1 = new uchar[ii + 1];

        if (msg1 && SUCCEEDED(retc))
        {
            msg1[0] = Nul;
            if (msg0)
            {
                strcat(msg1, msg0);
                if (msg) strcat(msg1, "; ");
            }

            if (msg) strcat(msg1, msg);

            pnts = msg1 + strlen(msg1);
            if (pnts > msg1) if (*(--pnts) == Lf) *pnts = Nul;
            if (pnts > msg1) if (*(--pnts) == Cr) *pnts = Nul;
            if (pnts > msg1) if (*(--pnts) == '.') *pnts = Nul;

            if (msg1[0] && str_buf[0]) strcat(msg1, "; ");
            strcat(msg1, str_buf);
        }
    }

    if (msg1 && SUCCEEDED(retc))
    {
        if (strlen(msg1) > KP_MAX_FILE_LIN_LEN)
        {
            msg1[KP_MAX_FILE_LIN_LEN] = Nul;
            KP_WARNING(KP_E_BUFFER_OVERFLOW, null);
        }
        strcpy(p_pszMsg, msg1);
    }

//  KP_DELETEA(msg1); // šiaip iškviečiamas ir iš KP_DELETE(), gali ir užsiciklint
    if (msg1) delete [] msg1;
    msg1 = null;

#ifdef __WIN32__
    if (msg!=null) LocalFree((HLOCAL)msg);
#endif

return(S_OK);
}


uchar *KpErrorClass::FormatSystemErrorMessage(long p_lWindowsErrorCode)
{
static uchar sys_err_msg[KP_MAX_FILE_LIN_LEN + 1];
    FormatSystemErrorMessage(p_lWindowsErrorCode, sys_err_msg, True);
return(sys_err_msg);
}


// ------------------------------------
const uchar *KpErrorClass::FormatErrorMessageHTTP(int p_iHTTP_RetCode)
{
static uchar out_buf[MAX_LONG_DIGITS + 100];
    sprintf((char *)out_buf, "HTTP status: %d", p_iHTTP_RetCode);

MSG_TYPE retv = out_buf;
    switch(p_iHTTP_RetCode)
    {
        case HTTP_ANSW_CONTINUE /* 100 */:
            retv = (MSG_TYPE)"Continue"; break;
        case 101: retv = (MSG_TYPE)"Switching Protocols"; break;
        case HTTP_ANSW_OK /* 200 */: retv = (MSG_TYPE)"OK"; break;
        case 201: retv = (MSG_TYPE)"Created"; break;
        case 202: retv = (MSG_TYPE)"Accepted"; break;
        case 203: retv = (MSG_TYPE)"Non-Authoritative Information"; break;
        case 204: retv = (MSG_TYPE)"No Content"; break;
        case 205: retv = (MSG_TYPE)"Reset Content"; break;
        case 206: retv = (MSG_TYPE)"Partial Content"; break;
        case 300: retv = (MSG_TYPE)"Multiple Choices"; break;
        case 301: retv = (MSG_TYPE)"Moved Permanently"; break;
        case HTTP_ANSW_FOUND /* 302 */: retv = (MSG_TYPE)"Found"; break;
        case 303: retv = (MSG_TYPE)"See Other"; break;
        case 304: retv = (MSG_TYPE)"Not Modified"; break;
        case 305: retv = (MSG_TYPE)"Use Proxy"; break;
        case 307: retv = (MSG_TYPE)"Temporary Redirect"; break;
        case 400: retv = (MSG_TYPE)"Bad Request"; break;
        case 401: retv = (MSG_TYPE)"Unauthorized"; break;
        case 402: retv = (MSG_TYPE)"Payment Required"; break;
        case 403: retv = (MSG_TYPE)"Forbidden"; break;
        case HTTP_ANSW_FILE_NOT_FOUND /* 404 */:
            retv = (MSG_TYPE)"Not Found"; break;
        case 405: retv = (MSG_TYPE)"Method Not Allowed"; break;
        case 406: retv = (MSG_TYPE)"Not Acceptable"; break;
            // serveris negali išsiųsti failo, užkoduoto nė vienu iš metodų,
            // nurodytų HTTP užklausos lauke Accept-Encoding:
        case 407: retv = (MSG_TYPE)"Proxy Authentication Required"; break;
        case 408: retv = (MSG_TYPE)"Request Timeout"; break;
        case 409: retv = (MSG_TYPE)"Conflict"; break;
        case 410: retv = (MSG_TYPE)"Gone"; break;
        case 411: retv = (MSG_TYPE)"Length Required"; break;
        case 412: retv = (MSG_TYPE)"Precondition Failed"; break;
        case 413: retv = (MSG_TYPE)"Request Entity Too Large"; break;
        case 414: retv = (MSG_TYPE)"Request-URI Too Long"; break;
        case 415: retv = (MSG_TYPE)"Unsupported Media Type"; break;
        case 416: retv =
            (MSG_TYPE)"Requested Range Not Satisfiable"; break;
        case 417: retv = (MSG_TYPE)"Expectation Failed"; break;
        case 500: retv = (MSG_TYPE)"Internal Server Error"; break;
        case 501: retv = (MSG_TYPE)"Not Implemented"; break;
        case 502: retv = (MSG_TYPE)"Bad Gateway"; break;
        case 503: retv = (MSG_TYPE)"Service Unavailable"; break;
        case 504: retv = (MSG_TYPE)"Gateway Timeout"; break;
        case 505: retv = (MSG_TYPE)"HTTP Version Not Supported"; break;
   }

return (retv);
}


// ------------------------------------
int KpErrorClass::TranslToHTTP_RetCode(HRESULT p_lRetc)
{
int retv = 500 /* Internal Server Error */;

    switch(p_lRetc)
    {
        case S_OK:                  retv = HTTP_ANSW_OK /* 200 OK */; break;
                                        // 100 continue
                                        // 201 Created
                                        // 202 Accepted
                                        // 302 Found
                                        // 300 Multiple Choices

//      case E_INVALIDARG:          retv = ; break; // 411 Length Required

        case E_NOTIMPL:             retv = 501 /* Not Implemented */; break;
                                        // 505 HTTP Version Not Supported

//      case KP_E_FERROR:           retv = ; break;

        case KP_E_SYSTEM_ERROR:     retv = 500 /* Internal Server Error */;
                                        break;
                                        // 409 Conflict
                                        // 412 Precondition Failed

//      case KP_E_EOF:              retv = ; break;

        case KP_E_FILE_FORMAT:      retv = 415; break;
                                        // Unsupported Media Type
                                        // 417 Expectation Failed
                                        // 406 Not Acceptable

        case KP_E_FILE_NOT_FOUND:   retv = HTTP_ANSW_FILE_NOT_FOUND
                                        /* 404 Not Found */; break;
                                        // 410 Gone
                                        // 301 Moved Permanently

//      case KP_E_DIR_ERROR:        retv = ; break;
//      case KP_E_OUTOFMEM:         retv = ; break;
        case KP_E_NO_FILE:          retv = 204 /* No Content */; break;
//      case KP_E_DOUBLE_UNGET:     retv = ; break;
//      case KP_E_UNKN_CHR:         retv = ; break;
//      case KP_E_COMMAND_ERROR:    retv = ; break;

        case KP_E_BUFFER_OVERFLOW:  retv = 413 /* Request Entity Too Large */;
                                        break;
                                        // 414 Request-URI Too long
                                        // 416 Requested Range Not Satisfiable

//      case KP_E_FONT_UNDEF:       retv = ; break;
//      case KP_E_KWD_NOT_FOUND:    retv = ; break;
//      case KP_E_UNKNOWN_SYSTEM:   retv = ; break;
//      case KP_E_ILL_CODE:         retv = ; break;
//      case KP_E_CANCEL:           retv = ; break;
//      case KP_E_DOUBLE_CALL:      retv = ; break;

        case KP_E_TIMEOUT:          retv = 408 /* Request Timeout */; break;
                                        // 504 Gateway Timeout

//      case KP_E_OBJ_NOT_FOUND:    retv = ; break;

        case KP_E_NO_CONN:          retv = 408 /* Request Timeout */; break;

        case KP_E_TRANS_ERR:        retv = 408 /* Request Timeout */; break;
                                        // 305 Use Proxy
                                        // 502 Bad Gateway

        case KP_E_REFUSED:          retv = 403 /* Forbidden */; break;

        case KP_E_ACCESS_DENIED:    retv = 401 /* Unauthorized */; break;
                                        // 402 Payment Required
                                        // 407 Proxy Authentication Required

//      case KP_E_ILL_CHR:          retv = ; break;
//      case KP_E_DIV_ZERO:         retv = ; break;
//      case KP_E_ILLMATHARG:       retv = ; break;

        case KP_E_ILLFUNC:          retv = 400 /* Bad Request */; break;
                                        // 405 Method Not Allowed

        case KP_E_NOTINST:          retv = 503 /* Service Unavailable */;
                                        break;
    }

// 101 Switching Protocols
// 203 Non-Authoritative Information
// 205 Reset Content
// 206 Partial Content
// 303 See Other
// 304 Not Modified
// 307 Temporary Redirect

return(retv);
}


// ------------------------------------
HRESULT KpErrorClass::TranslFromHTTP_RetCode(int p_iHTTP_RetCode)
{
HRESULT retc = (p_iHTTP_RetCode == HTTP_ANSW_OK)?S_OK:KP_E_NEG_ANSW;

    switch(p_iHTTP_RetCode)
    {
        case HTTP_ANSW_OK /* 200 OK */:
        case HTTP_ANSW_CONTINUE /* 100 */:
        case 201 /* Created */:
        case 202 /* Accepted */:
        case 300 /* Multiple Choices */:
                                            retc = S_OK; break;

// šitais atvejais reikėtų šokti nuoroda, nurodyta headerio lauke Location:,
// kol kas nerealizuota (kliento gale)
        case 302 /* Found */ /* Moved Temporarily */:
        case 303 /* See Other */:
        case 307 /* Temporary Redirect */:
        case 301 /* Moved Permanently */:
        case 305 /* Use Proxy */:
                                            retc = E_NOTIMPL; break;

        case 304 /* Not Modified */:
            // atsakymas į sąlyginę GET užklausą -- tuščias atsakymas apie
            //      nepasikeitusį failą (tikriausiai, pasitikrinimui, ar reikia
            //      perkrauti cache'intą failą)
            // aš tokių užklausų kol kas nesiunčiu, tai ir atsakymo turėtų
            //      neateiti
                                            retc = KP_E_FILE_FORMAT; break;

        case 411 /* Length Required */:     retc = E_INVALIDARG; break;

        case 501 /* Not Implemented */:
        case 505 /* HTTP Version Not Supported */:
            // nerealizuota funkcija serverio gale
                                            retc = E_NOTIMPL; break;

//      case :                              retc = KP_E_FERROR; break;

        case 500 /* Internal Server Error */:
        case 409 /* Conflict */:
        case 412 /* Precondition Failed */: retc = KP_E_SYSTEM_ERROR; break;

//      case :                              retc = KP_E_EOF; break;

        case 415 /* Unsupported Media Type */:
        case 417 /* Expectation Failed */:
        case 406 /* Not Acceptable */:      retc = KP_E_FILE_FORMAT; break;

        case HTTP_ANSW_FILE_NOT_FOUND /* 404 Not Found */:
        case 410 /* Gone */:
                                            retc = KP_E_FILE_NOT_FOUND; break;

//      case :                              retc = KP_E_DIR_ERROR; break;
//      case :                              retc = KP_E_OUTOFMEM; break;
        case 204 /* No Content */:          retc = KP_E_NO_FILE; break;
//      case :                              retc = KP_E_DOUBLE_UNGET; break;
//      case :                              retc = KP_E_UNKN_CHR; break;
//      case :                              retc = KP_E_COMMAND_ERROR; break;

        case 413 /* Request Entity Too Large */:
        case 414 /* Request-URI Too long */:
        case 416 /* Requested Range Not Satisfiable */:
                                            retc = KP_E_BUFFER_OVERFLOW; break;

//      case :                              retc = KP_E_FONT_UNDEF; break;
//      case :                              retc = KP_E_KWD_NOT_FOUND; break;
//      case :                              retc = KP_E_UNKNOWN_SYSTEM; break;
//      case :                              retc = KP_E_ILL_CODE; break;
//      case :                              retc = KP_E_CANCEL; break;
//      case :                              retc = KP_E_DOUBLE_CALL; break;

        case 502 /* Bad Gateway */:         retc = KP_E_TRANS_ERR; break;

        case 408 /* Request Timeout */:  // retc = KP_E_TRANS_ERR; break;
                                         // retc = KP_E_NO_CONN; break;
        case 504 /* Gateway Timeout */:     retc = KP_E_TIMEOUT; break;

//      case :                              retc = KP_E_OBJ_NOT_FOUND; break;

        case 401 /* Unauthorized */:        retc = KP_E_ACCESS_DENIED; break;
        case 403 /* Forbidden */:
        case 402 /* Payment Required */:
        case 407 /* Proxy Authentication Required */:
                                            retc = KP_E_REFUSED; break;

//      case :                              retc = KP_E_ILL_CHR; break;
//      case :                              retc = KP_E_DIV_ZERO; break;
//      case :                              retc = KP_E_ILLMATHARG; break;

        case 400 /* Bad Request */:
        case 405 /* Method Not Allowed */:  retc = KP_E_ILLFUNC; break;

        case 503 /* Service Unavailable */: retc = KP_E_NOTINST; break;
    }

// 101 Switching Protocols
// 203 Non-Authoritative Information
// 205 Reset Content
// 206 Partial Content
// 303 See Other
// 304 Not Modified
// 307 Temporary Redirect

return(retc);
}


// ---------------------
void KpErrorClass::SendDiagMsg(
    const uchar *
#if (!defined(KP_VERBOSE)) && (!defined(Debug))
        p_pszMessageText
#endif
    , bool /* p_bSevereError */, const uchar * /* p_pszAddMessage */)
{
#ifdef KP_CONSOLE
#if (!defined(KP_VERBOSE)) && (!defined(Debug))
   // KP_VERBOSE ar Debug režime OutputErrorMessage() (PutLogMessage()) jau išvedė
// cerr /* cout */ << p_pszMessageText << endl;
   fprintf(stderr, "%s\n", p_pszMessageText);
#endif
#else
// TODO:
// #error Not yet implemented
#endif
}

// ---------------------
void KpErrorClass::OutputErrorMessage(HRESULT p_lhRetc, const uchar *p_pszFmt,
   bool p_bSevereError, const uchar *p_pszSourceFile, int p_iSourceLine, ...)
{
HRESULT retc = p_lhRetc;
    if (retc == KP_S_DIAG_MSG) retc = S_OK;

// -----------------------
uchar msg_text[KP_MAX_FILE_LIN_LEN + 1];
    msg_text[0] = Nul;
    if (p_pszFmt)
    {
    uchar *out_str = null;
        KP_NEWA(out_str, uchar, KP_MAX_FILE_LIN_LEN + strlen(p_pszFmt) * 10 + 1000);

        va_list argptr;
        va_start(argptr, p_iSourceLine);
        sprintf((char *)out_str, (const char *)p_pszFmt, argptr);

        strcpy(msg_text, ": ");
    int ll = strlen(msg_text);
        strncpy(msg_text + ll, out_str, KP_MAX_FILE_LIN_LEN - ll);
        msg_text[KP_MAX_FILE_LIN_LEN] = Nul;

        KP_DELETEA(out_str);
    }

// -----------------------
    if
    (
        (m_lhLastRetc != retc) ||
        strcmp(m_pszLastMessageText, msg_text) ||
        strcmp(m_pszLastSourceFile, p_pszSourceFile) ||
        (m_iLastSourceLine != p_iSourceLine)
    )
    {
        m_lhLastRetc = p_lhRetc;
        strncpy(m_pszLastMessageText, msg_text, KP_MAX_FILE_LIN_LEN);
        m_pszLastMessageText[KP_MAX_FILE_LIN_LEN] = Nul;
        strncpy(m_pszLastSourceFile, p_pszSourceFile, KP_MAX_FNAME_LEN);
        m_pszLastSourceFile[KP_MAX_FNAME_LEN] = Nul;
        m_iLastSourceLine = p_iSourceLine;

// -----------------------
    uchar out_text[KP_MAX_FILE_LIN_LEN * 2 + 1];
        out_text[0] = Nul;

        if (FAILED(retc))
        {
            strncpy(out_text, p_bSevereError?KP_MSG_ERROR:KP_MSG_WARNING, KP_MAX_FILE_LIN_LEN - 2);
            out_text[KP_MAX_FILE_LIN_LEN - 2] = Nul;
            strcat(out_text, ": ");
        }

        FormatErrorMessage(p_lhRetc, out_text + strlen(out_text));

    int ll = strlen(out_text);
        strncpy(out_text + ll, msg_text, KP_MAX_FILE_LIN_LEN - ll);
        out_text[KP_MAX_FILE_LIN_LEN] = Nul;

    int msg_tail_pos = ll = strlen(out_text);
        sprintf((char *)out_text + ll, (const char *)KP_MSG_FILE_LINE, p_lhRetc, p_pszSourceFile, p_iSourceLine);
        out_text[KP_MAX_FILE_LIN_LEN] = Nul;

// ----------------------
        PutLogMessage(out_text);
//      if (bSevereError) StackDump();

#ifndef Debug
//      out_text[msg_tail_pos] = Nul;
#endif
        if (p_bSevereError || (p_lhRetc == KP_S_DIAG_MSG))
            SendDiagMsg(out_text, p_bSevereError, out_text + msg_tail_pos + 1);
#if ((defined(KP_VERBOSE)) && (!defined(Debug)) && (defined(KP_CONSOLE)))
        // Debug režime PutLogMessage() jau išvedė
        else
        {
//          cerr /* cout */ << out_text << endl;
            fprintf(stderr, "%s\n", out_text);
        }
#endif
    }
}


// ---------------------
#if FALSE
void KpErrorClass::StackDump(void)
{
    if (m_iInsideOfStackDump++ == 0)
    {
// --------------------
        KP_ASSERT(sizeof(int) == sizeof(unsigned int *), KP_E_SYSTEM_ERROR, null);

// --------------------
unsigned int ebp_buf = 0;
#ifdef __MINGW32__
        asm("movl %%ebp, %0\n":"=r"(ebp_buf));
        KP_ASSERT(ebp_buf, KP_E_SYSTEM_ERROR, null);
#endif
const unsigned int *stack_ptr = (const unsigned int *)ebp_buf;

// --------------------
const unsigned int *stack_top = NULL;
const unsigned int *stack_top_os = NULL;
#ifdef __MINGW32__
THREAD_BASIC_INFORMATION basicInfo;
NT_TIB *tib_ptr = NULL;
NTSTATUS retw = STATUS_SEVERITY_SUCCESS;

        retw = NtQueryInformationThread(GetCurrentThread(),
            ThreadBasicInformation, &basicInfo, sizeof(THREAD_BASIC_INFORMATION), NULL);
        KP_ASSERT(retw == STATUS_SEVERITY_SUCCESS, KP_E_SYSTEM_ERROR, retw);

        tib_ptr = (NT_TIB *)basicInfo.TebBaseAddress;
        KP_ASSERT(tib_ptr, KP_E_SYSTEM_ERROR, null);

        stack_top = stack_top_os = (unsigned int *)tib_ptr->StackBase;
        KP_ASSERT(stack_top, KP_E_SYSTEM_ERROR, null);
#endif
        if (KpApp) if (KpApp->m_pStackTop)
            stack_top = (const unsigned int *)KpApp->m_pStackTop;

        KpError.PutLogMessage("Stack ptr: %lx  Stack top: %lx  Stack top local: %lx", stack_ptr, stack_top_os, stack_top);

// --------------------
        if (ebp_buf && stack_top)
        {
        uchar *out_buf = null;
            KP_NEWA(out_buf, uchar, KP_MAX_FILE_LIN_LEN + 1);

            strcpy(out_buf, "Stack call trace: ");
            while ((stack_ptr < stack_top - 4 /* 0x40 */) && (strlen(out_buf) <= (KP_MAX_FILE_LIN_LEN - MAX_LONG_HEX_DIGITS - 1)))
            {
            uchar hex_buf[MAX_LONG_HEX_DIGITS + 1 + 1];
                sprintf((char *)hex_buf, "%08x ", stack_ptr[1]);
                strcat(out_buf, hex_buf);
                stack_ptr = (const unsigned int *)(*stack_ptr);
                if (stack_ptr == NULL) break;
            }

            KpError.PutLogMessage(out_buf);

            KP_DELETEA(out_buf);
        }

// --------------------
    }
    m_iInsideOfStackDump--;
    if (m_iInsideOfStackDump < 0) m_iInsideOfStackDump = 0;
}
#endif


// ----------------------------------------------
void KpErrorClass::EncodeLogBuf(uchar *p_pBuffer, int p_iDataLen)
{
   KP_ASSERT(p_pBuffer, E_INVALIDARG, null);
   for (int ii = 0; ii < p_iDataLen; ii++) p_pBuffer[ii] ^= 0xAA;
}


// ----------------------------------------------
void KpErrorClass::GetLogFileName(uchar *p_pszLogFNameBuf)
{
    KP_ASSERT(p_pszLogFNameBuf, E_INVALIDARG, null);

MSG_TYPE temp_dir = null;
#ifdef __WIN32__
    temp_dir = (MSG_TYPE)getenv("TEMP");
    KP_ASSERT(temp_dir, KP_E_SYSTEM_ERROR, null);
#else
    temp_dir = (MSG_TYPE)KP_CUR_DIR_STR;
#endif

static uchar app_name[KP_MAX_FNAME_LEN + 1];
    KpError.GetProdName(app_name);
    if (KpApp) KpApp->GetAppName(app_name);

static uchar app_disk[KP_MAX_FNAME_LEN + 1];
static uchar app_path[KP_MAX_FNAME_LEN + 1];
static uchar app_fname[KP_MAX_FNAME_LEN + 1];
static uchar app_ftype[KP_MAX_FNAME_LEN + 1];
    KpStdIo::TvFnameSplit(app_disk, app_path, app_fname, app_ftype, app_name);

const uchar *log_ftype = (MSG_TYPE)".log";
    KP_ASSERT(strlen(temp_dir) + 1 + strlen(app_fname) + strlen(log_ftype) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null);
    strcpy(p_pszLogFNameBuf, temp_dir);
    strcat(p_pszLogFNameBuf, "/");
    strcat(p_pszLogFNameBuf, app_fname);
    strcat(p_pszLogFNameBuf, log_ftype);
}


// ----------------------------------------------
void KpErrorClass::PutLogMessage(const uchar *p_pszFmt, va_list Args)
{
    if (m_iInsideOfPutLogMessage++ == 0)
    {
// --------------------

    uchar *out_str = null;
        KP_NEWA(out_str, uchar, KP_MAX_FILE_LIN_LEN + strlen(p_pszFmt) * 10 + 1000);

// --------------------
time_t ltime;
        time(&ltime);
tm *tm_ptr = NULL;
        tm_ptr = gmtime(&ltime);
        KP_ASSERT(tm_ptr, KP_E_SYSTEM_ERROR, null);
// gcc 5.4.0 does not distinguish between a pointer to const and const pointer
#if (__GNUC__ != 5) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 0)
    const
#endif
        uchar *prod_name = (MSG_TYPE)"kperr";
    int prod_ver = 0;
#if (__GNUC__ != 5) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 0)
    const
#endif
        uchar *prod_date = (MSG_TYPE)"0000-00-00";
        if (KpApp)
        {
            prod_name = m_pszProdName;
            prod_ver = KpApp->m_iProdVer;
            prod_date = KpApp->m_pszProdDate;
        }
        sprintf((char *)out_str, "%04d.%02d.%02d %02d:%02d:%02d %s[%05d:%s] %ld ",
            1900 + tm_ptr->tm_year, 1 + tm_ptr->tm_mon, tm_ptr->tm_mday, tm_ptr->tm_hour + 2, tm_ptr->tm_min, tm_ptr->tm_sec,
            prod_name, prod_ver, prod_date, ltime);

// --------------------
        if (p_pszFmt)
            vsprintf((char *)out_str + strlen(out_str), (const char *)p_pszFmt, Args);
        strcat(out_str, "\n");

#if (defined Debug) && (defined KP_CONSOLE)
        cerr /* cout */ << out_str;
#endif

// --------------------
int out_str_len = strlen(out_str);
#  ifdef ENCODE_LOG
        if (SUCCEEDED(retc)) retc = EncodeLogBuf(out_str, out_str_len);
#  endif

// --------------------
static uchar log_fname[KP_MAX_FNAME_LEN + 1];
        GetLogFileName(log_fname);

// --------------------
FILE *log_file = NULL;
        log_file = fopen((const char *)log_fname,
#  ifdef KP_ENCODE_LOG
            "ab"
#  else
            "a"
#  endif
            );
        KP_ASSERT(log_file, KP_E_DIR_ERROR, log_fname);

// --------------------
        fwrite(out_str, out_str_len, 1, log_file);
        KP_ASSERT((!feof(log_file)) && (!ferror(log_file)), KP_E_FERROR, log_fname);

// --------------------
        KP_ASSERT(fclose(log_file) == 0, KP_E_FERROR, log_fname);

// --------------------
        KP_DELETEA(out_str);

// --------------------
    }
    m_iInsideOfPutLogMessage--;
    if (m_iInsideOfPutLogMessage < 0) m_iInsideOfPutLogMessage = 0;
}


// --------------------
void KpErrorClass::Catch(const exception &p_rExc)
{
   try
   {
      if (&p_rExc == NULL)
      {
         KP_ERROR(E_POINTER, null);
      }
      else
      {
const KpException *exc = dynamic_cast<const KpException *>(&p_rExc);

         if (exc == NULL)
         {
            KP_ERROR(KP_E_UNHANDLED_EXCEPTION, p_rExc.what());
         }
         else
         {
// TODO: perdaryt į KpError.OutputErrorMessage(p_KpExc.what(), True, null); (parametrai kaip SendDiagMsg)
            if (exc->m_pszMsg[0])
               KpError.OutputErrorMessage(exc->m_lhErrCode, exc->m_pszMsg, True, exc->m_pszSourceFile, exc->m_iSourceLine);
            else
               KpError.OutputErrorMessage(exc->m_lhErrCode, exc->m_lWindowsErrorCode, True, exc->m_pszSourceFile, exc->m_iSourceLine);
         }
      }
   }
   catch(exception& rExc)
   {
      KP_ERROR(KP_E_UNHANDLED_EXCEPTION, rExc.what());
   }
}


// --------------------------------------------------
void KpOutputErrorMessage
(
    HRESULT p_lhRetc,
    const uchar *p_pszFmt,
    bool p_bSevereError,
    const uchar *p_pszSourceFile,
    int p_iSourceLine,
    ...
)
{
va_list argptr;
    va_start(argptr, p_iSourceLine);
    KpError.OutputErrorMessage(p_lhRetc, p_pszFmt, p_bSevereError, p_pszSourceFile, p_iSourceLine, argptr);
}


uchar *KpFormatSystemErrorMessage(LONG p_lWindowsErrorCode)
{
return(KpError.FormatSystemErrorMessage(p_lWindowsErrorCode));
}


void KpPutLogMessage(const uchar *p_pszFmt, ...)
{
va_list argptr;
    va_start(argptr, p_pszFmt);
    KpError.PutLogMessage(p_pszFmt, argptr);
}
