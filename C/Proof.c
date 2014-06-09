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
#include <string.h>
#include <stdlib.h>

FILE *fileone;
FILE *filetwo;
FILE *filethree;
FILE *filefour;

int p,c,d,e,f;
int t=0;
int y,z;
int u=0;

char n;

char s[1001];

void
zero_filetwo ( f )
char * f;
 {
   fputs("5\n",filetwo);
   fputs(f,filetwo);
   fputs("/BLIB/Toolkit14.bin\n6\n.Bthy\n6\n.Bpof\n3\n3\n5\n(\nbcall(\n(\n",filetwo);

   filefour=fopen(".Btac","r");
   if (filefour == NULL) {
     exit(102);
   }
   c = getc(filefour);
   while (c != EOF)
     {
       putc(c,filetwo);
       c = getc(filefour);
     }
   fputs("):c)\n=>(x <- c)\n)\n`\n",filetwo);
   fclose(filefour);

   fputs("5\n(\nbcall(\n(\n",filetwo);
   filefour=fopen(".Btad","r");
   if (filefour == NULL) {
     exit(102);
   }
   c = getc(filefour);
   while (c != EOF)
     {
       putc(c,filetwo);
       c = getc(filefour);
     }
   fputs("):c)\n=>(x <- x <- c)\n)\n`\n",filetwo); /* obsolete, but leave in */
   fclose(filefour);

   fputs("0\n4\n5\n",filetwo);
   filefour=fopen(".Btac","r");
   if (filefour == NULL) {
     exit(102);
   }
   c = getc(filefour);
   while (c != EOF)
     {
       putc(c,filetwo);
       c = getc(filefour);
     }
   fputs("\n`\n",filetwo);
   fclose(filefour);

   fputs("0\n0\n4\n.B.bin\n0\n\n",filetwo);
 }

 void
 one_filetwo()
 {
   if (filetwo == NULL) {
     exit(100);
   }
   fputs("5\n.B.bin\n3\n2\n5\nbcall(SwitchX:\n(\n",filetwo);
   if (filetwo == NULL) {
     exit(100);
   }
 }


 void
 two_filetwo()
 {
   if (filethree == NULL) {
     exit(101);
   }
   c = getc(filethree);
   while (c != EOF)
     {
       putc(c,filetwo);
       c = getc(filethree);
     }
 }

 void
 three_filetwo()
 {
   fputs(")|(QueryUserX: (SwitchX:",filetwo);
   fclose(filethree);
   filethree=fopen(".Bpob","r");
   two_filetwo();
   fputs("|",filetwo);
   fclose(filethree);
   filethree=fopen(".Bpob","r");
   two_filetwo();
   fputs("))\n)\n`\n3\n1\n8\n\n\n0\n0\n0\n0\n0\n\n",filetwo);
 }


void
read_ini()
{
  c = getc(fileone);
  while (c != EOF && t == 0) {
    if (c == 'P') {
      c = getc(fileone);
      if (c == 'R') {
        c = getc(fileone);
        if (c == 'O') {
          c = getc(fileone);
          if (c == 'O') {
            c = getc(fileone);
            if (c == 'F') {
              c = getc(fileone);
              if (c == '\n') {
                c = getc(fileone);
                if (c == '\n') {
                  t=1;
                }
              }
            }
          }
        }
      }
    }
    c = getc(fileone);
  }
}

void
next()
{
  p = c;
  c = getc(fileone);
  t=t+1;
}


void
step()
{
  if (c == '\n') {
    putc('?',filetwo);
    u = 1;
  }    
  else {
    d = getc(fileone);
    e = getc(fileone);
    f = getc(fileone);
    if (c == ' ' && d == ' ' && e == ' ' && f == ' ') {
      putc(c,filetwo);
      putc(d,filetwo);
      putc(e,filetwo);
      putc(f,filetwo);
      t=t+3;
      next();
    }
    else {
      putc('(',filetwo);
      putc(c,filetwo);
      putc(d,filetwo);
      putc(e,filetwo);
      putc(f,filetwo);
      t=t+3;
      next();
      while (c != ' ') {
        putc(c,filetwo);
        next();
      }
      z=t;
      while (c == ' ') {
        next();
      }
      z=(t-z)/2;
      putc('[',filetwo);
      if (z>9) { y=(z%10)+'0'; z=(z/10)+'0'; putc(z,filetwo); putc(y,filetwo); }
      else     { z=z+'0'; putc(z,filetwo); }
      putc(' ',filetwo);
      putc(']',filetwo);
      putc('|',filetwo);
      putc('(',filetwo);
      putc(' ',filetwo);
    }
  }
}


void
just()
{
  d = getc(fileone);
  if (d == '\n') {
      putc(c,filetwo);
      putc(d,filetwo);
      t=0;
      }
  else {
    putc(' ',filetwo);
    putc(')',filetwo);
    putc('|',filetwo);
    putc(c,filetwo);
    putc('(',filetwo);
    putc(d,filetwo);
    t=50;
  }
}


void
ins()
{
  while (c != EOF && u == 0) {
    if (t == 1) {
      step();
    }
    if (c == ' ') {
      if (t == 49 || t == 50) {
        just();
      }
      else if (t > 50) {
        while (c == ' ') {
          next();
        }
        if (c == '\n') {
          putc(' ',filetwo); 
          putc(')',filetwo); 
          putc(')',filetwo); 
          putc(',',filetwo); 
          putc('\n',filetwo); 
          t=0;
        }
        else {
          putc(',',filetwo);
          putc(c,filetwo);
        }
      }
      else
        putc(c,filetwo);
      }
    else if (c == '\n') {
      if (t < 51) {
        putc(c,filetwo);
        t=0;
      }
      else if (p == ' ') {
        putc(c,filetwo);
        t=0;
      }
      else {
        putc(' ',filetwo); 
        putc(')',filetwo); 
        putc(')',filetwo); 
        putc(',',filetwo); 
        putc('\n',filetwo); 
        t=0;
      }
    }
    else {
      putc(c,filetwo);
    }
    next();  
  }
}


void
inispc()
{
   fileone=fopen(".Bnum","w");
     if (filetwo == NULL) {
       exit(104);
     }
   n = '0';
   putc(n,fileone);
   fclose(fileone);
}


/*
void
spc()
{
   fileone=fopen(".Bnum","r");
     if (filetwo == NULL) {
       exit(105);
     }
   n = getc(fileone);
   fclose(fileone);
   n = n+1;
   if ( n == '5' ) {
     n = '0';
   }
   fileone=fopen(".Bnum","w");
     if (filetwo == NULL) {
       exit(104);
     }
   putc(n,fileone);
   fclose(fileone);
}
*/

void
spc()
{
   int m;
   fileone=fopen(".Bnum","r");
   if (filetwo == NULL) {
     exit(105);
   }
   m = 0;
   n = getc(fileone);
   while ( ( n != EOF ) && ( n != '\n' ) ) {
     m = ( m * 10 ) + n - '0';
     n = getc(fileone);
   }
   fclose(fileone);
   m++;
   fileone=fopen(".Bnum","w");
   if (filetwo == NULL) {
     exit(104);
   }
   n = m / 10000;
   putc(n+'0',fileone);
   m = m - ( n * 10000 );
   n = m / 1000;
   putc(n+'0',fileone);
   m = m - ( n * 1000 );
   n = m / 100;
   putc(n+'0',fileone);
   m = m - ( n * 100 );
   n = m / 10;
   putc(n+'0',fileone);
   m = m - ( n * 10 );
   putc(m+'0',fileone);
   fclose(fileone);
}

int
main(argc,argv)
  int argc;
  char *argv[];
{
 char bses[1000];
 char* bkit;

/***
{
  int i;
  printf ( " >>>>> Proof.c -  argc: %d\n", argc );
  for ( i = 0 ; i < argc ; i++ ) {
    printf ( "  %d: %s\n", i, argv [ i ] );
  }
}
***/

/***
system ( "ls -alrt" );
printf ( "------------\n" );
***/

    bkit=getenv("BKIT");
    if (bkit==NULL) {
      printf("\n              Environment variable BKIT not set\n\n");
      exit(1);
      }
    strcpy(bses,bkit);
    strcat(bses,"/BLIB/BSession");
    if (strcmp("1",argv[1]) == 0) {
     filetwo=fopen(".BBcom","w");
     if (filetwo == NULL) {
       exit(100);
     }
     zero_filetwo(argv[2]);
     fclose(filetwo);
     strcpy(s,argv[2]);
     strcat(s,"/BPLAT/bplatform rR1H1pp < .BBcom > .Berr");
     system(s);
/***
printf ( "Proof.c 1: |%s|\n", s );
***/
     inispc();
     fileone=fopen(".Bses","w");
     fputs("13\n",fileone);
     fclose(fileone);
     filetwo=fopen(".BBcom","w");
     filethree=fopen(".Bpob","r");
     filefour=fopen(".Btac","r");
     one_filetwo();
     two_filetwo();
     three_filetwo();
     fclose(filetwo);
     fclose(filethree);
     strcpy(s,argv[2]);
     strcat(s,"/BPLAT/bplatform ");
     strcat(s,"r");
     strcat(s,"R");
     strcat(s,"1");
     strcat(s,"H");
     strcat(s,"1");
     strcat(s,"p");
     strcat(s,"p");
     strcat(s," < .BBcom > .Berr ; rm -f .BBcom");
     system(s);
/***
printf ( "Proof.c 2: |%s|\n", s );
***/
     fileone=fopen(".Berr","r");
     filetwo=fopen(".Bprf","w");
     read_ini();
     ins();
     fclose(fileone);
     fclose(filetwo);
     fclose(filefour);
     fileone=fopen(".Bses","w");
     fputs("13\n",fileone);
     fclose(fileone);
     system("rm -f .Berr");
/*
     fputs(".",stdout);
     fflush(stdout);
*/
     spc();
   }
   else {
     filetwo=fopen(".BBcom","w");
     filethree=fopen(".Bpob","r");
     filefour=fopen(".Btac","r");
     one_filetwo();
     two_filetwo();
     three_filetwo();
     fclose(filetwo);
     fclose(filethree);
     strcpy(s,argv[1]);
     strcat(s,"/BPLAT/bplatform ");
     strcat(s,"r");
     strcat(s,"R");
     strcat(s,"1");
     strcat(s,"H");
     strcat(s,"1");
     strcat(s,"p");
     strcat(s,"p");
     strcat(s," < .BBcom > .Berr ; rm -f .BBcom");
     system(s);
/***
printf ( "Proof.c 3: |%s|\n", s );
***/
     fileone=fopen(".Berr","r");
     filetwo=fopen(".Bprf","w");
     read_ini();
     ins();
     fclose(fileone);
     fclose(filetwo);
/***
printf ( ".Bprf:\n" );
system ( "cat .Bprf" );
***/
     fclose(filefour);
     fileone=fopen(".Bses","w");
     fputs("13\n",fileone);
     fclose(fileone);
     system("rm -f .Berr");
/*
     fputs(".",stdout);
     fflush(stdout);
*/
     spc();
   }

/***
system ( "ls -alrt" );
***/
    return 0;
}
