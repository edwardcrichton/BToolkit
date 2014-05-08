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
int level_out,key_out,ctr_format_out,rev_vid_out;
  reset_out(l)
  {register int k ;
    itrn( k , 1 , l , {
      print_fic(BLK_sym)
   ;});
    mod_pre_fic(l);
    mod_col_ctr_fic(val_pre_fic+1);
  }

  newl_out(l)
  {register int k ;
    if( rev_vid_out==TRUE ){
      write_erv_fic;
    };
    print_newl_fic;
    itrn( k , 1 , val_pre_fic , {
      print_fic(BLK_sym)
   ;});
    itrn( k , 1 , l , {
      print_fic(BLK_sym)
   ;});
    mod_col_ctr_fic(val_pre_fic+l+1);
    if( rev_vid_out==TRUE ){
      write_srv_fic;
    };
}

  
  write_blk_out(l)
  {register int i ;
    itrn( i , 1 , l , {
      print_fic(BLK_sym)
   ;});
    mod_col_ctr_fic(val_col_ctr_fic+l);
  }

   
  write_chr_stri_out(i,l,v,b)
  {register int write_chr_stri_out_res ;
    write_chr_stri_out_res=FALSE;
    if( ((i==1) || (i==l)) && (v==SMPQUO_sym) ){
      {};
    } else if( v==ANTI_SLASH_sym ){
      if( b==TRUE ){
        mod_col_ctr_fic(val_col_ctr_fic+1);
        print_fic(v);
      } else {
        write_chr_stri_out_res=TRUE;
      };
    } else if( b==TRUE ){
      if( v==ord('n') ){
        
/* newl_out(0) */
        reset_out(0);
        print_newl_fic;
      } else if( v==ord('E') ){
        print_fic(27);
      } else if( v==ord('B') ){
        print_fic(7);
      } else if( v==ord('t') ){
        mod_col_ctr_fic(val_col_ctr_fic+1);
        print_fic(TAB_sym);
      } else if( v==SMPQUO_sym ){
        mod_col_ctr_fic(val_col_ctr_fic+1);
        print_fic(v);
      } else {
        mod_col_ctr_fic(val_col_ctr_fic+2);
        print_fic(ANTI_SLASH_sym);
        print_fic(v);
      };
} else {
      mod_col_ctr_fic(val_col_ctr_fic+1);
      print_fic(v);
    }
  ; return write_chr_stri_out_res;
  }

  write_stri_out(s)
  {register int i,v
/* ,b,l */
 ;
    
/* b=FALSE; */
    if( s<=0 ){
      mod_col_ctr_fic(val_col_ctr_fic+len_nat(0-s));
      write_nat_fic(0-s);
    } else if( s<=127 ){
      mod_col_ctr_fic(val_col_ctr_fic+1);
      print_fic(s);
    } else {
      
/* l=len_str(stri_sym(s)); */
      itr_str(stri_sym(s),i,v,mod_col_ctr_fic(val_col_ctr_fic+1);
      print_fic(v)
/* b=write_chr_stri_out(i,l,v,b) */
)
/* ;
      if( b==TRUE ){
        mod_col_ctr_fic(val_col_ctr_fic+1);
        print_fic(ANTI_SLASH_sym);
      } */;
    };
  }

  write_out(s)
  {register int c,k ;
    c=lexi_sym(s);
    k=edit_sym(s);
#ifdef BTOOLM_FLAG
    if ( s == ERR_sym ) {
      Popup_Info ( "      Syntax error in source file!    " );
      return;
    }
#endif /* BTOOLM_FLAG */
    if( k==keyt ){
      level_out=level_out-2;
      newl_out(level_out)        ;
    } else if( ((k==keyw) || (k==keyl)) ){
      if( c==bin ){
        if( key_out==TRUE ){
          write_blk_out(1);
        } else {
          newl_out(level_out-2);
        };
      } else if( c==opn ){
        if( level_out==0 ){
          mod_pre_fic(val_col_ctr_fic-1);
        };
      };
    } else if( (k==blkb) || ((k==blba) && (s!=BL2_sym)) || (k==blbt) || (k==bbat) ){
      write_blk_out(1);
    }

    if( s==BL0_sym ){
      {};
    } else if( s==BL2_sym ){
      write_blk_out(1);
    } else if( s==SRV_sym ){
      write_srv_fic;
      rev_vid_out=TRUE;
    } else if( s==ERV_sym ){
      write_erv_fic;
      rev_vid_out=FALSE;
    } else if( k!=voyd ){  
      write_stri_out(s);
    }

    if( k==keyw ){
      if( c==opn ){
        level_out=level_out+2;
      };
      key_out=TRUE;
      write_blk_out(1);
    } else if( k==keyl ){
      if( c==opn ){
        level_out=level_out+2;
      };
      key_out=FALSE;
      newl_out(level_out);
    } else if( (k==term) || (k==blbt) || (k==blat) || (k==bbat) ){
      if( (level_out==0) || (key_out==TRUE) ){
        if( ((k==blat) || (k==bbat)) ){
          write_blk_out(1);
        };
      } else {
        newl_out(level_out);
      };
    } else if( ((k==blba) && (s!=BL2_sym)) || (k==blka) ){
      write_blk_out(1);
    }
  ;
}

   
  unp0_out(v)
  {
    write_out(v);
  }

  unp1_out(v,t,i)
  {register int w ;
    w=val_tree(t,left_node_tree(t,i));
    if( (ari_sym(w)==2) && (lexi_sym(v)!=opn) ){
      if( prio_sym(v) > prio_sym(w) ){
        write_out(ord('('));
      };
    };
  }

  unp2_out(v,t,i)
  {register int w ;
    w=val_tree(t,left_node_tree(t,i));
    if( (ari_sym(w)==2) && (lexi_sym(v)!=opn) ){
      if( prio_sym(v) > prio_sym(w) ){
        write_out(ord(')'));
      };
    };
    write_out(v);
    w=val_tree(t,right_node_tree(t,i));
    if( (v==EVL_sym) && (w==ord('[')) ){
      {};
    } else if( ((v==EVL_sym) || ((lexi_sym(v)==unr) && (v>127))) && (lexi_sym(w)==atm) ){
      write_out(ord('('));
    } else if( (ari_sym(w)==2) && (lexi_sym(v)!=opn) ){
      if( prio_sym(v)>=prio_sym(w)+righ_sym(w) ){
        write_out(ord('('));
      };
    };
  }

unp3_out(v,t,i)
{register int w ;
  if( lexi_sym(v)==opn ){
    write_out(clos_sym(v));
  } else {
    w=val_tree(t,right_node_tree(t,i));
    if( (v==EVL_sym) && (w==ord('[')) ){
      {};
    } else if( ((v==EVL_sym) || ((lexi_sym(v)==unr) && (v>127))) && (lexi_sym(w)==atm) ){
      write_out(ord(')'));
    } else if( ari_sym(w)==2 ){
      if( prio_sym(v)>=prio_sym(w)+righ_sym(w) ){
        write_out(ord(')'));
      };
    };
  };
}

  unparse_out(t,n)
  {register int i,v ;
    itr_tree(t,n,i,v,unp0_out(v),
                     unp1_out(v,t,i),
                     unp2_out(v,t,i),
                     unp3_out(v,t,i));
  }

  write_tree_out(t,n,v)
  {
    rev_vid_out=FALSE;
    mod_pre_fic(v);
    level_out=0;
    key_out=FALSE;
    unparse_out(t,n);
}

  

#define write_frm_out(f,n) write_tree_out(f,root_tree(f),n)

  write_chr_stri_format_out(i,l,v,b,ff)
  {register int write_chr_stri_out_res ;
    write_chr_stri_out_res=FALSE;
    if( ((i==1) || (i==l)) && (v==SMPQUO_sym) ){
      {};
    } else if( v==PERCT_sym ){
      if( b==TRUE ){
        mod_col_ctr_fic(val_col_ctr_fic+1);
        print_fic(v);
      } else if( ctr_format_out<=len(ff) ){
        write_frm_out(val(ff,ctr_format_out),0);
        if( ctr_format_out==len(ff) ){
          ctr_format_out=2;
        } else {
          ctr_format_out=ctr_format_out+1;
        };
      };
    } else if( v==ANTI_SLASH_sym ){
      if( b==TRUE ){
        mod_col_ctr_fic(val_col_ctr_fic+1);
        print_fic(v);
      } else {
        write_chr_stri_out_res=TRUE;
      };
    } else if( b==TRUE ){
      if( v==ord('n') ){
        
/* newl_out(0) */
        reset_out(0);
        print_newl_fic;
      } else if( v==ord('E') ){
        print_fic(27);
      } else if( v==ord('B') ){
        print_fic(7);
      } else if( v==ord('t') ){
        mod_col_ctr_fic(val_col_ctr_fic+1);
        print_fic(TAB_sym);
      } else if( v==SMPQUO_sym ){
        mod_col_ctr_fic(val_col_ctr_fic+1);
        print_fic(v);
      } else {
        mod_col_ctr_fic(val_col_ctr_fic+2);
        print_fic(ANTI_SLASH_sym);
        print_fic(v);
      };
} else {
      mod_col_ctr_fic(val_col_ctr_fic+1);
      print_fic(v);
    }
  ; return write_chr_stri_out_res;
  }

  write_format_out(s,ff)
  {register int l,b,i,v,j,n,t,w,ss,m ;
    mod_pre_fic(0);
    level_out=0;
    key_out=FALSE;
    l=len_str(stri_sym(s));
    b=FALSE;
    ctr_format_out=2;
    i=2;
    while( i<l ){
      v=val_str(stri_sym(s),i);
      if( (v==PERCT_sym) && (b==FALSE) ){
        j=i+1;
        n=0;
        t=0;
        while( j<l ){
          w=val_str(stri_sym(s),j);
          if( digit_sym(w)==TRUE ){
            n=n*10+(w-'0');
            t=t+1;
            j=j+1;
          } else {
            j=l;
          };
        };
        if( ctr_format_out<=len(ff) ){
          ss=val_root_frm(val(ff,ctr_format_out));
          if( is_nbr_sym(ss)==TRUE ){
            m=len_nat(arith_val_sym(ss));
            if( n>m ){
              write_blk_out(n-m);
            };
          } else if( is_atm_sym(ss) == TRUE ){
            m=len_sym(ss);
            if( n>m ){
              write_blk_out(n-m);
            };
          };
        };
        b=write_chr_stri_format_out(i,l,v,b,ff);
        i=i+1+t;
      } else {
        b=write_chr_stri_format_out(i,l,v,b,ff);
        i=i+1;
      };
    }

/*  itr_str(stri_sym(s),i,v,b=write_chr_stri_format_out(i,l,v,b,ff));  */
    if( b==TRUE ){
      mod_col_ctr_fic(val_col_ctr_fic+1);
      print_fic(ANTI_SLASH_sym);
    };
  }

