# pinyin-php #

----------

***pinyin-php*** is a php extension which could translate Chinese character into Chinese PinYin.

## console application ##
before the extension file(`*.so`,`*.dll`) build, we will develop a console application for development and debug. <br>
**build**

1. build resource file, refer to `/data/README.md`
2. build the application<br>

```
$ make
$ make test
```

**about**

the file `pinyin.inc-example` should be `pinyin.inc`, it is a resource file. of course, you needn't change the file name or create a `pinyin.inc`, the file `pinyin.inc` will be built by a php script in the `/data/` directory. the file `pinyin.inc-example` just a reference for the developer, you can't get the variable in the file. it just for reference.

# License #

MIT License