#include <stdio.h>
#include "pinyin.h"

int main(void){
	char* rst;

	pinyin_init();
	rst=pinyin_get("原");
	
	printf("%s\n", rst);
	return 0;
}
