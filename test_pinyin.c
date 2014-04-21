#include "stdio.h"
#include "py_pinyin.h"

int main(int argc, char const *argv[])
{
	char* rst;
	
	pinyin_init();
	rst=pinyin_get("Àî");
	printf("result:%s", rst);
	return 0;
}