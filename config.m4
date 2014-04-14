PHP_ARG_WITH(pinyin, for pinyin support,
[  --with-pinyin             Include pinyin support])

PHP_ADD_INCLUDE(pinyin)

PHP_NEW_EXTENSION(pinyin, pinyin.c \
						py_hashtable.c \
						py_pinyin.c \
				,$ext_shared)
