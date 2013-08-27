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
mysql_query("set charset gb2312");
$result=mysql_query("select * from cn_hanzi order by cchar",$link);
while($row=@mysql_fetch_array($result)){
	//var_dump($row);
	$char=$char.$row['cchar'];
	$pinyin=$pinyin.$row['pinyin']."|";
	//$py=$py.$row['py']."|";
}

$py=$pinyin;

$py=preg_replace('/иб/', 'a', $py);
$py=preg_replace('/ив/', 'a', $py);
$py=preg_replace('/иг/', 'a', $py);
$py=preg_replace('/ид/', 'a', $py);

$py=preg_replace('/ин/', 'o', $py);
$py=preg_replace('/ио/', 'o', $py);
$py=preg_replace('/ип/', 'o', $py);
$py=preg_replace('/и░/', 'o', $py);

$py=preg_replace('/ие/', 'e', $py);
$py=preg_replace('/иж/', 'e', $py);
$py=preg_replace('/из/', 'e', $py);
$py=preg_replace('/ии/', 'e', $py);

$py=preg_replace('/ий/', 'i', $py);
$py=preg_replace('/ик/', 'i', $py);
$py=preg_replace('/ил/', 'i', $py);
$py=preg_replace('/им/', 'i', $py);

$py=preg_replace('/и▒/', 'u', $py);
$py=preg_replace('/и▓/', 'u', $py);
$py=preg_replace('/и│/', 'u', $py);
$py=preg_replace('/и┤/', 'u', $py);

$py=preg_replace('/и╡/', 'v', $py);
$py=preg_replace('/и╢/', 'v', $py);
$py=preg_replace('/и╖/', 'v', $py);
$py=preg_replace('/и╕/', 'v', $py);
$py=preg_replace('/и╣/', 'v', $py);

$char_arr=str_split($char, 2);
$pinyin_arr=explode('|', $pinyin);
$py_arr=explode('|', $py);

//echo "The following is chinese chars:\n",$char,"\nThe following is pinyin chars:\n",$pinyin,"\nThe following is pinyin alphabeta:\n",$py,"\n";

$str="";
$str=$str. "#ifndef RS\nextern char cnchar[]=\n";
foreach($char_arr as $value){
	$str=$str. "\"".$value."\"\n";
}
$str=$str.";\n";
$str=$str. "extern char pinyin[]=\n";
foreach($pinyin_arr as $value){
	$str=$str. "\"".$value."|\"\n";
}
$str=$str.";\n";
$str=$str. "extern char py[]=\n";
foreach($py_arr as $value){
	$str=$str. "\"".$value."|\"\n";
}
$str=$str.";\n";
$str=$str. "#endif\n#define RS\n";
$str=preg_replace('/\"\|\"/', '', $str);

echo $str;

file_put_contents("../pinyin.inc",$str);

