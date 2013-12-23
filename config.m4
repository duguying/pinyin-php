PHP_ARG_WITH(pinyin, for pinyin support,
[  --with-pinyin             Include pinyin support])

cd ./pinyin/
make
cd ..

PHP_ADD_INCLUDE(pinyin)
PHP_ADD_LIBRARY_WITH_PATH(pinyin, pinyin, PINYIN_LIBADD)

echo $PHP_PINYIN

if test "$PHP_PINYIN" != "no"; then
  PHP_NEW_EXTENSION(pinyin, pinyin.c, $ext_shared)
fi
