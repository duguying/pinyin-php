#include "stdio.h"
#include "py_pinyin.h"

int main(int argc, char const *argv[])
{
	char* source = "わたしわ李俊, and my English name is Rex Lee. 网名是独孤影！ ^_^。下面是一段多音分词歧义测试，这个人无伤无臭味。";
	char* pinyin = 0;

    PinTable dict;
	pinyin_init(&dict);
	pinyin = pinyin_translate(source);

    ht_print(&dict);

	return 0;
}
