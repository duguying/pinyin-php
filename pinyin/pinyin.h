#include <stdio.h>
#include <stdlib.h>

/**
 * initialize pinyin
 * @return
 */
int pinyin_init();

/**
 * get pinyin by chinese char
 * @param  cn chinese char
 * @return pinyin string
 */
char* pinyin_get(char* cn);