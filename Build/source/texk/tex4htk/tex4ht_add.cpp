/* ------------------------------
 * tex4ht_add.cpp
 *
 *    add-ons to tex4ht
 *
 */

#include <string.h>
#include <stdbool.h>

#include "tex4ht_add.h"

// ------------------------------
FILE *get_otf_fm(/* const */ char *fnt_name, /* const */ char *job_name)
{
    char fmap_fname[PATH_MAX + 40];
    FILE *fmap_file = NULL;
    char tfm_name[PATH_MAX + 1];
    char str_buf[STR_BUF_LEN + 1];
    /* const */ char *ps_name = NULL;
    char enc_fname[PATH_MAX + 40];
    FILE *enc_file = NULL;
    char *pnts = NULL;
    int ch_f = INT_MAX;
    int ch_l = 1;

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

    fmap_file = fopen(fmap_fname, "r");
    if (fmap_file == NULL)
    {
        warn_i_str(ERR_FILE_NFOUND, fmap_fname);
        return NULL;
    }

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

        pnts = str_buf;
        for (int ii = 0; ii < 4; ii++)
        {
            pnts = strchr(pnts, '\t');
            if (pnts == NULL)
            {
                warn_i_str(ERR_FILE_FORMAT, fmap_fname);
                break;
            }
            *pnts++ = 0;
            if (ii == 2)
                psname = pnts;
        }

        if (strcmp(tfm_name, str_buf) == 0)
        {
            if (psname == NULL)
            {
                warn_i_str(ERR_FILE_FORMAT, fmap_fname);
                return NULL;
            }
            ps_name = psname;

            break;
        }

    } while (TRUE);

    if (ps_name == NULL)
        return NULL;

    if (strlen(ps_name) > PATH_MAX)
        err_i_str(ERR_BUF_OVFL, ps_name);
    strcpy(enc_fname, ".xdvipsk/");
    strcat(enc_fname, ps_name);
    strcat(enc_fname, ".encodings.map");

    enc_file = fopen(enc_fname, "r");
    if (enc_file == NULL)
    {
        warn_i_str(ERR_FILE_NFOUND, enc_fname);
        return NULL;
    }

    do
    {
        int ch_code = 0;

        fgets(str_buf, STR_BUF_LEN, enc_file);
        if (ferror(enc_file))
            err_i_str(ERR_FILE_READ, enc_fname);
        if (feof(enc_file))
            break;

        if (sscanf(str_buf, "%d", &ch_code) == 1)
        {
            if (ch_code < ch_f)
                ch_f = ch_code;
            if (ch_code > ch_l)
                ch_l = ch_code;
        }

    } while (TRUE);

    new_font.char_f = ch_f;
    new_font.char_l = ch_l;

    // return pointer to fake .tfm file just not to ruin tfm scanning algorithm
    return fopen("otf.tfm", "rb");
}
