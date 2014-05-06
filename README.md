# pinyin-php #

----------

[![Build Status](https://drone.io/github.com/duguying/pinyin-php/status.png)](https://drone.io/github.com/duguying/pinyin-php/latest) 
[![travis](https://api.travis-ci.org/duguying/pinyin-php.png)](https://travis-ci.org/duguying/pinyin-php)

***pinyin-php*** is a php extension which could translate Chinese character into Chinese PinYin.

## build and install ##
**linux**

build the extension<br>

```shell
phpize
configure
make
make test
```

**win32(cmake)**

使用cmake编译，首先，您必须确保您本地存在PHP SDK(这个SDK可以由您编译php得来)，以及目标php版本的静态库(如`php5ts.lib`)，您可以按以下步骤进行：

- 打开VC命令行(以目标版本为VC9为例)

- 若您的SDK版本与目标版本不一致，搜索文件`${PHPSDK}/include/main/config.w32.h`中的字符串`PHP_COMPILER_ID`，将该宏的定义改为对应目标版本标识，如此例为`VC9`。

- 设置`CMakeList.txt`中`add_definitions`的对应参数以符合自己的环境。

- 设置`CMakeList.txt`中`PHPSDK`路径。

- 在VC9命令行中编译：

	```shell
	mkdir build & cd build
	cmake -G"NMake Makefiles" ..
	nmake
	```

  如此便可得到php_pinyin.dll

**about**

the file `pinyin.inc`, it is a resource file. of course, you needn't change the file name or create a `pinyin.inc`, the file `pinyin.inc` will be built by a php script in the `/data/` directory. 

# License #

MIT License


