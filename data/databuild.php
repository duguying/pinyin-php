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
mysql_query("use cchars",$link);
mysql_query("set charset utf8");
$result=mysql_query("select * from cn_hanzi order by cchar",$link);
while($row=@mysql_fetch_array($result)){
	//var_dump($row);
	$char=$char.$row['cchar'];
	$pinyin=$pinyin.$row['pinyin']."|";
	//$py=$py.$row['py']."|";
}

$py=$pinyin;

$py=preg_replace('/ā/', 'a', $py);
$py=preg_replace('/á/', 'a', $py);
$py=preg_replace('/ǎ/', 'a', $py);
$py=preg_replace('/à/', 'a', $py);

$py=preg_replace('/ō/', 'o', $py);
$py=preg_replace('/ó/', 'o', $py);
$py=preg_replace('/ǒ/', 'o', $py);
$py=preg_replace('/ò/', 'o', $py);

$py=preg_replace('/ē/', 'e', $py);
$py=preg_replace('/é/', 'e', $py);
$py=preg_replace('/ě/', 'e', $py);
$py=preg_replace('/è/', 'e', $py);

$py=preg_replace('/ī/', 'i', $py);
$py=preg_replace('/í/', 'i', $py);
$py=preg_replace('/ǐ/', 'i', $py);
$py=preg_replace('/ì/', 'i', $py);

$py=preg_replace('/ū/', 'u', $py);
$py=preg_replace('/ú/', 'u', $py);
$py=preg_replace('/ǔ/', 'u', $py);
$py=preg_replace('/ù/', 'u', $py);

$py=preg_replace('/ǖ/', 'v', $py);
$py=preg_replace('/ǘ/', 'v', $py);
$py=preg_replace('/ǚ/', 'v', $py);
$py=preg_replace('/ǜ/', 'v', $py);
$py=preg_replace('/ü/', 'v', $py);

$char_arr=str_split($char, 2);
$pinyin_arr=explode('|', $pinyin);
$py_arr=explode('|', $py);

//echo "The following is chinese chars:\n",$char,"\nThe following is pinyin chars:\n",$pinyin,"\nThe following is pinyin alphabeta:\n",$py,"\n";

$str="";
$str=$str. "#ifndef RS\nchar cnchar[]=\n";
foreach($char_arr as $value){
	$str=$str. "\"".$value."\"\n";
}
$str=$str.";\n";
$str=$str. "char pinyin[]=\n";
foreach($pinyin_arr as $value){
	$str=$str. "\"".$value."|\"\n";
}
$str=$str.";\n";
$str=$str. "char py[]=\n";
foreach($py_arr as $value){
	$str=$str. "\"".$value."|\"\n";
}
$str=$str.";\n";
$str=$str. "#endif\n#define RS\n";
$str=preg_replace('/\"\|\"/', '', $str);

echo $str;

file_put_contents("../pinyin.inc",$str);

