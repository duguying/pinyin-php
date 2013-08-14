-- --------------------------------------------------------
-- 主机:                           127.0.0.1
-- 服务器版本:                        5.5.31-MariaDB - mariadb.org binary distribution
-- 服务器操作系统:                      Win64
-- HeidiSQL 版本:                  8.0.0.4396
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- 导出 cchars 的数据库结构
CREATE DATABASE IF NOT EXISTS `cchars` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `cchars`;


-- 导出  表 cchars.hanzi 结构
CREATE TABLE IF NOT EXISTS `hanzi` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ID',
  `cchar` varchar(1) CHARACTER SET gb2312 NOT NULL COMMENT '汉字',
  `pinyin` varchar(50) DEFAULT NULL COMMENT '拼音',
  `py` varchar(50) DEFAULT NULL COMMENT '拼音字母',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8 COMMENT='汉字';

-- 正在导出表  cchars.hanzi 的数据：~7 rows (大约)
/*!40000 ALTER TABLE `hanzi` DISABLE KEYS */;
INSERT INTO `hanzi` (`id`, `cchar`, `pinyin`, `py`) VALUES
	(1, '里', 'lǐ', 'li'),
	(2, '啊', 'a', 'a'),
	(3, '阿', 'a', 'a'),
	(4, '万', 'wan', 'wan'),
	(5, '七', 'qi', 'qi'),
	(6, '丁', 'din', 'din'),
	(7, '一', 'yi', 'yi');
/*!40000 ALTER TABLE `hanzi` ENABLE KEYS */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
