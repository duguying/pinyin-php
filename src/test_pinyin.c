#include "stdio.h"
#include "py_pinyin.h"

int main(int argc, char const *argv[])
{
	char* rst;int i=0;char* source="わたしわ李俊, and my English name is Rex Lee. 网名是独孤影！ ^_^";
	
    PinTable dict;
	pinyin_init(&dict);

    ht_print(&dict);

	return 0;
}
