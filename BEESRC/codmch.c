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
int ttnm [ 25 ];

/*  ; return DONE  */


#ifdef BTOOL_FLAG

DesensitizeLSTButtons ( nn )
int nn;
{
  if ( nn >= 41 ) {
    fprintf ( bstdout, "\n\n                  BTool Error Code: %d%d%d%d\n\n", 1, 3, 2, nn + 1 );
    exit ( 0 );
  }
  Blm_registered = 1;
}

#endif /* BTOOL_FLAG */

FILE *coding;
char name_cod[1001];
int  index_name_cod;

#define is_symbol3(a,b,c)   ( (val_str(bbuf,1)==ord(a)) && (val_str(bbuf,2)==ord(b)) && (val_str(bbuf,3)==ord(c)) )
                            

#define is_symbol4(a,b,c,d) ( is_symbol3(a,b,c) && (val_str(bbuf,4)==ord(d)) )
                              

#define dig 1

#define low 2

#define upp 3

#define mix 4

#define opss 5
entersymb_coding(bbuf,i,s,t,k,neg)
{register int n,ss,entersymb_coding_res ;
  entersymb_coding_res=0;
  if( s==1 ){
    entersymb_coding_res=cre_sym(bbuf,atm,nrml,0);
  } else if( s==2 ){
    if( i==3 ){
      if( is_symbol3('c','l','o') ){
        mod_lexi_sym(k,clo);
      } else if( is_symbol3('o','p','n') ){
        mod_lexi_sym(k,opn);
      } else if( is_symbol3('u','n','r') ){
        mod_lexi_sym(k,unr);
      } else if( is_symbol3('p','s','t') ){
        mod_lexi_sym(k,pst);
      } else if( is_symbol3('b','i','n') ){
        mod_lexi_sym(k,bin);
      } else if( is_symbol3('a','t','m') ){
        mod_lexi_sym(k,atm);
      } else {
        mod_lexi_sym(k,atm);
      }
    } else {
      mod_lexi_sym(k,atm);
    }
    if( lexi_sym(k)==atm ){
      arity[k]=0;
    } else {
      arity[k]=2;
    }
  } else if( s==3 ){
    if( i==4 ){
      if( is_symbol4('k','e','y','w') ){
        mod_edit_sym(k,keyw);
      } else if( is_symbol4('k','e','y','l') ){
        mod_edit_sym(k,keyl);
      } else if( is_symbol4('k','e','y','t') ){
        mod_edit_sym(k,keyt);
      } else if( is_symbol4('n','r','m','l') ){
        mod_edit_sym(k,nrml);
      } else if( is_symbol4('v','o','i','d') ){
        mod_edit_sym(k,voyd);
      } else if( is_symbol4('b','l','k','b') ){
        mod_edit_sym(k,blkb);
      } else if( is_symbol4('b','l','k','a') ){
        mod_edit_sym(k,blka);
      } else if( is_symbol4('b','l','b','a') ){
        mod_edit_sym(k,blba);
      } else if( is_symbol4('b','l','b','t') ){
        mod_edit_sym(k,blbt);
      } else if( is_symbol4('b','l','a','t') ){
        mod_edit_sym(k,blat);
      } else if( is_symbol4('b','b','a','t') ){
        mod_edit_sym(k,bbat);
      } else if( is_symbol4('t','e','r','m') ){
        mod_edit_sym(k,term);
      } else {
        mod_edit_sym(k,nrml);
      }
    } else {
      mod_edit_sym(k,nrml);
    }
  } else if( s==4 ){
    if( t==dig ){
      n=trans_str(bbuf);
      if( neg==TRUE ){
        mod_prio_sym(k,0-n);
      } else {
        mod_prio_sym(k,n);
      }
    } else {
      mod_prio_sym(k,0);
    }
  } else if( s==5 ){
    if( lexi_sym(k)==bin ){
      mod_righ_sym(k,1);
    } else if( lexi_sym(k)==opn ){
      if( k>127 ){
        xst_sym(ss,(eql_str(bbuf,stri_sym(ss))==TRUE) && (lexi_sym(ss)==clo),mod_clos_sym(k,ss),mod_clos_sym(k,END_sym));
      } else if( len_str(bbuf)==1 ){
        if( lexi_sym(val_str(bbuf,1))==clo ){
          mod_clos_sym(k,val_str(bbuf,1));
        } else {
          mod_clos_sym(k,ord(')'));
        }
      }
    }
  }
  return entersymb_coding_res;
}

nature(o)
{register int natureres ;
  if( digit_sym(o)==TRUE ){
    natureres=dig;
  } else if( lower_sym(o)==TRUE ){
    natureres=low;
  } else if( upper_sym(o)==TRUE ){
    natureres=upp;
  } else {
    natureres=opss;
  }
  return natureres;
}

lexical_coding(bbuf,c)
{register int p,u,t,k,n,neg ;
  u=0;
  k=0;
  neg=FALSE;
  p=c;
  while( ( p!='\n' ) && ( p!=EOF ) ) {
/***
printf ( "%c\n", p );
***/
    if( (p==ord('-')) && (u>=1) ){
      neg=TRUE;
    } else if( p<=ord(' ') ){
      if( len_str(bbuf)!=0 ){
        u=u+1;
        n=entersymb_coding(bbuf,len_str(bbuf),u,t,k,neg);
        neg=FALSE;
        if( u==1 ){ 
          k=n;
        }
        clr_str(bbuf);
      }
    } else {
      if( len_str(bbuf)==0 ){
        t=nature(p);
      }
      if( t==mix ){
        {};
      } else if( t!=nature(p) ){
        t=mix;
      }
      psh_str(bbuf,p);
    }
    p=getc(coding);
  }
  if( len_str(bbuf)!=0 ){
    u=u+1;
    n=entersymb_coding(bbuf,len_str(bbuf),u,t,k,neg);
    neg=FALSE;
    if( u==1 ){ 
      k=n;
    }
    clr_str(bbuf);
  }
  if( k!=0 ){
    if( u==1 ){
      mod_lexi_sym(k,atm);
      mod_edit_sym(k,nrml);
      mod_prio_sym(k,0);
      arity[k]=0;
    } else if( u==2 ){
      mod_edit_sym(k,nrml);
      mod_prio_sym(k,0);
    } else if( u==3 ){
      mod_prio_sym(k,0);
    }
  }
}

  
ini_codfunc()
#define ini_cod ini_codfunc()
{register int bbuf,c ;
  
  char* bkit;
  char symfilname_cod[1001];
/***
printf ( " ***************************************************** ini_codfunc\n" );
***/
  bbuf=cre(10);
  bkit= (char *) getenv("BKIT");
  if( (bkit == NULL) ){
     fprintf ( bstdout, "\n  ++++++++++++++++++++++++++++++++++++++");
     fprintf ( bstdout, "\n     Environment variable BKIT not set");
     fprintf ( bstdout, "\n  ++++++++++++++++++++++++++++++++++++++\n\n");
     exit(1);
  }

#ifdef BTOOL_FLAG

  strcpy ( BKIT_path, bkit ); 

#endif /* BTOOL_FLAG */

  strcpy(symfilname_cod,bkit);
  strcat(symfilname_cod,"/BPLAT/SYMBOL");

#ifdef SSTL_FLAG

  strcpy(symfilname_cod, "BEESRC/SYMBOL" );

#endif /* SSTL_FLAG */

  coding=fopen(symfilname_cod,"r");
  if( (coding == NULL) ){
     fputs ( "\n       Can't open:\n\n         ", bstdout );
     fputs ( symfilname_cod, bstdout );
     fputs ( "\n\n       for reading\n\n", bstdout );
     exit(1);
  }
  c=getc(coding);
  while( c!=EOF ){
    lexical_coding(bbuf,c);
    c=getc(coding);
  }
  fclose(coding);

#ifdef BTOOLKIT_FLAG


  strcpy(symfilname_cod,bkit);
  strcat(symfilname_cod,"/BPLAT/AMNSYMBOL");
  coding=fopen(symfilname_cod,"r");
  if( (coding == NULL) ){
     fputs ( "\n       Can't open:\n\n         ", bstdout );
     fputs ( symfilname_cod, bstdout );
     fputs ( "\n\n       for reading\n\n", bstdout );
     exit(1);
  }
  c=getc(coding);
  while( c!=EOF ){
    lexical_coding(bbuf,c);
    c=getc(coding);
  }
  fclose(coding);


#endif
  
  kil(bbuf);
}

ini_spe_codfunc()
#define ini_spe_cod ini_spe_codfunc()
{register int bbuf,c ;
  bbuf=cre(10);
/***
printf ( "ini_spe_codfunc: name_cod=`%s'\n", name_cod );
***/
  coding=fopen(name_cod,"r");
  if ( coding != NULL ) {
    c=getc(coding);
    while( c!=EOF ){
      lexical_coding(bbuf,c);
      c=getc(coding);
    }
    fclose(coding);
  }
  else {
    printf ( "\n  WARNING: can't open symbol file ./%s for reading\n\n", name_cod );
#ifdef BTOOLM_FLAG
    sprintf ( str_buf, "\n  WARNING:\n    can't open symbol file ./%s for reading\n", name_cod );
  DisplayCurrWinText ( str_buf );
#endif
  }
  kil(bbuf);
}

ini_name_codfunc()
#define ini_name_cod ini_name_codfunc()
    
{
  index_name_cod = 0;
}

enter_name_cod(v)
{
  if( index_name_cod < 100 ){
    name_cod[index_name_cod] = v ;
    index_name_cod =  index_name_cod + 1;
  }
}

term_name_codfunc()
#define term_name_cod term_name_codfunc()
{
  name_cod[index_name_cod] = '\0' ;
  if( access(name_cod,R_OK) >= 0 ){
    ini_spe_cod;
  }
  else {
    printf ( "\n  WARNING: can't open symbol file ./%s for reading\n\n", name_cod );
#ifdef BTOOLM_FLAG
    sprintf ( str_buf, "\n  WARNING:\n    can't open symbol file ./%s for reading\n", name_cod );
  DisplayCurrWinText ( str_buf );
#endif
  }
}
