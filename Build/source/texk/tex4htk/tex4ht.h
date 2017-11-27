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

extern PLAIN_C void err_i_str(/* enum err_codes */ int nErrCode, char *pszErrMsg);
extern PLAIN_C void warn_i(/* enum err_codes */ int nErrCode);
extern PLAIN_C void warn_i_str(/* enum err_codes */ int nErrCode, const char *pszErrMsg);
extern PLAIN_C void warn_i_int(/* enum err_codes */ int nErrCode, int nSupplErrCode);

// new common definitions
#define DEF_FNT_SIZE_PT 10
#define DEF_GLYPH_WDT_PT (DEF_FNT_SIZE_PT * 3 / 4)

#define DEF_MAX_X_VAL -10000
#define DEF_WORD_SP 999999.0
#define WORD_SP_XDV 350000

#define DEF_CHAR_F 2
#define DEF_CHAR_L 1

#define CLASS_ON_SIZE 32

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
ERR_SPC_BAD_CHR,
ERR_SPC_NO_TILDE,
ERR_SPC_IGNORE,
ERR_SPC_PUSH,
ERR_SPC_BAD_CHR_CODE,
ERR_SPC_PBR,
ERR_FLS_NO_FILE,
ERR_ENTRY_LINE,
ERR_ENV_VAR,
ERR_MISSING,
ERR_BACK_FILE,
ERR_SPC_QUEST,
ERR_PAR_V,
#ifdef VTEX_SPACING_ADDONS
ERR_PAR_R,
#endif
ERR_BUF_OVFL,
ERR_FILE_NFOUND,
ERR_FILE_READ,
ERR_FILE_FORMAT
};

#endif // #ifndef TEX4HT_ADD_H_INCLUDED
