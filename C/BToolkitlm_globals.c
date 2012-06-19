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

int cv1 []  = { 5, 3, 6, 1, 0, 9, 2, 7, 4, 8 };
int cv1r [] = { 4, 3, 6, 1, 8, 0, 2, 7, 9, 5 };
int cv2 []  = { 9, 3, 5, 1 ,0, 7, 2, 6, 4, 8 };
int cv2r [] = { 4, 3, 6, 1, 8, 2, 7, 5, 9, 0 };

/*** tca = (tom) ***/
int tca [] = { 255, 37, 170, 62, 97, 151, 175, 199, 189, 162, 23, 133, 148, 157, 118, 126, 182, 244 };

/*** t0a = ( lit) ***/
int t0a [] = { 234, 71, 29, 99, 32, 112, 26, 221, 18, 78, 140, 41, 86, 51, 125, 57, 34, 84 };

/*** t1a = (toi) ***/
int t1a [] = { 43, 217, 132, 90, 135, 10, 27, 188, 87, 61, 220, 22, 168, 123, 85, 63, 55, 150 };

/*** t3a = (lat) ***/
int t3a [] = { 250, 72, 16, 12, 122, 222, 45, 20, 83, 201, 177, 105, 15, 11, 233, 147, 77, 39 };

/*** t5a = (cnt) ***/
int t5a [] = { 58, 94, 24, 160, 143, 64, 236, 165, 47, 149, 289, 212, 225, 100, 52, 40, 31, 176 };

/*** t6a = (zer) ***/
int t6a [] = { 74, 192, 130, 136, 19, 224, 205, 69, 54, 245, 154, 89, 35, 163, 67, 213, 152, 197 };

/*** t9a = (exp) ***/
int t9a [] = { 193, 145, 48, 185, 200, 91, 65, 159, 178, 214, 242, 251, 210, 202, 50, 95, 25, 17 };

/*** tda = (day) ***/
int tda [] = { 13, 183, 155, 187, 223, 79, 73, 28, 231, 167, 129, 139, 158, 141, 120, 113, 104, 203 };





/*** t2 = ?  ***/
int t2a [] = { 194, 156, 66, 173, 230, 181, 49, 238, 44, 107, 101, 96, 127, 196, 88, 70, 33, 46 };

/*** t7 hid ? ***/
int t7a [] = { 56, 171, 82, 80, 38, 169, 109, 134, 184, 93, 166, 30, 59, 190, 76, 110, 53, 198 };

/*** t8 = ( ? ) ***/
int t8a [] = { 14, 36, 180, 241, 195, 153, 98, 60, 68, 253, 204, 164, 137, 114, 117, 172, 232, 235 };

int hiipa [] = { 10, 15, 6, 17, 1, 5, 3, 9, 12, 19, 7, 14, 16, 8, 11, 13, 4, 2, 18 };

FILE * data_file_ptr;
int i, j, k, c, ok, kkk;
time_t tt, t_, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, tc;
int btd_id, blic_id;
int chk;
struct stat stat_buf;
struct tm * tm_struct_n;
struct tm tm_struct_i;
struct tm tm_struct_e;

#if ( !defined ( AIX_VERSION ) && !defined ( LINUX_VERSION ) && !defined ( IRIX_VERSION ) )
char time__zone [ 250 ];
#endif /* ( !defined ( AIX_VERSION ) && !defined ( LINUX_VERSION ) && !defined ( IRIX_VERSION ) ) */

#define max_hiip 100
#define hi_store 375
#define ps_store ( hi_store + ( 18 * max_hiip ) )
#define ma_max   ( ps_store + ( 36 * max_hiip ) )
int ma [ ma_max ];

/*
now in BMotif_version.c
#define lock_file_name             "/tmp/.Btkd_pid"
*/
#define port_file_name             "/B_port"
#define default_port               2107
#define Btkd_server_file_name      "/B_server"

#define STR   1
#define NUM   2


char licence_file [ 500 ];
char alex_data_file [ 500 ];  

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

int num_hiip;

int is_alex_or_not;
#define is_not_alex       ma [ 1 ] == 1
#define is_alex           ma [ 1 ] == 0

#ifndef BTOOL_FLAG
#define bstdout stdout
#endif /* BTOOL_FLAG */

char install_string       [  9 ];
char expiry_string        [  9 ];
char hiarr        [ 100 ] [ 19 ];
char max_count_string     [  9 ];
char null_string          [  9 ];
char days_string          [  9 ];
char manufacture_string   [ 13 ];

#define sock_buf_len_MAX 600
char sock_buf  [ sock_buf_len_MAX + 1 ];
int sock_buf_len;

int calloc_performed = 0;
long unsigned * actual_ip_arr;
int * user_id_arr;
#define user_name_len 50
char * user_name_arr;
time_t * user_time_arr;

#define LIC_FILE_SIZE_REL_5 1858

int btd_major_version_num, btd_minor_version_num, btd_minor_minor_version_num,
    btd_minor_minor_minor_version_num;

int lic_major_version_num, lic_minor_version_num, lic_minor_minor_version_num,
    lic_minor_minor_minor_version_num;

char argv1 [ 250 ];
int argv2;

#define alex_data_file_loc  "/BLIB/LIB/CDE/C/.bplat"
#define MIN_alex_data_file_len 50
