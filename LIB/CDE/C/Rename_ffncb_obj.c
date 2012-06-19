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
#include "Rename_ffnc_obj.h"


void
#ifdef _BT_ANSIC
Rename_CRE_FNC_OBJ( int *bb, int *ff )
#else
Rename_CRE_FNC_OBJ( bb, ff )
int *bb, *ff;
#endif
{
	int b,i,f;
	Rename_FUL_FNC_OBJ(&b);
	if( b==0 ){
	        /*
		if( Rename_sold_fnc_obj==0 ){
			Rename_ssize_fnc_obj = Rename_ssize_fnc_obj+1;
			f=Rename_ssize_fnc_obj;
		} else{
		        f=Rename_old_fnc_obj[Rename_sold_fnc_obj];
			Rename_sold_fnc_obj=Rename_sold_fnc_obj-1;
		}
	        */

               if( Rename_sold_fnc_obj<=10 ){ 
                        Rename_ssize_fnc_obj = Rename_ssize_fnc_obj+1; 
                        f=Rename_ssize_fnc_obj; 
               } else{ 
                        f=Rename_old_fnc_obj[1]; i=1; 
                        while( i< Rename_sold_fnc_obj ){ 
                              Rename_old_fnc_obj[i]=Rename_old_fnc_obj[i+1]; }
                        Rename_sold_fnc_obj=Rename_sold_fnc_obj-1; 

	       }

		i = 1;
		while( i<= Rename_ffnc_objP2 ){
			Rename_RMV_FNC_OBJ(f,i);
			i=i+1
			    ;
		};
		*ff = f;
		*bb = 1;
	} else{
		*ff = 0;
		*bb = 0;
	};
}


void
#ifdef _BT_ANSIC
Rename_XST_FNC_OBJ( int *bb, int pp )
#else
Rename_XST_FNC_OBJ( bb, pp )
int *bb, pp;
#endif
{
	int i;
	if ( (pp>0) && (pp<=Rename_ssize_fnc_obj) ) {
		i = Rename_sold_fnc_obj;
		*bb = 1;
		while ( i != 0 ) {
			if ( pp != Rename_old_fnc_obj[i] ) {
				i = i - 1;
			} else {
				i = 0 ;
				*bb = 0;
			};
		};
	}  else {
		*bb = 0
		    ;
	};
}

#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>

extern FILE *dump_file;

#define convert_arr_htonl(a,i,n) \
  j = i; \
  k = 0; \
  while ( k < n ) { \
    a [ j ] = htonl ( a [ j ] ); \
    j++; \
    k++; \
  }

#define convert_arr_ntohl(a,i,n) \
  j = i; \
  k = 0; \
  while ( k < n ) { \
    a [ j ] = htonl ( a [ j ] ); \
    j++; \
    k++; \
  }

#define  write_fm(a,b)    fwrite(&a,sizeof(int),b,dump_file)


void
Rename_SAV_FNC_OBJ()
{
	write_fm(Rename_ssize_fnc_obj,1);
        write_fm(Rename_ffnc_objP2,1);
	write_fm(Rename_fnc_obj[1],Rename_ssize_fnc_obj*Rename_ffnc_objP2);
	write_fm(Rename_sold_fnc_obj,1);
	write_fm(Rename_old_fnc_obj[1],Rename_ssize_fnc_obj);
}

void
Rename_SAVN_FNC_OBJ()
{
        int j, k;

	Rename_ssize_fnc_obj = htonl ( Rename_ssize_fnc_obj );
        write_fm(Rename_ssize_fnc_obj,1);
	Rename_ssize_fnc_obj = ntohl ( Rename_ssize_fnc_obj );

        Rename_ffnc_objP2 = htonl ( Rename_ffnc_objP2 );
        write_fm(Rename_ffnc_objP2,1);
        Rename_ffnc_objP2 = ntohl ( Rename_ffnc_objP2 );

        convert_arr_htonl(Rename_fnc_obj,1,Rename_ssize_fnc_obj*Rename_ffnc_objP2);
	write_fm(Rename_fnc_obj[1],Rename_ssize_fnc_obj*Rename_ffnc_objP2);
        convert_arr_ntohl(Rename_fnc_obj,1,Rename_ssize_fnc_obj*Rename_ffnc_objP2);

	Rename_sold_fnc_obj = htonl ( Rename_sold_fnc_obj );
        write_fm(Rename_sold_fnc_obj,1);
	Rename_sold_fnc_obj = ntohl ( Rename_sold_fnc_obj );

        convert_arr_htonl(Rename_old_fnc_obj,1,Rename_ssize_fnc_obj);
	write_fm(Rename_old_fnc_obj[1],Rename_ssize_fnc_obj);
        convert_arr_ntohl(Rename_old_fnc_obj,1,Rename_ssize_fnc_obj);
}

#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)

void
Rename_RST_FNC_OBJ()
{
	int old_size, i;
	read_fm(Rename_ssize_fnc_obj,1);
	read_fm(old_size,1);
        if ( old_size == Rename_ffnc_objP2 ) {
	  read_fm(Rename_fnc_obj[1],Rename_ssize_fnc_obj*Rename_ffnc_objP2);
	}
        else {
          i = 1;
          while ( i <= Rename_ssize_fnc_obj*Rename_ffnc_objP2 ) {
	    Rename_fnc_obj[i] = 2147483647;
            i = i+1;
	  };
          i = 1;
          while ( i <= Rename_ssize_fnc_obj ) {
	    read_fm(Rename_fnc_obj[1+(i-1)*Rename_ffnc_objP2], old_size);
            i = i+1;
	  }
	}
	read_fm(Rename_sold_fnc_obj,1);
	read_fm(Rename_old_fnc_obj[1],Rename_ssize_fnc_obj);
}

void
Rename_RSTN_FNC_OBJ()
{
	int old_size, i, j, k;
	read_fm(Rename_ssize_fnc_obj,1);
        Rename_ssize_fnc_obj = ntohl ( Rename_ssize_fnc_obj );

	read_fm(old_size,1);
        old_size = ntohl ( old_size );

        if ( old_size == Rename_ffnc_objP2 ) {
	  read_fm(Rename_fnc_obj[1],Rename_ssize_fnc_obj*Rename_ffnc_objP2);
          convert_arr_ntohl(Rename_fnc_obj,1,Rename_ssize_fnc_obj*Rename_ffnc_objP2);
	}
        else {
          i = 1;
          while ( i <= Rename_ssize_fnc_obj*Rename_ffnc_objP2 ) {
	    Rename_fnc_obj[i] = 2147483647;
            i = i+1;
	  };
          i = 1;
          while ( i <= Rename_ssize_fnc_obj ) {
	    read_fm(Rename_fnc_obj[1+(i-1)*Rename_ffnc_objP2], old_size);
            convert_arr_ntohl(Rename_fnc_obj,1+(i-1)*Rename_ffnc_objP2,old_size);
            i = i+1;
	  }
	}
	read_fm(Rename_sold_fnc_obj,1);
        Rename_sold_fnc_obj = ntohl ( Rename_sold_fnc_obj );

	read_fm(Rename_old_fnc_obj[1],Rename_ssize_fnc_obj);
        convert_arr_ntohl(Rename_old_fnc_obj,1,Rename_ssize_fnc_obj);
}


void
#ifdef _BT_ANSIC
Rename_FIRST_FNC_OBJ( int *cc, int *ss )
#else
Rename_FIRST_FNC_OBJ( cc, ss )
int *cc, *ss;
#endif
{
	int c,i,b;
	c = ( Rename_ssize_fnc_obj - Rename_sold_fnc_obj );
	if ( c != 0 ) {
		i = Rename_ssize_fnc_obj;
		Rename_XST_FNC_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			Rename_XST_FNC_OBJ(&b,i);
		};
		*ss = i;
		*cc = c;
	} else {
		*ss = 0;
		*cc = 0;
	};
}


void
#ifdef _BT_ANSIC
Rename_NEXT_FNC_OBJ( int *cc, int *ss, int oc, int os )
#else
Rename_NEXT_FNC_OBJ( cc, ss, oc, os )
int *cc, *ss, oc, os;
#endif
{
	int c,i,b;
	c = oc - 1;
	if ( c != 0 ) {
		i = os - 1;
		Rename_XST_FNC_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			Rename_XST_FNC_OBJ(&b,i);
		};
		*ss = i;
		*cc = c;
	} else {
		*ss = 0;
		*cc = 0;
	};

}
