pinyin:
	gcc -ggdb3 pinyin.c -o pinyin
test:
	./pinyin.exe
clean:
	rm pinyin.exe
	rm pinyin.exe.stackdump
