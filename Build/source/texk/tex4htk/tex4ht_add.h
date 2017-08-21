/* ------------------------------
 * tex4ht_add.h
 *
 *    add-ons to tex4ht
 *
 */

#include <limits.h>
#include <stdio.h>

#ifdef __cplusplus
#include <map>
#include <string>

using namespace std;
#endif

#include "kpstdlib.h"

#ifndef PATH_MAX
#define PATH_MAX 512
#endif

#define STR_BUF_LEN 1024

#if INT_MAX < 2147483647L
#define LONG L
#endif

#ifdef LONG
#define INTEGER long
#else
#define INTEGER int
#endif

#define U_CHAR char

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define DEF_FNT_SIZE_PT 10
#define DEF_GLYPH_WDT_PT (DEF_FNT_SIZE_PT * 3 / 4)

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
ERR_PAR_R,
ERR_BUF_OVFL,
ERR_FILE_NFOUND,
ERR_FILE_READ,
ERR_FILE_FORMAT
};

struct font_entry
{
    INTEGER num;
    INTEGER scale;
    INTEGER design_sz;
    INTEGER mag;
    char *family_name, *font_size;

    INTEGER design_pt;
    int char_f, char_l;
    U_CHAR *char_wi;
    U_CHAR *char_hidp;
    int  wtbl_n;
    int  htbl_n;
    int  dtbl_n;
    INTEGER  *wtbl;
    INTEGER  *htbl;
    INTEGER  *dtbl;
    INTEGER  word_sp;
    INTEGER  it;
    INTEGER  ex;
    char *name, *gif_on, *ch_str, ch255;
    unsigned U_CHAR **str, *ch, *gif1;
    unsigned U_CHAR *accent, *accented;
    unsigned int *accent_array, *accented_array, accent_N, accented_N;
    char *math, *math_closing;
    INTEGER layout_dir;
    unsigned long rgba_color;

    HANDLE pars; // pointer to OTF font HFontPars object actually
};

// TODO:

// tikrint kreipinius į:
// ch
// str
// accent_array
// accented_array

// tikrint, ar kreipimosi lentelė tab nenulinė ir ar simbolio kodas ch neviršija bitų skaičiaus n_gif_bytes = (n_gif + 7) / 8;
// add_bit(tab, ch, n)
// get_bit(tab, ch)
// store_bit_I(tab, ch)
// store_bit_Z(tab, ch)

// tikrint, ar simbolio kodas neviršija glifų skaičiaus n_gif

// inicijuot nereikia, sukurti ~255 elementų masyvai, tikrint, ar nesikreipia dideliais kodais
// char_wi
// char_hidp
// wtbl         // dydis: wtbl_n
// htbl         // dydis: htbl_n
// dtbl         // dydis: dtbl_n

// fiktyviai inicijuot kai nėra .tfm
// char_f = 0;
// char_l = 255;
// wtbl_n
// htbl_n
// dtbl_n
// accent_N = 0
// accented_N = 0


extern struct font_entry* font_tbl;
extern int font_tbl_size;

#define new_font font_tbl[font_tbl_size]

extern PLAIN_C void err_i_str(int, char *);
extern PLAIN_C void warn_i(int);
extern PLAIN_C void warn_i_str(int, const char *);

// ------------------------------
#ifdef __cplusplus
// conversion table from TeX character codes to unicode
// indexes -- TeX char codes as provided in .dvi file, values -- unicode equivalent
typedef map<long, long> HTable;

// structure of .otf font attributes
class HFontPars
{
public:
    int m_ChFirst;  // TeX char code of the first character in font
    int m_ChLast;   // last TeX char code
    HTable m_mHTable; // TeX to unicode conversion table

    HFontPars();
};

// dictionary of all .otf fonts attribute structure objects
// index -- internal TeX decorated font name as provided in .dvi file
// ("[DGMetaSerifScience-Regular.otf]:mode=node;script=latn;language=DFLT;+tlig;" for example)
typedef map<string, HFontPars> HFontParMap;
extern HFontParMap mapHFontParMap;
#endif

// ------------------------------
// tries to obtain otf font parameters from font mappings provided by luafonts.lua
// fnt_name -- internal TeX decorated font name
// return:
//      pointer to fake .tfm file just not to ruin tfm scanning algorithm of tex4ht
//      *ppars -- pointer to found or newly created font parameter structure object
extern PLAIN_C FILE *get_otf_fm(/* const */ char *fnt_name, /* const */ char *job_name, HANDLE *ppars);
