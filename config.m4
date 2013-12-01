PHP_ARG_WITH(pinyin, for pinyin support,
Make sure that the comment is aligned:
[  --with-pinyin             Include pinyin support])

if test "$PHP_PINYIN" != "no"; then
  PHP_NEW_EXTENSION(pinyin, pinyin.c, $ext_shared)
fi
