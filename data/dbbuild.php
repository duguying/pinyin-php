<?php
//header("Content-type:text/plaint;charset=gb2312");
//echo "Start, Please wait...\n";
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
mysql_query("use hanzi",$link);
mysql_query("set charset utf8");
$result=mysql_query("select * from cn_hanzi where pinyin='' order by cchar",$link);
while($row=@mysql_fetch_array($result)){
	$char=$char.$row['cchar'];
}

$char=iconv('GB2312','UTF-8',$char);

$charsarr=str_split($char, 3);

// var_dump(count($charsarr));

foreach ($charsarr as $value) {
	// echo $value;
	$url="http://dianzu.duapp.com/?app=app.pinyin.index&dyz=1&con=".urlencode($value);
	$str=file_get_contents($url);
	$str=preg_replace('/ok:/','',$str);
	$str=preg_replace('/^ /','',$str);
	$str=preg_replace('/ [\d\D]+/','',$str);
	$str=preg_replace('/ /','',$str);
	
	if($str=='none'){
		$url="http://dianzu.duapp.com/?app=app.pinyin.index&con=".urlencode($value);
		$str=file_get_contents($url);
		$str=preg_replace('/ /','',$str);
	}
	$value=iconv('UTF-8','GB2312',$value);
	$str=iconv('UTF-8','GB2312',$str);
	$sql="UPDATE cn_hanzi SET pinyin = '{$str}' WHERE cchar = '{$value}'";
	$rst=mysql_query($sql);
	echo "{$sql}\n";
}
