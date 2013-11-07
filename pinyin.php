<?php
set_time_limit(0);

$dict=pinyin();

echo "<pre>";
foreach ($dict as $key => $value) {
	echo "汉字: $key  拼音: $value\n";
}
echo "</pre>";