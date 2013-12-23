PHP_ARG_WITH(pinyin, for pinyin support,
[  --with-pinyin             Include pinyin support])

cd ./pinyin/
make
cd ..

PHP_ADD_INCLUDE(pinyin)

PHP_ADD_LIBPATH(pinyin, PINYIN_SHARED_LIBADD)
PHP_ADD_LIBRARY(pinyin,pinyin, PINYIN_SHARED_LIBADD)
PHP_SUBST(PINYIN_SHARED_LIBADD)

if test "$PHP_PINYIN" != "no"; then
  PHP_NEW_EXTENSION(pinyin, pinyin.c ,$ext_shared)
fi
