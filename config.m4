PHP_ARG_WITH(pinyin, for pinyin support,
[  --with-pinyin             Include pinyin support])

dnl cd ./pinyin/
dnl make
dnl cd ..

PHP_ADD_INCLUDE(pinyin)

dnl PHP_ADD_LIBPATH(pinyin, PINYIN_SHARED_LIBADD)
dnl PHP_ADD_LIBRARY(pinyin,pinyin, PINYIN_SHARED_LIBADD)
dnl PHP_SUBST(PINYIN_SHARED_LIBADD)

dnl if test "$PHP_PINYIN" != "no"; then
  PHP_NEW_EXTENSION(pinyin, pinyin.c \
							pinyin/hashtable.c \
							pinyin/pinyin.c \
					,$ext_shared)
dnl fi
