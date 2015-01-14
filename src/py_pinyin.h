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
PinTable *pinyin_init(PinTable * dict);

/**
 * get pinyin by chinese char
 * @param  cn chinese char
 * @return pinyin string
 */
char *pinyin_get(PinTable * dict, char *cn);

void pinyin_destroy(PinTable * dict);

#endif
