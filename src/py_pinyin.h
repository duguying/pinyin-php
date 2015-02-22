#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

#ifndef _PINYIN_MOD_H_
#define _PINYIN_MOD_H_

#define MAX_LEN 10000
#define MAX_CUT_LEN 10

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

int free_buffer(char* buffer);

void pinyin_destroy(PinTable * dict);

void load_char(const char* filename, PinTable * dict);

void load_word(const char* filename, PinTable * dict);

#endif
