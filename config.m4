PHP_ARG_WITH(pinyin, for pinyin support,
[  --with-pinyin             Include pinyin support])

cd ./pinyin/
make
cd ..

if test "$PHP_PINYIN" != "no"; then
  PHP_NEW_EXTENSION(pinyin, pinyin.c, $ext_shared)
fi
