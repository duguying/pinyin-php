#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "py_hashtable.h"
#include "py_pinyin.h"
#include "pinyin.inc"

/**
 * initialize pinyin
 * @return
 */
i_HashTable* pinyin_init(i_HashTable* dict){
	int cn_count,pinyin_arr_count,pinyin_index,i,j,index[MAX_LEN];
	char tmp[4];

	memset(dict,0,sizeof(i_HashTable));
	ht_init(dict);

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
		char* tmp_py;

		memset(tmp, 0, sizeof(char)*4);
		strncpy(tmp, (cnchar+JMP*(i)), JMP);
		
		tmp_py=(pinyin+index[i]+1);

		ht_insert(dict, tmp, tmp_py);
	}

	//ht_print(dict);
	return dict;
}

/**
 * get pinyin by chinese char
 * @param  cn chinese char
 * @return pinyin string
 */
char* pinyin_get(i_HashTable* dict, char* cn){
	char single_cn_buf[JMP+1];
	unsigned int len=0;
	unsigned int len_pybuf=0;
	unsigned int flag_cnchar_buf=0;
	char* pybuf=NULL;
	char* pybuf_pos=NULL;
	unsigned int i=0;

	len=strlen(cn);
	len_pybuf=(len/2)*7+1;
	pybuf_pos=pybuf=(char*)malloc(len_pybuf);
	memset(pybuf,0,len_pybuf);
	memset(single_cn_buf,0,JMP+1);

	// strip ascii
	for (i = 0; i < len; ++i)
	{
		
		if(cn[i]<0){ // chinese char
			if((JMP-1)!=flag_cnchar_buf){
				single_cn_buf[flag_cnchar_buf]=cn[i];
				++flag_cnchar_buf;
			}else{
				char* single_cn_pinyin=NULL;
				unsigned int len_of_py=0;
				HashNode* result_node=NULL;
				
				single_cn_buf[flag_cnchar_buf]=cn[i];
				flag_cnchar_buf=0;
				// translate
				
				result_node=(HashNode*)ht_lookup(dict, single_cn_buf);
				
				if(NULL==result_node){
					len_of_py=strlen(single_cn_buf);
					strncpy(pybuf_pos,single_cn_buf,len_of_py);
					pybuf_pos+=len_of_py;
				}else{
					single_cn_pinyin=(char*)result_node->nValue;
					len_of_py=strlen(single_cn_pinyin);
					strncpy(pybuf_pos,single_cn_pinyin,len_of_py);
					pybuf_pos+=len_of_py;
				}

				memset(single_cn_buf, 0, JMP+1);
			}
		}else{ // other
			memset(pybuf_pos,cn[i],1);
			++pybuf_pos;
		}
	}

	return pybuf;
}

/**
 * @brief release the pinyin dictionary
 * @details [long description]
 * 
 */
void pinyin_destroy(i_HashTable* dict){
	ht_release(dict);
}
