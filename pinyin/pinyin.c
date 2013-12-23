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
i_HashTable* pinyin_init(){
	int cn_count,pinyin_arr_count,pinyin_index,i,j,index[MAX_LEN];
	char tmp[4];
	char pinyin_char[8];

	memset(&dict,0,sizeof(i_HashTable));
	ht_init(&dict);

	cn_count=strlen(cnchar)/3;
	pinyin_arr_count=strlen(pinyin);

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
		strtok(pinyin+index[j]+1,"|");//cnchar
	}


	for (i = 0; i < cn_count; i++)
	{
		memset(tmp, 0, sizeof(char)*4);
		strncpy(tmp, (cnchar+3*(i)), 3);
		
		ht_insert(&dict, tmp, (pinyin+index[i]+1));
	}

	return &dict;
}

/**
 * get pinyin by chinese char
 * @param  cn chinese char
 * @return pinyin string
 */
char* pinyin_get(char* cn){
	char cnc[3];
	memset(cnc,0,sizeof(char)*);
	strncpy(cnc,cn,2);
	return (char*)ht_lookup(&dict, cn)->nValue;
}

/**
 * @brief release the pinyin dictionary
 * @details [long description]
 * 
 */
void pinyin_destroy(){
	ht_release(&dict);
}