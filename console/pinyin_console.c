#include <stdio.h>
#include "../funs.c"

/**
 * main function
 * program entrance
 */
int main(int argc, char** argv){
	 
	pinyin_init();
	
	char pinyin_char[8];
	HashNode *pNode = hash_table_lookup("胫");
	get_pinyin(pinyin_char, pNode->nValue+1);
	printf("lookup result:%s\n", pinyin_char);
	pNode = hash_table_lookup("一");
	get_pinyin(pinyin_char, pNode->nValue+1);
	printf("lookup result:%s\n", pinyin_char);
	pNode = hash_table_lookup("龠");
	get_pinyin(pinyin_char, pNode->nValue+1);
	printf("lookup result:%s\n", pinyin_char);
	
	return 0;
}

