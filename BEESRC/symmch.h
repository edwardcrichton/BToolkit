/* Copyright (c) 1985-2012, B-Core (UK) Ltd
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following
conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in
   the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT 
NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#define blk          0

#define clo          1

#define opn          2

#define unr          3

#define pst          4

#define bin          5

#define atm          6
                       
/*  EDITING CATEGORY  */
                       
                       

#define keyw         1

#define keyl         2

#define mixw         3

#define mixa         4

#define mixb         5

#define keyt         6

#define nrml         7

#define voyd         8

#define blkb         9

#define blka        10

#define blba        11

#define blbt        12

#define blat        13

#define bbat        14

#define term        15
                     
/*  SYMBOL MACHINE DECLARATION  */
/* 
int hcod[max_sym+1];
int stri[max_sym+1];
int lexi[max_sym+1];
int edit[max_sym+1];
int prio[max_sym+1];
int righ[max_sym+1];
int clos[max_sym+1];
int arity[max_sym+1];
 */
extern int hcod[];
extern int stri[];
extern int lexi[];
extern int edit[];
extern int prio[];
extern int righ[];
extern int clos[];
extern int arity[];
extern int max_sym;
int sym;
                 
/*  PROGRAMS FOR SYMBOL MACHINE  */

#define END_sym     128

#define EVL_sym     129

#define SPE_sym     130

#define GHO_sym     131

#define ERR_sym     132

#define IMP_sym     133

#define DED_sym     134

#define GEN_sym     135

#define HYP_sym     136

#define ARI_sym     137

#define BOT_sym     138

#define THE_sym     139

#define ISS_sym     140

#define TAC_sym     141

#define WRI_sym     142

#define PLEM_sym    143

#define RID_sym     144

#define SEQ_sym     145

#define GEQ_sym     146

#define NEQ_sym     147

#define LEM_sym     148

#define FAL_sym     149

#define EQV_sym     150

#define FTA_sym     151

#define CON_sym     152

#define UNPLEM_sym  153

#define TTY_sym     154

#define CEQ_sym     155

#define MAC_sym     156

#define MARK_sym    157

#define CAL_sym     158

#define MAP_sym     159

#define JK1_sym     160

#define JK2_sym     161

#define BQU_sym     162

#define REDO_sym    163

#define BL2_sym     164

#define BL0_sym     165

#define NEW_sym     166

#define LMAP_sym    167

#define RUL_sym     168

#define REV_sym     169

#define FLAT_sym    170

#define HALT_sym    171

#define REV_tac_sym 172

#define FLAT_tac_sym 173

#define SMAP_sym    174

#define SLMAP_sym   175

#define MAP_tac_sym 176

#define LMAP_tac_sym 177

#define FEQL_tac_sym 178

#define GET_sym     179

#define MODR_sym    180

#define ERV_sym     181

#define SRV_sym     182

#define SHL_sym     183

#define MODR_tac_sym 184

#define SHELL_tac_sym 185

#define NMAP_sym    186

#define NLMAP_sym   187

#define LOG2_sym    188

#define NRM2_sym    189

#define LEN_sym     190

#define LOW_sym     191

#define STR_sym     192

#define WRIF_sym    193

#define PRIF_sym    194

#define WRITE_tac_sym 195

#define RIDF_sym    196

#define IDENT_sym   197

#define BNUM_sym    198

#define BVRB_sym    199

#define BINH_sym    200

#define BCRER_sym   201

#define BCREL_sym   202

#define RULE_tac_sym 203

#define BTAC_sym    204

#define FTAC_sym    205

#define TAC_tac_sym 206

#define FEQLS_tac_sym 207

#define BCATL_sym   208

#define CATL_tac_sym 209

#define BNEWV_sym   210

#define NEWV_tac_sym 211

#define BCLEAN_sym   212

#define UIDENT_sym  213

#define LIDENT_sym  214

#define BCRELR_sym  215

#define SUB_sym     216

#define RIDE_sym    217

#define WRIM_sym    218

#define APP_sym     219

#define CLO_sym     220

#define ERV2_sym    221

#define SRV2_sym    222

#define BTST_sym    223

#define BPOP_sym    224

#define BGETHYP_sym 225

#define BGETALLHYP_sym 226

#define BLENT_sym   227

#define BSUSPEND_sym 228

#define BFIFOREAD_sym 229

#define BFIFOWRITE_sym 230

#define BBITSTR_sym    231

#define BLITERAL_sym    232

#define BSINGLETON_sym    233

#define BCONSTANT_sym    234

#define BLCONSTANT_sym    235

#define BINFO_sym    236

#define BINT_sym    237

#define BSETFWDPRF_sym    238

#define BGOALS_sym    239

#define BSEARCH_sym   240

#define BSPAREMEM_sym 241

#define BSTATISTICS_sym 242

#define BRECOMPACT_sym  243

#define last_bspec_sym BSEARCH_sym

#define AND_sym     38        
/* & */

#define UNV_sym     33        
/* ! */

#define EQL_sym     61        
/* == */

#define SMC_sym     59        
/* ; */

#define TIL_sym     126       
/* ~ */

#define COM_sym     44

#define LSB_sym     91        
/* [ */

#define RSB_sym     93        
/* [ */

#define LCB_sym     123
/* { */

#define RCB_sym     125
/* } */

#define DOT_sym     46        
/* . */

#define QUO_sym     39

#define ZER_sym     48        
/* 0 */

#define ANTI_SLASH_sym   92   
/* \ */

#define UNDERSCORE_sym   36
/* 95 */
   
/* $ */

#define REAL_UNDERSCORE_sym 95   
/* _ */

#define QUESTION_sym 63       
/* ? */

#define SMR_sym     60        
/* < */

#define GTR_sym     62        
/* > */

#define PLS_sym     43        
/* + */

#define DIV_sym     47        
/* / */

#define MIN_sym     45        
/* - */

#define MUL_sym     42        
/* * */

#define CLOBRK_sym  41        
/* ) */

#define OPNBRK_sym  40        
/* ( */

#define BLK_sym     32        
/*   */
   
/* 
#define SMPQUO_sym  39 */

#define SMPQUO_sym  34

#define DBLQUO_sym  34

#define BAR_sym     124       
/* | */

#define COL_sym     58        
/* : */

#define TAB_sym     9

#define PERCT_sym   37        
/* % */

#define inter_sym(o,x,y)     (((o>=ord(x)) && (o<=ord(y)))!=0)

#define digit_sym(o)         inter_sym(o,'0','9')

#define lower_sym(o)         inter_sym(o,'a','z')

#define upper_sym(o)         inter_sym(o,'A','Z')

#define lower_spe_sym(o)     (((lower_sym(o)==TRUE) || (o==QUESTION_sym) || (o==REAL_UNDERSCORE_sym))!=0)
                                  

#define letter_sym(o)        (((lower_sym(o)==TRUE) || (upper_sym(o)==TRUE))!=0)
                                  

#define letchif_sym(o)       (((digit_sym(o)==TRUE) || (lower_sym(o)==TRUE) || (upper_sym(o)==TRUE))!=0)

#define is_nbr_sym(s)   ((s<=0)!=0)

#define arith_val_sym(s) (-(s))

#define is_arith_sym(s) (((s==PLS_sym) || (s==MIN_sym) || (s==MUL_sym) || (s==DIV_sym) || (s==LOG2_sym) || (s==NRM2_sym) || (s==LEN_sym))!=0)
                             

#define is_rel_arith_sym(s) (((s==SMR_sym) || (s==GTR_sym) || (s==SEQ_sym) || (s==GEQ_sym) || (s==NEQ_sym) || (s==EQL_sym))!=0)
                         

#define EOT_sym     4

#define BET_sym     5

#define stri_sym(s)  stri[s]

#define righ_sym(s)  righ[s]

#define is_atm_sym(s)  ((lexi_sym(s)==atm)!=0)

#define mod_lexi_sym(s,l) lexi[s]=l

#define mod_edit_sym(s,e) edit[s]=e

#define mod_prio_sym(s,p) prio[s]=p

#define mod_righ_sym(s,r) righ[s]=r

#define mod_clos_sym(s,c) clos[s]=c

#define mod_arit_sym(s,a) arity[s]=a

#define nrml_stri_sym(s) ((s>127)!=0)

#define is_single_sym(s) (((s>0) && (s<=127))!=0)
  
#define write_prio_sym(s) write_nat(prio[s])

