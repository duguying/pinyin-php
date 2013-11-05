#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "./pinyin.inc"

#ifndef FUNS_C
#define FUNS_C
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
char g_ch[3];//keep the var as global
char* cutCnChar(char* cncharlist,int i){
	int length;
	int start;
	start=i*2;
	length=strlen(cncharlist)/2;
	g_ch[0]='\0';g_ch[1]='\0';g_ch[2]='\0';
	if(i>length){
		g_ch[0]=0;
		return g_ch;
	}
	g_ch[0]=*(cncharlist+start);
	g_ch[1]=*(cncharlist+start+1);
	g_ch[2]=0;
	return g_ch;
}
/**
 * cut the chinese pinyin char
 * @param char*	pinyin the pinyin charlist
 * @param int i	the ith pinyin
 * @return char*	the pinyin
 */
char g_buf[8];//global buffer
char* cutPinyin(char* pinyin,int i){
	int c=0;//count the separative sign
	int length=strlen(pinyin);
	int n,m;
	for(c=0;c<8;c++){
		g_buf[c]='\0';
	}//initialize buffer with 0
	c=0;
	m=0;//buffer increase
	if(i>length){
		return g_buf;
	}
	for(n=0;n<length;n++){
		if(DE==pinyin[n]){
			g_buf[m]=0;//stop the string with '\0'
			c++;
		}else{
			if(c==i){
				g_buf[m]=pinyin[n];
				m++;
			}
		}
	}
	return g_buf;
}
/**
 * The long Link contain all the chinese character
 * @param char*	cnchar	the chinese charlist
 * @param char*	pinyin	the chinese pinyin charlist
 * @param char*	py	the pinyin alphabet list
 * @param struct cchar*		the longlink of the whole chinese chracter and pinyin
 */
cchar* createLongLink(cchar* longlink,char* cnchar,char* pinyin,char* py){
	int length,i;
	cchar* llp;
	llp=longlink;
	length=strlen(cnchar)/2;
	for(i=0;i<length;i++){//TODO
		strncpy(llp->cnch,cutCnChar(cnchar,i),3);
		strncpy(llp->piny,cutPinyin(pinyin,i),8);
		strncpy(llp->pyab,cutPinyin(py,i),7);
		if(0!=llp->next){
			llp=llp->next;
		}
	}
	//longlink[i].next=0;//set the last node's `next` pointer as null
	llp->next=0;
	return longlink;//return the longlist struct
}
/**
 * search the target node(`a struct`) by the key which is a chinese character
 * @param cchar* longlist	the longlist list
 * @param char* key			the key chinese character
 * @return cchar*	the target list
 */
cchar* searchCnChar(cchar* longlink, char* key){
	cchar* result=0;
	cchar* rst=0;
	while(longlink){
		if(!strcmp(key,longlink->cnch)){//use strcmp to compare whether the two string is equal, mark `==` is not right
			if(0==result){
				result=longlink;
				rst=result;
			}else{
				result->next=longlink;
				result=result->next;
			}
		}
		if(longlink->next){
			longlink=longlink->next;
		}else{
			break;
		}
	};
	if(result){
		result->next=0;//close the result link
	}
	return rst;
}



#endif
