# get the latest data #

you can get the latest data file(pinyin.inc) from the internet via run the script `getData.sh`.

```
./getData.sh
```

## about pinyin-php resource build ##

the raw data is in the MySQL database, I read the data from the database and build the data into three variables.They are `char* cnchar`,`char* pinyin` and `char* py`. Chinese characters is in the variable `cnchar`. Chinese PinYin characters is in the variable `pinyin`. The PinYin alphabet is in the variable `py`.
