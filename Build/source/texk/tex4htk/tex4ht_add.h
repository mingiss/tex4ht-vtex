/* ------------------------------
 * tex4ht_add.h
 *
 *    vtex add-ons to tex4ht
 *
 */

#ifndef TEX4HT_ADD_H_INCLUDED
#define TEX4HT_ADD_H_INCLUDED

#include <limits.h>
#include <stdio.h>

#ifdef __cplusplus
#include <map>
#include <string>

using namespace std;
#endif

#include "kpstdlib.h"
#include "kpstring.h"
#include "kpstdio.h"

#include "tex4ht.h"

// scale and design_sz values of /usr/local/texlive/2016/texmf-dist/fonts/tfm/public/cm/cmmi10.tfm
#define DEF_FONT_SCALE  655360
#define DEF_DESIGN_SZ   655360
#define DEF_MAG_VAL     100

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
    uint *accent_array, *accented_array, accent_N, accented_N;
    char *math, *math_closing;
    INTEGER layout_dir;
    unsigned long rgba_color;

#ifdef VTEX_OTF_ADDONS
    char *span_class; // font span class attribute and .css entry name, extracted from the third column of the mapping file .xdvipsk/%jobname%.opentype.map
    HANDLE pars; // pointer to OTF font HFontPars object actually
#endif

#ifdef VTEX_MATH_CLASS_ADDONS
    char *htf_family_name;
#endif
};

#ifdef VTEX_OTF_ADDONS
// ------------------------------
#ifdef __cplusplus
// conversion table from TeX character codes to unicode
// indexes -- TeX char codes as provided in .dvi file, values -- unicode equivalent arrays (multiple elements means encoding to string of unicode characters, "ffl", for example)
typedef map<int, UniStr> TexUniTable;

// structure of .otf font attributes
class HFontPars
{
public:
    int m_ChFirst;  // TeX char code of the first character in font
    int m_ChLast;   // last TeX char code
    TexUniTable m_mapTexUniTable; // TeX to unicode conversion table

    HFontPars();
};

// dictionary of all .otf fonts attribute structure objects
// index -- internal TeX decorated font name as provided in .dvi file
// ("[DGMetaSerifScience-Regular.otf]:mode=node;script=latn;language=DFLT;+tlig;" for example)
typedef map<string, HFontPars> HFontParMap;

typedef map<int /* WCHAR */, string> MathVarMap;

// main data object of the add-ons package
class COtfAdds
{
public:
    HFontParMap m_mapHFontParMap;
    MathVarMap m_mapMathVars;
    COtfAdds();
};
extern COtfAdds theOtfAdds;

#endif

// ------------------------------
// tries to obtain otf font parameters from font mappings in subdirectory .xdvips provided by luafonts.lua
// vfnt_name -- internal TeX decorated font name, probably, supplemented with an extension ".tfm"
// returns *pfnt_pars -- pointer to found or newly created font parameter structure HFontPars object
extern PLAIN_C void get_otf_fm(/* const */ char *vfnt_name, /* const */ char *job_name, HANDLE *pfnt_pars);

// ------------------------------
// converts TeX character code to unicode
// tex_ch -- TeX character code
// fnt_pars -- pointer to current font HFontPars object
extern PLAIN_C void get_uni_ch(int /* UniChar */ *wch_buf, uint wch_buf_size, int tex_ch, HANDLE fnt_pars, BOOL cvt_to_math_var);
#endif // #ifdef VTEX_OTF_ADDONS

#endif // #ifndef TEX4HT_H_ADD_INCLUDED
