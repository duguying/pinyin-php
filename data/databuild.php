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

