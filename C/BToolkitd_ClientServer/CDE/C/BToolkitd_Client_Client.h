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
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/utsname.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <syslog.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#ifndef INADDR_NONE
#define INADDR_NONE  0xffffffff
#endif /* INADDR_NONE */

extern char * BToolkitd_Client_ClientP1[];
extern int BToolkitd_Client_ClientP2;
extern int BToolkitd_Client_ClientP3;

extern char _out_buf [];
extern int _out_buf_ptr;

extern char _in_buf [];
extern int _in_buf_ptr;
extern int _in_buf_len;


#define INI_BToolkitd_Client_Client()   { _out_buf_ptr = 2; _in_buf_ptr = 2; }

void BToolkitd_Client_INIT ( void * _ipaddress, int _port );
void BToolkitd_Client_CONNECT ( int * _rep );
void BToolkitd_Client_WRITE ( int * _rep );
void BToolkitd_Client_READ ( int * _rep, int * _pp );
void BToolkitd_Client_CLOSE ( int * _rep );
void BToolkitd_Client_GET_TOK ( int * _tok, int _toksize );
void BToolkitd_Client_GET_STR ( int * _ss );
void BToolkitd_Client_GET_FIL ( int * _rep, int * _filename );
void BToolkitd_Client_PUT_TOK ( int _tok, int _toksize );
void BToolkitd_Client_PUT_STR ( int * _ss );
void BToolkitd_Client_GET_IN_PTR ( int * _ptr );
void BToolkitd_Client_SET_IN_PTR ( int _ptr );
void BToolkitd_Client_GET_OUT_PTR ( int * _ptr );
void BToolkitd_Client_SET_OUT_PTR ( int _ptr );
