#include "stdio.h"
#include "py_pinyin.h"
#include <locale.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char* source = "わたしわ阿飞, and my English name is Rex Lee. 网名是独孤影！ ^_^。下面是一段多音分词歧义测试，这个人无伤无臭味磕头如捣蒜。";
	// char* source = "hello world, here is an English string to test buffer transfer. thank you.";
	char* pinyin = 0;

    PinTable dict;
	pinyin_init(&dict);

	printf("[source] \n%s\n\n", source);
	printf("[transl] \n");
	pinyin = pinyin_translate(source, &dict);

    // ht_print(&dict);

	char buf[256]={"わたしわ阿飞, and"};
	setlocale(LC_ALL,"zh_CN.UTF-8");
	wchar_t ar[256]={'\0'};
	int read = mbstowcs(ar,buf,strlen(buf)); 
	printf("%lu\n",strlen(buf)); //输出为：9 [字节] UF-8编码下一个汉字占三个字节3*3=9
	printf("%d\n",read); //输出为：3 [个数] “你好啊”三个子字个数

	return 0;
}
