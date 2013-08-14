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
	int length=strlen(cncharlist)/2;
	int start;
	start=i*2;
	static char ch[3];//keep the var as static
	if(i>length){
		ch[0]=0;
		return ch;
	}
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
	static char buf[8]={'\0','\0','\0','\0','\0','\0','\0','\0'};
	int m=0;//buffer increase
	if(i>length){
		return buf;
	}
	for(n=0;n<length;n++){
		if(DE==pinyin[n]){
			buf[m]=0;//stop the string with '\0'
			c++;
		}else{
			if(c==i){
				buf[m]=pinyin[n];
				m++;
			}
		}
	}
	return buf;
}
/**
 * The long Link contain all the chinese character
 */
void createLongLink(char* cnchar,char* pinyin,char* py){
	int length,i;
	length=strlen(cnchar)/2;
	cchar* longlink=(cchar*)malloc(sizeof(cnchar)*length);
	for(i=0;i<length;i++){//TODO
		printf("%s|",cutCnChar(cnchar,i));
		printf("%s|",cutPinyin(pinyin,i));
		printf("%s|\n",cutPinyin(py,i));
	}
	//return head;
}
/**
 * main function
 * program entrance
 */
int main(){
	createLongLink(cnchar,pinyin,py);
	//printf("%s",cutPinyin(pinyin,3));
	return 0;
}

