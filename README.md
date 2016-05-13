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

## configuration
add following into `php.ini`

```
pinyin.chars=/path/to/chars.csv
pinyin.words=/path/to/words.csv
pinyin.locale="en_GB.UTF-8"		[optional]
```

## usage

```php
<?php
echo pinyin("汉"),"\n";
echo pinyin("わたしわ阿飞, and my English name is Rex Lee. 网名是独孤影！ ^_^。下面是一段多音分词歧义测试，这个人无伤无臭味。"),"\n";
?>
```

# License #

MIT License


