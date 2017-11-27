/* ------------------------------
 * tex4ht_add.cpp
 *
 *    vtex add-ons to tex4ht
 *
 * TODO:
 *      all local char* and char[] to std::string
 */

#include <string.h>
#include <stdbool.h>
#include <iostream>
#include "tex4ht_add.h"

using namespace std;

// ------------------------------
COtfAdds theOtfAdds;

COtfAdds::COtfAdds()
{
#include "tex4ht_mathvar_init.cpp"
}

// ------------------------------
HFontPars::HFontPars()
{
    m_ChFirst = INT_MAX;
    m_ChLast = 1;
}

// ------------------------------
void get_otf_fm(/* const */ char *fnt_name, /* const */ char *job_name, HANDLE *pfont_pars)
{
    char fmap_fname[PATH_MAX + 40];
    FILE *fmap_file = NULL;
    char tfm_name[PATH_MAX + 1];
    char str_buf[STR_BUF_LEN + 1];
    /* const */ char *ps_name = NULL;
    char enc_fname[PATH_MAX + 40];
    FILE *enc_file = NULL;
    char *pnts = NULL;


    HFontParMap::const_iterator it = theOtfAdds.m_mapHFontParMap.find(fnt_name);
    const HFontPars *ppars = NULL;
    if (it != theOtfAdds.m_mapHFontParMap.end())
        ppars = &it->second;
    else
    {
        cout << ":::: searching for .otf font " << fnt_name << endl;

        if (strlen(job_name) > PATH_MAX)
            err_i_str(ERR_BUF_OVFL, job_name);
        strcpy(fmap_fname, ".xdvipsk/");
        strcat(fmap_fname, job_name);
        pnts = strstr(fmap_fname, ".idv");
        if (pnts)
            *pnts = 0;
        pnts = strstr(fmap_fname, ".dvi");
        if (pnts)
            *pnts = 0;
        strcat(fmap_fname, ".opentype.map");

        cout << ":::: reading font list " << fmap_fname << endl;

        fmap_file = fopen(fmap_fname, "r");
        if (fmap_file)
        {
            if (strlen(fnt_name) > PATH_MAX)
                err_i_str(ERR_BUF_OVFL, fnt_name);
            strcpy(tfm_name, fnt_name);
            pnts = strstr(tfm_name, ".tfm");
            if (pnts) *pnts = 0;

            do
            {
                /* const */ char *psname = NULL;

                fgets(str_buf, STR_BUF_LEN, fmap_file);
                if (ferror(fmap_file))
                    err_i_str(ERR_FILE_READ, fmap_fname);
                if (feof(fmap_file))
                    break;

                string errstr(fmap_fname);
                errstr += ": ";
                errstr += str_buf;

                pnts = str_buf;
                for (int ii = 0; ii < 4; ii++)
                {
                    pnts = strchr(pnts, '\t');
                    if (pnts == NULL)
                    {
                        warn_i_str(ERR_FILE_FORMAT, errstr.c_str());
                        break;
                    }
                    *pnts++ = 0;

                    if (ii == 2)
                        psname = pnts;
                }

                if (psname == NULL)
                    warn_i_str(ERR_FILE_FORMAT, errstr.c_str());

                if (strcmp(tfm_name, str_buf) == 0)
                {
                    ps_name = psname;
                    break;
                }

            } while (TRUE);

            fclose(fmap_file);
        }
        else // if (fmap_file)
            warn_i_str(ERR_FILE_NFOUND, fmap_fname);

        HFontPars pars;

        if (ps_name)
        {
            if (strlen(ps_name) > PATH_MAX)
                err_i_str(ERR_BUF_OVFL, ps_name);
            strcpy(enc_fname, ".xdvipsk/");
            strcat(enc_fname, ps_name);
            strcat(enc_fname, ".encodings.map");

            cout << ":::: parsing char map " << enc_fname << endl;

            enc_file = fopen(enc_fname, "r");
            if (enc_file)
            {
                do
                {
                    fgets(str_buf, STR_BUF_LEN, enc_file);
                    if (ferror(enc_file))
                        err_i_str(ERR_FILE_READ, enc_fname);
                    if (feof(enc_file))
                        break;

                    string errstr(enc_fname);
                    errstr += ": ";
                    errstr += str_buf;

                    KpString instr(str_buf);
                    vector<KpString> codes;
                    instr.Split("\r", codes);
                    instr = codes[0];
                    instr.Split("\n", codes);
                    instr = codes[0];
                    instr.Split(",", codes);

                    if (codes.size() < 3)
                        warn_i_str(ERR_FILE_FORMAT, errstr.c_str());
                    else
                    {
                        int tex_code = 0;
                        if (sscanf(codes[0], "%d", &tex_code) == 1)
                        {
                            if (tex_code < pars.m_ChFirst)
                                pars.m_ChFirst = tex_code;
                            if (tex_code > pars.m_ChLast)
                                pars.m_ChLast = tex_code;

                            UniStr utf16_str;
                            for (int cpos = 0; cpos < codes[2].length(); cpos += 4)
                            {
                                string cstr = "0000";
                                cstr += codes[2].substr(cpos, 4);
                                int /* UniChar */ uni_code = 0;
                                if (sscanf(cstr.c_str(), "%x", &uni_code) == 1)
                                    utf16_str.push_back(uni_code);
                            }

                            UniStr uni_str;
                            Utf16ToUniStr(utf16_str, uni_str);

                            pars.m_mapTexUniTable[tex_code] = uni_str;
                        }
                    }

                } while (TRUE);

                fclose(enc_file);
            }
            else // if (enc_file)
                warn_i_str(ERR_FILE_NFOUND, enc_fname);
        }

        ppars = &(theOtfAdds.m_mapHFontParMap[fnt_name] = pars);
    }

    if (ppars == NULL)
        warn_i(ERR_STO_ADDR);

    if (pfont_pars)
        *pfont_pars = (HANDLE)ppars;

    new_font.char_f = DEF_CHAR_F;
    new_font.char_l = DEF_CHAR_L;
    if (ppars)
    {
        new_font.char_f = ppars->m_ChFirst;
        new_font.char_l = ppars->m_ChLast;
    }
    if (new_font.char_l < new_font.char_f - 1)
    {
        new_font.char_f = DEF_CHAR_F;
        new_font.char_l = DEF_CHAR_L;
    }

    new_font.word_sp = DEF_WORD_SP;
    new_font.scale = DEF_FONT_SCALE;
    new_font.design_sz = DEF_DESIGN_SZ;
    new_font.mag = DEF_MAG_VAL;

cout << ":::: " << fnt_name << " first: " << ppars->m_ChFirst << " last: " << ppars->m_ChLast << endl;
}

void get_uni_ch(int /* UniChar */ *wch_buf, unsigned int wch_buf_size, int tex_ch, HANDLE fnt_pars, BOOL cvt_to_math_var)
{
    if ((!wch_buf) || (wch_buf_size == 0))
        return;
    wch_buf[0] = 0;
    HFontPars *ppars = (HFontPars *)fnt_pars;
    if (!ppars)
        return;

    TexUniTable::const_iterator it = ppars->m_mapTexUniTable.find(tex_ch);
    if (it == ppars->m_mapTexUniTable.end())
        return;

    int ix = 0;
    for (UniStr::const_iterator is = it->second.begin(); is != it->second.end(); is++)
    {
        const char *ch_str = NULL;
        if (cvt_to_math_var)
        {
            MathVarMap::const_iterator itv = theOtfAdds.m_mapMathVars.find(*is);
            if (itv != theOtfAdds.m_mapMathVars.end())
                ch_str = itv->second.c_str();
        }

        if (ch_str)
        {
            for (; ix < wch_buf_size - 1; ix++)
            {
                if (ch_str[ix] == '\0')
                    break;
                wch_buf[ix] = ch_str[ix];
            }
        }
        else
            if (ix < wch_buf_size - 1)
                wch_buf[ix++] = *is;
    }
    wch_buf[ix++] = 0;
}
