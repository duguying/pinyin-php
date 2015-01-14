#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

#ifndef _PINYIN_MOD_H_
#define _PINYIN_MOD_H_

#define DE '|'
#define MAX_LEN 10000
#if defined _WIN32
#define JMP 2
#else
#define JMP 3
#endif

/**
 * initialize pinyin
 * @return
 */
i_HashTable *pinyin_init(i_HashTable * dict);

/**
 * get pinyin by chinese char
 * @param  cn chinese char
 * @return pinyin string
 */
char *pinyin_get(i_HashTable * dict, char *cn);

void pinyin_destroy(i_HashTable * dict);

#endif
