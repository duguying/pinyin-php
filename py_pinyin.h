#include <stdio.h>
#include <stdlib.h>
#include "py_hashtable.h"


#ifndef _PINYIN_MOD_H_
#define _PINYIN_MOD_H_


#define DE '|'
#define MAX_LEN 10000
#if defined _WIN32
	#define JMP 2
#else
	#define JMP 3
#endif

///dictionary
i_HashTable dict;

/**
 * initialize pinyin
 * @return
 */
i_HashTable* pinyin_init();

/**
 * get pinyin by chinese char
 * @param  cn chinese char
 * @return pinyin string
 */
char* pinyin_get(char* cn);

void pinyin_destroy();

#endif
