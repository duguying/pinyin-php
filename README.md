# pinyin-php #

----------

[![Build Status](https://drone.io/github.com/duguying/pinyin-php/status.png)](https://drone.io/github.com/duguying/pinyin-php/latest)

***pinyin-php*** is a php extension which could translate Chinese character into Chinese PinYin.

## console application ##
before the extension file(`*.so`,`*.dll`) build, we will develop a console application for development and debug. <br>
**build**

1. build resource file, refer to `/data/README.md`
2. build the application<br>
```shell
cd pinyin-php/console/build
cmake
make
```<br>
3. build the extension<br>
```shell
phpize
configure
make
make test
```

**about**

the file `pinyin.inc`, it is a resource file. of course, you needn't change the file name or create a `pinyin.inc`, the file `pinyin.inc` will be built by a php script in the `/data/` directory. 

# License #

MIT License
