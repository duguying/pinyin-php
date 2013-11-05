<?php
//header("Content-type:text/plaint;charset=gb2312");
echo "Start, Please wait...\n";
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
	$char=$char.$row['cchar'];
}

$char=iconv('GB2312','UTF-8',$char);

$charsarr=str_split($char, 501);
$pinyin="";
$char="";
foreach ($charsarr as $value) {
	$url="http://dianzu.duapp.com/?app=app.pinyin.index&dyz=1&con=".urlencode($value);
	$str=file_get_contents($url);
	$str=preg_replace('/ok:/','',$str);
	$pinyin=$pinyin.$str."\"\n\"";
	$char=$char.$value."\"\n\"";
}
// echo $pinyin;
/*
$url="http://dianzu.duapp.com/?app=app.pinyin.index&con=".urlencode($char);
$hpinyin=fopen($url, "r");
$pinyin=fread($hpinyin, 70000);
*/
//$pinyin=preg_replace('/\n/','',$pinyin);
$pinyin=preg_replace('/\t/','',$pinyin);
$pinyin=preg_replace('/ /','|',$pinyin);
$pinyin=preg_replace('/\|\|/','|',$pinyin);
$pinyin=preg_replace('/none/','',$pinyin);
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


echo "The following is chinese chars:\n",$char,"\nThe following is pinyin chars:\n",$pinyin,"\nThe following is pinyin alphabeta:\n",$py,"\n";

$str="#ifndef RS\nextern char cnchar[]=\"$char\";\n";
$str=$str."extern char pinyin[]=\"$pinyin\";\n";
$str=$str."extern char py[]=\"$py\";\n#endif\n#define RS\n";

file_put_contents("../webpinyin.inc",$str);

echo "Finished! enjoy it.\n";
