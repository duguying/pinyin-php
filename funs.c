#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "./pinyin.inc"
#include "main/php.h"

#ifndef FUNS_C
#define FUNS_C
#define DE '|'
#define MAX_LEN 10000

void pinyin_init(zval* dict){
	int cn_count,pinyin_arr_count,pinyin_index;
	int index[MAX_LEN];
	char tmp[4];
	char pinyin_char[8];
	int i,j;
	
	array_init(dict);

	cn_count=strlen(cnchar)/3;
	pinyin_arr_count=strlen(pinyin);

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
	
	for(j=0;j<cn_count;j++){
		strtok(pinyin+index[j]+1,"|");
	}

	for (i = 0; i < cn_count; i++)
	{
		memset(tmp, 0, sizeof(char)*4);
		strncpy(tmp, (cnchar+3*(i)), 3);
		
		add_assoc_string(dict, tmp, (pinyin+index[i]+1), 1);
	}

}

#endif
