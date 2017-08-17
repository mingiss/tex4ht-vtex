// -----------------------------------------
// kpmsg.h
// kp programų pranešimai
//

#ifndef KPMSG_INCLUDED
#define KPMSG_INCLUDED


#if (__GNUC__ != 5) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 0)
#define MSG_TYPE const uchar *
#else
#define MSG_TYPE uchar *
#endif

// --------------------------------------- common kp messages
enum
{
KP_MSG_TITLE_IX,                    // "Pranešimas"
KP_INPUT_TITLE_IX,                  // "Įvedimas"

KP_MSG_TAIP_IX,                     // "Taip"
KP_MSG_YES_IX,                      // KP_MSG_TAIP
KP_MSG_NE_IX,                       // "Ne"
KP_MSG_NO_IX,                       // KP_MSG_NE
KP_MSG_GERAI_IX,                    // "Gerai"
KP_MSG_OK_IX,                       // KP_MSG_GERAI
KP_MSG_ATSAUKTI_IX,                 // "Atšaukti"
KP_MSG_CANCEL_IX,                   // KP_MSG_ATSAUKTI
KP_MSG_TESTI_IX,                    // "Toliau"
KP_MSG_BAIGTI_IX,                   // "Baigti"
KP_MSG_PAMIRSAU_SLAPTAZODI_IX,      // "Pamiršau slaptažodį"

KP_MSG_ERROR_IX,                    // "Klaida"
KP_MSG_WARNING_IX,                  // "Perspėjimas"
KP_MSG_FILE_LINE_IX,                // ", failas:%s, eilutė:%d"
KP_MSG_ENTRY_ID_IX,                 // ", Įrašo nr.:%ld"
KP_MSG_ENTRY_IX,                    // ", Įrašas: %s"

KP_MSG_NO_STANDARD_PROG_IX,         // "Nerasta programa skirta atverti šio tipo failus"
KP_MSG_WND_NOT_FOUND_IX,            // "Langas nerastas"
KP_MSG_PID_NOT_FOUND_IX,            // "Nerastas proceso identifikatorius"
KP_MSG_NO_SOCKET_IX,                // "Jungtis dar nesukurta"
KP_MSG_SOCK_UNRESOLVED_IX,          // "Tarnybinės stoties adresas dar nesurastas"

KP_MSG_ERR_OK_IX,                   // "Operacija atlikta sėkmingai" // !!!
KP_MSG_INVALIDARG_IX,               // "Neteisingi parametrai"
KP_MSG_NOTIMPL_IX,                  // "Priedas neįdiegtas"
KP_MSG_UNEXPECTED_IX,               // "Netikėtas kreipinys į sąsają"
KP_MSG_FERROR_IX,                   // "Failo skaitymo/rašymo klaida"
KP_MSG_SYSTEM_ERROR_IX,             // "Klaida sistemoje"
KP_MSG_EOF_IX,                      // "Neteisinga failo pabaiga"
KP_MSG_FILE_FORMAT_IX,              // "Neteisingas failo formatas"
KP_MSG_FILE_NOT_FOUND_IX,           // "Failas nerastas"
KP_MSG_DIR_ERROR_IX,                // "Nepavyko atverti/sukurti failo"
KP_MSG_OUTOFMEM_IX,                 // "Trūksta atminties"
KP_MSG_NO_FILE_IX,                  // "Failas neatvertas"
KP_MSG_DOUBLE_UNGET_IX,             // "Dvigubas įvedimo grąžinimas"
KP_MSG_UNKN_CHR_IX,                 // "Neatpažintas simbolis"
KP_MSG_COMMAND_ERROR_IX,            // "Išorinė klaida"
KP_MSG_BUFFER_OVERFLOW_IX,          // "Persipildė buferis"
KP_MSG_FONT_UNDEF_IX,               // "Neapibrėžtas šriftas"
KP_MSG_KWD_NOT_FOUND_IX,            // "Raktinis žodis nerastas"
KP_MSG_UNKNOWN_SYSTEM_IX,           // "Operacinė sistema neatpažinta"
KP_MSG_ILL_CODE_IX,                 // "Klaidingas registracijos kodas"
KP_MSG_CANCELLED_IX,                // "Operacija nutraukta"
KP_MSG_DOUBLE_CALL_IX,              // "Dvigubas iškvietimas"
KP_MSG_TIMEOUT_IX,                  // "Viršytas laukimo laikas"
KP_MSG_OBJ_NOT_FOUND_IX,            // "Objektas nerastas"
KP_MSG_NO_CONN_IX,                  // "Nėra ryšio"

KP_MSG_TRANS_ERR_IX,                // "Perdavimo klaida"
KP_MSG_TRANS_ERR_1_IX,              // "Ryšio klaida, pakartokite siuntimo procedūrą"

KP_MSG_REFUSED_IX,                  // "Registracija atmesta"
KP_MSG_ACCESS_DENIED_IX,            // "Neleista prisijungti"
KP_MSG_ILLEGAL_CHARACTER_IX,        // "Neleistinas simbolis"
KP_MSG_DIV_ZERO_IX,                 // "Dalyba iš nulio"
KP_MSG_ILLMATHARG_IX,               // "Neleistinas matematinės funkcijos argumentas" // "Šaknis iš neigiamo skaičiaus"
KP_MSG_ILLFUNC_IX,                  // "Neleistina operacija" // illegal function call (at the moment)

KP_MSG_NOTINST_IX,                  // "Programa neįdiegta arba diegimas sugedo, pakartokite diegimo procedūrą"
KP_MSG_NOTINST_S_IX,                // "Produktas „%s“ neįdiegtas arba jo diegimas sugedo, pakartokite diegimo procedūrą"
KP_MSG_NOTINST_DELETE_IX,           // "Produktas neįdiegtas arba jo diegimas sugedo, produktą panaikinkite ir pakartokite diegimo procedūrą"

KP_MSG_MSG_FORMAT_IX,               // "Neteisingas pranešimo formatas"
KP_MSG_OBSOLETE_IX,                 // "Pasenusi funkcija"
KP_MSG_ERROR_HELP_IX,               // ".  Dėl techninės pagalbos kreipkitės elektroniniu paštu, adresu %s"
KP_MSG_ERROR_HELP_REST_IX,          // "   Prie laiško prikabinkite failą %s"
KP_MSG_WSAEACCES_IX,                // "Teisės nesuteiktos"
KP_MSG_WSAEADDRINUSE_IX,            // "Adresas jau naudojamas"
KP_MSG_WSAEADDRNOTAVAIL_IX,         // "Prašomas adresas negali būti priskirtas"
KP_MSG_WSAEAFNOSUPPORT_IX,          // "Adresų šeimos grupė nepalaikoma protokolo"
KP_MSG_WSAEALREADY_IX,              // "Operacija jau vykdoma"
KP_MSG_WSAECONNABORTED_IX,          // "Programa iššaukė ryšio nutraukimą"
KP_MSG_WSAECONNREFUSED_IX,          // "Susijungimas atmestas"
KP_MSG_WSAECONNRESET_IX,            // "Sujungimas nutrauktas"
KP_MSG_WSAEDESTADDRREQ_IX,          // "Būtinas kreipties adresas"
KP_MSG_WSAEFAULT_IX,                // "Neteisingas adresas"
KP_MSG_WSAEHOSTDOWN_IX,             // "Serveris laikinai neveikia"
KP_MSG_WSAEHOSTUNREACH_IX,          // "Serveris nepasiekiamas"
KP_MSG_WSAEINPROGRESS_IX,           // "Operacija vykdoma"
KP_MSG_WSAEINTR_IX,                 // "Funkcija nutraukta"
KP_MSG_WSAEINVAL_IX,                // "Neteisingi parametrai"
KP_MSG_WSAEISCONN_IX,               // "Susijungimas jau įvykęs"
KP_MSG_WSAEMFILE_IX,                // "Perdaug atvertų failų"
KP_MSG_WSAEMSGSIZE_IX,              // "Perdaug ilgas pranešimas"
KP_MSG_WSAENETDOWN_IX,              // "Tinklas neveikia"
KP_MSG_WSAENETRESET_IX,             // "Atsijungė nuo tinklo"
KP_MSG_WSAENETUNREACH_IX,           // "Tinklas nepasiekiamas"
KP_MSG_WSAENOBUFS_IX,               // "Trūksta vietos buferyje"
KP_MSG_WSAENOPROTOOPT_IX,           // "Neteisinga protokolo parinktis"
KP_MSG_WSAENOTCONN_IX,              // "Sujungimas nepavyko"
KP_MSG_WSAENOTSOCK_IX,              // "Socket operation on non-socket"
KP_MSG_WSAEOPNOTSUPP_IX,            // "Operacija negali būti atlikta"
KP_MSG_WSAEPFNOSUPPORT_IX,          // "Protokolo šeima nepalaikoma"
KP_MSG_WSAEPROCLIM_IX,              // "Perdaug procesų"
KP_MSG_WSAEPROTONOSUPPORT_IX,       // "Protokolas nepalaikomas"
KP_MSG_WSAEPROTOTYPE_IX,            // "Neteisingas protokolo sujungimo tipas"
KP_MSG_WSAESHUTDOWN_IX,             // "Siuntimas nebegalimas, sujungimas nutrauktas"
KP_MSG_WSAESOCKTNOSUPPORT_IX,       // "Sujungimo tipas nepalaikomas"
KP_MSG_WSAETIMEDOUT_IX,             // "Viršytas maksimalus sujungimo laukimo laikas"
KP_MSG_WSATYPE_NOT_FOUND_IX,        // "Klasės tipas nerastas"
KP_MSG_WSAEWOULDBLOCK_IX,           // "Šaltinis laikinai nepasiekiamas"
KP_MSG_WSAHOST_NOT_FOUND_IX,        // "Serveris nerastas"
KP_MSG_WSA_INVALID_HANDLE_IX,       // "Klaidingas objekto valdiklis" // "Klaidingas pasirinkto įvykio objekto valdiklis"
KP_MSG_WSA_INVALID_PARAMETER_IX,    // "Neteisingi parametrai" // "Neteisingi vienas ar daugiau parametrų"
KP_MSG_WSAINVALIDPROCTABLE_IX,      // "Klaidinga procedūrų lentelė"
KP_MSG_WSAINVALIDPROVIDER_IX,       // "Neteisingas tiekėjo kodas"
KP_MSG_WSA_IO_INCOMPLETE_IX,        // "Persikloja įvesties/išvesties įvykiai"
KP_MSG_WSA_IO_PENDING_IX,           // "Persiklojančios operacijos bus atliktos vėliau"

KP_MSG_WSA_NOT_ENOUGH_MEMORY_IX,    // "Nepakanka atminties"
KP_MSG_WSANOTINITIALISED_IX,        // "Tinklo posistemis neaktyvuotas"
KP_MSG_WSANO_DATA_IX,               // "Vardas teisingas, tačiau nėra reikiamo tipo duomenų"
KP_MSG_WSANO_RECOVERY_IX,           // "Nepataisoma klaida"
KP_MSG_WSAPROVIDERFAILEDINIT_IX,    // "Negalima inicializuoti paslaugos tiekėjo"
KP_MSG_WSASYSCALLFAILURE_IX,        // "Sistemos kreipinio klaida"
KP_MSG_WSASYSNOTREADY_IX,           // "Tinklo posistemė nepasiekiama"
KP_MSG_WSATRY_AGAIN_IX,             // "Neautorizuotas serveris nerastas"
KP_MSG_WSAVERNOTSUPPORTED_IX,       // "Netinka WINSOCK.DLL versija"
KP_MSG_WSAEDISCON_IX,               // "Pradėtas tvarkingas išjungimas" // "Pradėtas gracingas išjungimas"
KP_MSG_WSA_OPERATION_ABORTED_IX,    // "Persiklojanti operacija nutraukta"

KP_MSG_OUT_OF_MEM_RES_IX,           // "Operacinei sistemai trūksta atminties"
KP_MSG_ERROR_FILE_NOT_FOUND_IX,     // "Nurodytas failas nerastas"
KP_MSG_ERROR_PATH_NOT_FOUND_IX,     // "Nurodytas kelias iki failų nerastas"
KP_MSG_ERROR_BAD_FORMAT_IX,         // "Pasirinktas .exe failas sugadintas"
KP_MSG_SE_ERR_ACCESSDENIED_IX,      // "Operacinė sistema uždraudė prisijungimą prie reikiamų failų"
KP_MSG_SE_ERR_ASSOCINCOMPLETE_IX,   // "Failo sąryšis su programa nepilnas arba neteisingas"
KP_MSG_SE_ERR_DDEBUSY_IX,           // "DDE transakcija negali būti baigta, nes kitos DDE transakcijos dar vykdomos"
KP_MSG_SE_ERR_DDEFAIL_IX,           // "DDE transakcija nutraukta"
KP_MSG_SE_ERR_DDETIMEOUT_IX,        // "DDE transakcija negali būti baigta, nes neužteko nurodyto laukimo laiko"
KP_MSG_SE_ERR_DLLNOTFOUND_IX,       // "Nurodyta dinaminė biblioteka nerasta"
KP_MSG_SE_ERR_FNF_IX,               // "Nurodytas failas nerastas"
KP_MSG_SE_ERR_NOASSOC_IX,           // "Nerasta programa skirta atverti šio tipo failus"
KP_MSG_SE_ERR_OOM_IX,               // "Nepakanka atminties atlikti operacijai"
KP_MSG_SE_ERR_PNF_IX,               // "Nurodytas kelias nerastas"
KP_MSG_SE_ERR_SHARE_IX,             // "Dalijimosi klaida"

KP_MSG_FIRST_TIME_ADMIN_IX,         // "Programą paleidžiant pirmą kartą, reikalingos\n administratoriaus teisės. Paleiskite programą iš naujo administratoriaus teisėmis."
KP_MSG_NOW_NOT_ADMIN_IX,            // KP_MSG_NOT_ADMIN // "Dabar programą paleiskite dar kartą paprasto vartotojo teisėmis"
KP_MSG_NOT_ADMIN_IX,                // "Programą paleiskite iš naujo paprasto vartotojo teisėmis"
KP_MSG_COPY_FILE_ACCESS_DENIED_IX,  // "Failo nukopijuoti nepavyko, programą paleiskite iš naujo administratoriaus teisėmis"

KP_PROGRESS_TITLE_IX,               // "Palaukite..."
KP_MSG_DELETING_FILE_IX,            // "Naikinamas failas %s.%s..."
KP_MSG_COPYING_IX,                  // "Kopijuojamas failas..."
KP_MSG_COPYING_DIR_IX,              // "Kopijuojamas aplankas %s.%s..."
KP_MSG_COPYING_FILE_IX,             // "Kopijuojamas failas %s.%s..."

KP_MSG_NEG_ANSW_IX,                 // "Neigiamas atsakymas"

KP_MSG_UNABLE_TO_EXECUTE_IX,        // "Komandos %s įvykdyti negaliu – patikrinkite, ar teisingai įdiegėte visus sistemos komponentus"

KP_MSG_FLASH_PLAYER_INSTALL_IX,     // "Dabar bus įdiegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus."

KP_MSG_FILE_CHANGED_IX,             // "Failas pasikeitė"

KP_MSG_ALL_FILES_IX,                // "Visi failai (*.*)"
KP_MSG_SAVE_AS_IX,                  // "Įrašyti kaip"

KP_MSG_FILE_EXISTS_IX,              // "Failas %s jau yra, perrašyti?"

KP_MSG_DIAG_MSG_IX,                 // "Formuojamas diagnostinis pranešimas"
KP_MSG_DIAG_MSG_TITLE_IX,           // "Diagnostinis pranešimas"
KP_MSG_DIAG_MSG_EXPL_IX,            // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite pateiktus laukus. Pranešimas apie kompiuterio konfigūraciją, produktą bei klaidos pobūdį bus išsiųstas internetu į produkto gamintojo tarnybinę stotį. Jei po kurio laiko su Jumis nebus susisiekta Jūsų nurodytu pašto adresu, kreipkitės adresu %s")
KP_MSG_DIAG_MSG_EMAIL_PROMPT_IX,    // "Jūsų e-pašto adresas:")
KP_MSG_DIAG_MSG_COMMENTS_PROMPT_IX, // "Komentarai apie klaidos atsiradimo aplinkybes:")
KP_MSG_DIAG_MSG_FILE_PROMPT_IX,     // "Papildomas failas, kurį norėtumėte nusiųsti (pvz., ekrano kopijos paveikslėlis):")

KP_MSG_BAD_EMAIL_ADDRESS_IX,        // "Neteisingas e-pašto adresas"

KP_MSG_DIAG_MSG_SEL_FILE_IX,        // "Pasirinkite siunčiamą failą"

KP_MSG_DIAG_MSG_SUCCEEDED_IX,       // "Diagnostinis pranešimas nusiųstas sėkmingai"

KP_MSG_DIAG_MSG_EXPL1_IX,           // "Jei norite siųsti diagnostinį pranešimą, spragtelėkite „Siųsti“, jei ne – „Atšaukti“."
KP_MSG_SIUSTI_IX,                   // "Siųsti"
KP_MSG_DIAG_MSG_EXPL2_IX,           // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite Jūsų e-pašto adreso lauką ir spragtelėkite mygtuką „Siųsti“."

KP_MSG_DOWNLOADING_IX,              // "Siunčiamas failas..."
KP_MSG_DOWNLOADING_FILE_IX,         // "Siunčiamas failas %s.%s..."

KP_MSG_FIREWALL_IX,                 // "Neleista prisijungti prie interneto. Patikrinkite Jūsų ugniasienės parinktis – pabandykite įtraukti %s į sąrašą programų, kurioms leidžiama kreiptis į internetą."

KP_MSG_POINTER_IX,                  // "Bloga rodyklė"

KP_MSG_LOG_STARTED_IX,              // "Žurnalas išvedamas ir į failą %s"
KP_MSG_CONS_TITLE_IX,               // "%s: Pranešimų žurnalas"

KP_MSG_UNHANDLED_EXCEPTION_IX,      // "Neapdorojamas trūkis"

KP_MSG_DATA_FORMAT_IX,              // "Neteisingas duomenų formatas"
KP_MSG_DBERROR_IX,                  // "Duomenų bazės klaida"

NumOfKpMessages
};

#define NumOfKpMessages_25 NumOfKpMessages

// -----------------------------------------
#define KP_MSG_TITLE                    KpErrorClass::m_pszaKpMessages[KP_MSG_TITLE_IX                  ][iMsgLangOff]  // "Pranešimas"
#define KP_INPUT_TITLE                  KpErrorClass::m_pszaKpMessages[KP_INPUT_TITLE_IX                ][KpCommonApp::m_iMsgLangOff]  // "Įvedimas"

#define KP_MSG_TAIP                     KpErrorClass::m_pszaKpMessages[KP_MSG_TAIP_IX                   ][KpCommonApp::m_iMsgLangOff]  // "Taip"
#define KP_MSG_YES                      KpErrorClass::m_pszaKpMessages[KP_MSG_YES_IX                    ][KpCommonApp::m_iMsgLangOff]  // KP_MSG_TAIP
#define KP_MSG_NE                       KpErrorClass::m_pszaKpMessages[KP_MSG_NE_IX                     ][KpCommonApp::m_iMsgLangOff]  // "Ne"
#define KP_MSG_NO                       KpErrorClass::m_pszaKpMessages[KP_MSG_NO_IX                     ][KpCommonApp::m_iMsgLangOff]  // KP_MSG_NE
#define KP_MSG_GERAI                    KpErrorClass::m_pszaKpMessages[KP_MSG_GERAI_IX                  ][KpCommonApp::m_iMsgLangOff]  // "Gerai"
#define KP_MSG_OK                       KpErrorClass::m_pszaKpMessages[KP_MSG_OK_IX                     ][KpCommonApp::m_iMsgLangOff]  // KP_MSG_GERAI
#define KP_MSG_ATSAUKTI                 KpErrorClass::m_pszaKpMessages[KP_MSG_ATSAUKTI_IX               ][KpCommonApp::m_iMsgLangOff]  // "Atšaukti"
#define KP_MSG_CANCEL                   KpErrorClass::m_pszaKpMessages[KP_MSG_CANCEL_IX                 ][KpCommonApp::m_iMsgLangOff]  // KP_MSG_ATSAUKTI
#define KP_MSG_TESTI                    KpErrorClass::m_pszaKpMessages[KP_MSG_TESTI_IX                  ][KpCommonApp::m_iMsgLangOff]  // "Toliau"
#define KP_MSG_BAIGTI                   KpErrorClass::m_pszaKpMessages[KP_MSG_BAIGTI_IX                 ][KpCommonApp::m_iMsgLangOff]  // "Baigti"
#define KP_MSG_PAMIRSAU_SLAPTAZODI      KpErrorClass::m_pszaKpMessages[KP_MSG_PAMIRSAU_SLAPTAZODI_IX    ][KpCommonApp::m_iMsgLangOff]  // "Pamiršau slaptažodį"

#define KP_MSG_ERROR                    KpErrorClass::m_pszaKpMessages[KP_MSG_ERROR_IX                  ][KpCommonApp::m_iMsgLangOff]  // "Klaida"
#define KP_MSG_WARNING                  KpErrorClass::m_pszaKpMessages[KP_MSG_WARNING_IX                ][KpCommonApp::m_iMsgLangOff]  // "Perspėjimas"
#define KP_MSG_FILE_LINE ((const char *)KpErrorClass::m_pszaKpMessages[KP_MSG_FILE_LINE_IX              ][KpCommonApp::m_iMsgLangOff]) // ", failas:%s, eilutė:%d"
#define KP_MSG_ENTRY_ID  ((const char *)KpErrorClass::m_pszaKpMessages[KP_MSG_ENTRY_ID_IX               ][KpCommonApp::m_iMsgLangOff]) // ", Įrašo nr.:%ld"
#define KP_MSG_ENTRY     ((const char *)KpErrorClass::m_pszaKpMessages[KP_MSG_ENTRY_IX                  ][KpCommonApp::m_iMsgLangOff]) // ", Įrašas: %s"

#define KP_MSG_NO_STANDARD_PROG         KpErrorClass::m_pszaKpMessages[KP_MSG_NO_STANDARD_PROG_IX       ][KpCommonApp::m_iMsgLangOff]  // "Nerasta programa skirta atverti šio tipo failus"
#define KP_MSG_WND_NOT_FOUND            KpErrorClass::m_pszaKpMessages[KP_MSG_WND_NOT_FOUND_IX          ][KpCommonApp::m_iMsgLangOff]  // "Langas nerastas"
#define KP_MSG_PID_NOT_FOUND            KpErrorClass::m_pszaKpMessages[KP_MSG_PID_NOT_FOUND_IX          ][KpCommonApp::m_iMsgLangOff]  // "Nerastas proceso identifikatorius"
#define KP_MSG_NO_SOCKET                KpErrorClass::m_pszaKpMessages[KP_MSG_NO_SOCKET_IX              ][KpCommonApp::m_iMsgLangOff]  // "Jungtis dar nesukurta"
#define KP_MSG_SOCK_UNRESOLVED          KpErrorClass::m_pszaKpMessages[KP_MSG_SOCK_UNRESOLVED_IX        ][KpCommonApp::m_iMsgLangOff]  // "Tarnybinės stoties adresas dar nesurastas"

#define KP_MSG_ERR_OK                   KpErrorClass::m_pszaKpMessages[KP_MSG_ERR_OK_IX                 ][KpCommonApp::m_iMsgLangOff]  // "Operacija atlikta sėkmingai"
#define KP_MSG_INVALIDARG               KpErrorClass::m_pszaKpMessages[KP_MSG_INVALIDARG_IX             ][KpCommonApp::m_iMsgLangOff]  // "Neteisingi parametrai"
#define KP_MSG_NOTIMPL                  KpErrorClass::m_pszaKpMessages[KP_MSG_NOTIMPL_IX                ][KpCommonApp::m_iMsgLangOff]  // "Priedas neįdiegtas"
#define KP_MSG_UNEXPECTED               KpErrorClass::m_pszaKpMessages[KP_MSG_UNEXPECTED_IX             ][KpCommonApp::m_iMsgLangOff]  // "Netikėtas kreipinys į sąsają"
#define KP_MSG_FERROR                   KpErrorClass::m_pszaKpMessages[KP_MSG_FERROR_IX                 ][KpCommonApp::m_iMsgLangOff]  // "Failo skaitymo/rašymo klaida"
#define KP_MSG_SYSTEM_ERROR             KpErrorClass::m_pszaKpMessages[KP_MSG_SYSTEM_ERROR_IX           ][KpCommonApp::m_iMsgLangOff]  // "Klaida sistemoje"
#define KP_MSG_EOF                      KpErrorClass::m_pszaKpMessages[KP_MSG_EOF_IX                    ][KpCommonApp::m_iMsgLangOff]  // "Neteisinga failo pabaiga"
#define KP_MSG_FILE_FORMAT              KpErrorClass::m_pszaKpMessages[KP_MSG_FILE_FORMAT_IX            ][KpCommonApp::m_iMsgLangOff]  // "Neteisingas failo formatas"
#define KP_MSG_FILE_NOT_FOUND           KpErrorClass::m_pszaKpMessages[KP_MSG_FILE_NOT_FOUND_IX         ][KpCommonApp::m_iMsgLangOff]  // "Failas nerastas"
#define KP_MSG_DIR_ERROR                KpErrorClass::m_pszaKpMessages[KP_MSG_DIR_ERROR_IX              ][KpCommonApp::m_iMsgLangOff]  // "Nepavyko atverti/sukurti failo"
#define KP_MSG_OUTOFMEM                 KpErrorClass::m_pszaKpMessages[KP_MSG_OUTOFMEM_IX               ][KpCommonApp::m_iMsgLangOff]  // "Trūksta atminties"
#define KP_MSG_NO_FILE                  KpErrorClass::m_pszaKpMessages[KP_MSG_NO_FILE_IX                ][KpCommonApp::m_iMsgLangOff]  // "Failas neatvertas"
#define KP_MSG_DOUBLE_UNGET             KpErrorClass::m_pszaKpMessages[KP_MSG_DOUBLE_UNGET_IX           ][KpCommonApp::m_iMsgLangOff]  // "Dvigubas įvedimo grąžinimas"
#define KP_MSG_UNKN_CHR                 KpErrorClass::m_pszaKpMessages[KP_MSG_UNKN_CHR_IX               ][KpCommonApp::m_iMsgLangOff]  // "Neatpažintas simbolis"
#define KP_MSG_COMMAND_ERROR            KpErrorClass::m_pszaKpMessages[KP_MSG_COMMAND_ERROR_IX          ][KpCommonApp::m_iMsgLangOff]  // "Išorinė klaida"
#define KP_MSG_BUFFER_OVERFLOW          KpErrorClass::m_pszaKpMessages[KP_MSG_BUFFER_OVERFLOW_IX        ][KpCommonApp::m_iMsgLangOff]  // "Persipildė buferis"
#define KP_MSG_FONT_UNDEF               KpErrorClass::m_pszaKpMessages[KP_MSG_FONT_UNDEF_IX             ][KpCommonApp::m_iMsgLangOff]  // "Neapibrėžtas šriftas"
#define KP_MSG_KWD_NOT_FOUND            KpErrorClass::m_pszaKpMessages[KP_MSG_KWD_NOT_FOUND_IX          ][KpCommonApp::m_iMsgLangOff]  // "Raktinis žodis nerastas"
#define KP_MSG_UNKNOWN_SYSTEM           KpErrorClass::m_pszaKpMessages[KP_MSG_UNKNOWN_SYSTEM_IX         ][KpCommonApp::m_iMsgLangOff]  // "Operacinė sistema neatpažinta"
#define KP_MSG_ILL_CODE                 KpErrorClass::m_pszaKpMessages[KP_MSG_ILL_CODE_IX               ][KpCommonApp::m_iMsgLangOff]  // "Klaidingas registracijos kodas"
#define KP_MSG_CANCELLED                KpErrorClass::m_pszaKpMessages[KP_MSG_CANCELLED_IX              ][KpCommonApp::m_iMsgLangOff]  // "Operacija nutraukta"
#define KP_MSG_DOUBLE_CALL              KpErrorClass::m_pszaKpMessages[KP_MSG_DOUBLE_CALL_IX            ][KpCommonApp::m_iMsgLangOff]  // "Dvigubas iškvietimas"
#define KP_MSG_TIMEOUT                  KpErrorClass::m_pszaKpMessages[KP_MSG_TIMEOUT_IX                ][KpCommonApp::m_iMsgLangOff]  // "Viršytas laukimo laikas"
#define KP_MSG_OBJ_NOT_FOUND            KpErrorClass::m_pszaKpMessages[KP_MSG_OBJ_NOT_FOUND_IX          ][KpCommonApp::m_iMsgLangOff]  // "Objektas nerastas"
#define KP_MSG_NO_CONN                  KpErrorClass::m_pszaKpMessages[KP_MSG_NO_CONN_IX                ][KpCommonApp::m_iMsgLangOff]  // "Nėra ryšio"

#define KP_MSG_TRANS_ERR                KpErrorClass::m_pszaKpMessages[KP_MSG_TRANS_ERR_IX              ][KpCommonApp::m_iMsgLangOff]  // "Perdavimo klaida"
#define KP_MSG_TRANS_ERR_1              KpErrorClass::m_pszaKpMessages[KP_MSG_TRANS_ERR_1_IX            ][KpCommonApp::m_iMsgLangOff]  // "Ryšio klaida, pakartokite siuntimo procedūrą"

#define KP_MSG_REFUSED                  KpErrorClass::m_pszaKpMessages[KP_MSG_REFUSED_IX                ][KpCommonApp::m_iMsgLangOff]  // "Registracija atmesta"
#define KP_MSG_ACCESS_DENIED            KpErrorClass::m_pszaKpMessages[KP_MSG_ACCESS_DENIED_IX          ][KpCommonApp::m_iMsgLangOff]  // "Neleista prisijungti"
#define KP_MSG_ILLEGAL_CHARACTER        KpErrorClass::m_pszaKpMessages[KP_MSG_ILLEGAL_CHARACTER_IX      ][KpCommonApp::m_iMsgLangOff]  // "Neleistinas simbolis"
#define KP_MSG_DIV_ZERO                 KpErrorClass::m_pszaKpMessages[KP_MSG_DIV_ZERO_IX               ][KpCommonApp::m_iMsgLangOff]  // "Dalyba iš nulio"
#define KP_MSG_ILLMATHARG               KpErrorClass::m_pszaKpMessages[KP_MSG_ILLMATHARG_IX             ][KpCommonApp::m_iMsgLangOff]  // "Neleistinas matematinės funkcijos argumentas"
#define KP_MSG_ILLFUNC                  KpErrorClass::m_pszaKpMessages[KP_MSG_ILLFUNC_IX                ][KpCommonApp::m_iMsgLangOff]  // "Neleistina operacija"

#define KP_MSG_NOTINST                  KpErrorClass::m_pszaKpMessages[KP_MSG_NOTINST_IX                ][KpCommonApp::m_iMsgLangOff]  // "Programa neįdiegta arba diegimas sugedo, pakartokite diegimo procedūrą"
#define KP_MSG_NOTINST_S ((const char *)KpErrorClass::m_pszaKpMessages[KP_MSG_NOTINST_S_IX              ][KpCommonApp::m_iMsgLangOff]) // "Produktas „%s“ neįdiegtas arba jo diegimas sugedo, pakartokite diegimo procedūrą"
#define KP_MSG_NOTINST_DELETE           KpErrorClass::m_pszaKpMessages[KP_MSG_NOTINST_DELETE_IX         ][KpCommonApp::m_iMsgLangOff]  // "Produktas neįdiegtas arba jo diegimas sugedo, produktą panaikinkite ir pakartokite diegimo procedūrą"

#define KP_MSG_MSG_FORMAT               KpErrorClass::m_pszaKpMessages[KP_MSG_MSG_FORMAT_IX             ][KpCommonApp::m_iMsgLangOff]  // "Neteisingas pranešimo formatas"
#define KP_MSG_OBSOLETE                 KpErrorClass::m_pszaKpMessages[KP_MSG_OBSOLETE_IX               ][KpCommonApp::m_iMsgLangOff]  // "Pasenusi funkcija"
#define KP_MSG_ERROR_HELP               KpErrorClass::m_pszaKpMessages[KP_MSG_ERROR_HELP_IX             ][KpCommonApp::m_iMsgLangOff]  // ".  Dėl techninės pagalbos kreipkitės elektroniniu paštu, adresu %s"
#define KP_MSG_ERROR_HELP_REST ((const char *)KpErrorClass::m_pszaKpMessages[KP_MSG_ERROR_HELP_REST_IX  ][KpCommonApp::m_iMsgLangOff]) // "   Prie laiško prikabinkite failą %s"
#define KP_MSG_WSAEACCES                KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEACCES_IX              ][KpCommonApp::m_iMsgLangOff]  // "Teisės nesuteiktos"
#define KP_MSG_WSAEADDRINUSE            KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEADDRINUSE_IX          ][KpCommonApp::m_iMsgLangOff]  // "Adresas jau naudojamas"
#define KP_MSG_WSAEADDRNOTAVAIL         KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEADDRNOTAVAIL_IX       ][KpCommonApp::m_iMsgLangOff]  // "Prašomas adresas negali būti priskirtas"
#define KP_MSG_WSAEAFNOSUPPORT          KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEAFNOSUPPORT_IX        ][KpCommonApp::m_iMsgLangOff]  // "Adresų šeimos grupė nepalaikoma protokolo"
#define KP_MSG_WSAEALREADY              KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEALREADY_IX            ][KpCommonApp::m_iMsgLangOff]  // "Operacija jau vykdoma"
#define KP_MSG_WSAECONNABORTED          KpErrorClass::m_pszaKpMessages[KP_MSG_WSAECONNABORTED_IX        ][KpCommonApp::m_iMsgLangOff]  // "Programa iššaukė ryšio nutraukimą"
#define KP_MSG_WSAECONNREFUSED          KpErrorClass::m_pszaKpMessages[KP_MSG_WSAECONNREFUSED_IX        ][KpCommonApp::m_iMsgLangOff]  // "Susijungimas atmestas"
#define KP_MSG_WSAECONNRESET            KpErrorClass::m_pszaKpMessages[KP_MSG_WSAECONNRESET_IX          ][KpCommonApp::m_iMsgLangOff]  // "Sujungimas nutrauktas"
#define KP_MSG_WSAEDESTADDRREQ          KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEDESTADDRREQ_IX        ][KpCommonApp::m_iMsgLangOff]  // "Būtinas kreities adresas"
#define KP_MSG_WSAEFAULT                KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEFAULT_IX              ][KpCommonApp::m_iMsgLangOff]  // "Neteisingas adresas"
#define KP_MSG_WSAEHOSTDOWN             KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEHOSTDOWN_IX           ][KpCommonApp::m_iMsgLangOff]  // "Serveris laikinai neveikia"
#define KP_MSG_WSAEHOSTUNREACH          KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEHOSTUNREACH_IX        ][KpCommonApp::m_iMsgLangOff]  // "Serveris nepasiekiamas"
#define KP_MSG_WSAEINPROGRESS           KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEINPROGRESS_IX         ][KpCommonApp::m_iMsgLangOff]  // "Operacija vykdoma"
#define KP_MSG_WSAEINTR                 KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEINTR_IX               ][KpCommonApp::m_iMsgLangOff]  // "Funkcija nutraukta"
#define KP_MSG_WSAEINVAL                KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEINVAL_IX              ][KpCommonApp::m_iMsgLangOff]  // "Neteisingi parametrai"
#define KP_MSG_WSAEISCONN               KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEISCONN_IX             ][KpCommonApp::m_iMsgLangOff]  // "Susijungimas jau įvykęs"
#define KP_MSG_WSAEMFILE                KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEMFILE_IX              ][KpCommonApp::m_iMsgLangOff]  // "Perdaug atvertų failų"
#define KP_MSG_WSAEMSGSIZE              KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEMSGSIZE_IX            ][KpCommonApp::m_iMsgLangOff]  // "Perdaug ilgas pranešimas"
#define KP_MSG_WSAENETDOWN              KpErrorClass::m_pszaKpMessages[KP_MSG_WSAENETDOWN_IX            ][KpCommonApp::m_iMsgLangOff]  // "Tinklas neveikia"
#define KP_MSG_WSAENETRESET             KpErrorClass::m_pszaKpMessages[KP_MSG_WSAENETRESET_IX           ][KpCommonApp::m_iMsgLangOff]  // "Atsijungė nuo tinklo"
#define KP_MSG_WSAENETUNREACH           KpErrorClass::m_pszaKpMessages[KP_MSG_WSAENETUNREACH_IX         ][KpCommonApp::m_iMsgLangOff]  // "Tinklas nepasiekiamas"
#define KP_MSG_WSAENOBUFS               KpErrorClass::m_pszaKpMessages[KP_MSG_WSAENOBUFS_IX             ][KpCommonApp::m_iMsgLangOff]  // "Trūksta vietos buferyje"
#define KP_MSG_WSAENOPROTOOPT           KpErrorClass::m_pszaKpMessages[KP_MSG_WSAENOPROTOOPT_IX         ][KpCommonApp::m_iMsgLangOff]  // "Neteisinga protokolo parinktis"
#define KP_MSG_WSAENOTCONN              KpErrorClass::m_pszaKpMessages[KP_MSG_WSAENOTCONN_IX            ][KpCommonApp::m_iMsgLangOff]  // "Sujungimas nepavyko"
#define KP_MSG_WSAENOTSOCK              KpErrorClass::m_pszaKpMessages[KP_MSG_WSAENOTSOCK_IX            ][KpCommonApp::m_iMsgLangOff]  // "Socket operation on non-socket"
#define KP_MSG_WSAEOPNOTSUPP            KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEOPNOTSUPP_IX          ][KpCommonApp::m_iMsgLangOff]  // "Operacija negali būti atlikta"
#define KP_MSG_WSAEPFNOSUPPORT          KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEPFNOSUPPORT_IX        ][KpCommonApp::m_iMsgLangOff]  // "Protokolo šeima nepalaikoma"
#define KP_MSG_WSAEPROCLIM              KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEPROCLIM_IX            ][KpCommonApp::m_iMsgLangOff]  // "Perdaug procesų"
#define KP_MSG_WSAEPROTONOSUPPORT       KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEPROTONOSUPPORT_IX     ][KpCommonApp::m_iMsgLangOff]  // "Protokolas nepalaikomas"
#define KP_MSG_WSAEPROTOTYPE            KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEPROTOTYPE_IX          ][KpCommonApp::m_iMsgLangOff]  // "Neteisingas protokolo sujungimo tipas"
#define KP_MSG_WSAESHUTDOWN             KpErrorClass::m_pszaKpMessages[KP_MSG_WSAESHUTDOWN_IX           ][KpCommonApp::m_iMsgLangOff]  // "Siuntimas nebegalimas, sujungimas nutrauktas"
#define KP_MSG_WSAESOCKTNOSUPPORT       KpErrorClass::m_pszaKpMessages[KP_MSG_WSAESOCKTNOSUPPORT_IX     ][KpCommonApp::m_iMsgLangOff]  // "Sujungimo tipas nepalaikomas"
#define KP_MSG_WSAETIMEDOUT             KpErrorClass::m_pszaKpMessages[KP_MSG_WSAETIMEDOUT_IX           ][KpCommonApp::m_iMsgLangOff]  // "Maksimalus sujungimo laukimo laikas viršytas"
#define KP_MSG_WSATYPE_NOT_FOUND        KpErrorClass::m_pszaKpMessages[KP_MSG_WSATYPE_NOT_FOUND_IX      ][KpCommonApp::m_iMsgLangOff]  // "Klasės tipas nerastas"
#define KP_MSG_WSAEWOULDBLOCK           KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEWOULDBLOCK_IX         ][KpCommonApp::m_iMsgLangOff]  // "Šaltinis laikinai nepasiekiamas"
#define KP_MSG_WSAHOST_NOT_FOUND        KpErrorClass::m_pszaKpMessages[KP_MSG_WSAHOST_NOT_FOUND_IX      ][KpCommonApp::m_iMsgLangOff]  // "Serveris nerastas"
#define KP_MSG_WSA_INVALID_HANDLE       KpErrorClass::m_pszaKpMessages[KP_MSG_WSA_INVALID_HANDLE_IX     ][KpCommonApp::m_iMsgLangOff]  // "Klaidingas objekto valdiklis"
#define KP_MSG_WSA_INVALID_PARAMETER    KpErrorClass::m_pszaKpMessages[KP_MSG_WSA_INVALID_PARAMETER_IX  ][KpCommonApp::m_iMsgLangOff]  // "Neteisingi parametrai"
#define KP_MSG_WSAINVALIDPROCTABLE      KpErrorClass::m_pszaKpMessages[KP_MSG_WSAINVALIDPROCTABLE_IX    ][KpCommonApp::m_iMsgLangOff]  // "Klaidinga procedūrų lentelė"
#define KP_MSG_WSAINVALIDPROVIDER       KpErrorClass::m_pszaKpMessages[KP_MSG_WSAINVALIDPROVIDER_IX     ][KpCommonApp::m_iMsgLangOff]  // "Neteisingas tiekėjo kodas"
#define KP_MSG_WSA_IO_INCOMPLETE        KpErrorClass::m_pszaKpMessages[KP_MSG_WSA_IO_INCOMPLETE_IX      ][KpCommonApp::m_iMsgLangOff]  // "Persikloja įvesties/išvesties įvykiai"
#define KP_MSG_WSA_IO_PENDING           KpErrorClass::m_pszaKpMessages[KP_MSG_WSA_IO_PENDING_IX         ][KpCommonApp::m_iMsgLangOff]  // "Persiklojančios operacijos bus atliktos vėliau"

#define KP_MSG_WSA_NOT_ENOUGH_MEMORY    KpErrorClass::m_pszaKpMessages[KP_MSG_WSA_NOT_ENOUGH_MEMORY_IX  ][KpCommonApp::m_iMsgLangOff]  // "Nepakanka atminties"
#define KP_MSG_WSANOTINITIALISED        KpErrorClass::m_pszaKpMessages[KP_MSG_WSANOTINITIALISED_IX      ][KpCommonApp::m_iMsgLangOff]  // "Tinklo posistemis neaktyvuotas"
#define KP_MSG_WSANO_DATA               KpErrorClass::m_pszaKpMessages[KP_MSG_WSANO_DATA_IX             ][KpCommonApp::m_iMsgLangOff]  // "Vardas teisingas, tačiau nėra reikiamo tipo duomenų"
#define KP_MSG_WSANO_RECOVERY           KpErrorClass::m_pszaKpMessages[KP_MSG_WSANO_RECOVERY_IX         ][KpCommonApp::m_iMsgLangOff]  // "Nepataisoma klaida"
#define KP_MSG_WSAPROVIDERFAILEDINIT    KpErrorClass::m_pszaKpMessages[KP_MSG_WSAPROVIDERFAILEDINIT_IX  ][KpCommonApp::m_iMsgLangOff]  // "Negalima inicializuoti paslaugos tiekėjo"
#define KP_MSG_WSASYSCALLFAILURE        KpErrorClass::m_pszaKpMessages[KP_MSG_WSASYSCALLFAILURE_IX      ][KpCommonApp::m_iMsgLangOff]  // "Sistemos kreipinio klaida"
#define KP_MSG_WSASYSNOTREADY           KpErrorClass::m_pszaKpMessages[KP_MSG_WSASYSNOTREADY_IX         ][KpCommonApp::m_iMsgLangOff]  // "Tinklo posistemė nepasiekiama"
#define KP_MSG_WSATRY_AGAIN             KpErrorClass::m_pszaKpMessages[KP_MSG_WSATRY_AGAIN_IX           ][KpCommonApp::m_iMsgLangOff]  // "Neautorizuotas serveris nerastas"
#define KP_MSG_WSAVERNOTSUPPORTED       KpErrorClass::m_pszaKpMessages[KP_MSG_WSAVERNOTSUPPORTED_IX     ][KpCommonApp::m_iMsgLangOff]  // "Netinka WINSOCK.DLL versija"
#define KP_MSG_WSAEDISCON               KpErrorClass::m_pszaKpMessages[KP_MSG_WSAEDISCON_IX             ][KpCommonApp::m_iMsgLangOff]  // "Pradėtas tvarkingas išjungimas"
#define KP_MSG_WSA_OPERATION_ABORTED    KpErrorClass::m_pszaKpMessages[KP_MSG_WSA_OPERATION_ABORTED_IX  ][KpCommonApp::m_iMsgLangOff]  // "Persiklojanti operacija nutraukta"

#define KP_MSG_OUT_OF_MEM_RES           KpErrorClass::m_pszaKpMessages[KP_MSG_OUT_OF_MEM_RES_IX         ][KpCommonApp::m_iMsgLangOff]  // "Operacinei sistemai trūksta atminties"
#define KP_MSG_ERROR_FILE_NOT_FOUND     KpErrorClass::m_pszaKpMessages[KP_MSG_ERROR_FILE_NOT_FOUND_IX   ][KpCommonApp::m_iMsgLangOff]  // "Nurodytas failas nerastas"
#define KP_MSG_ERROR_PATH_NOT_FOUND     KpErrorClass::m_pszaKpMessages[KP_MSG_ERROR_PATH_NOT_FOUND_IX   ][KpCommonApp::m_iMsgLangOff]  // "Nurodytas kelias iki failų nerastas"
#define KP_MSG_ERROR_BAD_FORMAT         KpErrorClass::m_pszaKpMessages[KP_MSG_ERROR_BAD_FORMAT_IX       ][KpCommonApp::m_iMsgLangOff]  // "Pasirinktas .exe failas sugadintas"
#define KP_MSG_SE_ERR_ACCESSDENIED      KpErrorClass::m_pszaKpMessages[KP_MSG_SE_ERR_ACCESSDENIED_IX    ][KpCommonApp::m_iMsgLangOff]  // "Operacinė sistema uždraudė prisijungimą prie reikiamų failų"
#define KP_MSG_SE_ERR_ASSOCINCOMPLETE   KpErrorClass::m_pszaKpMessages[KP_MSG_SE_ERR_ASSOCINCOMPLETE_IX ][KpCommonApp::m_iMsgLangOff]  // "Failo sąryšis su programa nepilnas arba neteisingas"
#define KP_MSG_SE_ERR_DDEBUSY           KpErrorClass::m_pszaKpMessages[KP_MSG_SE_ERR_DDEBUSY_IX         ][KpCommonApp::m_iMsgLangOff]  // "DDE transakcija negali būti baigta, nes kitos DDE transakcijos dar vykdomos"
#define KP_MSG_SE_ERR_DDEFAIL           KpErrorClass::m_pszaKpMessages[KP_MSG_SE_ERR_DDEFAIL_IX         ][KpCommonApp::m_iMsgLangOff]  // "DDE transakcija nutraukta"
#define KP_MSG_SE_ERR_DDETIMEOUT        KpErrorClass::m_pszaKpMessages[KP_MSG_SE_ERR_DDETIMEOUT_IX      ][KpCommonApp::m_iMsgLangOff]  // "DDE transakcija negali būti baigta, nes neužteko nurodyto laukimo laiko"
#define KP_MSG_SE_ERR_DLLNOTFOUND       KpErrorClass::m_pszaKpMessages[KP_MSG_SE_ERR_DLLNOTFOUND_IX     ][KpCommonApp::m_iMsgLangOff]  // "Nurodyta dinaminė biblioteka nerasta"
#define KP_MSG_SE_ERR_FNF               KpErrorClass::m_pszaKpMessages[KP_MSG_SE_ERR_FNF_IX             ][KpCommonApp::m_iMsgLangOff]  // "Nurodytas failas nerastas"
#define KP_MSG_SE_ERR_NOASSOC           KpErrorClass::m_pszaKpMessages[KP_MSG_SE_ERR_NOASSOC_IX         ][KpCommonApp::m_iMsgLangOff]  // "Nerasta programa skirta atverti šio tipo failus"
#define KP_MSG_SE_ERR_OOM               KpErrorClass::m_pszaKpMessages[KP_MSG_SE_ERR_OOM_IX             ][KpCommonApp::m_iMsgLangOff]  // "Nepakanka atminties atlikti operacijai"
#define KP_MSG_SE_ERR_PNF               KpErrorClass::m_pszaKpMessages[KP_MSG_SE_ERR_PNF_IX             ][KpCommonApp::m_iMsgLangOff]  // "Nurodytas kelias nerastas"
#define KP_MSG_SE_ERR_SHARE             KpErrorClass::m_pszaKpMessages[KP_MSG_SE_ERR_SHARE_IX           ][KpCommonApp::m_iMsgLangOff]  // "Dalijimosi klaida"

#define KP_MSG_FIRST_TIME_ADMIN         KpErrorClass::m_pszaKpMessages[KP_MSG_FIRST_TIME_ADMIN_IX       ][KpCommonApp::m_iMsgLangOff]  // "Programą paleidžiant pirmą kartą, reikalingos\n administratoriaus teisės. Paleiskite programą iš naujo administratoriaus teisėmis."
#define KP_MSG_NOW_NOT_ADMIN            KpErrorClass::m_pszaKpMessages[KP_MSG_NOW_NOT_ADMIN_IX          ][KpCommonApp::m_iMsgLangOff]  // KP_MSG_NOT_ADMIN
#define KP_MSG_NOT_ADMIN                KpErrorClass::m_pszaKpMessages[KP_MSG_NOT_ADMIN_IX              ][KpCommonApp::m_iMsgLangOff]  // "Programą paleiskite iš naujo paprasto vartotojo teisėmis"
#define KP_MSG_COPY_FILE_ACCESS_DENIED  KpErrorClass::m_pszaKpMessages[KP_MSG_COPY_FILE_ACCESS_DENIED_IX][KpCommonApp::m_iMsgLangOff]  // "Failo nukopijuoti nepavyko, programą paleiskite iš naujo administratoriaus teisėmis"

#define KP_PROGRESS_TITLE               KpErrorClass::m_pszaKpMessages[KP_PROGRESS_TITLE_IX             ][KpCommonApp::m_iMsgLangOff]  // "Palaukite..."
#define KP_MSG_DELETING_FILE ((const char *)KpErrorClass::m_pszaKpMessages[KP_MSG_DELETING_FILE_IX      ][KpCommonApp::m_iMsgLangOff]) // "Naikinamas failas %s.%s..."
#define KP_MSG_COPYING                  KpErrorClass::m_pszaKpMessages[KP_MSG_COPYING_IX                ][KpCommonApp::m_iMsgLangOff]  // "Kopijuojamas failas..."
#define KP_MSG_COPYING_DIR ((const char *)KpErrorClass::m_pszaKpMessages[KP_MSG_COPYING_DIR_IX          ][KpCommonApp::m_iMsgLangOff]) // "Kopijuojamas aplankas %s.%s..."
#define KP_MSG_COPYING_FILE ((const char *)KpErrorClass::m_pszaKpMessages[KP_MSG_COPYING_FILE_IX        ][KpCommonApp::m_iMsgLangOff]) // "Kopijuojamas failas %s.%s..."

#define KP_MSG_NEG_ANSW                 KpErrorClass::m_pszaKpMessages[KP_MSG_NEG_ANSW_IX               ][KpCommonApp::m_iMsgLangOff]  // "Neigiamas atsakymas"

#define KP_MSG_UNABLE_TO_EXECUTE ((const char *)KpErrorClass::m_pszaKpMessages[KP_MSG_UNABLE_TO_EXECUTE_IX][KpCommonApp::m_iMsgLangOff]) // "Komandos %s įvykdyti negaliu – patikrinkite, ar teisingai įdiegėte visus sistemos komponentus"

#define KP_MSG_FLASH_PLAYER_INSTALL     KpErrorClass::m_pszaKpMessages[KP_MSG_FLASH_PLAYER_INSTALL_IX   ][KpCommonApp::m_iMsgLangOff]  // "Dabar bus įdiegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus."

#define KP_MSG_FILE_CHANGED             KpErrorClass::m_pszaKpMessages[KP_MSG_FILE_CHANGED_IX           ][KpCommonApp::m_iMsgLangOff]  // "Failas pasikeitė"

#define KP_MSG_ALL_FILES                KpErrorClass::m_pszaKpMessages[KP_MSG_ALL_FILES_IX              ][KpCommonApp::m_iMsgLangOff]  // "Visi failai (*.*)"
#define KP_MSG_SAVE_AS                  KpErrorClass::m_pszaKpMessages[KP_MSG_SAVE_AS_IX                ][KpCommonApp::m_iMsgLangOff]  // "Įrašyti kaip"

#define KP_MSG_FILE_EXISTS ((const char *)KpErrorClass::m_pszaKpMessages[KP_MSG_FILE_EXISTS_IX          ][KpCommonApp::m_iMsgLangOff]) // "Failas %s jau yra, perrašyti?"

#define KP_MSG_DIAG_MSG                 KpErrorClass::m_pszaKpMessages[KP_MSG_DIAG_MSG_IX               ][KpCommonApp::m_iMsgLangOff]  // "Formuojamas diagnostinis pranešimas"
#define KP_MSG_DIAG_MSG_TITLE           KpErrorClass::m_pszaKpMessages[KP_MSG_DIAG_MSG_TITLE_IX         ][KpCommonApp::m_iMsgLangOff]  // "Formuojamas diagnostinis pranešimas"
#define KP_MSG_DIAG_MSG_EXPL            KpErrorClass::m_pszaKpMessages[KP_MSG_DIAG_MSG_EXPL_IX          ][KpCommonApp::m_iMsgLangOff]  // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite pateiktus laukus. Pranešimas apie kompiuterio konfigūraciją, produktą bei klaidos pobūdį bus išsiųstas internetu į produkto gamintojo tarnybinę stotį. Jei po kurio laiko su Jumis nebus susisiekta Jūsų nurodytu pašto adresu, kreipkitės adresu %s"
#define KP_MSG_DIAG_MSG_EMAIL_PROMPT    KpErrorClass::m_pszaKpMessages[KP_MSG_DIAG_MSG_EMAIL_PROMPT_IX  ][KpCommonApp::m_iMsgLangOff]  // "Jūsų e-pašto adresas:"
#define KP_MSG_DIAG_MSG_COMMENTS_PROMPT KpErrorClass::m_pszaKpMessages[KP_MSG_DIAG_MSG_COMMENTS_PROMPT_IX][KpCommonApp::m_iMsgLangOff] // "Komentarai apie klaidos atsiradimo aplinkybes:"
#define KP_MSG_DIAG_MSG_FILE_PROMPT     KpErrorClass::m_pszaKpMessages[KP_MSG_DIAG_MSG_FILE_PROMPT_IX   ][KpCommonApp::m_iMsgLangOff]  // "Papildomas failas, kurį norėtumėte nusiųsti (pvz., ekrano kopijos paveikslėlis):"

#define KP_MSG_BAD_EMAIL_ADDRESS        KpErrorClass::m_pszaKpMessages[KP_MSG_BAD_EMAIL_ADDRESS_IX      ][KpCommonApp::m_iMsgLangOff]  // "Neteisingas e-pašto adresas"

#define KP_MSG_DIAG_MSG_SEL_FILE        KpErrorClass::m_pszaKpMessages[KP_MSG_DIAG_MSG_SEL_FILE_IX      ][KpCommonApp::m_iMsgLangOff]  // "Pasirinkite siunčiamą failą"

#define KP_MSG_DIAG_MSG_SUCCEEDED       KpErrorClass::m_pszaKpMessages[KP_MSG_DIAG_MSG_SUCCEEDED_IX     ][KpCommonApp::m_iMsgLangOff]  // "Diagnostinis pranešimas nusiųstas sėkmingai"

#define KP_MSG_DIAG_MSG_EXPL1           KpErrorClass::m_pszaKpMessages[KP_MSG_DIAG_MSG_EXPL1_IX         ][KpCommonApp::m_iMsgLangOff]  // "Jei norite siųsti diagnostinį pranešimą, spragtelėkite „Siųsti“, jei ne – „Atšaukti“."
#define KP_MSG_SIUSTI                   KpErrorClass::m_pszaKpMessages[KP_MSG_SIUSTI_IX                 ][KpCommonApp::m_iMsgLangOff]  // "Siųsti"
#define KP_MSG_DIAG_MSG_EXPL2           KpErrorClass::m_pszaKpMessages[KP_MSG_DIAG_MSG_EXPL2_IX         ][KpCommonApp::m_iMsgLangOff]  // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite Jūsų e-pašto adreso lauką ir spragtelėkite mygtuką „Siųsti“."

#define KP_MSG_DOWNLOADING              KpErrorClass::m_pszaKpMessages[KP_MSG_DOWNLOADING_IX            ][KpCommonApp::m_iMsgLangOff]  // "Siunčiamas failas..."
#define KP_MSG_DOWNLOADING_FILE ((const char *)KpErrorClass::m_pszaKpMessages[KP_MSG_DOWNLOADING_FILE_IX][KpCommonApp::m_iMsgLangOff]) // "Siunčiamas failas %s.%s..."

#define KP_MSG_FIREWALL                 KpErrorClass::m_pszaKpMessages[KP_MSG_FIREWALL_IX               ][KpCommonApp::m_iMsgLangOff]  // "Neleista prisijungti prie interneto. Patikrinkite Jūsų ugniasienės parinktis – pabandykite įtraukti %s į sąrašą programų, kurioms leidžiama kreiptis į internetą."

#define KP_MSG_POINTER                  KpErrorClass::m_pszaKpMessages[KP_MSG_POINTER_IX                ][KpCommonApp::m_iMsgLangOff]  // "Bloga rodyklė"

#define KP_MSG_LOG_STARTED ((const char *)KpErrorClass::m_pszaKpMessages[KP_MSG_LOG_STARTED_IX          ][KpCommonApp::m_iMsgLangOff]) // "Žurnalas išvedamas ir į failą %s"
#define KP_MSG_CONS_TITLE ((const char *)KpErrorClass::m_pszaKpMessages[KP_MSG_CONS_TITLE_IX            ][KpCommonApp::m_iMsgLangOff]) // "%s: Pranešimų žurnalas"

#define KP_MSG_UNHANDLED_EXCEPTION      KpErrorClass::m_pszaKpMessages[KP_MSG_UNHANDLED_EXCEPTION_IX    ][KpCommonApp::m_iMsgLangOff]  // "Neapdorojamas trūkis"

#define KP_MSG_DATA_FORMAT              KpErrorClass::m_pszaKpMessages[KP_MSG_DATA_FORMAT_IX            ][KpCommonApp::m_iMsgLangOff]  // "Neteisingas duomenų formatas"
#define KP_MSG_DBERROR                  KpErrorClass::m_pszaKpMessages[KP_MSG_DBERROR_IX                ][KpCommonApp::m_iMsgLangOff]  // "Duomenų bazės klaida"


// --------------------------------
#if FALSE // ((MsgLang != KpLangNo_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangEn_p))

#define KP_MSG_TITLE_EN             ((MSG_TYPE)"") // "Message")
#define KP_INPUT_TITLE_EN           ((MSG_TYPE)"") // "Input"

#define KP_MSG_YES_EN               ((MSG_TYPE)"") // "Yes")
#define KP_MSG_TAIP_EN              KP_MSG_YES
#define KP_MSG_NO_EN                ((MSG_TYPE)"") // "No")
#define KP_MSG_NE_EN                KP_MSG_NO
#define KP_MSG_OK_EN                ((MSG_TYPE)"") // "OK")
#define KP_MSG_GERAI_EN             KP_MSG_OK
#define KP_MSG_CANCEL_EN            ((MSG_TYPE)"") // "Cancel")
#define KP_MSG_ATSAUKTI_EN          KP_MSG_CANCEL
#define KP_MSG_TESTI_EN             ((MSG_TYPE)"") // "Continue")
#define KP_MSG_BAIGTI_EN            ((MSG_TYPE)"") // "Finish")
#define KP_MSG_PAMIRSAU_SLAPTAZODI_EN ((MSG_TYPE)"") // "Forgot password")

#define KP_MSG_ERROR_EN             ((MSG_TYPE)"") // "Error")
#define KP_MSG_WARNING_EN           ((MSG_TYPE)"") // "Warning")
#define KP_MSG_FILE_LINE_EN         ((MSG_TYPE)"") // ", file:%s, line:%d")
#define KP_MSG_ENTRY_ID_EN          ((MSG_TYPE)"") // ", Entry Id:%ld")
#define KP_MSG_ENTRY_EN             ((MSG_TYPE)"") // ", Entry: %s")

#define KP_MSG_NO_STANDARD_PROG_EN  ((MSG_TYPE)"") // "Standard program not set to open given file type")
#define KP_MSG_WND_NOT_FOUND_EN     ((MSG_TYPE)"") // "Window not found")
#define KP_MSG_PID_NOT_FOUND_EN     ((MSG_TYPE)"") // "PID not found")
#define KP_MSG_NO_SOCKET_EN         ((MSG_TYPE)"") // "Socket not created yet")
#define KP_MSG_SOCK_UNRESOLVED_EN   ((MSG_TYPE)"") // "Server address not resolved yet")

#define KP_MSG_ERR_OK_EN            ((MSG_TYPE)"") // "Operation ended successfully")
#define KP_MSG_INVALIDARG_EN        ((MSG_TYPE)"") // "Invalid parameter")
#define KP_MSG_NOTIMPL_EN           ((MSG_TYPE)"") // "Feature not implemented yet")
#define KP_MSG_UNEXPECTED_EN        ((MSG_TYPE)"") // "Unexpected interface call") // Interface call result: Unexpected error
#define KP_MSG_FERROR_EN            ((MSG_TYPE)"") // "File I/O error")
#define KP_MSG_SYSTEM_ERROR_EN      ((MSG_TYPE)"") // "Internal error")
#define KP_MSG_EOF_EN               ((MSG_TYPE)"") // "Unexpected end of input file")
#define KP_MSG_FILE_FORMAT_EN       ((MSG_TYPE)"") // "Unexpected input file format")
#define KP_MSG_FILE_NOT_FOUND_EN    ((MSG_TYPE)"") // "File not found")
#define KP_MSG_DIR_ERROR_EN         ((MSG_TYPE)"") // "Unable to create file")
#define KP_MSG_OUTOFMEM_EN          ((MSG_TYPE)"") // "Out of memory")
#define KP_MSG_NO_FILE_EN           ((MSG_TYPE)"") // "No file open")
#define KP_MSG_DOUBLE_UNGET_EN      ((MSG_TYPE)"") // "Double unget")
#define KP_MSG_UNKN_CHR_EN          ((MSG_TYPE)"") // "Unknown character")
#define KP_MSG_COMMAND_ERROR_EN     ((MSG_TYPE)"") // "External error")
#define KP_MSG_BUFFER_OVERFLOW_EN   ((MSG_TYPE)"") // "Buffer overflow")
#define KP_MSG_FONT_UNDEF_EN        ((MSG_TYPE)"") // "Font undefined")
#define KP_MSG_KWD_NOT_FOUND_EN     ((MSG_TYPE)"") // "Keyword not found")
#define KP_MSG_UNKNOWN_SYSTEM_EN    ((MSG_TYPE)"") // "Unknown OS version")
#define KP_MSG_ILL_CODE_EN          ((MSG_TYPE)"") // "Illegal registration code")
#define KP_MSG_CANCELLED_EN         ((MSG_TYPE)"") // "Job cancelled")
#define KP_MSG_DOUBLE_CALL_EN       ((MSG_TYPE)"") // "Double call")
#define KP_MSG_TIMEOUT_EN           ((MSG_TYPE)"") // "Timeout")
#define KP_MSG_OBJ_NOT_FOUND_EN     ((MSG_TYPE)"") // "Object not found")
#define KP_MSG_NO_CONN_EN           ((MSG_TYPE)"") // "No connection")

#define KP_MSG_TRANS_ERR_EN         ((MSG_TYPE)"") // "Transfer error")
#define KP_MSG_TRANS_ERR_1_EN       ((MSG_TYPE)"") // "Transfer error, repeat the download procedure, please"

#define KP_MSG_REFUSED_EN           ((MSG_TYPE)"") // "Registration refused")
#define KP_MSG_ACCESS_DENIED_EN     ((MSG_TYPE)"") // "Access denied")
#define KP_MSG_ILLEGAL_CHARACTER_EN ((MSG_TYPE)"") // "Unexpected character")
#define KP_MSG_DIV_ZERO_EN          ((MSG_TYPE)"") // "Division by zero")
#define KP_MSG_ILLMATHARG_EN        ((MSG_TYPE)"") // "Illegal math argument")
#define KP_MSG_ILLFUNC_EN           ((MSG_TYPE)"") // "Illegal function call")

#define KP_MSG_NOTINST_EN           ((MSG_TYPE)"") // "Program not yet installed or installation is damaged, repeat the installation procedure again, please")
#define KP_MSG_NOTINST_S_EN         ((MSG_TYPE)"") // "Produktas „%s“ neįdiegtas arba jo diegimas sugedo, pakartokite diegimo procedūrą"
#define KP_MSG_NOTINST_DELETE_EN    ((MSG_TYPE)"") // "Produktas neįdiegtas arba jo diegimas sugedo, produktą panaikinkite ir pakartokite diegimo procedūrą"

#define KP_MSG_MSG_FORMAT_EN        ((MSG_TYPE)"") // "Illegal message format")
#define KP_MSG_OBSOLETE_EN          ((MSG_TYPE)"") // "Obsolete function call")

#define KP_MSG_ERROR_HELP_EN        ((MSG_TYPE)"") // ".  Technical support by e-mail %s")
#define KP_MSG_ERROR_HELP_REST_EN   ((MSG_TYPE)"") // "   For further information look file %s")

#define KP_MSG_WSAEACCES_EN               ((MSG_TYPE)"") // "Permission denied")
#define KP_MSG_WSAEADDRINUSE_EN           ((MSG_TYPE)"") // "Address already in use")
#define KP_MSG_WSAEADDRNOTAVAIL_EN        ((MSG_TYPE)"") // "Cannot assign requested address")
#define KP_MSG_WSAEAFNOSUPPORT_EN         ((MSG_TYPE)"") // "Address family not supported by protocol family")
#define KP_MSG_WSAEALREADY_EN             ((MSG_TYPE)"") // "Operation already in progress")
#define KP_MSG_WSAECONNABORTED_EN         ((MSG_TYPE)"") // "Software caused connection abort")
#define KP_MSG_WSAECONNREFUSED_EN         ((MSG_TYPE)"") // "Connection refused")
#define KP_MSG_WSAECONNRESET_EN           ((MSG_TYPE)"") // "Connection reset by peer")
#define KP_MSG_WSAEDESTADDRREQ_EN         ((MSG_TYPE)"") // "Destination address required")
#define KP_MSG_WSAEFAULT_EN               ((MSG_TYPE)"") // "Bad address")
#define KP_MSG_WSAEHOSTDOWN_EN            ((MSG_TYPE)"") // "Host is down")
#define KP_MSG_WSAEHOSTUNREACH_EN         ((MSG_TYPE)"") // "No route to host")
#define KP_MSG_WSAEINPROGRESS_EN          ((MSG_TYPE)"") // "Operation now in progress")
#define KP_MSG_WSAEINTR_EN                ((MSG_TYPE)"") // "Interrupted function call")
#define KP_MSG_WSAEINVAL_EN               ((MSG_TYPE)"") // "Invalid argument")
#define KP_MSG_WSAEISCONN_EN              ((MSG_TYPE)"") // "Socket is already connected")
#define KP_MSG_WSAEMFILE_EN               ((MSG_TYPE)"") // "Too many open files")
#define KP_MSG_WSAEMSGSIZE_EN             ((MSG_TYPE)"") // "Message too long")
#define KP_MSG_WSAENETDOWN_EN             ((MSG_TYPE)"") // "Network is down")
#define KP_MSG_WSAENETRESET_EN            ((MSG_TYPE)"") // "Network dropped connection on reset")
#define KP_MSG_WSAENETUNREACH_EN          ((MSG_TYPE)"") // "Network is unreachable")
#define KP_MSG_WSAENOBUFS_EN              ((MSG_TYPE)"") // "No buffer space available")
#define KP_MSG_WSAENOPROTOOPT_EN          ((MSG_TYPE)"") // "Bad protocol option")
#define KP_MSG_WSAENOTCONN_EN             ((MSG_TYPE)"") // "Socket is not connected")
#define KP_MSG_WSAENOTSOCK_EN             ((MSG_TYPE)"") // "Socket operation on non-socket")
#define KP_MSG_WSAEOPNOTSUPP_EN           ((MSG_TYPE)"") // "Operation not supported")
#define KP_MSG_WSAEPFNOSUPPORT_EN         ((MSG_TYPE)"") // "Protocol family not supported")
#define KP_MSG_WSAEPROCLIM_EN             ((MSG_TYPE)"") // "Too many processes")
#define KP_MSG_WSAEPROTONOSUPPORT_EN      ((MSG_TYPE)"") // "Protocol not supported")
#define KP_MSG_WSAEPROTOTYPE_EN           ((MSG_TYPE)"") // "Protocol wrong type for socket")
#define KP_MSG_WSAESHUTDOWN_EN            ((MSG_TYPE)"") // "Cannot send after socket shutdown")
#define KP_MSG_WSAESOCKTNOSUPPORT_EN      ((MSG_TYPE)"") // "Socket type not supported")
#define KP_MSG_WSAETIMEDOUT_EN            ((MSG_TYPE)"") // "Connection timed out")
#define KP_MSG_WSATYPE_NOT_FOUND_EN       ((MSG_TYPE)"") // "class type not found")
#define KP_MSG_WSAEWOULDBLOCK_EN          ((MSG_TYPE)"") // "Resource temporarily unavailable")
#define KP_MSG_WSAHOST_NOT_FOUND_EN       ((MSG_TYPE)"") // "Host not found")
#define KP_MSG_WSA_INVALID_HANDLE_EN      ((MSG_TYPE)"") // "Specified event object handle is invalid")
#define KP_MSG_WSA_INVALID_PARAMETER_EN   ((MSG_TYPE)"") // "One or more parameters are invalid")
#define KP_MSG_WSAINVALIDPROCTABLE_EN     ((MSG_TYPE)"") // "Invalid procedure table from service provider")
#define KP_MSG_WSAINVALIDPROVIDER_EN      ((MSG_TYPE)"") // "Invalid service provider version number")
#define KP_MSG_WSA_IO_INCOMPLETE_EN       ((MSG_TYPE)"") // "Overlapped I/O event object not in signaled state")
#define KP_MSG_WSA_IO_PENDING_EN          ((MSG_TYPE)"") // "Overlapped operations will complete later")

#define KP_MSG_WSA_NOT_ENOUGH_MEMORY_EN   ((MSG_TYPE)"") // "Insufficient memory available")
#define KP_MSG_WSANOTINITIALISED_EN       ((MSG_TYPE)"") // "Successful WSAStartup not yet performed")
#define KP_MSG_WSANO_DATA_EN              ((MSG_TYPE)"") // "Valid name, no data record of requested type")
#define KP_MSG_WSANO_RECOVERY_EN          ((MSG_TYPE)"") // "this is a non-recoverable error")
#define KP_MSG_WSAPROVIDERFAILEDINIT_EN   ((MSG_TYPE)"") // "Unable to initialize a service provider")
#define KP_MSG_WSASYSCALLFAILURE_EN       ((MSG_TYPE)"") // "System call failure")
#define KP_MSG_WSASYSNOTREADY_EN          ((MSG_TYPE)"") // "Network subsystem is unavailable")
#define KP_MSG_WSATRY_AGAIN_EN            ((MSG_TYPE)"") // "Non-authoritative host not found")
#define KP_MSG_WSAVERNOTSUPPORTED_EN      ((MSG_TYPE)"") // "WINSOCK.DLL version out of range")
#define KP_MSG_WSAEDISCON_EN              ((MSG_TYPE)"") // "Graceful shutdown in progress")
#define KP_MSG_WSA_OPERATION_ABORTED_EN   ((MSG_TYPE)"") // "Overlapped operation aborted")

#define KP_MSG_OUT_OF_MEM_RES_EN          ((MSG_TYPE)"") // "The operating system is out of memory or resources")
#define KP_MSG_ERROR_FILE_NOT_FOUND_EN    ((MSG_TYPE)"") // "The file specified was not found")
#define KP_MSG_ERROR_PATH_NOT_FOUND_EN    ((MSG_TYPE)"") // "The path specified was not found")
#define KP_MSG_ERROR_BAD_FORMAT_EN        ((MSG_TYPE)"") // "The .exe file is invalid (non-Win32(r) .exe or error in .exe image)")
#define KP_MSG_SE_ERR_ACCESSDENIED_EN     ((MSG_TYPE)"") // "The operating system denied access to the specified file")
#define KP_MSG_SE_ERR_ASSOCINCOMPLETE_EN  ((MSG_TYPE)"") // "The file name association is incomplete or invalid")
#define KP_MSG_SE_ERR_DDEBUSY_EN          ((MSG_TYPE)"") // "The DDE transaction could not be completed because other DDE transactions were being processed")
#define KP_MSG_SE_ERR_DDEFAIL_EN          ((MSG_TYPE)"") // "The DDE transaction failed")
#define KP_MSG_SE_ERR_DDETIMEOUT_EN       ((MSG_TYPE)"") // "The DDE transaction could not be completed because the request timed out")
#define KP_MSG_SE_ERR_DLLNOTFOUND_EN      ((MSG_TYPE)"") // "The specified dynamic-link library was not found")
#define KP_MSG_SE_ERR_FNF_EN              ((MSG_TYPE)"") // "The specified file was not found")
#define KP_MSG_SE_ERR_NOASSOC_EN          ((MSG_TYPE)"") // "There is no application associated with the given file name extension")
#define KP_MSG_SE_ERR_OOM_EN              ((MSG_TYPE)"") // "There was not enough memory to complete the operation")
#define KP_MSG_SE_ERR_PNF_EN              ((MSG_TYPE)"") // "The specified path was not found")
#define KP_MSG_SE_ERR_SHARE_EN            ((MSG_TYPE)"") // "A sharing violation occurred")

#define KP_MSG_FIRST_TIME_ADMIN_EN        ((MSG_TYPE)"") // "Starting the program first time administrator\n rights are necessary. Run the program again as privileged user.")
#define KP_MSG_NOW_NOT_ADMIN_EN           KP_MSG_NOT_ADMIN
#define KP_MSG_NOT_ADMIN_EN               ((MSG_TYPE)"") // "Run the program again as ordinary user")
#define KP_MSG_COPY_FILE_ACCESS_DENIED_EN ((MSG_TYPE)"") // "Unsuccessfull file copy operation, run the program again as privileged user")

#define KP_PROGRESS_TITLE_EN              ((MSG_TYPE)"") // "Wait...")
#define KP_MSG_DELETING_FILE_EN           ((MSG_TYPE)"") // "Deleting file %s.%s...")
#define KP_MSG_COPYING_EN                 ((MSG_TYPE)"") // "Copying file...")
#define KP_MSG_COPYING_FILE_EN            ((MSG_TYPE)"") // "Copying file %s.%s...")
#define KP_MSG_COPYING_DIR_EN             ((MSG_TYPE)"") // "Copying folder %s.%s...")

#define KP_MSG_UNABLE_TO_EXECUTE_EN       ((MSG_TYPE)"") // "Komandos %s įvykdyti negaliu – patikrinkite, ar teisingai įdiegėte visus sistemos komponentus"

#define KP_MSG_FLASH_PLAYER_INSTALL_EN    ((MSG_TYPE)"") // "Dabar bus įdiegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus."

#define KP_MSG_FILE_CHANGED_EN            ((MSG_TYPE)"") // "Failas pasikeitė"

#define KP_MSG_ALL_FILES_EN               ((MSG_TYPE)"") // "Visi failai (*.*)"
#define KP_MSG_SAVE_AS_EN                 ((MSG_TYPE)"") // "Įrašyti kaip"

#define KP_MSG_FILE_EXISTS_EN             ((MSG_TYPE)"") // "Failas %s jau yra, perrašyti?"

#define KP_MSG_DIAG_MSG_EN                ((MSG_TYPE)"") // "Formuojamas diagnostinis pranešimas"
#define KP_MSG_DIAG_MSG_TITLE_EN          ((MSG_TYPE)"") // "Diagnostinis pranešimas"
#define KP_MSG_DIAG_MSG_EXPL_EN           ((MSG_TYPE)"") // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite pateiktus laukus. Pranešimas apie kompiuterio konfigūraciją, produktą bei klaidos pobūdį bus išsiųstas internetu į produkto gamintojo tarnybinę stotį. Jei po kurio laiko su Jumis nebus susisiekta Jūsų nurodytu pašto adresu, kreipkitės adresu %s")
#define KP_MSG_DIAG_MSG_EMAIL_PROMPT_EN   ((MSG_TYPE)"") // "Jūsų e-pašto adresas:")
#define KP_MSG_DIAG_MSG_COMMENTS_PROMPT_EN ((MSG_TYPE)"") // "Komentarai apie klaidos atsiradimo aplinkybes:")
#define KP_MSG_DIAG_MSG_FILE_PROMPT_EN    ((MSG_TYPE)"") // "Papildomas failas, kurį norėtumėte nusiųsti (pvz., ekrano kopijos paveikslėlis):")

#define KP_MSG_BAD_EMAIL_ADDRESS_EN       ((MSG_TYPE)"") // "Neteisingas e-pašto adresas"

#define KP_MSG_DIAG_MSG_SEL_FILE_EN       ((MSG_TYPE)"") // "Pasirinkite siunčiamą failą"

#define KP_MSG_DIAG_MSG_SUCCEEDED_EN      ((MSG_TYPE)"") // "Diagnostinis pranešimas nusiųstas sėkmingai"

#define KP_MSG_DIAG_MSG_EXPL1_EN          ((MSG_TYPE)"") // "Jei norite siųsti diagnostinį pranešimą, spragtelėkite „Siųsti“, jei ne – „Atšaukti“."
#define KP_MSG_SIUSTI_EN                  ((MSG_TYPE)"") // "Siųsti"
#define KP_MSG_DIAG_MSG_EXPL2_EN          ((MSG_TYPE)"") // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite Jūsų e-pašto adreso lauką ir spragtelėkite mygtuką „Siųsti“."

#define KP_MSG_DOWNLOADING_EN             ((MSG_TYPE)"") // "Siunčiamas failas..."
#define KP_MSG_DOWNLOADING_FILE_EN        ((MSG_TYPE)"") // "Siunčiamas failas %s.%s..."

#define KP_MSG_FIREWALL_EN                ((MSG_TYPE)"") // "Neleista prisijungti prie interneto. Patikrinkite Jūsų ugniasienės parinktis – pabandykite įtraukti %s į sąrašą programų, kurioms leidžiama kreiptis į internetą."

#define KP_MSG_POINTER_EN                 ((MSG_TYPE)"") // "Bloga rodyklė"

#define KP_MSG_LOG_STARTED_EN             ((MSG_TYPE)"") // "Žurnalas išvedamas ir į failą %s"
#define KP_MSG_CONS_TITLE_EN              ((MSG_TYPE)"") // "%s: Pranešimų žurnalas"

#define KP_MSG_UNHANDLED_EXCEPTION_EN     ((MSG_TYPE)"") // "Neapdorojamas trūkis"

#define KP_MSG_DATA_FORMAT_EN,            ((MSG_TYPE)"") // "Neteisingas duomenų formatas"
#define KP_MSG_DBERROR_EN,                ((MSG_TYPE)"") // "Duomenų bazės klaida"

#endif // #if ((MsgLang != KpLangNo_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangEn_p))


// --------------------------------
#if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangLt_p))

#define KP_MSG_TITLE_LT             ((MSG_TYPE)"") // "Pranešimas"
#define KP_INPUT_TITLE_LT           ((MSG_TYPE)"") // "Įvedimas"

#define KP_MSG_TAIP_LT              ((MSG_TYPE)"") // "Taip")
#define KP_MSG_YES_LT               KP_MSG_TAIP
#define KP_MSG_NE_LT                ((MSG_TYPE)"") // "Ne")
#define KP_MSG_NO_LT                KP_MSG_NE
#define KP_MSG_GERAI_LT             ((MSG_TYPE)"") // "Gerai")
#define KP_MSG_OK_LT                KP_MSG_GERAI
#define KP_MSG_ATSAUKTI_LT          ((MSG_TYPE)"") // "Atšaukti")
#define KP_MSG_CANCEL_LT            KP_MSG_ATSAUKTI
#define KP_MSG_TESTI_LT             ((MSG_TYPE)"") // "Toliau")
#define KP_MSG_BAIGTI_LT            ((MSG_TYPE)"") // "Baigti")
#define KP_MSG_PAMIRSAU_SLAPTAZODI_LT ((MSG_TYPE)"") // "Pamiršau slaptažodį")

#define KP_MSG_ERROR_LT             ((MSG_TYPE)"") // "Klaida")
#define KP_MSG_WARNING_LT           ((MSG_TYPE)"") // "Perspėjimas")
#define KP_MSG_FILE_LINE_LT         ((MSG_TYPE)"") // ", failas:%s, eilutė:%d")
#define KP_MSG_ENTRY_ID_LT          ((MSG_TYPE)"") // ", Įrašo nr.:%ld")
#define KP_MSG_ENTRY_LT             ((MSG_TYPE)"") // ", Įrašas: %s")

#define KP_MSG_NO_STANDARD_PROG_LT  ((MSG_TYPE)"") // "Nerasta programa skirta atverti šio tipo failus")
#define KP_MSG_WND_NOT_FOUND_LT     ((MSG_TYPE)"") // "Langas nerastas")
#define KP_MSG_PID_NOT_FOUND_LT     ((MSG_TYPE)"") // "Nerastas proceso identifikatorius")
#define KP_MSG_NO_SOCKET_LT         ((MSG_TYPE)"") // "Jungtis dar nesukurta")
#define KP_MSG_SOCK_UNRESOLVED_LT   ((MSG_TYPE)"") // "Tarnybinės stoties adresas dar nesurastas")

#define KP_MSG_ERR_OK_LT            ((MSG_TYPE)"") // "Operacija atlikta sėkmingai") // !!!
#define KP_MSG_INVALIDARG_LT        ((MSG_TYPE)"") // "Neteisingi parametrai")
#define KP_MSG_NOTIMPL_LT           ((MSG_TYPE)"") // "Funkcija dar nerealizuota")
#define KP_MSG_UNEXPECTED_LT        ((MSG_TYPE)"") // "Netikėtas kreipinys į sąsają")
#define KP_MSG_FERROR_LT            ((MSG_TYPE)"") // "Failo skaitymo/rašymo klaida")
#define KP_MSG_SYSTEM_ERROR_LT      ((MSG_TYPE)"") // "Klaida sistemoje")
#define KP_MSG_EOF_LT               ((MSG_TYPE)"") // "Neteisinga failo pabaiga")
#define KP_MSG_FILE_FORMAT_LT       ((MSG_TYPE)"") // "Neteisingas failo formatas")
#define KP_MSG_FILE_NOT_FOUND_LT    ((MSG_TYPE)"") // "Failas nerastas")
#define KP_MSG_DIR_ERROR_LT         ((MSG_TYPE)"") // "Nepavyko atverti/sukurti failo")
#define KP_MSG_OUTOFMEM_LT          ((MSG_TYPE)"") // "Trūksta atminties")
#define KP_MSG_NO_FILE_LT           ((MSG_TYPE)"") // "Failas neatvertas")
#define KP_MSG_DOUBLE_UNGET_LT      ((MSG_TYPE)"") // "Dvigubas įvedimo grąžinimas")
#define KP_MSG_UNKN_CHR_LT          ((MSG_TYPE)"") // "Neatpažintas simbolis")
#define KP_MSG_COMMAND_ERROR_LT     ((MSG_TYPE)"") // "Išorinė klaida")
#define KP_MSG_BUFFER_OVERFLOW_LT   ((MSG_TYPE)"") // "Persipildė buferis")
#define KP_MSG_FONT_UNDEF_LT        ((MSG_TYPE)"") // "Neapibrėžtas šriftas")
#define KP_MSG_KWD_NOT_FOUND_LT     ((MSG_TYPE)"") // "Raktinis žodis nerastas")
#define KP_MSG_UNKNOWN_SYSTEM_LT    ((MSG_TYPE)"") // "Operacinė sistema neatpažinta")
#define KP_MSG_ILL_CODE_LT          ((MSG_TYPE)"") // "Klaidingas registracijos kodas")
#define KP_MSG_CANCELLED_LT         ((MSG_TYPE)"") // "Operacija nutraukta")
#define KP_MSG_DOUBLE_CALL_LT       ((MSG_TYPE)"") // "Dvigubas iškvietimas")
#define KP_MSG_TIMEOUT_LT           ((MSG_TYPE)"") // "Viršytas laukimo laikas")
#define KP_MSG_OBJ_NOT_FOUND_LT     ((MSG_TYPE)"") // "Objektas nerastas")
#define KP_MSG_NO_CONN_LT           ((MSG_TYPE)"") // "Nėra ryšio")

#define KP_MSG_TRANS_ERR_LT         ((MSG_TYPE)"") // "Perdavimo klaida")
#define KP_MSG_TRANS_ERR_1_LT       ((MSG_TYPE)"") // "Ryšio klaida, pakartokite siuntimo procedūrą"

#define KP_MSG_REFUSED_LT           ((MSG_TYPE)"") // "Registracija atmesta")
#define KP_MSG_ACCESS_DENIED_LT     ((MSG_TYPE)"") // "Neleista prisijungti")
#define KP_MSG_ILLEGAL_CHARACTER_LT ((MSG_TYPE)"") // "Neleistinas simbolis")
#define KP_MSG_DIV_ZERO_LT          ((MSG_TYPE)"") // "Dalyba iš nulio")
#define KP_MSG_ILLMATHARG_LT        ((MSG_TYPE)"") // "Neleistinas matematinės funkcijos argumentas") // "Šaknis iš neigiamo skaičiaus"
#define KP_MSG_ILLFUNC_LT           ((MSG_TYPE)"") // "Neleistina operacija") // illegal function call (at the moment)

#define KP_MSG_NOTINST_LT           ((MSG_TYPE)"") // "Programa neįdiegta arba diegimas sugedo, pakartokite diegimo procedūrą")
#define KP_MSG_NOTINST_S_LT         ((MSG_TYPE)"") // "Produktas „%s“ neįdiegtas arba jo diegimas sugedo, pakartokite diegimo procedūrą"
#define KP_MSG_NOTINST_DELETE_LT    ((MSG_TYPE)"") // "Produktas neįdiegtas arba jo diegimas sugedo, produktą panaikinkite ir pakartokite diegimo procedūrą"

#define KP_MSG_MSG_FORMAT_LT        ((MSG_TYPE)"") // "Neteisingas pranešimo formatas")
#define KP_MSG_OBSOLETE_LT          ((MSG_TYPE)"") // "Pasenusi funkcija")

#define KP_MSG_ERROR_HELP_LT        ((MSG_TYPE)"") // ".  Dėl techninės pagalbos kreipkitės elektroniniu paštu, adresu %s")
#define KP_MSG_ERROR_HELP_REST_LT   ((MSG_TYPE)"") // "   Prie laiško prikabinkite failą %s")

#define KP_MSG_WSAEACCES_LT               ((MSG_TYPE)"") // "Teisės nesuteiktos")
#define KP_MSG_WSAEADDRINUSE_LT           ((MSG_TYPE)"") // "Adresas jau naudojamas")
#define KP_MSG_WSAEADDRNOTAVAIL_LT        ((MSG_TYPE)"") // "Prašomas adresas negali būti priskirtas")
#define KP_MSG_WSAEAFNOSUPPORT_LT         ((MSG_TYPE)"") // "Adresų šeimos grupė nepalaikoma protokolo")
#define KP_MSG_WSAEALREADY_LT             ((MSG_TYPE)"") // "Operacija jau vykdoma")
#define KP_MSG_WSAECONNABORTED_LT         ((MSG_TYPE)"") // "Programa iššaukė ryšio nutraukimą")
#define KP_MSG_WSAECONNREFUSED_LT         ((MSG_TYPE)"") // "Susijungimas atmestas")
#define KP_MSG_WSAECONNRESET_LT           ((MSG_TYPE)"") // "Sujungimas nutrauktas")
#define KP_MSG_WSAEDESTADDRREQ_LT         ((MSG_TYPE)"") // "Būtinas kreities adresas")
#define KP_MSG_WSAEFAULT_LT               ((MSG_TYPE)"") // "Neteisingas adresas")
#define KP_MSG_WSAEHOSTDOWN_LT            ((MSG_TYPE)"") // "Serveris laikinai neveikia")
#define KP_MSG_WSAEHOSTUNREACH_LT         ((MSG_TYPE)"") // "Serveris nepasiekiamas")
#define KP_MSG_WSAEINPROGRESS_LT          ((MSG_TYPE)"") // "Operacija vykdoma")
#define KP_MSG_WSAEINTR_LT                ((MSG_TYPE)"") // "Funkcija nutraukta")
#define KP_MSG_WSAEINVAL_LT               ((MSG_TYPE)"") // "Neteisingi parametrai")
#define KP_MSG_WSAEISCONN_LT              ((MSG_TYPE)"") // "Susijungimas jau įvykęs")
#define KP_MSG_WSAEMFILE_LT               ((MSG_TYPE)"") // "Perdaug atvertų failų")
#define KP_MSG_WSAEMSGSIZE_LT             ((MSG_TYPE)"") // "Perdaug ilgas pranešimas")
#define KP_MSG_WSAENETDOWN_LT             ((MSG_TYPE)"") // "Tinklas neveikia")
#define KP_MSG_WSAENETRESET_LT            ((MSG_TYPE)"") // "Atsijungė nuo tinklo")
#define KP_MSG_WSAENETUNREACH_LT          ((MSG_TYPE)"") // "Tinklas nepasiekiamas")
#define KP_MSG_WSAENOBUFS_LT              ((MSG_TYPE)"") // "Trūksta vietos buferyje")
#define KP_MSG_WSAENOPROTOOPT_LT          ((MSG_TYPE)"") // "Neteisinga protokolo parinktis")
#define KP_MSG_WSAENOTCONN_LT             ((MSG_TYPE)"") // "Sujungimas nepavyko")
#define KP_MSG_WSAENOTSOCK_LT             ((MSG_TYPE)"") // "Socket operation on non-socket")
#define KP_MSG_WSAEOPNOTSUPP_LT           ((MSG_TYPE)"") // "Operacija negali būti atlikta")
#define KP_MSG_WSAEPFNOSUPPORT_LT         ((MSG_TYPE)"") // "Protokolo šeima nepalaikoma")
#define KP_MSG_WSAEPROCLIM_LT             ((MSG_TYPE)"") // "Perdaug procesų")
#define KP_MSG_WSAEPROTONOSUPPORT_LT      ((MSG_TYPE)"") // "Protokolas nepalaikomas")
#define KP_MSG_WSAEPROTOTYPE_LT           ((MSG_TYPE)"") // "Neteisingas protokolo sujungimo tipas")
#define KP_MSG_WSAESHUTDOWN_LT            ((MSG_TYPE)"") // "Siuntimas nebegalimas, sujungimas nutrauktas")
#define KP_MSG_WSAESOCKTNOSUPPORT_LT      ((MSG_TYPE)"") // "Sujungimo tipas nepalaikomas")
#define KP_MSG_WSAETIMEDOUT_LT            ((MSG_TYPE)"") // "Maksimalus sujungimo laukimo laikas viršytas")
#define KP_MSG_WSATYPE_NOT_FOUND_LT       ((MSG_TYPE)"") // "Klasės tipas nerastas")
#define KP_MSG_WSAEWOULDBLOCK_LT          ((MSG_TYPE)"") // "Šaltinis laikinai nepasiekiamas")
#define KP_MSG_WSAHOST_NOT_FOUND_LT       ((MSG_TYPE)"") // "Serveris nerastas")
#define KP_MSG_WSA_INVALID_HANDLE_LT      ((MSG_TYPE)"") // "Klaidingas objekto valdiklis") // "Klaidingas pasirinkto įvykio objekto valdiklis"
#define KP_MSG_WSA_INVALID_PARAMETER_LT   ((MSG_TYPE)"") // "Neteisingi parametrai") // "Neteisingi vienas ar daugiau parametrų"
#define KP_MSG_WSAINVALIDPROCTABLE_LT     ((MSG_TYPE)"") // "Klaidinga procedūrų lentelė")
#define KP_MSG_WSAINVALIDPROVIDER_LT      ((MSG_TYPE)"") // "Neteisingas tiekėjo kodas")
#define KP_MSG_WSA_IO_INCOMPLETE_LT       ((MSG_TYPE)"") // "Persikloja įvesties/išvesties įvykiai")
#define KP_MSG_WSA_IO_PENDING_LT          ((MSG_TYPE)"") // "Persiklojančios operacijos bus atliktos vėliau")

#define KP_MSG_WSA_NOT_ENOUGH_MEMORY_LT   ((MSG_TYPE)"") // "Nepakanka atminties")
#define KP_MSG_WSANOTINITIALISED_LT       ((MSG_TYPE)"") // "Tinklo posistemis neaktyvuotas")
#define KP_MSG_WSANO_DATA_LT              ((MSG_TYPE)"") // "Vardas teisingas, tačiau nėra reikiamo tipo duomenų")
#define KP_MSG_WSANO_RECOVERY_LT          ((MSG_TYPE)"") // "Nepataisoma klaida")
#define KP_MSG_WSAPROVIDERFAILEDINIT_LT   ((MSG_TYPE)"") // "Negalima inicializuoti paslaugos tiekėjo")
#define KP_MSG_WSASYSCALLFAILURE_LT       ((MSG_TYPE)"") // "Sistemos kreipinio klaida")
#define KP_MSG_WSASYSNOTREADY_LT          ((MSG_TYPE)"") // "Tinklo posistemė nepasiekiama")
#define KP_MSG_WSATRY_AGAIN_LT            ((MSG_TYPE)"") // "Neautorizuotas serveris nerastas")
#define KP_MSG_WSAVERNOTSUPPORTED_LT      ((MSG_TYPE)"") // "Netinka WINSOCK.DLL versija")
#define KP_MSG_WSAEDISCON_LT              ((MSG_TYPE)"") // "Pradėtas tvarkingas išjungimas") // ((MSG_TYPE)"Pradėtas gracingas išjungimas")
#define KP_MSG_WSA_OPERATION_ABORTED_LT   ((MSG_TYPE)"") // "Persiklojanti operacija nutraukta")

#define KP_MSG_OUT_OF_MEM_RES_LT          ((MSG_TYPE)"") // "Operacinei sistemai trūksta atminties")
#define KP_MSG_ERROR_FILE_NOT_FOUND_LT    ((MSG_TYPE)"") // "Nurodytas failas nerastas")
#define KP_MSG_ERROR_PATH_NOT_FOUND_LT    ((MSG_TYPE)"") // "Nurodytas kelias iki failų nerastas")
#define KP_MSG_ERROR_BAD_FORMAT_LT        ((MSG_TYPE)"") // "Pasirinktas .exe failas sugadintas")
#define KP_MSG_SE_ERR_ACCESSDENIED_LT     ((MSG_TYPE)"") // "Operacinė sistema uždraudė prisijungimą prie reikiamų failų")
#define KP_MSG_SE_ERR_ASSOCINCOMPLETE_LT  ((MSG_TYPE)"") // "Failo sąryšis su programa nepilnas arba neteisingas")
#define KP_MSG_SE_ERR_DDEBUSY_LT          ((MSG_TYPE)"") // "DDE transakcija negali būti baigta, nes kitos DDE transakcijos dar vykdomos")
#define KP_MSG_SE_ERR_DDEFAIL_LT          ((MSG_TYPE)"") // "DDE transakcija nutraukta")
#define KP_MSG_SE_ERR_DDETIMEOUT_LT       ((MSG_TYPE)"") // "DDE transakcija negali būti baigta, nes neužteko nurodyto laukimo laiko")
#define KP_MSG_SE_ERR_DLLNOTFOUND_LT      ((MSG_TYPE)"") // "Nurodyta dinaminė biblioteka nerasta")
#define KP_MSG_SE_ERR_FNF_LT              ((MSG_TYPE)"") // "Nurodytas failas nerastas")
#define KP_MSG_SE_ERR_NOASSOC_LT          ((MSG_TYPE)"") // "Nerasta programa skirta atverti šio tipo failus")
#define KP_MSG_SE_ERR_OOM_LT              ((MSG_TYPE)"") // "Nepakanka atminties atlikti operacijai")
#define KP_MSG_SE_ERR_PNF_LT              ((MSG_TYPE)"") // "Nurodytas kelias nerastas")
#define KP_MSG_SE_ERR_SHARE_LT            ((MSG_TYPE)"") // "Dalijimosi klaida")

#define KP_MSG_FIRST_TIME_ADMIN_LT        ((MSG_TYPE)"") // "Programą paleidžiant pirmą kartą, reikalingos\n administratoriaus teisės. Paleiskite programą iš naujo administratoriaus teisėmis.")
#define KP_MSG_NOW_NOT_ADMIN_LT           KP_MSG_NOT_ADMIN_LT // ((MSG_TYPE)"") // "Dabar programą paleiskite dar kartą paprasto vartotojo teisėmis")
#define KP_MSG_NOT_ADMIN_LT               ((MSG_TYPE)"") // "Programą paleiskite iš naujo paprasto vartotojo teisėmis")
#define KP_MSG_COPY_FILE_ACCESS_DENIED_LT ((MSG_TYPE)"") // "Failo nukopijuoti nepavyko, programą paleiskite iš naujo administratoriaus teisėmis")

#define KP_PROGRESS_TITLE_LT              ((MSG_TYPE)"") // "Palaukite...")
#define KP_MSG_DELETING_FILE_LT           ((MSG_TYPE)"") // "Naikinamas failas %s.%s...")
#define KP_MSG_COPYING_LT                 ((MSG_TYPE)"") // "Kopijuojamas failas...")
#define KP_MSG_COPYING_FILE_LT            ((MSG_TYPE)"") // "Kopijuojamas failas %s.%s...")
#define KP_MSG_COPYING_DIR_LT             ((MSG_TYPE)"") // "Kopijuojamas aplankas %s.%s...")

#define KP_MSG_NEG_ANSW_LT                ((MSG_TYPE)"") // "Neigiamas atsakymas")

#define KP_MSG_UNABLE_TO_EXECUTE_LT       ((MSG_TYPE)"") // "Komandos %s įvykdyti negaliu – patikrinkite, ar teisingai įdiegėte visus sistemos komponentus"

#define KP_MSG_FLASH_PLAYER_INSTALL_LT    ((MSG_TYPE)"") // "Dabar bus įdiegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus."

#define KP_MSG_FILE_CHANGED_LT            ((MSG_TYPE)"") // "Failas pasikeitė"

#define KP_MSG_ALL_FILES_LT               ((MSG_TYPE)"") // "Visi failai (*.*)"
#define KP_MSG_SAVE_AS_LT                 ((MSG_TYPE)"") // "Įrašyti kaip"

#define KP_MSG_FILE_EXISTS_LT             ((MSG_TYPE)"") // "Failas %s jau yra, perrašyti?"

#define KP_MSG_DIAG_MSG_LT                ((MSG_TYPE)"") // "Formuojamas diagnostinis pranešimas"
#define KP_MSG_DIAG_MSG_TITLE_LT          ((MSG_TYPE)"") // "Diagnostinis pranešimas"
#define KP_MSG_DIAG_MSG_EXPL_LT           ((MSG_TYPE)"") // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite pateiktus laukus. Pranešimas apie kompiuterio konfigūraciją, produktą bei klaidos pobūdį bus išsiųstas internetu į produkto gamintojo tarnybinę stotį. Jei po kurio laiko su Jumis nebus susisiekta Jūsų nurodytu pašto adresu, kreipkitės adresu %s")
#define KP_MSG_DIAG_MSG_EMAIL_PROMPT_LT   ((MSG_TYPE)"") // "Jūsų e-pašto adresas:")
#define KP_MSG_DIAG_MSG_COMMENTS_PROMPT_LT ((MSG_TYPE)"") // "Komentarai apie klaidos atsiradimo aplinkybes:")
#define KP_MSG_DIAG_MSG_FILE_PROMPT_LT    ((MSG_TYPE)"") // "Papildomas failas, kurį norėtumėte nusiųsti (pvz., ekrano kopijos paveikslėlis):")

#define KP_MSG_BAD_EMAIL_ADDRESS_LT       ((MSG_TYPE)"") // "Neteisingas e-pašto adresas"

#define KP_MSG_DIAG_MSG_SEL_FILE_LT       ((MSG_TYPE)"") // "Pasirinkite siunčiamą failą"

#define KP_MSG_DIAG_MSG_SUCCEEDED_LT      ((MSG_TYPE)"") // "Diagnostinis pranešimas nusiųstas sėkmingai"

#define KP_MSG_DIAG_MSG_EXPL1_LT          ((MSG_TYPE)"") // "Jei norite siųsti diagnostinį pranešimą, spragtelėkite „Siųsti“, jei ne – „Atšaukti“."
#define KP_MSG_SIUSTI_LT                  ((MSG_TYPE)"") // "Siųsti"
#define KP_MSG_DIAG_MSG_EXPL2_LT          ((MSG_TYPE)"") // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite Jūsų e-pašto adreso lauką ir spragtelėkite mygtuką „Siųsti“."

#define KP_MSG_DOWNLOADING_LT             ((MSG_TYPE)"") // "Siunčiamas failas..."
#define KP_MSG_DOWNLOADING_FILE_LT        ((MSG_TYPE)"") // "Siunčiamas failas %s.%s..."

#define KP_MSG_FIREWALL_LT                ((MSG_TYPE)"") // "Neleista prisijungti prie interneto. Patikrinkite Jūsų ugniasienės parinktis – pabandykite įtraukti %s į sąrašą programų, kurioms leidžiama kreiptis į internetą."

#define KP_MSG_POINTER_LT                 ((MSG_TYPE)"") // "Bloga rodyklė"

#define KP_MSG_LOG_STARTED_LT             ((MSG_TYPE)"") // "Žurnalas išvedamas ir į failą %s"
#define KP_MSG_CONS_TITLE_LT              ((MSG_TYPE)"") // "%s: Pranešimų žurnalas"

#define KP_MSG_UNHANDLED_EXCEPTION_LT     ((MSG_TYPE)"") // "Neapdorojamas trūkis"

#define KP_MSG_DATA_FORMAT_LT             ((MSG_TYPE)"") // "Neteisingas duomenų formatas"
#define KP_MSG_DBERROR_LT                 ((MSG_TYPE)"") // "Duomenų bazės klaida"

#endif // #if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangLt_p))


// --------------------------------
#if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1250_p))

#define KP_MSG_TITLE_PL_1250              ((MSG_TYPE)"") // "Komunikat")
#define KP_INPUT_TITLE_PL_1250            ((MSG_TYPE)"") // "Wprowadzanie"

#define KP_MSG_TAIP_PL_1250               ((MSG_TYPE)"") // "Tak")
#define KP_MSG_YES_PL_1250                KP_MSG_TAIP
#define KP_MSG_NE_PL_1250                 ((MSG_TYPE)"") // "Nie")
#define KP_MSG_NO_PL_1250                 KP_MSG_NE
#define KP_MSG_GERAI_PL_1250              ((MSG_TYPE)"") // "Dobrze")
#define KP_MSG_OK_PL_1250                 KP_MSG_GERAI
#define KP_MSG_ATSAUKTI_PL_1250           ((MSG_TYPE)"") // "Odwo³aj")
#define KP_MSG_CANCEL_PL_1250             KP_MSG_ATSAUKTI
#define KP_MSG_TESTI_PL_1250              ((MSG_TYPE)"") // "Dalej")
#define KP_MSG_BAIGTI_PL_1250             ((MSG_TYPE)"") // "Zakończ")
#define KP_MSG_PAMIRSAU_SLAPTAZODI_PL_1250 ((MSG_TYPE)"") // "Zapomnia³em has³o")

#define KP_MSG_ERROR_PL_1250              ((MSG_TYPE)"") // "B³¹d")
#define KP_MSG_WARNING_PL_1250            ((MSG_TYPE)"") // "Ostrzeæenie")
#define KP_MSG_FILE_LINE_PL_1250          ((MSG_TYPE)"") // ", plik:%s, linijka:%d")
#define KP_MSG_ENTRY_ID_PL_1250           ((MSG_TYPE)"") // ", Nr. wpisu:%ld")
#define KP_MSG_ENTRY_PL_1250              ((MSG_TYPE)"") // ", Wpis: %s")

#define KP_MSG_NO_STANDARD_PROG_PL_1250   ((MSG_TYPE)"") // "Nie znaleziono programu do otwierania plików tego typu")
#define KP_MSG_WND_NOT_FOUND_PL_1250      ((MSG_TYPE)"") // "Nie znaleziono okna")
#define KP_MSG_PID_NOT_FOUND_PL_1250      ((MSG_TYPE)"") // "Nie znaleziono indentyfikatora procesu")
#define KP_MSG_NO_SOCKET_PL_1250          ((MSG_TYPE)"") // "Wiź jeszcze nie stworzona")
#define KP_MSG_SOCK_UNRESOLVED_PL_1250    ((MSG_TYPE)"") // "Nie znaleziono adresu stacji s³uæbowej")

#define KP_MSG_ERR_OK_PL_1250             ((MSG_TYPE)"") // "Operacja wykonana")
#define KP_MSG_INVALIDARG_PL_1250         ((MSG_TYPE)"") // "B³źdne parametry")
#define KP_MSG_NOTIMPL_PL_1250            ((MSG_TYPE)"") // "W³aciwoę jeszcze nie zrealizowana")
#define KP_MSG_UNEXPECTED_PL_1250         ((MSG_TYPE)"") // "Nieoczekiwny zwrot do interfejsu")
#define KP_MSG_FERROR_PL_1250             ((MSG_TYPE)"") // "B³¹d sczytywania/zapisywania pliku")
#define KP_MSG_SYSTEM_ERROR_PL_1250       ((MSG_TYPE)"") // "B³¹d systemu")
#define KP_MSG_EOF_PL_1250                ((MSG_TYPE)"") // "Nieprawid³owe zakończenie pliku")
#define KP_MSG_FILE_FORMAT_PL_1250        ((MSG_TYPE)"") // "Nieprawid³owy format pliku")
#define KP_MSG_FILE_NOT_FOUND_PL_1250     ((MSG_TYPE)"") // "Nie znaleziono pliku")
#define KP_MSG_DIR_ERROR_PL_1250          ((MSG_TYPE)"") // "Nie uda³o siź otworzyę/stworzyę pliku")
#define KP_MSG_OUTOFMEM_PL_1250           ((MSG_TYPE)"") // "Niewystarcza pamiźci")
#define KP_MSG_NO_FILE_PL_1250            ((MSG_TYPE)"") // "Nie otworzono pliku")
#define KP_MSG_DOUBLE_UNGET_PL_1250       ((MSG_TYPE)"") // "Podwójny unget")
#define KP_MSG_UNKN_CHR_PL_1250           ((MSG_TYPE)"") // "Nierozpoznano symbol")
#define KP_MSG_COMMAND_ERROR_PL_1250      ((MSG_TYPE)"") // "B³¹d zewnźtrzny")

#define KP_MSG_BUFFER_OVERFLOW_PL_1250    ((MSG_TYPE)"") // "Przepe³niony bufor")
#define KP_MSG_FONT_UNDEF_PL_1250         ((MSG_TYPE)"") // "Nieokrelono szryft")
#define KP_MSG_KWD_NOT_FOUND_PL_1250      ((MSG_TYPE)"") // "Nie znaleziono kluczowego s³owa")
#define KP_MSG_UNKNOWN_SYSTEM_PL_1250     ((MSG_TYPE)"") // "Nie rozpoznano systemu operacyjnego")
#define KP_MSG_ILL_CODE_PL_1250           ((MSG_TYPE)"") // "B³źdny kod rejestracji")

#define KP_MSG_CANCELLED_PL_1250          ((MSG_TYPE)"") // "Przerwano operacjź")
#define KP_MSG_DOUBLE_CALL_PL_1250        ((MSG_TYPE)"") // "Podwójne wywo³anie")
#define KP_MSG_TIMEOUT_PL_1250            ((MSG_TYPE)"") // "Przekroczono czas oczekiwania")
#define KP_MSG_OBJ_NOT_FOUND_PL_1250      ((MSG_TYPE)"") // "Nie znaleziono objektu")

#define KP_MSG_NO_CONN_PL_1250            ((MSG_TYPE)"") // "Nie ma ³¹cznoci")

#define KP_MSG_TRANS_ERR_PL_1250          ((MSG_TYPE)"") // "B³¹d przekazu")
#define KP_MSG_TRANS_ERR_1_PL_1250        ((MSG_TYPE)"") // "B³¹d przekazu. Zapuszczaj wysy³anie ponownie"

#define KP_MSG_REFUSED_PL_1250            ((MSG_TYPE)"") // "Odrzucono rejestracjź")
#define KP_MSG_ACCESS_DENIED_PL_1250      ((MSG_TYPE)"") // "£¹cznoę niedozwolona")
#define KP_MSG_ILLEGAL_CHARACTER_PL_1250  ((MSG_TYPE)"") // "Niedopuszczalny symbol")
#define KP_MSG_DIV_ZERO_PL_1250           ((MSG_TYPE)"") // "Dzielenie przez zero")
#define KP_MSG_ILLMATHARG_PL_1250         ((MSG_TYPE)"") // "Niedopuszczalny argument matematycznej funkcji")
#define KP_MSG_ILLFUNC_PL_1250            ((MSG_TYPE)"") // "Niedopuszczalna operacja")

#define KP_MSG_NOTINST_PL_1250            ((MSG_TYPE)"") // "Program nie zainstalowany lub zepsuta instalacja. Zainstaluj ponownie")
#define KP_MSG_NOTINST_S_PL_1250          ((MSG_TYPE)"") // "Produktas „%s“ neįdiegtas arba jo diegimas sugedo, pakartokite diegimo procedūrą"
#define KP_MSG_NOTINST_DELETE_PL_1250     ((MSG_TYPE)"") // "Produktas neįdiegtas arba jo diegimas sugedo, produktą panaikinkite ir pakartokite diegimo procedūrą"

#define KP_MSG_MSG_FORMAT_PL_1250         ((MSG_TYPE)"") // "B³źdny format komunikatu")
#define KP_MSG_OBSOLETE_PL_1250           ((MSG_TYPE)"") // "Stara funkcja")
#define KP_MSG_ERROR_HELP_PL_1250         ((MSG_TYPE)"") // ".  Po pomoc techniczn¹ zwróę siź pod adres %s")
#define KP_MSG_ERROR_HELP_REST_PL_1250    ((MSG_TYPE)"") // "   Do listu za³¹cz plik %s")
#define KP_MSG_WSAEACCES_PL_1250               ((MSG_TYPE)"") // "Nie masz uprawnienia")
#define KP_MSG_WSAEADDRINUSE_PL_1250           ((MSG_TYPE)"") // "Adres jest juæ wykorzystany")
#define KP_MSG_WSAEADDRNOTAVAIL_PL_1250        ((MSG_TYPE)"") // "Wskazany adres nie moæe byę przy³¹czony")
#define KP_MSG_WSAEAFNOSUPPORT_PL_1250         ((MSG_TYPE)"") // "Grupa adresów nie podtrzymywana przez protokó³")
#define KP_MSG_WSAEALREADY_PL_1250             ((MSG_TYPE)"") // "Operacja juæ jest wykonywana")
#define KP_MSG_WSAECONNABORTED_PL_1250         ((MSG_TYPE)"") // "Program wywo³a³ rozerwanie po³¹czenia")
#define KP_MSG_WSAECONNREFUSED_PL_1250         ((MSG_TYPE)"") // "Po³¹czenie zosta³o odrzucone")

#define KP_MSG_WSAECONNRESET_PL_1250           ((MSG_TYPE)"") // "Po³¹czenie zosta³o rozerwane")
#define KP_MSG_WSAEDESTADDRREQ_PL_1250         ((MSG_TYPE)"") // "Wymagany jest adres")
#define KP_MSG_WSAEFAULT_PL_1250               ((MSG_TYPE)"") // "B³źdny adres")

#define KP_MSG_WSAEHOSTDOWN_PL_1250            ((MSG_TYPE)"") // "Serwer czasowo niedostźpny")
#define KP_MSG_WSAEHOSTUNREACH_PL_1250         ((MSG_TYPE)"") // "Serwer jest nieosi¹galny")
#define KP_MSG_WSAEINPROGRESS_PL_1250          ((MSG_TYPE)"") // "Operacja jest wykonywana")
#define KP_MSG_WSAEINTR_PL_1250                ((MSG_TYPE)"") // "Funkcja zosta³a przerwana")

#define KP_MSG_WSAEINVAL_PL_1250               ((MSG_TYPE)"") // "B³źdne parametry")
#define KP_MSG_WSAEISCONN_PL_1250              ((MSG_TYPE)"") // "Po³¹czenie juæ jest nawi¹zane")
#define KP_MSG_WSAEMFILE_PL_1250               ((MSG_TYPE)"") // "Otworzono za duæo plików")

#define KP_MSG_WSAEMSGSIZE_PL_1250             ((MSG_TYPE)"") // "Zbyt d³ugi komunikat")
#define KP_MSG_WSAENETDOWN_PL_1250             ((MSG_TYPE)"") // "Sieę nie dzia³a")
#define KP_MSG_WSAENETRESET_PL_1250            ((MSG_TYPE)"") // "Od³¹czono siź od sieci")

#define KP_MSG_WSAENETUNREACH_PL_1250          ((MSG_TYPE)"") // "Sieę nieosi¹galna")
#define KP_MSG_WSAENOBUFS_PL_1250              ((MSG_TYPE)"") // "Brakuje miejsca w buforze")
#define KP_MSG_WSAENOPROTOOPT_PL_1250          ((MSG_TYPE)"") // "B³źdne opcje protoko³u")

#define KP_MSG_WSAENOTCONN_PL_1250             ((MSG_TYPE)"") // "Nieudane po³¹czenie")
#define KP_MSG_WSAENOTSOCK_PL_1250             ((MSG_TYPE)"") // "Socket operation on non-socket")
#define KP_MSG_WSAEOPNOTSUPP_PL_1250           ((MSG_TYPE)"") // "Operacja nie moæe byę wykonana")

#define KP_MSG_WSAEPFNOSUPPORT_PL_1250         ((MSG_TYPE)"") // "Niepodtrzymywana rodzina protoko³ów")
#define KP_MSG_WSAEPROCLIM_PL_1250             ((MSG_TYPE)"") // "Zbyt duæo procesów")
#define KP_MSG_WSAEPROTONOSUPPORT_PL_1250      ((MSG_TYPE)"") // "Protokó³ nie jest podtrzymywany")

#define KP_MSG_WSAEPROTOTYPE_PL_1250           ((MSG_TYPE)"") // "Nieprawid³owy typ po³¹czenia protoko³u")
#define KP_MSG_WSAESHUTDOWN_PL_1250            ((MSG_TYPE)"") // "Wysy³anie niemoæliwe, po³¹czenie zerwane")
#define KP_MSG_WSAESOCKTNOSUPPORT_PL_1250      ((MSG_TYPE)"") // "Typ po³¹czenia niepodtrzymywany")
#define KP_MSG_WSAETIMEDOUT_PL_1250            ((MSG_TYPE)"") // "Przewyæszono maksymalny czas oczekiwania po³¹czenia")

#define KP_MSG_WSATYPE_NOT_FOUND_PL_1250       ((MSG_TYPE)"") // "Nie znaleziono typ klasy")
#define KP_MSG_WSAEWOULDBLOCK_PL_1250          ((MSG_TYPE)"") // "¸ród³o czasowo niedostźpne")
#define KP_MSG_WSAHOST_NOT_FOUND_PL_1250       ((MSG_TYPE)"") // "Nie znaleziono serweru")
#define KP_MSG_WSA_INVALID_HANDLE_PL_1250      ((MSG_TYPE)"") // "B³źdny kontroler objektu")
#define KP_MSG_WSA_INVALID_PARAMETER_PL_1250   ((MSG_TYPE)"") // "B³źdne parametry")
#define KP_MSG_WSAINVALIDPROCTABLE_PL_1250     ((MSG_TYPE)"") // "B³źdna tablica procedur")
#define KP_MSG_WSAINVALIDPROVIDER_PL_1250      ((MSG_TYPE)"") // "B³źdny kod dostawcy")
#define KP_MSG_WSA_IO_INCOMPLETE_PL_1250       ((MSG_TYPE)"") // "Nak³adaj¹ siź zdarzenia wprowdzania/wyprowadzania")
#define KP_MSG_WSA_IO_PENDING_PL_1250          ((MSG_TYPE)"") // "Nak³adaj¹ce siź operacje bźd¹ wykonane póniej")

#define KP_MSG_WSA_NOT_ENOUGH_MEMORY_PL_1250   ((MSG_TYPE)"") // "Brak pamiźci")
#define KP_MSG_WSANOTINITIALISED_PL_1250       ((MSG_TYPE)"") // "Podsystem sieci nieaktywowany")
#define KP_MSG_WSANO_DATA_PL_1250              ((MSG_TYPE)"") // "Nie ma danych wymaganego typu")
#define KP_MSG_WSANO_RECOVERY_PL_1250          ((MSG_TYPE)"") // "Nienaprawialny b³¹d")
#define KP_MSG_WSAPROVIDERFAILEDINIT_PL_1250   ((MSG_TYPE)"") // "Nie moæliwa jest inicjacja dostawcy us³ugi")
#define KP_MSG_WSASYSCALLFAILURE_PL_1250       ((MSG_TYPE)"") // "B³źdny zwrot systemu")
#define KP_MSG_WSASYSNOTREADY_PL_1250          ((MSG_TYPE)"") // "Podsystem sieci nieosi¹galny")
#define KP_MSG_WSATRY_AGAIN_PL_1250            ((MSG_TYPE)"") // "Nieautoryzowany serwer nie znaleziony")

#define KP_MSG_WSAVERNOTSUPPORTED_PL_1250      ((MSG_TYPE)"") // "B³źdna wersja WINSOCK.DLL")
#define KP_MSG_WSAEDISCON_PL_1250              ((MSG_TYPE)"") // "Rozpoczźto porz¹dne wy³¹czanie")
#define KP_MSG_WSA_OPERATION_ABORTED_PL_1250   ((MSG_TYPE)"") // "Nak³adaj¹ca siź operacja przerwana")

#define KP_MSG_OUT_OF_MEM_RES_PL_1250          ((MSG_TYPE)"") // "Brak pamiźci systemu operacyjnego")
#define KP_MSG_ERROR_FILE_NOT_FOUND_PL_1250    ((MSG_TYPE)"") // "Nie znaleziono wskazanego pliku")
#define KP_MSG_ERROR_PATH_NOT_FOUND_PL_1250    ((MSG_TYPE)"") // "Nie znaleziono wskazanej cieæki do pliku")
#define KP_MSG_ERROR_BAD_FORMAT_PL_1250        ((MSG_TYPE)"") // "Wybrany plik .exe jest zepsuty")
#define KP_MSG_SE_ERR_ACCESSDENIED_PL_1250     ((MSG_TYPE)"") // "System operacyjny zabroni³ ³¹cznoci z potrzebnymi plikami")
#define KP_MSG_SE_ERR_ASSOCINCOMPLETE_PL_1250  ((MSG_TYPE)"") // "Wiź pliku z programem jest niepe³na lub b³źdna")
#define KP_MSG_SE_ERR_DDEBUSY_PL_1250          ((MSG_TYPE)"") // "DDE transakcja nie moæe byę zakończona, bo inne DDE transakcje s¹ jeszcze wykonywane")
#define KP_MSG_SE_ERR_DDEFAIL_PL_1250          ((MSG_TYPE)"") // "DDE transakcja przerwana")
#define KP_MSG_SE_ERR_DDETIMEOUT_PL_1250       ((MSG_TYPE)"") // "DDE transakcja nie moæe byę zakończona, bo zabrak³o wskazanego czasu oczekiwania")
#define KP_MSG_SE_ERR_DLLNOTFOUND_PL_1250      ((MSG_TYPE)"") // "Nie znaleziono wskazanej biblioteki dynamicznej")
#define KP_MSG_SE_ERR_FNF_PL_1250              ((MSG_TYPE)"") // "Nie znaleziono wskazanego pliku")
#define KP_MSG_SE_ERR_NOASSOC_PL_1250          ((MSG_TYPE)"") // "Nie znaleziono programu do otwarcia plików danego typu")

#define KP_MSG_SE_ERR_OOM_PL_1250              ((MSG_TYPE)"") // "Brak pamiźci do wykonania operacji")
#define KP_MSG_SE_ERR_PNF_PL_1250              ((MSG_TYPE)"") // "Nie znaleziono wskazanej cieæki")
#define KP_MSG_SE_ERR_SHARE_PL_1250            ((MSG_TYPE)"") // "B³¹d podzia³u")

#define KP_MSG_FIRST_TIME_ADMIN_PL_1250        ((MSG_TYPE)"") // "Zapuszczaj¹c program poraz pierwszy wymagane s¹ uprawnienia administratora. Zapuę program ponownie z uprawnieniami administratora.")

#define KP_MSG_NOW_NOT_ADMIN_PL_1250           KP_MSG_NOT_ADMIN_PL_1250
#define KP_MSG_NOT_ADMIN_PL_1250               ((MSG_TYPE)"") // "Zapuę program ponownie z uprawnieniami zwyk³ego uæytkownika")

#define KP_MSG_COPY_FILE_ACCESS_DENIED_PL_1250 ((MSG_TYPE)"") // "Nie uda³o siź skopiowaę pliku. Zapuę program ponownie z uprawnieniami administratora.")


#define KP_PROGRESS_TITLE_PL_1250               ((MSG_TYPE)"") // "Zaczekaj...")
#define KP_MSG_DELETING_FILE_PL_1250            ((MSG_TYPE)"") // "Kasuje siź plik %s.%s...")

#define KP_MSG_COPYING_PL_1250                  ((MSG_TYPE)"") // "Kopiuje siź plik...")

#define KP_MSG_COPYING_DIR_PL_1250              ((MSG_TYPE)"") // "Kopiuje siź katalog %s.%s...")
#define KP_MSG_COPYING_FILE_PL_1250             ((MSG_TYPE)"") // "Kopiuje siź plik %s.%s...")

#define KP_MSG_NEG_ANSW_PL_1250                 ((MSG_TYPE)"") // "Neigiamas atsakymas")

#define KP_MSG_UNABLE_TO_EXECUTE_PL_1250        ((MSG_TYPE)"") // "Komandos %s įvykdyti negaliu – patikrinkite, ar teisingai įdiegėte visus sistemos komponentus"

#define KP_MSG_FLASH_PLAYER_INSTALL_PL_1250     ((MSG_TYPE)"") // "Dabar bus įdiegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus."

#define KP_MSG_FILE_CHANGED_PL_1250             ((MSG_TYPE)"") // "Failas pasikeitė"

#define KP_MSG_ALL_FILES_PL_1250                ((MSG_TYPE)"") // "Visi failai (*.*)"
#define KP_MSG_SAVE_AS_PL_1250                  ((MSG_TYPE)"") // "Įrašyti kaip"

#define KP_MSG_FILE_EXISTS_PL_1250              ((MSG_TYPE)"") // "Failas %s jau yra, perrašyti?"

#define KP_MSG_DIAG_MSG_PL_1250                 ((MSG_TYPE)"") // "Formuojamas diagnostinis pranešimas"
#define KP_MSG_DIAG_MSG_TITLE_PL_1250           ((MSG_TYPE)"") // "Diagnostinis pranešimas"
#define KP_MSG_DIAG_MSG_EXPL_PL_1250            ((MSG_TYPE)"") // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite pateiktus laukus. Pranešimas apie kompiuterio konfigūraciją, produktą bei klaidos pobūdį bus išsiųstas internetu į produkto gamintojo tarnybinę stotį. Jei po kurio laiko su Jumis nebus susisiekta Jūsų nurodytu pašto adresu, kreipkitės adresu %s")
#define KP_MSG_DIAG_MSG_EMAIL_PROMPT_PL_1250    ((MSG_TYPE)"") // "Jūsų e-pašto adresas:")
#define KP_MSG_DIAG_MSG_COMMENTS_PROMPT_PL_1250 ((MSG_TYPE)"") // "Komentarai apie klaidos atsiradimo aplinkybes:")
#define KP_MSG_DIAG_MSG_FILE_PROMPT_PL_1250     ((MSG_TYPE)"") // "Papildomas failas, kurį norėtumėte nusiųsti (pvz., ekrano kopijos paveikslėlis):")

#define KP_MSG_BAD_EMAIL_ADDRESS_PL_1250        ((MSG_TYPE)"") // "Neteisingas e-pašto adresas"

#define KP_MSG_DIAG_MSG_SEL_FILE_PL_1250        ((MSG_TYPE)"") // "Pasirinkite siunčiamą failą"

#define KP_MSG_DIAG_MSG_SUCCEEDED_PL_1250       ((MSG_TYPE)"") // "Diagnostinis pranešimas nusiųstas sėkmingai"

#define KP_MSG_DIAG_MSG_EXPL1_PL_1250           ((MSG_TYPE)"") // "Jei norite siųsti diagnostinį pranešimą, spragtelėkite „Siųsti“, jei ne – „Atšaukti“."
#define KP_MSG_SIUSTI_PL_1250                   ((MSG_TYPE)"") // "Siųsti"
#define KP_MSG_DIAG_MSG_EXPL2_PL_1250           ((MSG_TYPE)"") // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite Jūsų e-pašto adreso lauką ir spragtelėkite mygtuką „Siųsti“."

#define KP_MSG_DOWNLOADING_PL_1250              ((MSG_TYPE)"") // "Siunčiamas failas..."
#define KP_MSG_DOWNLOADING_FILE_PL_1250         ((MSG_TYPE)"") // "Siunčiamas failas %s.%s..."

#define KP_MSG_FIREWALL_PL_1250                 ((MSG_TYPE)"") // "Neleista prisijungti prie interneto. Patikrinkite Jūsų ugniasienės parinktis – pabandykite įtraukti %s į sąrašą programų, kurioms leidžiama kreiptis į internetą."

#define KP_MSG_POINTER_PL_1250                  ((MSG_TYPE)"") // "Bloga rodyklė"

#define KP_MSG_LOG_STARTED_PL_1250              ((MSG_TYPE)"") // "Žurnalas išvedamas ir į failą %s"
#define KP_MSG_CONS_TITLE_PL_1250               ((MSG_TYPE)"") // "%s: Pranešimų žurnalas"

#define KP_MSG_UNHANDLED_EXCEPTION_PL_1250      ((MSG_TYPE)"") // "Neapdorojamas trūkis"

#define KP_MSG_DATA_FORMAT_PL_1250              ((MSG_TYPE)"") // "Neteisingas duomenų formatas"
#define KP_MSG_DBERROR_PL_1250                  ((MSG_TYPE)"") // "Duomenų bazės klaida"

#endif // #if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1250_p))

// --------------------------------
#if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1257_p))

#define KP_MSG_TITLE_PL_1257              ((MSG_TYPE)"") // "Komunikat")
#define KP_INPUT_TITLE_PL_1257            ((MSG_TYPE)"") // "Wprowadzanie"

#define KP_MSG_TAIP_PL_1257               ((MSG_TYPE)"") // "Tak")
#define KP_MSG_YES_PL_1257                KP_MSG_TAIP
#define KP_MSG_NE_PL_1257                 ((MSG_TYPE)"") // "Nie")
#define KP_MSG_NO_PL_1257                 KP_MSG_NE
#define KP_MSG_GERAI_PL_1257              ((MSG_TYPE)"") // "Dobrze")
#define KP_MSG_OK_PL_1257                 KP_MSG_GERAI
#define KP_MSG_ATSAUKTI_PL_1257           ((MSG_TYPE)"") // "Odwołaj")
#define KP_MSG_CANCEL_PL_1257             KP_MSG_ATSAUKTI
#define KP_MSG_TESTI_PL_1257              ((MSG_TYPE)"") // "Dalej")
#define KP_MSG_BAIGTI_PL_1257             ((MSG_TYPE)"") // "Zakończ")
#define KP_MSG_PAMIRSAU_SLAPTAZODI_PL_1257 ((MSG_TYPE)"") // "Zapomniałem hasło")

#define KP_MSG_ERROR_PL_1257              ((MSG_TYPE)"") // "Błąd")
#define KP_MSG_WARNING_PL_1257            ((MSG_TYPE)"") // "Ostrzeżenie")
#define KP_MSG_FILE_LINE_PL_1257          ((MSG_TYPE)"") // ", plik:%s, linijka:%d")
#define KP_MSG_ENTRY_ID_PL_1257           ((MSG_TYPE)"") // ", Nr. wpisu:%ld")
#define KP_MSG_ENTRY_PL_1257              ((MSG_TYPE)"") // ", Wpis: %s")

#define KP_MSG_NO_STANDARD_PROG_PL_1257   ((MSG_TYPE)"") // "Nie znaleziono programu do otwierania plików tego typu")
#define KP_MSG_WND_NOT_FOUND_PL_1257      ((MSG_TYPE)"") // "Nie znaleziono okna")
#define KP_MSG_PID_NOT_FOUND_PL_1257      ((MSG_TYPE)"") // "Nie znaleziono indentyfikatora procesu")
#define KP_MSG_NO_SOCKET_PL_1257          ((MSG_TYPE)"") // "Więź jeszcze nie stworzona")
#define KP_MSG_SOCK_UNRESOLVED_PL_1257    ((MSG_TYPE)"") // "Nie znaleziono adresu stacji służbowej")

#define KP_MSG_ERR_OK_PL_1257             ((MSG_TYPE)"") // "Operacja wykonana")
#define KP_MSG_INVALIDARG_PL_1257         ((MSG_TYPE)"") // "Błędne parametry")
#define KP_MSG_NOTIMPL_PL_1257            ((MSG_TYPE)"") // "Właściwość jeszcze nie zrealizowana")
#define KP_MSG_UNEXPECTED_PL_1257         ((MSG_TYPE)"") // "Nieoczekiwny zwrot do interfejsu")
#define KP_MSG_FERROR_PL_1257             ((MSG_TYPE)"") // "Błąd sczytywania/zapisywania pliku")
#define KP_MSG_SYSTEM_ERROR_PL_1257       ((MSG_TYPE)"") // "Błąd systemu")
#define KP_MSG_EOF_PL_1257                ((MSG_TYPE)"") // "Nieprawidłowe zakończenie pliku")
#define KP_MSG_FILE_FORMAT_PL_1257        ((MSG_TYPE)"") // "Nieprawidłowy format pliku")
#define KP_MSG_FILE_NOT_FOUND_PL_1257     ((MSG_TYPE)"") // "Nie znaleziono pliku")
#define KP_MSG_DIR_ERROR_PL_1257          ((MSG_TYPE)"") // "Nie udało się otworzyć/stworzyć pliku")
#define KP_MSG_OUTOFMEM_PL_1257           ((MSG_TYPE)"") // "Niewystarcza pamięci")
#define KP_MSG_NO_FILE_PL_1257            ((MSG_TYPE)"") // "Nie otworzono pliku")
#define KP_MSG_DOUBLE_UNGET_PL_1257       ((MSG_TYPE)"") // "Podwójny unget")
#define KP_MSG_UNKN_CHR_PL_1257           ((MSG_TYPE)"") // "Nierozpoznano symbol")
#define KP_MSG_COMMAND_ERROR_PL_1257      ((MSG_TYPE)"") // "Błąd zewnętrzny")

#define KP_MSG_BUFFER_OVERFLOW_PL_1257    ((MSG_TYPE)"") // "Przepełniony bufor")
#define KP_MSG_FONT_UNDEF_PL_1257         ((MSG_TYPE)"") // "Nieokreślono szryft")
#define KP_MSG_KWD_NOT_FOUND_PL_1257      ((MSG_TYPE)"") // "Nie znaleziono kluczowego słowa")
#define KP_MSG_UNKNOWN_SYSTEM_PL_1257     ((MSG_TYPE)"") // "Nie rozpoznano systemu operacyjnego")
#define KP_MSG_ILL_CODE_PL_1257           ((MSG_TYPE)"") // "Błędny kod rejestracji")

#define KP_MSG_CANCELLED_PL_1257          ((MSG_TYPE)"") // "Przerwano operację")
#define KP_MSG_DOUBLE_CALL_PL_1257        ((MSG_TYPE)"") // "Podwójne wywołanie")
#define KP_MSG_TIMEOUT_PL_1257            ((MSG_TYPE)"") // "Przekroczono czas oczekiwania")
#define KP_MSG_OBJ_NOT_FOUND_PL_1257      ((MSG_TYPE)"") // "Nie znaleziono objektu")

#define KP_MSG_NO_CONN_PL_1257            ((MSG_TYPE)"") // "Nie ma łączności")

#define KP_MSG_TRANS_ERR_PL_1257          ((MSG_TYPE)"") // "Błąd przekazu")
#define KP_MSG_TRANS_ERR_1_PL_1257        ((MSG_TYPE)"") // "Błąd przekazu. Zapuszczaj wysyłanie ponownie"

#define KP_MSG_REFUSED_PL_1257            ((MSG_TYPE)"") // "Odrzucono rejestrację")
#define KP_MSG_ACCESS_DENIED_PL_1257      ((MSG_TYPE)"") // "Łączność niedozwolona")
#define KP_MSG_ILLEGAL_CHARACTER_PL_1257  ((MSG_TYPE)"") // "Niedopuszczalny symbol")
#define KP_MSG_DIV_ZERO_PL_1257           ((MSG_TYPE)"") // "Dzielenie przez zero")
#define KP_MSG_ILLMATHARG_PL_1257         ((MSG_TYPE)"") // "Niedopuszczalny argument matematycznej funkcji")
#define KP_MSG_ILLFUNC_PL_1257            ((MSG_TYPE)"") // "Niedopuszczalna operacja")

#define KP_MSG_NOTINST_PL_1257            ((MSG_TYPE)"") // "Program nie zainstalowany lub zepsuta instalacja. Zainstaluj ponownie")
#define KP_MSG_NOTINST_S_PL_1257          ((MSG_TYPE)"") // "Produktas „%s“ neįdiegtas arba jo diegimas sugedo, pakartokite diegimo procedūrą"
#define KP_MSG_NOTINST_DELETE_PL_1257     ((MSG_TYPE)"") // "Produktas neįdiegtas arba jo diegimas sugedo, produktą panaikinkite ir pakartokite diegimo procedūrą"

#define KP_MSG_MSG_FORMAT_PL_1257         ((MSG_TYPE)"") // "Błędny format komunikatu")
#define KP_MSG_OBSOLETE_PL_1257           ((MSG_TYPE)"") // "Stara funkcja")
#define KP_MSG_ERROR_HELP_PL_1257         ((MSG_TYPE)"") // ".  Po pomoc techniczną zwróć się pod adres %s")
#define KP_MSG_ERROR_HELP_REST_PL_1257    ((MSG_TYPE)"") // "   Do listu załącz plik %s")
#define KP_MSG_WSAEACCES_PL_1257               ((MSG_TYPE)"") // "Nie masz uprawnienia")
#define KP_MSG_WSAEADDRINUSE_PL_1257           ((MSG_TYPE)"") // "Adres jest już wykorzystany")
#define KP_MSG_WSAEADDRNOTAVAIL_PL_1257        ((MSG_TYPE)"") // "Wskazany adres nie może być przyłączony")
#define KP_MSG_WSAEAFNOSUPPORT_PL_1257         ((MSG_TYPE)"") // "Grupa adresów nie podtrzymywana przez protokół")
#define KP_MSG_WSAEALREADY_PL_1257             ((MSG_TYPE)"") // "Operacja już jest wykonywana")
#define KP_MSG_WSAECONNABORTED_PL_1257         ((MSG_TYPE)"") // "Program wywołał rozerwanie połączenia")
#define KP_MSG_WSAECONNREFUSED_PL_1257         ((MSG_TYPE)"") // "Połączenie zostało odrzucone")

#define KP_MSG_WSAECONNRESET_PL_1257           ((MSG_TYPE)"") // "Połączenie zostało rozerwane")
#define KP_MSG_WSAEDESTADDRREQ_PL_1257         ((MSG_TYPE)"") // "Wymagany jest adres")
#define KP_MSG_WSAEFAULT_PL_1257               ((MSG_TYPE)"") // "Błędny adres")

#define KP_MSG_WSAEHOSTDOWN_PL_1257            ((MSG_TYPE)"") // "Serwer czasowo niedostępny")
#define KP_MSG_WSAEHOSTUNREACH_PL_1257         ((MSG_TYPE)"") // "Serwer jest nieosiągalny")
#define KP_MSG_WSAEINPROGRESS_PL_1257          ((MSG_TYPE)"") // "Operacja jest wykonywana")
#define KP_MSG_WSAEINTR_PL_1257                ((MSG_TYPE)"") // "Funkcja została przerwana")

#define KP_MSG_WSAEINVAL_PL_1257               ((MSG_TYPE)"") // "Błędne parametry")
#define KP_MSG_WSAEISCONN_PL_1257              ((MSG_TYPE)"") // "Połączenie już jest nawiązane")
#define KP_MSG_WSAEMFILE_PL_1257               ((MSG_TYPE)"") // "Otworzono za dużo plików")

#define KP_MSG_WSAEMSGSIZE_PL_1257             ((MSG_TYPE)"") // "Zbyt długi komunikat")
#define KP_MSG_WSAENETDOWN_PL_1257             ((MSG_TYPE)"") // "Sieć nie działa")
#define KP_MSG_WSAENETRESET_PL_1257            ((MSG_TYPE)"") // "Odłączono się od sieci")

#define KP_MSG_WSAENETUNREACH_PL_1257          ((MSG_TYPE)"") // "Sieć nieosiągalna")
#define KP_MSG_WSAENOBUFS_PL_1257              ((MSG_TYPE)"") // "Brakuje miejsca w buforze")
#define KP_MSG_WSAENOPROTOOPT_PL_1257          ((MSG_TYPE)"") // "Błędne opcje protokołu")

#define KP_MSG_WSAENOTCONN_PL_1257             ((MSG_TYPE)"") // "Nieudane połączenie")
#define KP_MSG_WSAENOTSOCK_PL_1257             ((MSG_TYPE)"") // "Socket operation on non-socket")
#define KP_MSG_WSAEOPNOTSUPP_PL_1257           ((MSG_TYPE)"") // "Operacja nie może być wykonana")

#define KP_MSG_WSAEPFNOSUPPORT_PL_1257         ((MSG_TYPE)"") // "Niepodtrzymywana rodzina protokołów")
#define KP_MSG_WSAEPROCLIM_PL_1257             ((MSG_TYPE)"") // "Zbyt dużo procesów")
#define KP_MSG_WSAEPROTONOSUPPORT_PL_1257      ((MSG_TYPE)"") // "Protokół nie jest podtrzymywany")

#define KP_MSG_WSAEPROTOTYPE_PL_1257           ((MSG_TYPE)"") // "Nieprawidłowy typ połączenia protokołu")
#define KP_MSG_WSAESHUTDOWN_PL_1257            ((MSG_TYPE)"") // "Wysyłanie niemożliwe, połączenie zerwane")
#define KP_MSG_WSAESOCKTNOSUPPORT_PL_1257      ((MSG_TYPE)"") // "Typ połączenia niepodtrzymywany")
#define KP_MSG_WSAETIMEDOUT_PL_1257            ((MSG_TYPE)"") // "Przewyższono maksymalny czas oczekiwania połączenia")

#define KP_MSG_WSATYPE_NOT_FOUND_PL_1257       ((MSG_TYPE)"") // "Nie znaleziono typ klasy")
#define KP_MSG_WSAEWOULDBLOCK_PL_1257          ((MSG_TYPE)"") // "Źródło czasowo niedostępne")
#define KP_MSG_WSAHOST_NOT_FOUND_PL_1257       ((MSG_TYPE)"") // "Nie znaleziono serweru")
#define KP_MSG_WSA_INVALID_HANDLE_PL_1257      ((MSG_TYPE)"") // "Błędny kontroler objektu")
#define KP_MSG_WSA_INVALID_PARAMETER_PL_1257   ((MSG_TYPE)"") // "Błędne parametry")
#define KP_MSG_WSAINVALIDPROCTABLE_PL_1257     ((MSG_TYPE)"") // "Błędna tablica procedur")
#define KP_MSG_WSAINVALIDPROVIDER_PL_1257      ((MSG_TYPE)"") // "Błędny kod dostawcy")
#define KP_MSG_WSA_IO_INCOMPLETE_PL_1257       ((MSG_TYPE)"") // "Nakładają się zdarzenia wprowdzania/wyprowadzania")
#define KP_MSG_WSA_IO_PENDING_PL_1257          ((MSG_TYPE)"") // "Nakładające się operacje będą wykonane później")

#define KP_MSG_WSA_NOT_ENOUGH_MEMORY_PL_1257   ((MSG_TYPE)"") // "Brak pamięci")
#define KP_MSG_WSANOTINITIALISED_PL_1257       ((MSG_TYPE)"") // "Podsystem sieci nieaktywowany")
#define KP_MSG_WSANO_DATA_PL_1257              ((MSG_TYPE)"") // "Nie ma danych wymaganego typu")
#define KP_MSG_WSANO_RECOVERY_PL_1257          ((MSG_TYPE)"") // "Nienaprawialny błąd")
#define KP_MSG_WSAPROVIDERFAILEDINIT_PL_1257   ((MSG_TYPE)"") // "Nie możliwa jest inicjacja dostawcy usługi")
#define KP_MSG_WSASYSCALLFAILURE_PL_1257       ((MSG_TYPE)"") // "Błędny zwrot systemu")
#define KP_MSG_WSASYSNOTREADY_PL_1257          ((MSG_TYPE)"") // "Podsystem sieci nieosiągalny")
#define KP_MSG_WSATRY_AGAIN_PL_1257            ((MSG_TYPE)"") // "Nieautoryzowany serwer nie znaleziony")

#define KP_MSG_WSAVERNOTSUPPORTED_PL_1257      ((MSG_TYPE)"") // "Błędna wersja WINSOCK.DLL")
#define KP_MSG_WSAEDISCON_PL_1257              ((MSG_TYPE)"") // "Rozpoczęto porządne wyłączanie")
#define KP_MSG_WSA_OPERATION_ABORTED_PL_1257   ((MSG_TYPE)"") // "Nakładająca się operacja przerwana")

#define KP_MSG_OUT_OF_MEM_RES_PL_1257          ((MSG_TYPE)"") // "Brak pamięci systemu operacyjnego")
#define KP_MSG_ERROR_FILE_NOT_FOUND_PL_1257    ((MSG_TYPE)"") // "Nie znaleziono wskazanego pliku")
#define KP_MSG_ERROR_PATH_NOT_FOUND_PL_1257    ((MSG_TYPE)"") // "Nie znaleziono wskazanej ścieżki do pliku")
#define KP_MSG_ERROR_BAD_FORMAT_PL_1257        ((MSG_TYPE)"") // "Wybrany plik .exe jest zepsuty")
#define KP_MSG_SE_ERR_ACCESSDENIED_PL_1257     ((MSG_TYPE)"") // "System operacyjny zabronił łączności z potrzebnymi plikami")
#define KP_MSG_SE_ERR_ASSOCINCOMPLETE_PL_1257  ((MSG_TYPE)"") // "Więź pliku z programem jest niepełna lub błędna")
#define KP_MSG_SE_ERR_DDEBUSY_PL_1257          ((MSG_TYPE)"") // "DDE transakcja nie może być zakończona, bo inne DDE transakcje są jeszcze wykonywane")
#define KP_MSG_SE_ERR_DDEFAIL_PL_1257          ((MSG_TYPE)"") // "DDE transakcja przerwana")
#define KP_MSG_SE_ERR_DDETIMEOUT_PL_1257       ((MSG_TYPE)"") // "DDE transakcja nie może być zakończona, bo zabrakło wskazanego czasu oczekiwania")
#define KP_MSG_SE_ERR_DLLNOTFOUND_PL_1257      ((MSG_TYPE)"") // "Nie znaleziono wskazanej biblioteki dynamicznej")
#define KP_MSG_SE_ERR_FNF_PL_1257              ((MSG_TYPE)"") // "Nie znaleziono wskazanego pliku")
#define KP_MSG_SE_ERR_NOASSOC_PL_1257          ((MSG_TYPE)"") // "Nie znaleziono programu do otwarcia plików danego typu")

#define KP_MSG_SE_ERR_OOM_PL_1257              ((MSG_TYPE)"") // "Brak pamięci do wykonania operacji")
#define KP_MSG_SE_ERR_PNF_PL_1257              ((MSG_TYPE)"") // "Nie znaleziono wskazanej ścieżki")
#define KP_MSG_SE_ERR_SHARE_PL_1257            ((MSG_TYPE)"") // "Błąd podziału")

#define KP_MSG_FIRST_TIME_ADMIN_PL_1257        ((MSG_TYPE)"") // "Zapuszczając program poraz pierwszy wymagane są uprawnienia administratora. Zapuść program ponownie z uprawnieniami administratora.")

#define KP_MSG_NOW_NOT_ADMIN_PL_1257           KP_MSG_NOT_ADMIN_PL_1257
#define KP_MSG_NOT_ADMIN_PL_1257               ((MSG_TYPE)"") // "Zapuść program ponownie z uprawnieniami zwykłego użytkownika")

#define KP_MSG_COPY_FILE_ACCESS_DENIED_PL_1257 ((MSG_TYPE)"") // "Nie udało się skopiować pliku. Zapuść program ponownie z uprawnieniami administratora.")


#define KP_PROGRESS_TITLE_PL_1257               ((MSG_TYPE)"") // "Zaczekaj...")
#define KP_MSG_DELETING_FILE_PL_1257            ((MSG_TYPE)"") // "Kasuje się plik %s.%s...")

#define KP_MSG_COPYING_PL_1257                  ((MSG_TYPE)"") // "Kopiuje się plik...")

#define KP_MSG_COPYING_DIR_PL_1257              ((MSG_TYPE)"") // "Kopiuje się katalog %s.%s...")
#define KP_MSG_COPYING_FILE_PL_1257             ((MSG_TYPE)"") // "Kopiuje się plik %s.%s...")

#define KP_MSG_NEG_ANSW_PL_1257                 ((MSG_TYPE)"") // "Neigiamas atsakymas")

#define KP_MSG_UNABLE_TO_EXECUTE_PL_1257        ((MSG_TYPE)"") // "Komandos %s įvykdyti negaliu – patikrinkite, ar teisingai įdiegėte visus sistemos komponentus"

#define KP_MSG_FLASH_PLAYER_INSTALL_PL_1257     ((MSG_TYPE)"") // "Dabar bus įdiegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus."

#define KP_MSG_FILE_CHANGED_PL_1257             ((MSG_TYPE)"") // "Failas pasikeitė"

#define KP_MSG_ALL_FILES_PL_1257                ((MSG_TYPE)"") // "Visi failai (*.*)"
#define KP_MSG_SAVE_AS_PL_1257                  ((MSG_TYPE)"") // "Įrašyti kaip"

#define KP_MSG_FILE_EXISTS_PL_1257              ((MSG_TYPE)"") // "Failas %s jau yra, perrašyti?"

#define KP_MSG_DIAG_MSG_PL_1257                 ((MSG_TYPE)"") // "Formuojamas diagnostinis pranešimas"
#define KP_MSG_DIAG_MSG_TITLE_PL_1257           ((MSG_TYPE)"") // "Diagnostinis pranešimas"
#define KP_MSG_DIAG_MSG_EXPL_PL_1257            ((MSG_TYPE)"") // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite pateiktus laukus. Pranešimas apie kompiuterio konfigūraciją, produktą bei klaidos pobūdį bus išsiųstas internetu į produkto gamintojo tarnybinę stotį. Jei po kurio laiko su Jumis nebus susisiekta Jūsų nurodytu pašto adresu, kreipkitės adresu %s")
#define KP_MSG_DIAG_MSG_EMAIL_PROMPT_PL_1257    ((MSG_TYPE)"") // "Jūsų e-pašto adresas:")
#define KP_MSG_DIAG_MSG_COMMENTS_PROMPT_PL_1257 ((MSG_TYPE)"") // "Komentarai apie klaidos atsiradimo aplinkybes:")
#define KP_MSG_DIAG_MSG_FILE_PROMPT_PL_1257     ((MSG_TYPE)"") // "Papildomas failas, kurį norėtumėte nusiųsti (pvz., ekrano kopijos paveikslėlis):")

#define KP_MSG_BAD_EMAIL_ADDRESS_PL_1257        ((MSG_TYPE)"") // "Neteisingas e-pašto adresas"

#define KP_MSG_DIAG_MSG_SEL_FILE_PL_1257        ((MSG_TYPE)"") // "Pasirinkite siunčiamą failą"

#define KP_MSG_DIAG_MSG_SUCCEEDED_PL_1257       ((MSG_TYPE)"") // "Diagnostinis pranešimas nusiųstas sėkmingai"

#define KP_MSG_DIAG_MSG_EXPL1_PL_1257           ((MSG_TYPE)"") // "Jei norite siųsti diagnostinį pranešimą, spragtelėkite „Siųsti“, jei ne – „Atšaukti“."
#define KP_MSG_SIUSTI_PL_1257                   ((MSG_TYPE)"") // "Siųsti"
#define KP_MSG_DIAG_MSG_EXPL2_PL_1257           ((MSG_TYPE)"") // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite Jūsų e-pašto adreso lauką ir spragtelėkite mygtuką „Siųsti“."

#define KP_MSG_DOWNLOADING_PL_1257              ((MSG_TYPE)"") // "Siunčiamas failas..."
#define KP_MSG_DOWNLOADING_FILE_PL_1257         ((MSG_TYPE)"") // "Siunčiamas failas %s.%s..."

#define KP_MSG_FIREWALL_PL_1257                 ((MSG_TYPE)"") // "Neleista prisijungti prie interneto. Patikrinkite Jūsų ugniasienės parinktis – pabandykite įtraukti %s į sąrašą programų, kurioms leidžiama kreiptis į internetą."

#define KP_MSG_POINTER_PL_1257                  ((MSG_TYPE)"") // "Bloga rodyklė"

#define KP_MSG_LOG_STARTED_PL_1257              ((MSG_TYPE)"") // "Žurnalas išvedamas ir į failą %s"
#define KP_MSG_CONS_TITLE_PL_1257               ((MSG_TYPE)"") // "%s: Pranešimų žurnalas"

#define KP_MSG_UNHANDLED_EXCEPTION_PL_1257      ((MSG_TYPE)"") // "Neapdorojamas trūkis"

#define KP_MSG_DATA_FORMAT_PL_1257              ((MSG_TYPE)"") // "Neteisingas duomenų formatas"
#define KP_MSG_DBERROR_PL_1257                  ((MSG_TYPE)"") // "Duomenų bazės klaida"

#endif // #if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1257_p))

// --------------------------------------------
#if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangRu_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p))

#define KP_MSG_TITLE_RU             ((MSG_TYPE)"") // "Message")
#define KP_INPUT_TITLE_RU           ((MSG_TYPE)"") // "Input"

#define KP_MSG_YES_RU               ((MSG_TYPE)"") // "Yes")
#define KP_MSG_TAIP_RU              KP_MSG_YES
#define KP_MSG_NO_RU                ((MSG_TYPE)"") // "No")
#define KP_MSG_NE_RU                KP_MSG_NO
#define KP_MSG_OK_RU                ((MSG_TYPE)"") // "OK")
#define KP_MSG_GERAI_RU             KP_MSG_OK
#define KP_MSG_CANCEL_RU            ((MSG_TYPE)"") // "Cancel")
#define KP_MSG_ATSAUKTI_RU          KP_MSG_CANCEL
#define KP_MSG_TESTI_RU             ((MSG_TYPE)"") // "Continue")
#define KP_MSG_BAIGTI_RU            ((MSG_TYPE)"") // "Finish")
#define KP_MSG_PAMIRSAU_SLAPTAZODI_RU ((MSG_TYPE)"") // "Forgot password")

#define KP_MSG_ERROR_RU             ((MSG_TYPE)"") // "Error")
#define KP_MSG_WARNING_RU           ((MSG_TYPE)"") // "Warning")
#define KP_MSG_FILE_LINE_RU         ((MSG_TYPE)"") // ", file:%s, line:%d")
#define KP_MSG_ENTRY_ID_RU          ((MSG_TYPE)"") // ", Entry Id:%ld")
#define KP_MSG_ENTRY_RU             ((MSG_TYPE)"") // ", Entry: %s")

#define KP_MSG_NO_STANDARD_PROG_RU  ((MSG_TYPE)"") // "Standard program not set to open given file type")
#define KP_MSG_WND_NOT_FOUND_RU     ((MSG_TYPE)"") // "Window not found")
#define KP_MSG_PID_NOT_FOUND_RU     ((MSG_TYPE)"") // "PID not found")
#define KP_MSG_NO_SOCKET_RU         ((MSG_TYPE)"") // "Socket not created yet")
#define KP_MSG_SOCK_UNRESOLVED_RU   ((MSG_TYPE)"") // "Server address not resolved yet")

#define KP_MSG_ERR_OK_RU            ((MSG_TYPE)"") // "Operation ended successfully")
#define KP_MSG_INVALIDARG_RU        ((MSG_TYPE)"") // "Invalid parameter")
#define KP_MSG_NOTIMPL_RU           ((MSG_TYPE)"") // "Feature not implemented yet")
#define KP_MSG_UNEXPECTED_RU        ((MSG_TYPE)"") // "Unexpected interface call") // Interface call result: Unexpected error
#define KP_MSG_FERROR_RU            ((MSG_TYPE)"") // "File I/O error")
#define KP_MSG_SYSTEM_ERROR_RU      ((MSG_TYPE)"") // "Internal error")
#define KP_MSG_EOF_RU               ((MSG_TYPE)"") // "Unexpected end of input file")
#define KP_MSG_FILE_FORMAT_RU       ((MSG_TYPE)"") // "Unexpected input file format")
#define KP_MSG_FILE_NOT_FOUND_RU    ((MSG_TYPE)"") // "File not found")
#define KP_MSG_DIR_ERROR_RU         ((MSG_TYPE)"") // "Unable to create file")
#define KP_MSG_OUTOFMEM_RU          ((MSG_TYPE)"") // "Out of memory")
#define KP_MSG_NO_FILE_RU           ((MSG_TYPE)"") // "No file open")
#define KP_MSG_DOUBLE_UNGET_RU      ((MSG_TYPE)"") // "Double unget")
#define KP_MSG_UNKN_CHR_RU          ((MSG_TYPE)"") // "Unknown character")
#define KP_MSG_COMMAND_ERROR_RU     ((MSG_TYPE)"") // "External error")
#define KP_MSG_BUFFER_OVERFLOW_RU   ((MSG_TYPE)"") // "Buffer overflow")
#define KP_MSG_FONT_UNDEF_RU        ((MSG_TYPE)"") // "Font undefined")
#define KP_MSG_KWD_NOT_FOUND_RU     ((MSG_TYPE)"") // "Keyword not found")
#define KP_MSG_UNKNOWN_SYSTEM_RU    ((MSG_TYPE)"") // "Unknown OS version")
#define KP_MSG_ILL_CODE_RU          ((MSG_TYPE)"") // "Illegal registration code")
#define KP_MSG_CANCELLED_RU         ((MSG_TYPE)"") // "Job cancelled")
#define KP_MSG_DOUBLE_CALL_RU       ((MSG_TYPE)"") // "Double call")
#define KP_MSG_TIMEOUT_RU           ((MSG_TYPE)"") // "Timeout")
#define KP_MSG_OBJ_NOT_FOUND_RU     ((MSG_TYPE)"") // "Object not found")
#define KP_MSG_NO_CONN_RU           ((MSG_TYPE)"") // "No connection")

#define KP_MSG_TRANS_ERR_RU         ((MSG_TYPE)"") // "Transfer error")
#define KP_MSG_TRANS_ERR_1_RU       ((MSG_TYPE)"") // "Transfer error, repeat the download procedure, please"

#define KP_MSG_REFUSED_RU           ((MSG_TYPE)"") // "Registration refused")
#define KP_MSG_ACCESS_DENIED_RU     ((MSG_TYPE)"") // "Access denied")
#define KP_MSG_ILLEGAL_CHARACTER_RU ((MSG_TYPE)"") // "Unexpected character")
#define KP_MSG_DIV_ZERO_RU          ((MSG_TYPE)"") // "Division by zero")
#define KP_MSG_ILLMATHARG_RU        ((MSG_TYPE)"") // "Illegal math argument")
#define KP_MSG_ILLFUNC_RU           ((MSG_TYPE)"") // "Illegal function call")

#define KP_MSG_NOTINST_RU           ((MSG_TYPE)"") // "Program not yet installed or installation is damaged, repeat the installation procedure again, please")
#define KP_MSG_NOTINST_S_RU         ((MSG_TYPE)"") // "Produktas „%s“ neįdiegtas arba jo diegimas sugedo, pakartokite diegimo procedūrą"
#define KP_MSG_NOTINST_DELETE_RU    ((MSG_TYPE)"") // "Produktas neįdiegtas arba jo diegimas sugedo, produktą panaikinkite ir pakartokite diegimo procedūrą"

#define KP_MSG_MSG_FORMAT_RU        ((MSG_TYPE)"") // "Illegal message format")
#define KP_MSG_OBSOLETE_RU          ((MSG_TYPE)"") // "Obsolete function call")

#define KP_MSG_ERROR_HELP_RU        ((MSG_TYPE)"") // ".  Technical support by e-mail %s")
#define KP_MSG_ERROR_HELP_REST_RU   ((MSG_TYPE)"") // "   For further information look file %s")

#define KP_MSG_WSAEACCES_RU               ((MSG_TYPE)"") // "Permission denied")
#define KP_MSG_WSAEADDRINUSE_RU           ((MSG_TYPE)"") // "Address already in use")
#define KP_MSG_WSAEADDRNOTAVAIL_RU        ((MSG_TYPE)"") // "Cannot assign requested address")
#define KP_MSG_WSAEAFNOSUPPORT_RU         ((MSG_TYPE)"") // "Address family not supported by protocol family")
#define KP_MSG_WSAEALREADY_RU             ((MSG_TYPE)"") // "Operation already in progress")
#define KP_MSG_WSAECONNABORTED_RU         ((MSG_TYPE)"") // "Software caused connection abort")
#define KP_MSG_WSAECONNREFUSED_RU         ((MSG_TYPE)"") // "Connection refused")
#define KP_MSG_WSAECONNRESET_RU           ((MSG_TYPE)"") // "Connection reset by peer")
#define KP_MSG_WSAEDESTADDRREQ_RU         ((MSG_TYPE)"") // "Destination address required")
#define KP_MSG_WSAEFAULT_RU               ((MSG_TYPE)"") // "Bad address")
#define KP_MSG_WSAEHOSTDOWN_RU            ((MSG_TYPE)"") // "Host is down")
#define KP_MSG_WSAEHOSTUNREACH_RU         ((MSG_TYPE)"") // "No route to host")
#define KP_MSG_WSAEINPROGRESS_RU          ((MSG_TYPE)"") // "Operation now in progress")
#define KP_MSG_WSAEINTR_RU                ((MSG_TYPE)"") // "Interrupted function call")
#define KP_MSG_WSAEINVAL_RU               ((MSG_TYPE)"") // "Invalid argument")
#define KP_MSG_WSAEISCONN_RU              ((MSG_TYPE)"") // "Socket is already connected")
#define KP_MSG_WSAEMFILE_RU               ((MSG_TYPE)"") // "Too many open files")
#define KP_MSG_WSAEMSGSIZE_RU             ((MSG_TYPE)"") // "Message too long")
#define KP_MSG_WSAENETDOWN_RU             ((MSG_TYPE)"") // "Network is down")
#define KP_MSG_WSAENETRESET_RU            ((MSG_TYPE)"") // "Network dropped connection on reset")
#define KP_MSG_WSAENETUNREACH_RU          ((MSG_TYPE)"") // "Network is unreachable")
#define KP_MSG_WSAENOBUFS_RU              ((MSG_TYPE)"") // "No buffer space available")
#define KP_MSG_WSAENOPROTOOPT_RU          ((MSG_TYPE)"") // "Bad protocol option")
#define KP_MSG_WSAENOTCONN_RU             ((MSG_TYPE)"") // "Socket is not connected")
#define KP_MSG_WSAENOTSOCK_RU             ((MSG_TYPE)"") // "Socket operation on non-socket")
#define KP_MSG_WSAEOPNOTSUPP_RU           ((MSG_TYPE)"") // "Operation not supported")
#define KP_MSG_WSAEPFNOSUPPORT_RU         ((MSG_TYPE)"") // "Protocol family not supported")
#define KP_MSG_WSAEPROCLIM_RU             ((MSG_TYPE)"") // "Too many processes")
#define KP_MSG_WSAEPROTONOSUPPORT_RU      ((MSG_TYPE)"") // "Protocol not supported")
#define KP_MSG_WSAEPROTOTYPE_RU           ((MSG_TYPE)"") // "Protocol wrong type for socket")
#define KP_MSG_WSAESHUTDOWN_RU            ((MSG_TYPE)"") // "Cannot send after socket shutdown")
#define KP_MSG_WSAESOCKTNOSUPPORT_RU      ((MSG_TYPE)"") // "Socket type not supported")
#define KP_MSG_WSAETIMEDOUT_RU            ((MSG_TYPE)"") // "Connection timed out")
#define KP_MSG_WSATYPE_NOT_FOUND_RU       ((MSG_TYPE)"") // "class type not found")
#define KP_MSG_WSAEWOULDBLOCK_RU          ((MSG_TYPE)"") // "Resource temporarily unavailable")
#define KP_MSG_WSAHOST_NOT_FOUND_RU       ((MSG_TYPE)"") // "Host not found")
#define KP_MSG_WSA_INVALID_HANDLE_RU      ((MSG_TYPE)"") // "Specified event object handle is invalid")
#define KP_MSG_WSA_INVALID_PARAMETER_RU   ((MSG_TYPE)"") // "One or more parameters are invalid")
#define KP_MSG_WSAINVALIDPROCTABLE_RU     ((MSG_TYPE)"") // "Invalid procedure table from service provider")
#define KP_MSG_WSAINVALIDPROVIDER_RU      ((MSG_TYPE)"") // "Invalid service provider version number")
#define KP_MSG_WSA_IO_INCOMPLETE_RU       ((MSG_TYPE)"") // "Overlapped I/O event object not in signaled state")
#define KP_MSG_WSA_IO_PENDING_RU          ((MSG_TYPE)"") // "Overlapped operations will complete later")

#define KP_MSG_WSA_NOT_ENOUGH_MEMORY_RU   ((MSG_TYPE)"") // "Insufficient memory available")
#define KP_MSG_WSANOTINITIALISED_RU       ((MSG_TYPE)"") // "Successful WSAStartup not yet performed")
#define KP_MSG_WSANO_DATA_RU              ((MSG_TYPE)"") // "Valid name, no data record of requested type")
#define KP_MSG_WSANO_RECOVERY_RU          ((MSG_TYPE)"") // "this is a non-recoverable error")
#define KP_MSG_WSAPROVIDERFAILEDINIT_RU   ((MSG_TYPE)"") // "Unable to initialize a service provider")
#define KP_MSG_WSASYSCALLFAILURE_RU       ((MSG_TYPE)"") // "System call failure")
#define KP_MSG_WSASYSNOTREADY_RU          ((MSG_TYPE)"") // "Network subsystem is unavailable")
#define KP_MSG_WSATRY_AGAIN_RU            ((MSG_TYPE)"") // "Non-authoritative host not found")
#define KP_MSG_WSAVERNOTSUPPORTED_RU      ((MSG_TYPE)"") // "WINSOCK.DLL version out of range")
#define KP_MSG_WSAEDISCON_RU              ((MSG_TYPE)"") // "Graceful shutdown in progress")
#define KP_MSG_WSA_OPERATION_ABORTED_RU   ((MSG_TYPE)"") // "Overlapped operation aborted")

#define KP_MSG_OUT_OF_MEM_RES_RU          ((MSG_TYPE)"") // "The operating system is out of memory or resources")
#define KP_MSG_ERROR_FILE_NOT_FOUND_RU    ((MSG_TYPE)"") // "The file specified was not found")
#define KP_MSG_ERROR_PATH_NOT_FOUND_RU    ((MSG_TYPE)"") // "The path specified was not found")
#define KP_MSG_ERROR_BAD_FORMAT_RU        ((MSG_TYPE)"") // "The .exe file is invalid (non-Win32(r) .exe or error in .exe image)")
#define KP_MSG_SE_ERR_ACCESSDENIED_RU     ((MSG_TYPE)"") // "The operating system denied access to the specified file")
#define KP_MSG_SE_ERR_ASSOCINCOMPLETE_RU  ((MSG_TYPE)"") // "The file name association is incomplete or invalid")
#define KP_MSG_SE_ERR_DDEBUSY_RU          ((MSG_TYPE)"") // "The DDE transaction could not be completed because other DDE transactions were being processed")
#define KP_MSG_SE_ERR_DDEFAIL_RU          ((MSG_TYPE)"") // "The DDE transaction failed")
#define KP_MSG_SE_ERR_DDETIMEOUT_RU       ((MSG_TYPE)"") // "The DDE transaction could not be completed because the request timed out")
#define KP_MSG_SE_ERR_DLLNOTFOUND_RU      ((MSG_TYPE)"") // "The specified dynamic-link library was not found")
#define KP_MSG_SE_ERR_FNF_RU              ((MSG_TYPE)"") // "The specified file was not found")
#define KP_MSG_SE_ERR_NOASSOC_RU          ((MSG_TYPE)"") // "There is no application associated with the given file name extension")
#define KP_MSG_SE_ERR_OOM_RU              ((MSG_TYPE)"") // "There was not enough memory to complete the operation")
#define KP_MSG_SE_ERR_PNF_RU              ((MSG_TYPE)"") // "The specified path was not found")
#define KP_MSG_SE_ERR_SHARE_RU            ((MSG_TYPE)"") // "A sharing violation occurred")

#define KP_MSG_FIRST_TIME_ADMIN_RU        ((MSG_TYPE)"") // "Starting the program first time administrator\n rights are necessary. Run the program again as privileged user.")
#define KP_MSG_NOW_NOT_ADMIN_RU           KP_MSG_NOT_ADMIN
#define KP_MSG_NOT_ADMIN_RU               ((MSG_TYPE)"") // "Run the program again as ordinary user")
#define KP_MSG_COPY_FILE_ACCESS_DENIED_RU ((MSG_TYPE)"") // "Unsuccessfull file copy operation, run the program again as privileged user")

#define KP_PROGRESS_TITLE_RU              ((MSG_TYPE)"") // "Wait...")
#define KP_MSG_DELETING_FILE_RU           ((MSG_TYPE)"") // "Deleting file %s.%s...")
#define KP_MSG_COPYING_RU                 ((MSG_TYPE)"") // "Copying file...")
#define KP_MSG_COPYING_FILE_RU            ((MSG_TYPE)"") // "Copying file %s.%s...")
#define KP_MSG_COPYING_DIR_RU             ((MSG_TYPE)"") // "Copying folder %s.%s...")

#define KP_MSG_NEG_ANSW_RU                ((MSG_TYPE)"") // "Neigiamas atsakymas")

#define KP_MSG_UNABLE_TO_EXECUTE_RU       ((MSG_TYPE)"") // "Komandos %s įvykdyti negaliu – patikrinkite, ar teisingai įdiegėte visus sistemos komponentus"

#define KP_MSG_FLASH_PLAYER_INSTALL_RU    ((MSG_TYPE)"") // "Dabar bus įdiegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus."

#define KP_MSG_FILE_CHANGED_RU            ((MSG_TYPE)"") // "Failas pasikeitė"

#define KP_MSG_ALL_FILES_RU               ((MSG_TYPE)"") // "Visi failai (*.*)"
#define KP_MSG_SAVE_AS_RU                 ((MSG_TYPE)"") // "Įrašyti kaip"

#define KP_MSG_FILE_EXISTS_RU             ((MSG_TYPE)"") // "Failas %s jau yra, perrašyti?"

#define KP_MSG_DIAG_MSG_RU                ((MSG_TYPE)"") // "Formuojamas diagnostinis pranešimas"
#define KP_MSG_DIAG_MSG_TITLE_RU          ((MSG_TYPE)"") // "Diagnostinis pranešimas"
#define KP_MSG_DIAG_MSG_EXPL_RU           ((MSG_TYPE)"") // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite pateiktus laukus. Pranešimas apie kompiuterio konfigūraciją, produktą bei klaidos pobūdį bus išsiųstas internetu į produkto gamintojo tarnybinę stotį. Jei po kurio laiko su Jumis nebus susisiekta Jūsų nurodytu pašto adresu, kreipkitės adresu %s")
#define KP_MSG_DIAG_MSG_EMAIL_PROMPT_RU   ((MSG_TYPE)"") // "Jūsų e-pašto adresas:")
#define KP_MSG_DIAG_MSG_COMMENTS_PROMPT_RU ((MSG_TYPE)"") // "Komentarai apie klaidos atsiradimo aplinkybes:")
#define KP_MSG_DIAG_MSG_FILE_PROMPT_RU    ((MSG_TYPE)"") // "Papildomas failas, kurį norėtumėte nusiųsti (pvz., ekrano kopijos paveikslėlis):")

#define KP_MSG_BAD_EMAIL_ADDRESS_RU       ((MSG_TYPE)"") // "Neteisingas e-pašto adresas"

#define KP_MSG_DIAG_MSG_SEL_FILE_RU       ((MSG_TYPE)"") // "Pasirinkite siunčiamą failą"

#define KP_MSG_DIAG_MSG_SUCCEEDED_RU      ((MSG_TYPE)"") // "Diagnostinis pranešimas nusiųstas sėkmingai"

#define KP_MSG_DIAG_MSG_EXPL1_RU          ((MSG_TYPE)"") // "Jei norite siųsti diagnostinį pranešimą, spragtelėkite „Siųsti“, jei ne – „Atšaukti“."
#define KP_MSG_SIUSTI_RU                  ((MSG_TYPE)"") // "Siųsti"
#define KP_MSG_DIAG_MSG_EXPL2_RU          ((MSG_TYPE)"") // "Jei norite nusiųsti diagnostinį pranešimą gamintojui, užpildykite Jūsų e-pašto adreso lauką ir spragtelėkite mygtuką „Siųsti“."

#define KP_MSG_DOWNLOADING_RU             ((MSG_TYPE)"") // "Siunčiamas failas..."
#define KP_MSG_DOWNLOADING_FILE_RU        ((MSG_TYPE)"") // "Siunčiamas failas %s.%s..."

#define KP_MSG_FIREWALL_RU                ((MSG_TYPE)"") // "Neleista prisijungti prie interneto. Patikrinkite Jūsų ugniasienės parinktis – pabandykite įtraukti %s į sąrašą programų, kurioms leidžiama kreiptis į internetą."

#define KP_MSG_POINTER_RU                 ((MSG_TYPE)"") // "Bloga rodyklė"

#define KP_MSG_LOG_STARTED_RU             ((MSG_TYPE)"") // "Žurnalas išvedamas ir į failą %s"
#define KP_MSG_CONS_TITLE_RU              ((MSG_TYPE)"") // "%s: Pranešimų žurnalas"

#define KP_MSG_UNHANDLED_EXCEPTION_RU     ((MSG_TYPE)"") // "Neapdorojamas trūkis"

#define KP_MSG_DATA_FORMAT_RU             ((MSG_TYPE)"") // "Neteisingas duomenų formatas"
#define KP_MSG_DBERROR_RU                 ((MSG_TYPE)"") // "Duomenų bazės klaida"

#endif // #if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangRu_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p))

#endif // #ifndef KPMSG_INCLUDED
