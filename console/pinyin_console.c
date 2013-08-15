#include <stdio.h>
#include "../pinyin.inc"

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
 * @param char*	cnchar	the chinese charlist
 * @param char*	pinyin	the chinese pinyin charlist
 * @param char*	py	the pinyin alphabet list
 * @param struct cchar*		the longlink of the whole chinese chracter and pinyin
 */
cchar* createLongLink(char* cnchar,char* pinyin,char* py){
	int length,i;
	length=strlen(cnchar)/2;
	cchar* longlink=(cchar*)malloc(sizeof(cnchar)*length);
	for(i=0;i<length;i++){
		strcpy(longlink[i].cnch,cutCnChar(cnchar,i));
		strcpy(longlink[i].piny,cutPinyin(pinyin,i));
		strcpy(longlink[i].pyab,cutPinyin(py,i));
		longlink[i].next=&longlink[i+1];
	}
	longlink[i].next=0;//set the last node's `next` pointer as null
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
/**
 * main function
 * program entrance
 */
int main(int argc, char** argv){
	cchar* ll=createLongLink(cnchar,pinyin,py);
	if(3==argc){
		if(!strcmp(argv[1],"-s")){
			cchar* rs=searchCnChar(ll,argv[2]);
			while(rs){
				printf("%s:%s %s\n",rs->cnch,rs->piny,rs->pyab);
				if(rs->next){
					rs=rs->next;
				}else{
					break;
				}
			}
		}
	}
	return 0;
}

