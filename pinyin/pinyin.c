#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "pinyin.h"
#include "../pinyin.inc"

/**
 * initialize pinyin
 * @return
 */
int pinyin_init(){
	HashTable ht;
	memset(&ht,0,sizeof(HashTable));
	ht_init(&ht);
	return 0;
}

/**
 * get pinyin by chinese char
 * @param  cn chinese char
 * @return pinyin string
 */
char* pinyin_get(char* cn){
	return 0;
}
