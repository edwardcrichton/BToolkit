/* Copyright (c) 1992-96, B-Core (UK) Ltd
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
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <syslog.h>
#include <unistd.h>
#include <pwd.h>

#define max_count 5000

/* char buf [ 250 ];  already in BMotif_globals.c */

extern int cv1 [];
extern int cv1r [];
extern int cv2 [];
extern int cv2r [];

/* lid */
extern int t0a [];
/* doi */
extern int t1a [];
/* dom */
extern int t2a [];
/* lad */
extern int t3a [];
/* cnt */
extern int t5a [];
/* nul */
extern int t6a [];
/* hid */
extern int t7a [];
/* nou */
extern int t8a [];
/* doe */
extern int t9a [];
/* day */
extern int tda [];
/* lct */
extern int tca [];
extern int hiipa [];

/*FILE * data_file_ptr;*/
/* should be extern? */

#ifndef H_DATA_FILE_PTR

#define H_DATA_FILE_PTR
extern FILE * data_file_ptr;
#endif

extern int i, j, k, c, ok, kkk;
extern time_t tt, t_, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, tc;
extern int btd_id, blic_id;
extern int chk;
extern struct stat stat_buf;
extern struct tm * tm_struct_n;
extern struct tm tm_struct_i;
extern struct tm tm_struct_e;

#if ( !defined ( AIX_VERSION ) && !defined ( LINUX_VERSION ) && !defined ( IRIX_VERSION ) )
extern char time__zone [];
#endif /* ( !defined ( AIX_VERSION ) && !defined ( LINUX_VERSION ) && !defined ( IRIX_VERSION ) ) */

#define max_hiip 100
#define hi_store 375
#define ps_store ( hi_store + ( 18 * max_hiip ) )
#define ma_max   ( ps_store + ( 36 * max_hiip ) )
extern int ma [];

/*
now in BMotif_version.c
#define lock_file_name             "/tmp/.Btkd_pid"
*/
#define port_file_name             "/B_port"
#define default_port               2107
#define Btkd_server_file_name      "/B_server"

#define STR   1
#define NUM   2



extern char licence_file [];
extern char alex_data_file [];  

#define shutdown_all 2

#define BTd_id_BT_id_check           379
#define count_request                579
#define non_count_request            207
#define hiip_request                 332
#define pre_init_request             111
#define init_request                 129
#define chk_vers_request             928
#define user_uid_request             156
#define user_name_request            190
#define BPInfo_remove                339
#define fini_request                 188
#define rem_zombie_request           404
#define Bpda_time_request            771
#define am_anonymous_server_request  499
#define BToolkitd_util_status    711
#define BToolkitd_util_down      610
#define BToolkitd_util_remove    391
#define BToolkitd_util_reread    288
#define BToolkitd_util_generate  598

extern int num_hiip;

extern int is_alex_or_not;
#define is_not_alex     ma [ 1 ] == 1
#define is_alex         ma [ 1 ] == 0

#ifndef BTOOL_FLAG
#define bstdout stdout
#endif /* BTOOL_FLAG */

extern char install_string       [];
extern char expiry_string        [];
extern char hiarr                [] [ 19 ];
extern char max_count_string     [];
extern char null_string          [];
extern char days_string          [];
extern char manufacture_string   [];

#define sock_buf_len_MAX 600
extern char sock_buf  [];
extern int sock_buf_len;
/*
extern char * sock_buf_ptr;
*/

extern int calloc_performed;
extern long unsigned * actual_ip_arr;
extern int * user_id_arr;
#define user_name_len 50
extern char * user_name_arr;
extern time_t * user_time_arr;

#define LIC_FILE_SIZE_REL_5 1858

extern int btd_major_version_num, btd_minor_version_num, btd_minor_minor_version_num,
       btd_minor_minor_minor_version_num;

extern int lic_major_version_num, lic_minor_version_num, lic_minor_minor_version_num,
       lic_minor_minor_minor_version_num;

extern char argv1 [];
extern int argv2;

#define alex_data_file_loc  "/BLIB/LIB/CDE/C/.bplat"
#define MIN_alex_data_file_len 50
