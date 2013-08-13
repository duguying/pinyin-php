#include <stdio.h>
#include "pinyin.inc"

/**
 * The struct of a single chinese character
 */
typedef struct character{
	char cnch[3];//a single character
	char piny[8];//the pinyin char of the character
	char pyab[7];//the pinyin alphabet of the character
	struct character* next;//point to the next character struct
} cchar;
/**
 * cut the chinese character
 * 2013-8-13
 * @param cncharlist the chinese character list
 * @param i the ith chinese character
 * @return the chinese character
 */
char* cutCnChar(char* cncharlist,int i){
	int length=sizeof(cncharlist)/2;
	int start;
	start=i*2;
	static char ch[3];//keep the var as static
	ch[0]=*(cncharlist+start);
	ch[1]=*(cncharlist+start+1);
	ch[2]=0;
	return ch;
}
/**
 * The long Link contain all the chinese character
 */
cchar* createLongLink(char* cnchar,char* pinyin,char* py){//TODO
	int i;
	cchar* head=(cchar*)malloc(sizeof(cchar));
	//head->cnch={cnchar[i],cnchar[i+1]};
	//printf(cnchar);
	return head;
}
/**
 * main function
 * program entrance
 */
int main(){
	char* ch=cutCnChar(cnchar,2);
	printf("%s",ch);
	createLongLink(cnchar,pinyin,py);
	return 0;
}

