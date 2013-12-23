all:
	echo "\033[32;1mprecompile the static library...\033[0m"
	gcc -c hashtable.c -fPIC
	gcc -c pinyin.c -fPIC
	ar r libpinyin.a pinyin.o hashtable.o
	echo "\033[33;1mprecompiled over!\033[0m"
clean:
	rm *.o
	rm *.la