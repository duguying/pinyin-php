#include <stdio.h>
#include "pinyin.inc"
#include "pinyin.h"

#define DE '|'
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
 * @param char*	cncharlist the chinese character list
 * @param int	i the ith chinese character
 * @return char*	the chinese character
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
 * cut the chinese pinyin char
 * @param char*	pinyin the pinyin charlist
 * @param int i	the ith pinyin
 * @return char*	the pinyin
 */
char* cutPinyin(char* pinyin,int i){
	int c=0;//count the separative sign
	int length=strlen(pinyin);
	int n;
	char buf[8]={'\0','\0','\0','\0','\0','\0','\0','\0'};
	int m=0;//buffer increase
	for(n=0;n<length;n++){
		if(DE==pinyin[n]){
			c++;
		};
		if(c==i){
			if(DE!=pinyin[n]){
				buf[m]=pinyin[n];
				m++;
			}
		}
	}
	printf("%s\n",buf);
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
	//char* ch=cutCnChar(cnchar,2);
	//printf("%s",ch);
	//createLongLink(cnchar,pinyin,py);
	cutPinyin(pinyin,0);
	cutPinyin(pinyin,1);
	cutPinyin(pinyin,2);
	return 0;
}

