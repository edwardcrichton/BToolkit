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
#include <stdio.h>
/**/
#include <stdlib.h>

int c, d, i, non_remove;
char buf [ 10000 ];

void
output_nl ()
{
        if ( non_remove ) {
                printf( " Xx___nl___ /0O0/ " );
        }
        else {
                printf("/* */");
        }
}

void
output_np ()
{
        if ( non_remove ) {
                printf( " Xx___np___ /0O0/ " );
        }
        else {
                printf("/* */");
        }
}

void
get_next_word ()
{
        i = 0;
        buf [ i++ ] = '\\';
        while ( c != EOF && c != ' ' && c != '\t' && c != '\n' && c != '\\' ) {
                buf [ i++ ] = c;
                c = getchar ();
                d = c;
        };
        buf [ i ] = '\0';
/*
        if ( c == '\\' ) {
          ungetc ( c, stdin );
          buf [ i-1 ] = '\0';
          c = d;
       }
*/
}

/*void*/
/* should be int*/
int
main(argc,argv)
int argc;
char *argv[];
{
        if ( strcmp ( argv [ 1 ], "1" ) == 0 ) {
                non_remove = 1;
        }
        else {
                non_remove = 0;
        };
        c = getchar();
        while ( c != EOF ) {
                if ( c == '\\' ) {
                        c = getchar ();
                        if ( c == '\\' ) {
                                output_nl ();
                                c = getchar ();
                        }
                        else {
                                get_next_word ();
                                if ( strcmp ( buf, "\\newpage" ) == 0 ) {
                                        output_np ();
                                }
                                else {
                                        printf( "%s", buf );
                                }
                        }
                };
                if ( c != EOF && c != '\\' ) {
                        printf( "%c", c );
                        c = getchar ();
                }
        };
        exit ( 0 );
}
