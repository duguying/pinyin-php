echo off
set php=D:\wamp\www\php_c\php\Release_TS\php.exe
set ini=D:\wamp\www\php_c\php\Release_TS\php.ini
set test=D:\wamp\www\php_c\php\ext\pinyin\pinyin.php
%php% -c %ini% -f %test%
pause
