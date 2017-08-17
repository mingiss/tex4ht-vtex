/* ----------------------------------------------------
 *  kptt.h
 *      Kpt style character codes, code table definitions
 *
 * Changelog:
 *  2013-05-22  mp  shared kpadd.so
 *  2013-07-15  mp  dvi2ht: u_strToUTF8()
 *  2013-10-30  mp  luatex: kpadd: kp_get_cs_exp_str()
 *  2017-05-22  mp  build on Linux Mint 18.1 Serena 64
 *
 */


#ifndef KPTT_INCLUDED
#define KPTT_INCLUDED

/* =================================================== */
#define KPT_NoCodeTable   (-1)   /* No code table – value for undefined font table */
                                 /*    entry                                       */
#define KPT_UnknCodeTable (-2)   /* Unknown code table – value not used ??? */
#define KPT_UpCodeTable   (-3)   /* xml tags: codetable of the father tag should be inherited */

#define TV_NO_CTBL             0
#define TV_CTBL_ASCII          1
#define TV_CPP_SOURCE_CTBL    71 // ISO-8859-13 // Windows-1257
#define TV_MAIN_CTBL          71 // ISO-8859-13 // Windows-1257
#define TV_CTBL_TRANSPARENT   99

#define KPT_Ctnum       100      /* Number of code tables */
#define Ctnum           KPT_Ctnum

#define KPT_FirstKptChar 0x80 /* C_AE */

// start of private area – used for coding of unmapped Kpt characters
// code = KPT_UniPrivateStart + <Kpt code>
#ifdef NO_LTCOD
#define KPT_UniPrivateStart 0xE000 // Vyčio kodų nenaudojam – kaip seniau
#else
#define KPT_UniPrivateStart 0xE100 // pradžia jau užimta – Vytis accented lit. chars 0xE000..0xE01A
#endif
// #define KPT_UniPrivateEnd 0xF900  // MS Word uses codes >= 0xF000
#define KPT_UniPrivateEnd 0xEFFF

// pasirinkimas tarp naujų (Vytis) ir senų (KPT_UniPrivateStart + <Kpt code>) lietuviškų akcentuotų raidžių kodų
#ifdef NO_LTCOD
#define CH_LTCOD(new_code, old_code) (old_code)
#else
#define CH_LTCOD(new_code, old_code) (new_code)
#endif

#define KPT_UniUnknown 0xfffd

// -----------------------
// typedef unsigned short UniChar; // WCHAR
#ifndef WIN32
// typedef unsigned short WCHAR;
#endif
typedef WCHAR UniChar;

// -----------------------
extern int LangToCtbl[KpNumOfLangs]; // naudoti LangToCtbl[iMsgLangOff] 

// ---------------- coding modes of whole text file
typedef enum
{
        UC_No_Mode,

        UC_Binary,    // XML index binary file, former UC_UTF_Binary

        UC_PlainText, // 8-bit character plain text, XML index file text format, former UC_UTF_PlainText

// -----------
        UC_Unicode,  // for distinguishing between plain text and Unicode

// Unicode modes
        UC_UTF_7,
        UC_UTF_8,

        UC_Unicode16,  // for distinguishing between 8-bit and 16-bit Unicode modes

        UC_UTF_16,
        UC_UTF_16_Big_Endian,

        UC_Num_Of_Modes

} UC_Modes;


// ---------------- text coding types
#define EC_First_Type 1000

typedef enum
{
        EC_No_Type = EC_First_Type,

   EC_ASCII,      // plain ascii without diacrytics

        EC_8_BIT,      // 8-bit encoding – code table number should be specifyed instead
                       // by encoding of XML indexes:
                       //    if letter not found in target code table – accents schold be
                       //    skipped first (KptNoAccTbl[]), if still not found – converted to
                       //    plain ASCII (KptToLatTbl[])
                       // instead of EC_8_BIT simply code table number 0..KPT_Ctnum could be used as EC_Types value

        EC_KP_INT,     // 16-bit internal Kp encoding

// -----------
        EC_Unicode,  // for distinguishing between plain text and Unicode

// Unicode modes
        EC_UTF_7,
        EC_UTF_8,

        EC_Unicode16,  // for distinguishing between 8-bit and 16-bit Unicode modes

        EC_UTF_16,
        EC_UTF_16_Big_Endian,

        EC_Num_Of_Types_0

} EC_Types;


#define EC_Num_Of_Types (EC_Num_Of_Types_0-EC_First_Type)

/* =================================================== Kpt 16-bit characters */
#define C_Tab C_Ht

#define C_CharArrSize44  C_CharSize0

typedef enum
{
   C_Unkn =             (-2),
   C_Noch,           /*  -1 */

   C_Nul,            //   0 /* 0x00 */
   C_Soh,            //   1 /* 0x01 */
   C_Stx,            //   2 /* 0x02 */
   C_Etx,            //   3 /* 0x03 */
   C_Eot,            //   4 /* 0x04 */
   C_Enq,            //   5 /* 0x05 */
   C_Ack,            //   6 /* 0x06 */
   C_Bel,            //   7 /* 0x07 */
   C_Bs,             //   8 /* 0x08 */
   C_Ht,             //   9 /* '\t' 0x09 */
   C_Lf,             //  10 /* '\n' 0x0a */
   C_Vt,             //  11 /* 0x0b */
   C_Ff,             //  12 /* '\f' 0x0c */
   C_Cr,             //  13 /* '\r' 0x0d */
   C_So,             //  14 /* 0x0e */
   C_Si,             //  15 /* 0x0f */
   C_Dle,            //  16 /* 0x10 */
   C_Dc1,            //  17 /* 0x11 */
   C_Dc2,            //  18 /* 0x12 */
   C_Dc3,            //  19 /* 0x13 */
   C_Dc4,            //  20 /* 0x14 */
   C_Nak,            //  21 /* 0x15 */
   C_Syn,            //  22 /* 0x16 */
   C_Etb,            //  23 /* 0x17 */
   C_Can,            //  24 /* 0x18 */
   C_Em,             //  25 /* 0x19 */
   C_Sub,            //  26 /* 0x1a */
   C_Esc,            //  27 /* 0x1b */
   C_Fs,             //  28 /* 0x1c */
   C_Gs,             //  29 /* 0x1d */
   C_Rs,             //  30 /* 0x1e */
   C_Us,             //  31 /* 0x1f */

   C_Spc,            //  32 /* Space */
   C_Excl,           //  33 /* !  Exclamation Mark (šauktukas) */
   C_Quote,          //  34 /* "  Quotation Mark (kabutės) */
   C_Numb,           //  35 /* #  Number Sign (numerio ženklas) */
   C_Doll,           //  36 /* $  Currency Sign (pinigu ženklas) */
   C_Perc,           //  37 /* %  Per Cent Sign (procento ženklas) */
   C_Amp,            //  38 /* &  Ampersand (ampersandas) */
   C_Apost,          //  39 /* '  Apostrophe (apostrofa, apostrofas, kablelio formos) C_Acute; C_AcuteNcomb */
   C_Lpar,           //  40 /* (  Left Parenthesis (kairysis skliaustas) */
   C_Rpar,           //  41 /* )  Right Parenthesis (dešinysis skliaustas) */
   C_Ast,            //  42 /* *  Asterisk (žvaigždutė) */
   C_Plus,           //  43 /* +  Plus Sign (pliusas) */
   C_Comma,          //  44 /* ,  Comma (kablelis) */
   C_Dash,           //  45 /* -  Dash, Hyphen, Minus Sign (minusas) */ // former C_Minus
   C_Point,          //  46 /* .  Full Stop, Period, Point (taškas) */
   C_Slash,          //  47 /* /  Slash, Solidus (įstrižas brūkšnys) */
   C_0,              //  48 /* 0 */
   C_1,              //  49 /* 1 */
   C_2,              //  50 /* 2 */
   C_3,              //  51 /* 3 */
   C_4,              //  52 /* 4 */
   C_5,              //  53 /* 5 */
   C_6,              //  54 /* 6 */
   C_7,              //  55 /* 7 */
   C_8,              //  56 /* 8 */
   C_9,              //  57 /* 9 */
   C_Colon,          //  58 /* :  Colon (dvitaškis) */
   C_Semic,          //  59 /* ;  Semi-colon (kabliataškis) */
   C_Less,           //  60 /* <  Less than Sign (mažiau) */
   C_Eq,             //  61 /* =  Equals Sign (lygybės ženklas) */
   C_Great,          //  62 /* >  Greater than Sign (daugiau) */
   C_Quest,          //  63 /* ?  Question Mark (klaustukas) */

   C_At,             //  64 /* @  Commercial At (Prekybinis ženklas "Pas") */
   C_A,              //  65 /* A */
   C_B,              //  66 /* B */
   C_C,              //  67 /* C */
   C_D,              //  68 /* D */
   C_E,              //  69 /* E */
   C_F,              //  70 /* F */
   C_G,              //  71 /* G */
   C_H,              //  72 /* H */
   C_I,              //  73 /* I */
   C_J,              //  74 /* J */
   C_K,              //  75 /* K */
   C_L,              //  76 /* L */
   C_M,              //  77 /* M */
   C_N,              //  78 /* N */
   C_O,              //  79 /* O */
   C_P,              //  80 /* P */
   C_Q,              //  81 /* Q */
   C_R,              //  82 /* R */
   C_S,              //  83 /* S */
   C_T,              //  84 /* T */
   C_U,              //  85 /* U */
   C_V,              //  86 /* V */
   C_W,              //  87 /* W */
   C_X,              //  88 /* X */
   C_Y,              //  89 /* Y */
   C_Z,              //  90 /* Z */
   C_Lbrack,         //  91 /* [  Left Square Bracket (Kairysis laužtinis skliaustas) */
   C_Lslash,         //  92 /* \  Reverse Solidus, Reverse Slash (Atvirkščias įstrižas brūkšnys) */
   C_Rbrack,         //  93 /* ]  Right Square Bracket (Dešinysis laužtinis skliaustas) */
   C_Circ,           //  94 /* ^  Circumflex Accent (Cirkumfleksas), standalone, nekombinacinis (diakritas) */
   C_Underl,         //  95 /* _  Underline (Pabraukimas) */

   C_Grave,          //  96 /* `  Grave Accent (gravis), standalone, nekombinacinis (diakritas) */
   C_a,              //  97 /* a */
   C_b,              //  98 /* b */
   C_c,              //  99 /* c */
   C_d,              // 100 /* d */
   C_e,              // 101 /* e */
   C_f,              // 102 /* f */
   C_g,              // 103 /* g */
   C_h,              // 104 /* h */
   C_i,              // 105 /* i */
   C_j,              // 106 /* j */
   C_k,              // 107 /* k */
   C_l,              // 108 /* l */
   C_m,              // 109 /* m */
   C_n,              // 110 /* n */
   C_o,              // 111 /* o */
   C_p,              // 112 /* p */
   C_q,              // 113 /* q */
   C_r,              // 114 /* r */
   C_s,              // 115 /* s */
   C_t,              // 116 /* t */
   C_u,              // 117 /* u */
   C_v,              // 118 /* v */
   C_w,              // 119 /* w */
   C_x,              // 120 /* x */
   C_y,              // 121 /* y */
   C_z,              // 122 /* z */
   C_Lcurl,          // 123 /* {  Left Curly Bracket (Kairysis riestinis skliaustas) */
   C_Vertl,          // 124 /* |  Vertical Line (Vertikali linija), C_v_b */
   C_Rcurl,          // 125 /* }  Right Curly Bracket (Dešinysis riestinis skliaustas) */
   C_Tilde,          // 126 /* ~  Tilde (Overline) (Tildė, Brukšnys viršuje), standalone, net ne diakritas – TEX-e stambesnis ir per vidurį; C_TildeNcomb; C_TildeAcc */

   C_Del,            // 127

   C_AE,             // 128
   C_ae,             // 129
   C_OE,             // 130
   C_oe,             // 131
   C_IJ,             // 132
   C_ij,             // 133
   C_ss,             // 134 /* sharp s (german, C_beta) */

   C_A_Cyr,          // 135
   C_B_Cyr,          // 136
   C_V_Cyr,          // 137
   C_G_Cyr,          // 138
   C_D_Cyr,          // 139
   C_E_Cyr,          // 140
   C_Zh_Cyr,         // 141
   C_Z_Cyr,          // 142
   C_I_Cyr,          // 143
   C_J_Cyr,          // 144
   C_K_Cyr,          // 145
   C_L_Cyr,          // 146
   C_M_Cyr,          // 147
   C_N_Cyr,          // 148
   C_O_Cyr,          // 149
   C_P_Cyr,          // 150
   C_R_Cyr,          // 151
   C_S_Cyr,          // 152
   C_T_Cyr,          // 153
   C_U_Cyr,          // 154
   C_F_Cyr,          // 155
   C_H_Cyr,          // 156
   C_C_Cyr,          // 157
   C_Ch_Cyr,         // 158
   C_Sh_Cyr,         // 159
   C_Shch_Cyr,       // 160
   C_Hard_Cyr,       // 161
   C_Y_Cyr,          // 162
   C_Soft_Cyr,       // 163
   C_Ee_Cyr,         // 164
   C_Yu_Cyr,         // 165 // former C_Ju_Cyr
   C_Ya_Cyr,         // 166 // former C_Ja_Cyr

   C_a_Cyr,          // 167
   C_b_Cyr,          // 168
   C_v_Cyr,          // 169
   C_g_Cyr,          // 170
   C_d_Cyr,          // 171
   C_e_Cyr,          // 172
   C_zh_Cyr,         // 173
   C_z_Cyr,          // 174
   C_i_Cyr,          // 175
   C_j_Cyr,          // 176
   C_k_Cyr,          // 177
   C_l_Cyr,          // 178
   C_m_Cyr,          // 179
   C_n_Cyr,          // 180
   C_o_Cyr,          // 181
   C_p_Cyr,          // 182
   C_r_Cyr,          // 183
   C_s_Cyr,          // 184
   C_t_Cyr,          // 185
   C_u_Cyr,          // 186
   C_f_Cyr,          // 187
   C_h_Cyr,          // 188
   C_c_Cyr,          // 189
   C_ch_Cyr,         // 190
   C_sh_Cyr,         // 191
   C_shch_Cyr,       // 192
   C_hard_Cyr,       // 193
   C_y_Cyr,          // 194
   C_soft_Cyr,       // 195
   C_ee_Cyr,         // 196
   C_yu_Cyr,         // 197 // former C_ju_Cyr
   C_ya_Cyr,         // 198 // former C_ja_Cyr

                     // ----------------------------
                     /* Additional greek chars variations follow later */

   C_Alpha,          // 199
   C_Beta,           // 200
   C_Gamma,          // 201
   C_Delta,          // 202
   C_Epsilon,        // 203
   C_Zeta,           // 204
   C_Eta,            // 205
   C_Theta,          // 206
   C_Jota,           // 207
   C_Kappa,          // 208
   C_Lambda,         // 209
   C_My,             // 210
   C_Ny,             // 211
   C_Xi,             // 212
   C_Omicron,        // 213 // buv. C_Omikron
   C_Pi,             // 214
   C_Rho,            // 215
   C_Sigma,          // 216
   C_Tau,            // 217
   C_Ypsilon,        // 218
   C_Phi,            // 219
   C_Chi,            // 220
   C_Psi,            // 221
   C_Omega,          // 222

   C_alpha,          // 223
   C_beta,           // 224
   C_gamma,          // 225
   C_delta,          // 226
   C_epsilon,        // 227 // curly epsilon
   C_zeta,           // 228
   C_eta,            // 229
   C_theta,          // 230 // straight theta
   C_jota,           // 231
   C_kappa,          // 232 // straight kappa
   C_lambda,         // 233
   C_my,             // 234
   C_ny,             // 235
   C_xi,             // 236
   C_omicron,        // 237 // buv. C_omikron
   C_pi,             // 238 // straight pi
   C_rho,            // 239 // straight rho
   C_sigma,          // 240 // inner sigma
   C_tau,            // 241
   C_ypsilon,        // 242
   C_phi,            // 243 // straight phi
   C_chi,            // 244
   C_psi,            // 245
   C_omega,          // 246

   C_delta_Dash,     // 247 /* skardi th */ // former C_delt_Mn

                     // ----------------------------
                     /* All accents have no width (over the next letter) */
                     /* more accents later – C_...Acc */
                     // kombinaciniai diakritai

   C_Acute,          // 248 /* '  Acute (aku/tas, C_Apost, dešinysis kirtis) (zr. dar C_AcuteNcomb) */
   C_Dacut,          // 249 /* '' Double Acute */
   C_Ogon,           // 250 /* ,  Ogonek (nosine) */
   C_Adot,           // 251 /* .  Dot Above (. virsuje) */
   C_Car,            // 252 /* v  Caron (Pauksciukas) */
   C_Macr,           // 253 /* _  Macron, Overline (bruksnys virsuje), C_Oline */
   C_Diaer,          // 254 /* .. Diaeresis (Umlaut) */
   C_Ring,           // 255 /* o  Ring (Circle) Above (o virsuje, degree) */
   C_Tacom,          // 256 /* '  Turned Comma Above */
   C_Bcomma,         // 257 /* ,  Comma Bellow */
   C_Cedil,          // 258 /* ,  Cedilla (atbula nosine) */

                     // ----------------------------

   C_A_Ogon,         // 259 /* A, */
   C_a_Ogon,         // 260 /* a, */
   C_E_Ogon,         // 261 /* E, */
   C_e_Ogon,         // 262 /* e, */
   C_I_Ogon,         // 263 /* I, */
   C_i_Ogon,         // 264 /* i, */
   C_U_Ogon,         // 265 /* U, */
   C_u_Ogon,         // 266 /* u, */

   C_E_Adot,         // 267 /* E. */
   C_e_Adot,         // 268 /* e. */
   C_Z_Adot,         // 269 /* Z. */
   C_z_Adot,         // 270 /* z. */

   C_G_Cyr_Adot,     // 271 /* G Cyr . */
   C_g_Cyr_Adot,     // 272 /* g Cyr . */

   C_C_Car,          // 273 /* Cv */
   C_c_Car,          // 274 /* cv */
   C_D_Car,          // 275 /* Dv */
   C_d_Car,          // 276 /* dv */
   C_E_Car,          // 277 /* Ev */
   C_e_Car,          // 278 /* ev */
   C_L_Car,          // 279 /* Lv */
   C_l_Car,          // 280 /* lv */
   C_N_Car,          // 281 /* Nv */
   C_n_Car,          // 282 /* nv */
   C_R_Car,          // 283 /* Rv */
   C_r_Car,          // 284 /* rv */
   C_S_Car,          // 285 /* Sv */
   C_s_Car,          // 286 /* sv */
   C_T_Car,          // 287 /* Tv */
   C_t_Car,          // 288 /* tv */
   C_Z_Car,          // 289 /* Zv */
   C_z_Car,          // 290 /* zv */

   C_A_Macr,         // 291 /* A_ */
   C_a_Macr,         // 292 /* a_ */
   C_E_Macr,         // 293 /* E_ */
   C_e_Macr,         // 294 /* e_ */
   C_I_Macr,         // 295 /* I_ */
   C_i_Macr,         // 296 /* i_ */
   C_O_Macr,         // 297 /* O_ */
   C_o_Macr,         // 298 /* o_ */
   C_U_Macr,         // 299 /* U_ */
   C_u_Macr,         // 300 /* u_ */

   C_A_Diaer,        // 301 /* A.. */
   C_a_Diaer,        // 302 /* a.. */
   C_E_Diaer,        // 303 /* E.. */
   C_e_Diaer,        // 304 /* e.. */
   C_I_Diaer,        // 305 /* I.. */
   C_i_Diaer,        // 306 /* i.. */
   C_O_Diaer,        // 307 /* O.. */
   C_o_Diaer,        // 308 /* o.. */
   C_U_Diaer,        // 309 /* U.. */
   C_u_Diaer,        // 310 /* u.. */
   C_Y_Diaer,        // 311 /* Y.. */
   C_y_Diaer,        // 312 /* y.. */

   C_E_Cyr_Diaer,    // 313 /* E.. */
   C_e_Cyr_Diaer,    // 314 /* e.. */

   C_A_Ring,         // 315 /* Ao */
   C_a_Ring,         // 316 /* ao */
   C_U_Ring,         // 317 /* Uo */
   C_u_Ring,         // 318 /* uo */

   C_G_Tacom,        // 319 /* G' */
   C_g_Tacom,        // 320 /* g' */

   C_G_Bcomma,       // 321 /* G, */
   C_g_Bcomma,       // 322 /* g, */
   C_K_Bcomma,       // 323 /* K, */
   C_k_Bcomma,       // 324 /* k, */
   C_L_Bcomma,       // 325 /* L, */
   C_l_Bcomma,       // 326 /* l, */
   C_N_Bcomma,       // 327 /* N, */
   C_n_Bcomma,       // 328 /* n, */
   C_R_Bcomma,       // 329 /* R, */
   C_r_Bcomma,       // 330 /* r, */

   C_C_Cedil,        // 331 /* C, */
   C_c_Cedil,        // 332 /* c, */
   C_S_Cedil,        // 333 /* S, */
   C_s_Cedil,        // 334 /* s, */
   C_T_Cedil,        // 335 /* T, */
   C_t_Cedil,        // 336 /* t, */

   C_A_Grave,        // 337 /* A` */
   C_a_Grave,        // 338 /* a` */
   C_E_Grave,        // 339 /* E` */
   C_e_Grave,        // 340 /* e` */
   C_I_Grave,        // 341 /* I` */
   C_i_Grave,        // 342 /* i` */
   C_O_Grave,        // 343 /* O` */
   C_o_Grave,        // 344 /* o` */
   C_U_Grave,        // 345 /* U` */
   C_u_Grave,        // 346 /* u` */

   C_A_Acute,        // 347 /* A' */
   C_a_Acute,        // 348 /* a' */
   C_C_Acute,        // 349 /* C' */
   C_c_Acute,        // 350 /* c' */
   C_E_Acute,        // 351 /* E' */
   C_e_Acute,        // 352 /* e' */
   C_I_Acute,        // 353 /* I' */
   C_i_Acute,        // 354 /* i' */
   C_L_Acute,        // 355 /* L' */
   C_l_Acute,        // 356 /* l' */
   C_N_Acute,        // 357 /* N' */
   C_n_Acute,        // 358 /* n' */
   C_O_Acute,        // 359 /* O' */
   C_o_Acute,        // 360 /* o' */
   C_R_Acute,        // 361 /* R' */
   C_r_Acute,        // 362 /* r' */
   C_S_Acute,        // 363 /* S' */
   C_s_Acute,        // 364 /* s' */
   C_U_Acute,        // 365 /* U' */
   C_u_Acute,        // 366 /* u' */
   C_Y_Acute,        // 367 /* Y' */
   C_y_Acute,        // 368 /* y' */
   C_Z_Acute,        // 369 /* Z' */
   C_z_Acute,        // 370 /* z' */

   C_K_Cyr_Acute,    // 371 /* K Cyr ' */
   C_k_Cyr_Acute,    // 372 /* k Cyr ' */

   C_O_Dacut,        // 373 /* O'' */
   C_o_Dacut,        // 374 /* o'' */
   C_U_Dacut,        // 375 /* U'' */
   C_u_Dacut,        // 376 /* u'' */

   C_A_Tilde,        // 377 /* A~ */
   C_a_Tilde,        // 378 /* a~ */
   C_N_Tilde,        // 379 /* N~ */
   C_n_Tilde,        // 380 /* n~ */
   C_O_Tilde,        // 381 /* O~ */
   C_o_Tilde,        // 382 /* o~ */

   C_L_Slash,        // 383 /* L/ */
   C_l_Slash,        // 384 /* l/ */
   C_O_Slash,        // 385 /* O/ */
   C_o_Slash,        // 386 /* o/ */

   C_A_Circ,         // 387 /* A^ */
   C_a_Circ,         // 388 /* a^ */
   C_E_Circ,         // 389 /* E^ */
   C_e_Circ,         // 390 /* e^ */
   C_I_Circ,         // 391 /* I^ */
   C_i_Circ,         // 392 /* i^ */
   C_O_Circ,         // 393 /* O^ */
   C_o_Circ,         // 394 /* o^ */
   C_U_Circ,         // 395 /* U^ */
   C_u_Circ,         // 396 /* u^ */

   C_D_Dash,         // 397 /* D- Island. */   // former C_D_Minus
   C_d_Dash,         // 398 /* d- */           // former C_d_Minus
   C_H_Dash,         // 399 /* H- */           // former C_H_Minus
   C_h_Dash,         // 400 /* h- */           // former C_h_Minus
   C_P_Dash,         // 401 /* P- */           // former C_P_Minus
   C_p_Dash,         // 402 /* p- */           // former C_p_Minus

   C_NBSP,           // 403 /* No break space */

   C_Rouble,         // 404 /* rublis, $ Cyr */
   C_Pound,          // 405 /* svaras, L/ */
   C_Yenna,          // 406 /* jena, Y- */
   C_cent,           // 407 /* c/ */

   C_Para,           // 408 /* paragrafas, # engl. */
   C_Pren,           // 409 /* paragraph end sign (pastraipos pabaiga, C_pi – pi) */
   C_Multipl,        // 410 /* x */
   C_Divide,         // 411 /* -:- */
   C_PlMin,          // 412 /* -+- */
   C_1up,            // 413 /* 1 virsuj */
   C_2up,            // 414 /* 2 virsuj, kvadratu */
   C_3up,            // 415 /* 3 virsuj, kubu */
   C_a_up,           // 416 /* a virsuj */
   C_o_up,           // 417 /* o virsuj */
   C_Half,           // 418 /* 1/2 */
   C_Quart,          // 419 /* 1/4 */
   C_34,             // 420 /* 3/4 */
   C_Ldopang,        // 421 /* << – rusiška kabutė */
   C_Rdopang,        // 422 /* >> – rusiška kabutė */
   C_Lang,           // 423 /* < */
   C_Rang,           // 424 /* > */
   C_Dvertl,         // 425 /* | Koi-7-0 */
   C_Rminbr,         // 426 /* ^ Koi-7-0 ( not, neiginys, -| ) */
   C_Lminbr,         // 427 /* |- */
   C_Lpoint,         // 428 /* mažas taškas vidury, daugybos ženklas */
   C_Bpoint,         // 429 /* bullet, didelis taškas vidury */ // naudojamas homonimų identifikavimui (DOUBLE_ENTRIES_KPCHAR), tikram bullet'ui naudoti C_hBpoint
   C_LBquote,        // 430 /* ,, (" left bellow, double comma, liet. kairė, 99 apacioje) */
   C_LAquote,        // 431 /* `` (" left above, reversed double comma above, angl. kairė, liet. dešinė, 66 viršuj) */
   C_Rquote,         // 432 /* '' (" right, double comma above, angl. dešinė, 99 viršuj) */
   C_LBapost,        // 433 /* , (' left bellow, comma, liet. kairė, 9 apačioj) */
   C_LAapost,        // 434 /* ` (' left above, C_Grave, reversed comma above, angl. kairė, liet. dešinė, 6 viršuj) */
   C_Rapost,         // 435 /* ' (' right, C_Apost, comma above, angl. dešinė, 9 viršuj) */

   C_Qst_Ov,         // 436 /* apverstas ? */
   C_Ex_Ov,          // 437 /* apverstas ! */
   C_Dots,           // 438 /* ... daugtaškis, ellipsis */
   C_Prom,           // 439 /* %o promilės */
   C_TM,             // 440 /* TM, Trade Mark */
   C_CO,             // 441 /* (C) Copyright */
   C_RO,             // 442 /* (R) */

                     /* Additional greek chars, look SGML DTD */

   C_epsilon_var,    // 443 // straight epsilon
   C_theta_var,      // 444 // curly theta
   C_DiGamma,        // 445
   C_digamma,        // 446
   C_kappa_var,      // 447 // curly kappa
   C_DiLambda,       // 448
   C_dilambda,       // 449
   C_pi_var,         // 450 // curly pi, like C_omega
   C_rho_var,        // 451 // curly rho
   C_Sigma_var,      // 452 // like "S"
   C_sigma_var,      // 453 // final sigma, like "s"
   C_phi_var,        // 454 // curly phi

                     // ----------------------------
                     /* additional accents, all of them have no width (over the next letter) */
                     // kombinaciniai diakritai

   C_GraveAcc,       // 455 /* `  Grave Accent (C_Grave, kairysis kirtis), over the next letter */
   C_CircAcc,        // 456 /* ^  Circumflex Accent (C_Circ), over the next letter */
   C_TildeAcc,       // 457 /* ~  Tilde (C_Tilde), over the next letter; C_TildeNcomb, C_Tilde */
   C_BreveAcc,       // 458 /* u  (lankelis virsuje) */
   C_SlashAcc,       // 459 /* /  Slash, Solidus (Istrizas bruksnys per raide) */
   C_BdotAcc,        // 460 /* .  Dot bellow */
   C_UnderlAcc,      // 461 /* _  Underline (Pabraukimas) */

   C_prim,           // 462 /* strichas prie raides (C_Acute, C_Apost; C_AcuteNcomb) */
   C_dprim,          // 463 /* du strichai (C_Dacut) */

                     // ----------------------------

   C_Each,           // 464 /* V – "kiekvienam" – apversta A raide */
   C_Exists,         // 465 /* E – "egzistuoja" – apversta E raide */

   C_Aleph,          // 466 /* N – alefas */
   C_Im,             // 467 /* C_I_Got */
   C_Re,             // 468 /* C_R_Got */
   C_wp,             // 469 /* C_p_Got */

   C_le,             // 470 /* <= – mažiau arba lygu */
   C_ge,             // 471 /* >= – daugiau arba lygu */
   C_ne,             // 472 /* =/= – nelygu */
   C_ll,             // 473 /* << */
   C_gg,             // 474 /* >> */
   C_sim,            // 475 /* ~ – panašu */
   C_simeq,          // 476 /* ~- – panašu arba sutampa */
   C_approx,         // 477 /* ~~ – apytiksliai lygu */
   C_cong,           // 478 /* ~= – kongruentu */
   C_equiv,          // 479 /* = – triguba lygybė – ekvivalentu */

   C_sqrt,           // 480 /* square root */
   C_int,            // 481 /* integralas */
   C_oint,           // 482 /* kreivinis integralas */
   C_Sum,            // 483 /* sum sign (C_Sigma) */
   C_Prod,           // 484 /* C_Pi */
   C_O_times,        // 485 /* OX – O perbraukta kryžmai */
   C_O_plus,         // 486 /* O+ – O perbraukta pliusu */

   C_infty,          // 487 /* infinity – begalybė */
   C_propto,         // 488 /* (C_alpha) */
   C_part,           // 489 /* partial (C_delta) */
   C_empty,          // 490 /* O/ (C_O_Slash) */
   C_triangle,       // 491 /* lygiakraštis trikampis, ~C_Delta */
   C_nabla,          // 492 /* V – C_Delta apversta, lygiašonis siauras trikampis */

   C_perp,           // 493 /* T apversta – statmena */
   C_angle,          // 494 /* < – kampas (geom.) */

   C_langle,         // 495 /* < – skliaustas !!! keisti i C_Lang */
   C_rangle,         // 496 /* > – skliaustas !!! keisti i C_Rang */

   C_cap,            // 497 /* U apversta – pjūvis */
   C_cup,            // 498 /* U – junginys */

   C_vee,            // 499 /* V */
   C_wedge,          // 500 /* C_Lambda */

   C_supset,         // 501 /* D – viršaibis */
   C_supseteq,       // 502 /* D= – viršaibis arba sutampa */
   C_subset,         // 503 /* C – poaibis */
   C_subseteq,       // 504 /* C= – poaibis arba sutampa */
   C_nsubset,        // 505 /* C/ – nepoaibis */

   C_in,             // 506 /* C_epsilon_var – priklauso */
   C_notin,          // 507 /* C_epsilon_var_Slash – nepriklauso */
   C_ni,             // 508 /* C_epsilon_var apsuktas – apima */

   C_leftarr,        // 509 /* <-- */
   C_rightarr,       // 510 /* --> */
   C_leftrightarr,   // 511 /* <--> */
   C_uparr,          // 512 /* ^| */
   C_downarr,        // 513 /* |v */
   C_updownarr,      // 514 /* ^|v */

   C_Leftarr,        // 515 /* <== */
   C_Rightarr,       // 516 /* ==> */
   C_Leftrightarr,   // 517 /* <==> */
   C_Uparr,          // 518 /* ^|| */
   C_Downarr,        // 519 /* ||v */
   C_Updownarr,      // 520 /* ^||v */

   C_mid,            // 521 /* | */
   C_paral,          // 522 /* || */

   C_diamond,        // 523 /* tusciaviduris rombas */

   C_Club,           // 524 /* giles */
   C_Diamond,        // 525 /* bugnai, pilnaviduris rombas, C_bdiamond */
   C_Heart,          // 526 /* cirvai sirdys */
   C_Spade,          // 527 /* pikai lapai */

   C_hyph,           // 528 /* hidden hyphenation sign ("\-" for TEX) */ // C_Dash
   C_break,          // 529 /* line break character, no \hfill */

   C_a_Car,          // 530 /* av – laikinai, po to išmesti !!! */

   C_euro,           // 531 /* C= euro piniginis vienetas !!! kelti prie pinigų */

   C_deg,            // 532 /* degree – panašiai, kaip C_Ring, tik dešinėje */
   C_micro,          // 533 /* mikro – panašiai, kaip C_my */
   C_Ohm,            // 534 /* Ohm sign – panašiai, kaip C_Omega */
   C_Angst,          // 535 /* Angstroem – C_A_Ring */

   C_Horl,           // 536 /* horizontal line --- , C_h_b */

   C_Dag,            // 537 /* Dagger +| (kryzius) */
   C_Ddag,           // 538 /* Double dagger +|+ (Kestucio kryzius) */

   C_ff,             // 539 /* ff ligature */
   C_fi,             // 540 /* fi ligature */
   C_fj,             // 541 /* fj ligature */
   C_ffi,            // 542 /* ff ligature */
   C_ffl,            // 543 /* ff ligature */
   C_fl,             // 544 /* ff ligature */

   C_and,            // 545 /* ^ logical and */
   C_or,             // 546 /* V logical or */

   C_fun,            // 547 /* f function of */

   C_MinPl,          // 548 /* -+ minus plus */

   C_EnDash,         // 549 /* -- – vidutinio ilgio brūkšnys */
   C_EmDash,         // 550 /* --- – ilgas brukšnys */

   C_Cdots,          // 551 /* ... – daugtaškis per vidurį */
   C_WideTilde,      // 552 /* ~ didele tilde */

   C_QemSpc,         // 553 /* 1/4 m space */
   C_EnSpc,          // 554 /* n space */
   C_EmSpc,          // 555 /* m space */
   C_2emSpc,         // 556 /* 2 m space */

   C_NewPar,         // 557 /* paragraph end control character */

                     // ----------------------------
                     // lithuanian accented letters

   C_Y_Grave,        // 558 // Y`
   C_y_Grave,        // 559 // y`
   C_E_Tilde,        // 560 // E~
   C_e_Tilde,        // 561 // e~
   C_I_Tilde,        // 562 // I~
   C_i_Tilde,        // 563        // i~
   C_U_Tilde,        // 564 // U~
   C_u_Tilde,        // 565 // u~
   C_Y_Tilde,        // 566 // Y~
   C_y_Tilde,        // 567 // y~
   C_L_Tilde,        // 568 // L~
   C_l_Tilde,        // 569 // l~
   C_M_Tilde,        // 570 // M~
   C_m_Tilde,        // 571 // m~
   C_R_Tilde,        // 572 // R~
   C_r_Tilde,        // 573 // r~
   C_A_Ogon_Acute,   // 574
   C_a_Ogon_Acute,   // 575
   C_E_Ogon_Acute,   // 576
   C_e_Ogon_Acute,   // 577
   C_E_Adot_Acute,   // 578
   C_e_Adot_Acute,   // 579
   C_I_Ogon_Acute,   // 580
   C_i_Ogon_Acute,   // 581
   C_U_Ogon_Acute,   // 582
   C_u_Ogon_Acute,   // 583
   C_U_Macr_Acute,   // 584
   C_u_Macr_Acute,   // 585
   C_A_Ogon_Grave,   // 586
   C_a_Ogon_Grave,   // 587
   C_E_Ogon_Grave,   // 588
   C_e_Ogon_Grave,   // 589
   C_E_Adot_Grave,   // 590
   C_e_Adot_Grave,   // 591
   C_I_Ogon_Grave,   // 592
   C_i_Ogon_Grave,   // 593
   C_U_Ogon_Grave,   // 594
   C_u_Ogon_Grave,   // 595
   C_U_Macr_Grave,   // 596
   C_u_Macr_Grave,   // 597
   C_A_Ogon_Tilde,   // 598
   C_a_Ogon_Tilde,   // 599
   C_E_Ogon_Tilde,   // 600
   C_e_Ogon_Tilde,   // 601
   C_E_Adot_Tilde,   // 602
   C_e_Adot_Tilde,   // 603
   C_I_Ogon_Tilde,   // 604
   C_i_Ogon_Tilde,   // 605
   C_U_Ogon_Tilde,   // 606
   C_u_Ogon_Tilde,   // 607
   C_U_Macr_Tilde,   // 608
   C_u_Macr_Tilde,   // 609

                     // ----------------------------
                     // phonetic characters; vowels:

   C_ph_a,           // 610 // low back unrounded; a, open a; italic C_a

   C_ph_a_inv,       // 611 // low back rounded; oa; inverted italic C_a

   C_ph_a_sh,        // 612 // low-mid back unrounded; short a; inverted C_v
   C_ph_o_sh,        // 613 // low-mid back rounded; short o, open o; inverted C_c
// C_ph_o,           // mid back rounded?; o, closed o; C_o

   C_ph_u_sh,        // 614 // semi-high back rounded; short u, short open u; C_ypsilon
   C_ph_w_sh,        // 615 // semi-high back rounded; short u, short open u, obsolete; C_omega
// C_ph_u,           // semi-high central rounded?; u, closed u; C_u
// C_ph_u_soft,      // high central rounded; soft u, iu, german C_u_Diaer; C_y,

   C_ph_e_sh,        // 616 // low-mid front unrounded; short e, open e; C_epsilon
   C_ph_ae,          // 617 // low front unrounded?; e, open e; C_ae
// C_ph_e_cl,        // high central unrounded?; closed e, german e; C_e
   C_ph_e_sh_inv,    // 618 // low-mid central unrounded; hard e; inverted C_epsilon
   C_ph_e_inv,       // 619 // mid central unrounded; reduced e; inverted C_e

   C_ph_i_sh,        // 620 // semi-high front unrounded; short i, short open i; C_i without dot
// C_ph_i,           // high front unrounded?; i, closed i; C_i

                     // ----------------------------
                     // phonetic characters; consonants:

   C_ph_sh,          // 621 // sh; C_f, C_int
   C_ph_zh,          // 622 // zh; C_3
   C_ph_tsh,         // 623 // tsh; C_t C_f, C_t C_int
   C_ph_dzh,         // 624 // dzh; C_d C_3
   C_ph_th_b,        // 625 // breath th; C_theta
   C_ph_th_v,        // 626 // voiced th; C_delta_Dash
   C_ph_ng,          // 627 // nasal g; C_eta
   C_ph_g,           // 628 // g; italic C_g

                     // ----------------------------
                     // additional phonetic characters:

   C_ph_oe,          // 629 // high back rounded?; soft o, open soft o, io, german C_o_Diaer; C_oe,
   C_ph_o_slash,     // 630 // high back rounded?; soft o, closed soft o, io, german C_o_Diaer; C_o_Slash; "o/"

   C_ph_a_l,         // 631 // low back unrounded long; a long, open a long; a:, italic C_a C_Colon
   C_ph_e_inv_l,     // 632 // mid central unrounded long; reduced e long; e:, inverted C_e C_Colon
   C_ph_i_l,         // 633 // high front unrounded long?; i long, closed i long; i:, C_i C_Colon
   C_ph_o_l,         // 634 // low-mid back rounded long; o long, open o long; o:, inverted C_c C_Colon
   C_ph_u_l,         // 635 // ; u long; C_u C_Colon

   C_ph_a_n,         // 636 // low back unrounded nasal; a nasal, open a nasal; a~, italic C_a C_TildeAcc
   C_ph_a_str_n,     // 637 // ; straight a nasal; a~, C_a_Tilde
   C_ph_e_n,         // 638 // low-mid front unrounded nasal; short e nasal, open e nasal; e~, C_epsilon C_TildeAcc
   C_ph_oe_n,        // 639 // ; oe nasal; oe~, C_oe C_TildeAcc
   C_ph_o_n,         // 640 // low-mid back rounded nasal; open o nasal; o~, inverted C_c + C_TildeAcc

   C_ph_ch,          // 641 // german ch; C_c_Cedil

                     // ----------------------------
                     // diphtongs

   C_ph_ai_d,        // 642 // C_a C_LigaLow C_i
   C_ph_ae_d,        // 643 // C_a C_LigaLow C_e
   C_ph_ao_d,        // 644 // C_a C_LigaLow C_o
   C_ph_au_d,        // 645 // C_a C_LigaLow C_u
   C_ph_ei_d,        // 646 // C_e C_LigaLow C_i
   C_ph_eu_d,        // 647 // C_e C_LigaLow C_u
   C_ph_ie_d,        // 648 // C_i C_LigaLow C_e
   C_ph_oe_d,        // 649 // C_ph_o_sh C_LigaLow C_ph_o_slash
   C_ph_oy_d,        // 650 // C_ph_o_sh C_LigaLow C_y
   C_ph_uo_d,        // 651 // C_u C_LigaLow C_o

                     // ----------------------------
                     // breved phonetics

   C_ph_i_Brev,      // 652 // ; j; C_i_Brev
   C_ph_o_Brev,      // 653 //  C_o_Brev
   C_ph_u_Brev,      // 654 //  C_u_Brev

                     // liga accents (for diphtongs)

   C_LigaUp,         // 655 // lankelis virs dvieju raidziu
   C_LigaLow,        // 656 // lankelis po dviem raidem

   C_MidRing,        // 657 // mažas apskritimas viduryje (tuščiaviduris bulletas – kaip C_Bpoint)

                     // phonetic accents

   C_ph_acc,         // 658 // C_Apost
   C_ph_acc_low,     // 659 // C_Comma

   C_square,         // 660 // tusciaviduris kvadratas viduryje

   C_male,           // 661 // vyr. lytis, male sex, mars, o^
   C_female,         // 662 // mot. lytis, female sex, venus, o+

   C_O_ring,         // 663 // Oo – mažas apskritimas O viduje
   C_O_dot,          // 664 // O. – taškas O viduje

   C_BigRing,        // 665 // didelis apskritimas, C_O

   C_longleftarr,    // 666 /* <---- */
   C_longrightarr,   // 667 /* ----> */

   C_smile,          // 668 // lankas, ~C_LigaLow

   C_box,            // 669 // pilnaviduris kvadratas viduryje, square bullet

                     // ----------------------------
                     // DOS frames

   C_v_b,            // 670 // vert; ne DOS-e – C_Vertl
   C_h_b,            // 671 // hor; ne DOS-e – C_Horl
   C_vh_b,           // 672 // vert hor
   C_vl_b,           // 673 // vert left
   C_vr_b,           // 674 // vert right
   C_hu_b,           // 675 // hor up
   C_hd_b,           // 676 // hor down
   C_ul_b,           // 677 // up left
   C_dl_b,           // 678 // down left
   C_ur_b,           // 679 // up right
   C_dr_b,           // 680 // down right

   C_2v_b,           // 681 // double vert; C_paral
   C_2h_b,           // 682 // double hor
   C_2v2h_b,         // 683 // double vert double hor
   C_2v2l_b,         // 684 // double vert double left
   C_2v2r_b,         // 685 // double vert double right
   C_2h2u_b,         // 686 // double hor double up
   C_2h2d_b,         // 687 // double hor double down
   C_2u2l_b,         // 688 // double up double left
   C_2d2l_b,         // 689 // double down double left
   C_2u2r_b,         // 690 // double up double right
   C_2d2r_b,         // 691 // double down double right

   C_2vh_b,          // 692 // double vert hor
   C_2vl_b,          // 693 // double vert left
   C_2vr_b,          // 694 // double vert right
   C_h2u_b,          // 695 // hor double up
   C_h2d_b,          // 696 // hor double down
   C_2ul_b,          // 697 // double up left
   C_2dl_b,          // 698 // double down left
   C_2ur_b,          // 699 // double up right
   C_2dr_b,          // 700 // double down right

   C_v2h_b,          // 701 // vert double hor
   C_v2l_b,          // 702 // vert double left
   C_v2r_b,          // 703 // vert double right
   C_2hu_b,          // 704 // double hor up
   C_2hd_b,          // 705 // double hor down
   C_u2l_b,          // 706 // up double left
   C_d2l_b,          // 707 // down double left
   C_u2r_b,          // 708 // up double right
   C_d2r_b,          // 709 // down double right

   C_block,          // 710 // pilnaviduris kvadratas per visa laukeli
   C_dgrblk,         // 711 // tamsiai pilkas ---//--- (75% shaded)
   C_grblk,          // 712 // pilkas ---//--- (50% shaded)
   C_lgrblk,         // 713 // sviesiai pilkas ---//--- (25% shaded)
   C_uphblk,         // 714 // pilnaviduris staciakampis per puse laukelio virsuje
   C_dnhblk,         // 715 // ---//--- apačioje
   C_lthblk,         // 716 // ---//--- kairėje
   C_rthblk,         // 717 // ---//--- dešinėje

   C_utrif,          // 718 // pilnaviduris lygiakraštis trikampis smaigaliu į viršų, MS Word UTF16
   C_dtrif,          // 719 // pilnaviduris trikampis žemyn, MS Word UTF16
   C_ltrif,          // 720 // pilnaviduris trikampis į kairę; MS Word UTF16, IExplorer ir Netscape C_ltri
   C_rtrif,          // 721 // pilnaviduris trikampis į dešinę; MS Word UTF16, IExplorer ir Netscape C_rtri

                     // ----------------------------
   C_ph_uu_sh,       // 722 // phonetics: semi-high back rounded; short u, short open u; inverted C_Omega

   C_hhyph,          // 723 // hard hyphen – žodžio kėlimas per prievartą "-\break" // C_hyph, C_Dash
   C_sbreak,         // 724 // soft break \lastwordinpar{5}{...} iki pastraipos (lizdo) pabaigos
   C_hSpc,           // 725 // hard space – technical space after TEX commands – do not process
   C_hbreak,         // 726 // break su \hfill, xmlsty keiciamas is C_Cr ("\r"), C_break
   C_lSpc,           // 727 // last space – space, to be changed to C_NBSP after LAST_WORD_LEN
   C_hlSpc,          // 728 // hard last space – C_hSpc, to be changed to C_NBSP after LAST_WORD_LEN

   C_utrif_rtf,      // 729 // pilnaviduris lygiakraštis trikampis smaigaliu į viršų, MS Word RTF
   C_dtrif_rtf,      // 730 // pilnaviduris trikampis žemyn, MS Word RTF
   C_ltrif_rtf,      // 731 // pilnaviduris trikampis i kairę, MS Word RTF
   C_rtrif_rtf,      // 732 // pilnaviduris trikampis i dešinę, MS Word RTF

// erdvinės rodyklės – žr. mcm_src.48d mac_p.rtf lizdas 2231
   C_3DTopLightLeftArrowHead,    // 733
   C_3DBotLightLeftArrowHead,    // 734
   C_3DTopLightRightArrowHead,   // 735
   C_3DBotLightRightArrowHead,   // 736
   C_3DLeftLightUpArrowHead,     // 737
   C_3DRightLightUpArrowHead,    // 738
   C_3DLeftLightDownArrowHead,   // 739
   C_3DRightLightDownArrowHead,  // 740

   C_MinusMath,      // 741   // C_Dash

   C_ZeroWidthSpace, // 742   // C_Spc

   C_ph_glot_stop,   // 743   // phonetics: glottal stop, ~ C_Quest be tasko

                     // ---------------------------
                     // nekombinaciniai diakritai

   C_AcuteNcomb,     // 744   // nekombinacinis dešininis kirtis (C_Acute, C_Apost)
   C_CedilNcomb,     // 745   // nekombinacine cedilla (C_Cedil)
   C_MacrNcomb,      // 746   // nekombinacinis brūkšnys viršuje (C_Macr)

                     // ---------------------------

   C_DollNctrl,      // 747   // nevaldantis dolerio ženklas (C_Doll); TEX'e yra atitikmuo TX_SP_Doll

   C_OgonNcomb,      // 748   // nekombinacinis nosines diakritas (C_Ogon)

   C_No,             // 749   // rusiškas numerio ženklas No

                     // ---------------------------
                     // nekombinaciniai diakritai

   C_CarNcomb,       // 750   // nekombinacinis Caron (Pauksciukas) (C_Car)
   C_DiaerNcomb,     // 751   // nekombinacinis umlautas (C_Diaer)
   C_TildeNcomb,     // 752   // nekombinacinis tildes diakritas, galmetu C_Tilde, bet TEX-e storesne ir per viduri, o reikia pakeltos; C_TildeAcc

                     // ---------------------------

   C_utri,           // 753   // tusciaviduris lygiakrastis trikampis smaigaliu i virsu
   C_dtri,           // 754   // tusciaviduris trikampis zemyn
   C_ltri,           // 755   // tusciaviduris trikampis į kairę; MS Word UTF16, IExplorer ir Netscape pilnaviduris
   C_rtri,           // 756   // tusciaviduris trikampis į dešinę; MS Word UTF16, IExplorer ir Netscape pilnaviduris

// ----------------------------
   C_Oline,          // 757   // kombinacinis matematinis diakritas – brukšnys virš raidės, C_Macr

   C_R_Oline,        // 758   // R su bruksniu, C_R_Macr
   C_X_Oline,        // 759   // X su bruksniu, C_X_Macr

   C_leqslant,       // 760   /* <= – mažiau arba lygu, lygybė lygiagreti su < */
   C_geqslant,       // 761   /* >= – daugiau arba lygu, lygybė lygiagreti su > */

   C_i_Grave_Dotless, // 762 // C_i_Grave, // i`
   C_i_Acute_Dotless, // 763 // C_i_Acute, // i'
   C_i_Tilde_Dotless, // 764 // C_i_Tilde, // i~

//------------------------- accented cyrillic
   C_A_Cyr_Acute,    // 765
   C_E_Cyr_Acute,    // 766
   C_I_Cyr_Acute,    // 767
   C_O_Cyr_Acute,    // 768
   C_U_Cyr_Acute,    // 769
   C_Y_Cyr_Acute,    // 770
   C_Ee_Cyr_Acute,   // 771
   C_Yu_Cyr_Acute,   // 772
   C_Ya_Cyr_Acute,   // 773

   C_a_Cyr_Acute,    // 774
   C_e_Cyr_Acute,    // 775
   C_i_Cyr_Acute,    // 776
   C_o_Cyr_Acute,    // 777
   C_u_Cyr_Acute,    // 778
   C_y_Cyr_Acute,    // 779
   C_ee_Cyr_Acute,   // 780
   C_yu_Cyr_Acute,   // 781
   C_ya_Cyr_Acute,   // 782

   C_NullSpc,        // 783 /* null width space, skirtuku atskyriklis, tarpu valgytojas */

   C_Dash_Diaer,     // 784   dash su umlautu -"

   C_bdiamond,       // 785 /* pilnaviduris rombas, C_Diamond */

   C_DegCels,        // 786 /* degree Celsius – celsijaus laipsniai, C_deg C_C */

   C_hBpoint,        // 787 /* bullet, didelis taskas vidury */ // tiems atvejams, kai C_Bpoint naudojamas homonimų identifikavimui (DOUBLE_ENTRIES_KPCHAR) 

// ----------------------- old style cyrillic
   C_Fita_Cyr,       // 788
   C_fita_Cyr,       // 789
   C_Yat_Cyr,        // 790
   C_yat_Cyr,        // 791

   C_checkmark,      // 792 // varnelė pažymėjimui

                     // ----------------------------
                     // nekombinaciniai diakritai

   C_prim_Ncomb,     // 793 /* strichas prie raides (C_Acute, C_Apost; C_AcuteNcomb) */
   C_dprim_Ncomb,    // 794 /* du strichai (C_Dacut) */

                     // ----------------------------
   C_CharSize0,

} KpChar_enum;

typedef int KpChar;


#endif // #ifndef KPTT_INCLUDED
