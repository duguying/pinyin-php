#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "./pinyin.inc"
#include "hashtable.c"

#ifndef FUNS_C
#define FUNS_C
#define DE '|'
#define MAX_LEN 10000

void get_pinyin(char pinyin_char[8], int index){
	memset(pinyin_char, 0, sizeof(char)*8);
	strncpy(pinyin_char, pinyin+index, 8);
	strtok(pinyin_char,"|");
}

void pinyin_init(){
	int cn_count,pinyin_arr_count,pinyin_index;
	int index[MAX_LEN];
	char tmp[3];
	int i,j;

	hash_table_init();
	cn_count=strlen(cnchar)/3;
	pinyin_arr_count=strlen(pinyin);
	printf("%d\n", cn_count);

	//scan pinyin
	pinyin_index=0;
	for (j = 0; j < pinyin_arr_count; j++)
	{
		if (pinyin[j]=='|')
		{
			index[pinyin_index]=j;
			pinyin_index++;
		}
	}

	for (i = 0; i < cn_count; i++)
	{
		memset(tmp, 0, sizeof(char)*3);
		strncpy(tmp, (cnchar+3*(i)), 3);
		hash_table_insert(tmp, index[i]);
	}

	 char pinyin_char[8];
	 HashNode *pNode = hash_table_lookup("胫");
	 get_pinyin(pinyin_char, pNode->nValue+1);
	 printf("lookup result:%s\n", pinyin_char);
	// pNode = hash_table_lookup("一");
	// get_pinyin(pinyin_char, pNode->nValue+1);
	// printf("lookup result:%s\n", pinyin_char);
	// pNode = hash_table_lookup("龠");
	// get_pinyin(pinyin_char, pNode->nValue+1);
	// printf("lookup result:%s\n", pinyin_char);
}

#endif
