#include <stdio.h>
#include "../funs.c"

/**
 * main function
 * program entrance
 */
int main(int argc, char** argv){
	cchar* rs;
	int i,length;
	cchar* ll;
	length=strlen(cnchar)/2;
	ll=(cchar*)malloc(sizeof(cnchar)*length);
	for(i=0;i<10000;i++){
		createLongLink(ll,cnchar,pinyin,py);
		if(3==argc){
			if(!strcmp(argv[1],"-s")){
				rs=searchCnChar(ll,argv[2]);
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
	}
	return 0;
}

