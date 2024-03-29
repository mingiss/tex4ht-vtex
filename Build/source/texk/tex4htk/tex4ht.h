/* -----------------------------
 * tex4ht common definitions
 */

#ifndef TEX4HT_H_INCLUDED
#define TEX4HT_H_INCLUDED

// ------------------------------
// definitions to manipulate tex4ht VTEX add-ons compilation
#define VTEX_SPACING_ADDONS     // add-ons for space generator
#define VTEX_OTF_ADDONS         // OpenType font processing
#define VTEX_SSCRIPT_ADDONS     // add-ons for baseless sub / superscripts
#define VTEX_MATH_CLASS_ADDONS  // add-ons for character math classes

// #include <assert.h>
#undef assert
#define assert(expr) { if (!(expr)) err_i(ERR_FATAL, __FILE__, __LINE__); }

#include <stdio.h>
#include "kpstdlib.h"
#include "kpstring.h"
#include "kpstdio.h"

// ------------------------------
// definitions moved from tex4ht-c.tex / tex4ht.c
#if INT_MAX < 2147483647L // `%2^31`%
#define LONG L
#endif

#ifdef LONG
#define INTEGER long
#else
#define INTEGER int
#endif

#define U_CHAR char

extern PLAIN_C struct font_entry* font_tbl;
extern PLAIN_C int font_tbl_size;

#define new_font font_tbl[font_tbl_size]

extern
#ifdef __cplusplus
    "C"
#endif
        FILE *log_file;

extern PLAIN_C void err_i(/* enum err_codes */ int nErrCode, ...);
extern PLAIN_C void err_i_str(/* enum err_codes */ int nErrCode, const char *pszErrMsg);
extern PLAIN_C void warn_i(/* enum err_codes */ int nErrCode);
extern PLAIN_C void warn_i_str(/* enum err_codes */ int nErrCode, const char *pszErrMsg);
extern PLAIN_C void warn_i_str2(/* enum err_codes */ int nErrCode, const char *pszErrMsg1, const char *pszErrMsg2);
extern PLAIN_C void warn_i_int(/* enum err_codes */ int nErrCode, int nSupplErrCode);

// new common definitions
#define DEF_FNT_SIZE_PT 10
#define DEF_GLYPH_WDT_PT (DEF_FNT_SIZE_PT * 3 / 4)

#define DEF_MAX_X_VAL -10000
#define DEF_WORD_SP 999999.0
#define WORD_SP_XDV 350000

#define DEF_CHAR_F 0
#define MAX_T1_CHAR_L 255
#define DEF_CHAR_L MAX_T1_CHAR_L
#define T1_NCHARS 256
#define MAXCHAR 127

#define NO_CHAR_F 2
#define NO_CHAR_L 1

#define CLASS_ON_SIZE 32

#define MAX_PUSH_DEPTH 256
#define MAX_SPEC_LEN 254 // max num of bytes in \special body to be parsed
#define FONT_NAME_BUF_LEN PATH_MAX // (256 - 1)
#define STR_BUF_LEN 2048 // (256 - 1)

enum err_codes
{
ERR_HELP,
ERR_IN_FILE,
ERR_OUT_FILE,
ERR_CLOSE_FILE,
ERR_MEM,
ERR_BAD_CHAR,
ERR_FONT_NUM,
ERR_DVI_FILE,
ERR_FONT_DEF,
ERR_CMD_LINE,
ERR_FONT_DEF_REP,
ERR_FONT_EMPTY_ENV,
ERR_DIR_ACC,
ERR_FONT_DIR_ENV,
ERR_NO_FONTS,
ERR_HEAD,
ERR_CHKSUM,
ERR_MAXFONTS,
ERR_EOF_SIG,
ERR_STA_SIG,
ERR_HTF_FILE_FMT,
ERR_HTF_FILE,
ERR_HTF_STA_EOF,
ERR_IMPL,
ERR_SPC_GRP,
ERR_MAP_LINE_OVFL,
ERR_SPC_OVFL,
ERR_PBR,
ERR_CHR_CODE_OVFL,
ERR_CHR_HTF,
ERR_STO_ADDR,
ERR_FLOAT,
ERR_CTRLC,
ERR_SCPT_OVFL,
ERR_MAP_ROWS_OVFL,
ERR_FNT_OVFL,
ERR_SPC_CHAR,
ERR_SPC_BAR_STR,
ERR_SPC_TILDE_STR,
ERR_SPC_BSL_STR,
ERR_SYS_40,
ERR_SPC_BAD_CHAR,
ERR_SPC_NO_TILDE,
ERR_SPC_IGNORE,
ERR_SPC_PUSH,
ERR_SPC_BAD_CHAR_CODE,
ERR_SPC_PBR,
ERR_FLS_NO_FILE,
ERR_ENTRY_LINE,
ERR_ENV_VAR,
ERR_MISSING,
ERR_BACK_FILE,
ERR_SPC_QUEST,
ERR_PAR_V,
ERR_PAR_R,
ERR_BUF_OVFL,
ERR_FILE_NFOUND,
ERR_FILE_READ,
ERR_FILE_FORMAT,
ERR_FATAL,
ERR_FILE_WRITE,
ERR_NOT_WELL
};

#ifdef VTEX_SSCRIPT_ADDONS
extern BOOL dump_parse_back_nodes_flag;
#endif

#endif // #ifndef TEX4HT_ADD_H_INCLUDED
