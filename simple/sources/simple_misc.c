
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple_misc.c
 * Author: thecarisma
 *
 * Created on July 12, 2017, 3:34 PM
 */

#include "../includes/simple.h"

int NOT_CASE_SENSITIVE = 0 ;
int SKIP_ERROR = 0 ;
char *DEFAULT_FILE_NAME = "" ;
char *DEFAULT_FILE_PATH = "" ;

int list_index = 0 ;
char* time_frame = "seconds" ;

SIMPLE_API void print_line ( void )
{
    puts("============================================================================================="); 
}

void display_help(){
    printf("Usage:  simple ([OPTIONS]) [PATH] [ARGS...]\n");
    printf("\t\t\t<to run a simple or complex file>\n\n");
    printf("[PATH]     : The Simple/Complex source file to execute.\n");
    printf("[ARG...]   : The arguments to pass to your simple application.\n");
    printf("([OPTIONS]): The flags/options to pass to the Simple VM/Simplify.\n\n");
    printf("The OPTIONS include : \n");
    printf("  -h -help                    Displays this help and exits.\n");
    printf("  -k -show-tokens             Scans and outputs the tokens in the source file.\n");
    //printf("  -s -simplify                Compile simple file to one complex file.\n");
    printf("  -t -time                    Shows time before and after program execution.\n");
    printf("  -c -case-insensitive        Make simple case insensitive 'a=A'.\n");
    printf("  -v -verbose                 Displays all the modules and libraries of SIMPLE and exits.\n");
    printf("  -a -about                   Display the SIMPLE Property and exits.\n");
    printf("  -l -license                 Print the current SIMPLE LICENCE and exits.\n");
    //printf("  -n -no-run                  Compile the program but don't run it.\n");
    //printf("  -b -byte-code               Print the program Byte Code after compilation.\n");
    printf("  -e -error                   Skip all error instance and print error report in console.\n");
    //printf("  -l [PATH] -log-error [PATH] Skip all error instance and print error report in file.\n");
    //print_line(); printf("MORE OPTION BELOW"); print_line(); 
    //printf("\t-k [PATH] -show-tokens [PATH]             Save the token into a file for debugging.\n");
    exit(0);
}

void display_licence(){
    print_line();
    printf("\t\tSimple Intelligent and Modular Programming Language \n"
            "\t\tSIMPLE v%s | %s | %d - %d\n"
            , SIMPLE_VERSION, PRIMARY_AUTHOR, START_YEAR, CURRENT_YEAR);
    print_line();
    printf("\n\t\t\t\t\tMIT License\n\n");
    printf("\t\t\t\tCopyright (c) %d - %d simple\n\n",START_YEAR, CURRENT_YEAR);
    printf("\tPermission is hereby granted, free of charge, to any person obtaining a copy\n"
            "\tof this software and associated documentation files (the \"Software\"), to deal\n"
            "\tin the Software without restriction, including without limitation the rights\n"
            "\tto use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
            "\tcopies of the Software, and to permit persons to whom the Software is\n"
            "\tfurnished to do so, subject to the following conditions:\n\n"
            "\tThe above copyright notice and this permission notice shall be included in all\n"
            "\tcopies or substantial portions of the Software.\n\n"
            "\tTHE SOFTWARE IS PROVIDED\"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
            "\tIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
            "\tFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
            "\tAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
            "\tLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
            "\tOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
            "\tSOFTWARE.\n"); 
    print_line(); exit(0);
}

void display_about(){
    print_line();
    printf("\t\tSimple Intelligent and Modular Programming Language - SIMPLE\n"
            "\tVERSION  : v%s\n"
            "\tAUTHOR   : %s\n"
            "\tLICENCE  : %s\n"
            "\tDATE     : %d - %d\n"
            , SIMPLE_VERSION, PRIMARY_AUTHOR, SIMPLE_LICENCE, START_YEAR, CURRENT_YEAR);
    print_line();
    exit(0);
}

int is_simple_file( const char *file_name )
{
    int x  ; 
    x = strlen(file_name) - 1 ;
    if ( x >= 5 ) {
        if ( tolower(file_name[x]) == 'm' && tolower(file_name[x-1]) == 'i' && tolower(file_name[x-2]) == 's' && tolower(file_name[x-3]) == '.'  ) {
            return 1 ;
        }
    }
    return 0 ;
}

int is_complex_file( const char *file_name )
{
    int x ;
    x = strlen(file_name) - 1 ;
    if ( x > 6 ) {
        if ( tolower(file_name[x]) == 'x' && tolower(file_name[x-1]) == 'e' && tolower(file_name[x-2]) == 'l' && tolower(file_name[x-3]) == 'm' && tolower(file_name[x-4]) == 'o' && file_name[x-5] == 'c' && file_name[x-5] == '.' ) {
            return 1 ;
        }
    } 
    return 0 ;
}

const char *file_real_name(const char *absolute_name){
    char *filename = (char*)calloc(1, sizeof(KB_BYTE_SIZE));
    if (strstr(absolute_name, "\\") != NULL ) {
        filename = (strrchr(absolute_name, '\\'))+1;
    } else if (strstr(absolute_name, "/") != NULL ) {
        filename = (strrchr(absolute_name, '/'))+1;
    } else {
		return absolute_name;
	}

    return filename;
}

const char *change_file_ext(const char *absolute_name, const char *extension){
    const char* file_name = file_real_name(absolute_name); int name_lenght = strlen(file_name);
    const char *name = "" ; int a ;
    for(a = 0; a<name_lenght;a++) {
        if (file_name[a] == '.'){
            break;
        }
        //name[a] = file_name[a];
    }
    return name;
}

void simple_showtime ( clock_t before_execution)
{
    clock_t after_execution = clock();
    float seconds = get_time_different((float)(after_execution - before_execution) / CLOCKS_PER_SEC);
    printf("\nExecution Time : %.5f %s", seconds, time_frame);
}

float get_time_different(float current_seconds) { 
    if (current_seconds > 60 && current_seconds < 3600) {
        time_frame = "minutes" ; return (current_seconds / 60 );  
    }
    return current_seconds ;
}

void get_file_folder ( char *absolute_path ) {
	char cDir2[SIMPLE_PATHSIZE]  ;
	int x,x2,nSize  ;
	nSize = strlen( absolute_path ) ;
	for ( x = nSize-1 ; x >= 0 ; x-- ) {
		if ( (absolute_path[x] == '\\') || (absolute_path[x] == '/') ) {
			for ( x2 = x ; x2 >= 0 ; x2-- ) {
				cDir2[x2] = absolute_path[x2] ;
			}
			cDir2[x+1] = '\0' ;
			break ;
		}
	}
	strcpy(absolute_path,cDir2);
}

unsigned simple_hash(unsigned pid)
{
    return pid / 1000 % 100;
}

unsigned simple_add_hash(unsigned char *key, int len)
{
    unsigned char *p = key;
    unsigned h = 0;
    int i;

    for (i = 0; i < len; i++)
    {
        h += p[i];
    }

    return h;
}

unsigned simple_xor_hash(unsigned char *key, int len)
{
    unsigned char *p = key;
    unsigned h = 0;
    int i;

    for (i = 0; i < len; i++)
    {
        h ^= p[i];
    }

    return h;
}

unsigned simple_rot_hash(unsigned char *key, int len)
{
    unsigned char *p = key;
    unsigned h = 0;
    int i;

    for (i = 0; i < len; i++)
    {
        h = (h << 4) ^ (h >> 28) ^ p[i];
    }

    return h;
}

unsigned simple_djb_hash(unsigned char *key, int len)
{
    unsigned char *p = key;
    unsigned h = 0;
    int i;

    for (i = 0; i < len; i++)
    {
        h = 33 * h ^ p[i];
    }

    return h;
}

unsigned simple_sax_hash(unsigned char *key, int len)
{
    unsigned char *p = key;
    unsigned h = 0;
    int i;

    for (i = 0; i < len; i++)
    {
        h ^= (h << 5) + (h >> 2) + p[i];
    }

    return h;
}

unsigned simple_oat_hash(unsigned char *key, int len)
{
    unsigned char *p = key;
    unsigned h = 0;
    int i;

    for (i = 0; i < len; i++)
    {
        h += p[i];
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);
    return h;
}

unsigned simple_elf_hash(unsigned char *key, int len)
{
    unsigned char *p = key;
    unsigned h = 0, g;
    int i;

    for (i = 0; i < len; i++)
    {
        h = (h << 4) + p[i];
        g = h & 0xf0000000L;

        if (g != 0)
        {
            h ^= g >> 24;
        }

        h &= ~g;
    }

    return h;
}

#define hashsize(n) (1U << (n))
#define hashmask(n) (hashsize(n) - 1)

#define mix(a,b,c) \
{ \
    a -= b; a -= c; a ^= (c >> 13); \
    b -= c; b -= a; b ^= (a << 8); \
    c -= a; c -= b; c ^= (b >> 13); \
    a -= b; a -= c; a ^= (c >> 12); \
    b -= c; b -= a; b ^= (a << 16); \
    c -= a; c -= b; c ^= (b >> 5); \
    a -= b; a -= c; a ^= (c >> 3); \
    b -= c; b -= a; b ^= (a << 10); \
    c -= a; c -= b; c ^= (b >> 15); \
}

unsigned simple_jen_hash(unsigned char *k, unsigned length, unsigned initval)
{
    unsigned a, b;
    unsigned c = initval;
    unsigned len = length;

    a = b = 0x9e3779b9;

    while (len >= 12)
    {
        a += (k[0] + ((unsigned)k[1] << 8) + ((unsigned)k[2] << 16) + ((unsigned)k[3] << 24));
        b += (k[4] + ((unsigned)k[5] << 8) + ((unsigned)k[6] << 16) + ((unsigned)k[7] << 24));
        c += (k[8] + ((unsigned)k[9] << 8) + ((unsigned)k[10] << 16) + ((unsigned)k[11] << 24));

        mix(a, b, c);

        k += 12;
        len -= 12;
    }

    c += length;

    switch (len)
    {
    case 11: c += ((unsigned)k[10] << 24);
    case 10: c += ((unsigned)k[9] << 16);
    case 9: c += ((unsigned)k[8] << 8);
        /* First byte of c reserved for length */
    case 8: b += ((unsigned)k[7] << 24);
    case 7: b += ((unsigned)k[6] << 16);
    case 6: b += ((unsigned)k[5] << 8);
    case 5: b += k[4];
    case 4: a += ((unsigned)k[3] << 24);
    case 3: a += ((unsigned)k[2] << 16);
    case 2: a += ((unsigned)k[1] << 8);
    case 1: a += k[0];
    }

    mix(a, b, c);

    return c;
}

unsigned int simple_murmur3_32(const char *key, unsigned int len, unsigned int seed) {
	static const unsigned int c1 = 0xcc9e2d51;
	static const unsigned int c2 = 0x1b873593;
	static const unsigned int r1 = 15;
	static const unsigned int r2 = 13;
	static const unsigned int m = 5;
	static const unsigned int n = 0xe6546b64;

	unsigned int hash = seed;

	const int nblocks = len / 4;
	const unsigned int *blocks = (const unsigned int *) key;
	int i;

	const unsigned char *tail ;
	unsigned int k1 = 0;

	for (i = 0; i < nblocks; i++) {
		unsigned int k = blocks[i];
		k *= c1;
		k = (k << r1) | (k >> (32 - r1));
		k *= c2;

		hash ^= k;
		hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
	}

	tail = (const unsigned char *) (key + nblocks * 4);

	switch (len & 3) {
	case 3:
		k1 ^= tail[2] << 16;
	case 2:
		k1 ^= tail[1] << 8;
	case 1:
		k1 ^= tail[0];

		k1 *= c1;
		k1 = (k1 << r1) | (k1 >> (32 - r1));
		k1 *= c2;
		hash ^= k1;
	}

	hash ^= len;
	hash ^= (hash >> 16);
	hash *= 0x85ebca6b;
	hash ^= (hash >> 13);
	hash *= 0xc2b2ae35;
	hash ^= (hash >> 16);

	return hash;
}

