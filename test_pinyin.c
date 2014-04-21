#include "stdio.h"
#include "py_pinyin.h"

int main(int argc, char const *argv[])
{
	char* rst;int i=0;char* source="わたしわ李俊, and my English name is Rex Lee. 网名是独孤影！ ^_^";
	
	pinyin_init();

	/*for (i = 0; i < 2; ++i)
	{
		if (source[i]<0)
		{
			printf("%d\n", source[i]);
		}
	}*/
	
	rst=pinyin_get(source);
	printf("%s\n%s", source, rst);

	return 0;
}