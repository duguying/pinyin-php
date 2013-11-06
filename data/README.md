# get the latest data #

you can get the latest data file(pinyin.inc) from the internet via run the script `getData.sh`.

```
./getData.sh
```

## pinyin-php resource build ##

----------

the raw data is in the MySQL database, I read the data from the database and build the data into three variables.They are `char* cnchar`,`char* pinyin` and `char* py`. Chinese characters is in the variable `cnchar`. Chinese PinYin characters is in the variable `pinyin`. The PinYin alphabet is in the variable `py`.

**how to build**

you can build the resource file pinyin.inc by run `build.cmd`. this script will let you php execute the `databuild.php` script. of course, before you run the `build.cmd` you should set the environment variable `path`, you must let you php can be called.<br>

```
echo off
set path=%path%D:\wamp\bin\php\php5.3.13;
php databuild.php
pause
```

maybe, you can change the string `D:\wamp\bin\php\php5.3.13` into you own php home path. the following is the php script:<br>

```php
<?php
//header("Content-type:text/plaint;charset=gb2312");
$link = mysql_connect('127.0.0.1:3307', 'root', 'lijun');
if(!$link){
	die('Could not connect:'.mysql_error());
}
/**
 * chinese charactor
 */
$char="";
/**
 * chinese pinyin char
 */
$pinyin="";
/**
 * chinese pinyin alphabeta
 */
$py="";
/**
 * get data from database
 */
mysql_query("use ansi",$link);
mysql_query("set charset gb2312");
$result=mysql_query("select * from hanzi",$link);
while($row=@mysql_fetch_array($result)){
	//var_dump($row);
	$char=$char.$row['char'];
	$pinyin=$pinyin.$row['pinyin']."|";
	$py=$py.$row['py']."|";
}

echo "The following is chinese chars:\n",$char,"\nThe following is pinyin chars:\n",$pinyin,"\nThe following is pinyin alphabeta:\n",$py,"\n";

$str="extern char cnchar[]=\"$char\";\n";
$str=$str."extern char pinyin[]=\"$pinyin\";\n";
$str=$str."extern char py[]=\"$py\";\n";

file_put_contents("../pinyin.inc",$str);


```

configure you own database host, user and password. run the `build.cmd` and you php will create the file `/pinyin.inc`. 
