#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

#ifndef _PINYIN_MOD_H_
#define _PINYIN_MOD_H_

#define DE '|'
#define MAX_LEN 10000
#define MAX_CUT_LEN 10
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
 * translate chinese sentence into pinyin
 * @param  raw raw string
 * @return     pinyin string
 */
char* pinyin_translate(char* raw, PinTable * dict);

void pinyin_destroy(PinTable * dict);

#endif
