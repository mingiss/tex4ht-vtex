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
#include "tex4ht.h"
#include "tex4ht_add.h"

using namespace std;

#ifdef VTEX_OTF_ADDONS
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
void extract_css_token(char *font_style, const char *token, const char *css_kwd)
{
    char *pnts1 = NULL;
    char *pnts = strstr(font_style, token);
    if (pnts)
    {
        fprintf(log_file, css_kwd);
        pnts1 = pnts + strlen(token);
        while (*pnts1)
            *pnts++ = *pnts1++;
        *pnts = '\0';            
    }
}

void get_otf_fm(/* const */ char *vfnt_name, /* const */ char *job_name, HANDLE *pfont_pars)
{
    char fmap_fname[PATH_MAX + 40];
    FILE *fmap_file = NULL;
    char tfm_name[PATH_MAX + 1];
    char str_buf[STR_BUF_LEN + 1];
    /* const */ char *ps_name = NULL;
    const char *font_name = NULL;
    char *font_style = NULL;
    char enc_fname[PATH_MAX + 40];
    FILE *enc_file = NULL;
    char *pnts, *pnts1 = NULL;
    long ch_cnt = 0L;
    double ch_wdt = 0.;

    HFontParMap::const_iterator it = theOtfAdds.m_mapHFontParMap.find(vfnt_name);
    const HFontPars *ppars = NULL;
    if (it != theOtfAdds.m_mapHFontParMap.end())
        ppars = &it->second;
    else
    {
        cout << ":::: searching for .otf font " << vfnt_name << endl;

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
            if (strlen(vfnt_name) > PATH_MAX)
                err_i_str(ERR_BUF_OVFL, vfnt_name);
            strcpy(tfm_name, vfnt_name);
            pnts = strstr(tfm_name, ".tfm");
            if (pnts) *pnts = 0;

            do
            {
                /* const */ char *psname = NULL;

                font_name = NULL;
                font_style = NULL;
                fgets(str_buf, STR_BUF_LEN, fmap_file);
                if (ferror(fmap_file))
                    err_i_str(ERR_FILE_READ, fmap_fname);
                if (feof(fmap_file))
                    break;

                string errstr(fmap_fname);
                errstr += ": ";
                errstr += str_buf;

                pnts = str_buf;
                for (int ii = 0; ii < 6; ii++)
                {
                    pnts1 = strchr(pnts, '\t');
                    if (pnts1 == NULL) pnts1 = strchr(pnts, '\r');
                    if (pnts1 == NULL) pnts1 = strchr(pnts, '\n');
                    if (pnts1 == NULL)
                    {
                        if (ii < 4)
                            warn_i_str(ERR_FILE_FORMAT, errstr.c_str());
                        break;
                    }
                    pnts = pnts1;
                    *pnts++ = 0;

                    switch (ii)
                    {
                    case 1: font_name = pnts; break;
                    case 2: psname = pnts; break;
                    case 4: font_style = pnts; break;
                    }
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
            while (*ps_name == ' ')
                ps_name++;
            cout << ":::::::::::::::: [" << tfm_name << "] [" << new_font.name << "] [" << new_font.span_class << "] [" << ps_name << "] [" << (font_style?font_style:"") << "]" << endl;
            if (font_name)
            {
                while (*font_name == ' ')
                    font_name++;
                if (*font_name)
                {
                    if (new_font.span_class) free(new_font.span_class);
                    new_font.span_class = (char *)malloc(strlen(font_name) + 1);
                    if (new_font.span_class)
                        strcpy(new_font.span_class, font_name);
                    else
                        err_i(ERR_MEM);

                    if (font_style)
                    {
                        if (!log_file)
                            err_i_str(ERR_OUT_FILE, "*.lg");

                        fprintf(log_file, "htfcss: %s ", font_name);
                        extract_css_token(font_style, "Regular", " font-style:normal;");
                        extract_css_token(font_style, "Italic", " font-style:italic;");
                        extract_css_token(font_style, "Bold", " font-weight: bold;");
                        // extract_css_token(font_style, "???", " font-style:oblique;");
                        // extract_css_token(font_style, "???", " font-family:cursive;");
                        // extract_css_token(font_style, "???", " font-family:monospace;");
                        // extract_css_token(font_style, "???", " font-family:sans-serif;");
                        // extract_css_token(font_style, "???", " font-variant:small-caps;");
                        fprintf(log_file, "\n");
                        
                        while (*font_style == ' ')
                            font_style++;
                        if (*font_style)
                            warn_i_str(ERR_FILE_FORMAT, font_style);
                    }
                }
            }
            cout << ":::::::::::::::: [" << tfm_name << "] [" << new_font.name << "] [" << new_font.span_class << "] [" << ps_name << "] [" << (font_style?font_style:"") << "]" << endl;

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
                            for (uint cpos = 0; cpos < codes[2].length(); cpos += 4)
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

                            if (codes.size() < 4)
                                warn_i_str(ERR_FILE_FORMAT, errstr.c_str());
                            else
                            {
                                ch_wdt += atof(codes[3]);
                                ch_cnt++;
                            }
                        }

                    }

                } while (TRUE);

                fclose(enc_file);
            }
            else // if (enc_file)
                warn_i_str(ERR_FILE_NFOUND, enc_fname);
        }

        ppars = &(theOtfAdds.m_mapHFontParMap[vfnt_name] = pars);
    }

    if (ppars == NULL)
        warn_i(ERR_STO_ADDR);

    if (pfont_pars)
        *pfont_pars = (HANDLE)ppars;

    new_font.char_f = NO_CHAR_F;
    new_font.char_l = NO_CHAR_L;
    if (ppars)
    {
        new_font.char_f = ppars->m_ChFirst;
        new_font.char_l = ppars->m_ChLast;
    }
    if (new_font.char_l < new_font.char_f)
    {
        new_font.char_f = NO_CHAR_F;
        new_font.char_l = NO_CHAR_L;
    }

    if ((ch_cnt > 0L) && (ch_wdt > 0.001))
        new_font.word_sp = ch_wdt / ch_cnt;
    else
        new_font.word_sp = WORD_SP_XDV;

    new_font.scale = DEF_FONT_SCALE;
    new_font.design_sz = DEF_DESIGN_SZ;
    new_font.mag = DEF_MAG_VAL;

cout << ":::: " << vfnt_name << " first: " << ppars->m_ChFirst << " last: " << ppars->m_ChLast << endl;
}

void get_uni_ch(int /* UniChar */ *wch_buf, uint wch_buf_size, int tex_ch, HANDLE fnt_pars, BOOL cvt_to_math_var)
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

    uint ix = 0;
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
#endif // #ifdef VTEX_OTF_ADDONS

#ifdef VTEX_SSCRIPT_ADDONS
TiXmlDocument *xml_doc = NULL;
TiXmlNode *cur_node = NULL;

void init_xml_doc(const char *filename)
{
    KpString fname(filename);
    fname += ".trace.xml";
    cur_node = xml_doc = new TiXmlDocument((const char *)fname.c_str());
    assert(xml_doc);
}

void finit_xml_doc(void)
{
    if (xml_doc)
    {
        if (!xml_doc->SaveFile())
            err_i_str(ERR_FILE_WRITE, xml_doc->Value());
        delete xml_doc;
    }
    cur_node = xml_doc = NULL;
}

void add_new_child(const unsigned char *tag)
{
    assert(cur_node);
    if (dump_parse_back_nodes_flag)
        cout << "...... add_new_child(\"" << tag << "\")" << endl;
    TiXmlElement new_node((const char *)tag);
    cur_node = cur_node->InsertEndChild(new_node);
}

void close_cur_node(const unsigned char *tag)
{
    assert(cur_node);
    if (dump_parse_back_nodes_flag)
        cout << "...... close_cur_node(\"" << tag << "\") [" << cur_node->Value() << "]" << endl;
    if (strcmp(cur_node->Value(), tag))
        warn_i_str(ERR_NOT_WELL, (const char *)tag);
    else if (cur_node != xml_doc)
        cur_node = cur_node->Parent();
}

void parse_chunk(const unsigned char *chunk)
{
    KpString chunk_str(chunk);

    if (dump_parse_back_nodes_flag)
        cout << "...... parse_chunk(\"" << chunk_str << "\")" << endl;

    vector<KpString> st_tags;
    chunk_str.Split("<", st_tags);
    for (vector<KpString>::iterator st_it = st_tags.begin(); st_it < st_tags.end(); st_it++)
        if (st_it->c_str())
        {
            vector<KpString> end_tags;
            st_it->Split(">", end_tags);
            switch (end_tags[0][0])
            {
            case '!': // comment
                break;
            case '?': // instruction
                break;
            case '/': // end tag
                close_cur_node(end_tags[0].c_str() + 1);
                break;
            default:
                bool single_tag = False;
                uint tag_len = end_tags[0].length();
                if (tag_len > 0)
                {
                    if (end_tags[0][tag_len - 1] == '/')
                    {
                        single_tag = True;
                        end_tags[0][--tag_len] = '\0';
                    }
                    vector<KpString> pure_tags;
                    end_tags[0].Split(" ", pure_tags);
                    if (pure_tags[0][0])
                    {
                        add_new_child(pure_tags[0].c_str());
                        if (single_tag)
                            close_cur_node(pure_tags[0].c_str());
                    }
                }
                break;
            }
        }
    cout << endl;
}
#endif
