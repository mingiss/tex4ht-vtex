/* -----------------------------
 * kpsort.h
 *      searching and sorting definitions
 *      
 *  Changelog:
 *      2013-06-11  mp  initial creation
 *       
 */  

#ifndef KPSORT_INCLUDED
#define KPSORT_INCLUDED


// ----------------------
#define TV_TG_NoKey  (-1)


// ================================================== static fields for sorting
extern int iCharWeigths[C_CharSize0];        // sort order definition
                                             // third digit will be ignored for for TvStrCmp()
                                             // use RoundChWgt(iCharWeigths[ii]) for it
#define KpCharWgtElem(chr, dig2, dig3, dig4) (chr * 10000 + dig2 * 1000 + dig3 * 100 + dig4) 
                                             // former ChWgt()
                                             // dig2 - skirtingu abeceles poziuriu diakritiniu raidziu eil. nr. (C, Č, S, Š, etc.) eil. nr.
                                             // dig3 - didziosios raides pozymis
                                             // dig4 (former dig3) - abeceliskai to paties svorio diakritiniu raidziu eil. nr.
#define ToLowWgt(ii)   (ii-ii%1000+ii%100)   // numeta didziosios raides pozymi dig3
#define RoundChWgt(ii) (ii-ii%100)           // numeta diakrito eiles nr dig4


// ----------------------
// Calculates keyword index in keyword table.
//    returns TV_TG_NoKey (-1) if not found
extern int GetKwrdIndex
(
const uchar *p_pszKeywrd,
const uchar *
#if (__GNUC__ != 5) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 0)
   const    // gcc 5.4.0 throws an error: duplicate ‘const’
#endif
      *p_ppszKeytable,
                        //      array of pointers to all
                        //      keywords -- null terminated strings,
                        //      not longer than KP_KWD_LEN bytes each;
const int p_iTabSize,   //  number of elements in p_ppszKeytable[]
                        //  if p_iTabSize < 0, then end of keyword table
                        //      is marked by NULL pointer,
                        //  if p_iTabSize >= 0, then all p_iTabSize records
                        //      will be tested, regardless if they are NULL
                        //      or not.
bool p_bCaseSens,       //  case sensitivity flag
bool p_bWholeWords      //  search for p_pszKeywrd as whole word,
);                      //      otherwise - only starting characters up to keyword length currently checked


extern int GetKwrdIndexArr
(
const uchar *p_pszKeywrd,
const uchar *p_ppszKeytable, // const uchar p_ppszKeytable[][p_iKeySize]
const int p_iTabSize,   //  number of elements in p_ppszKeytable[]
                        //  if p_iTabSize < 0, then end of keyword table
                        //      is marked by empty strint "" (p_ppszKeytable[ix][0] == Nul),
bool p_bCaseSens,
bool p_bWholeWords,
int p_iKeySize          //  size of one p_ppszKeytable[] element
);

#endif // #ifndef KPSORT_INCLUDED
