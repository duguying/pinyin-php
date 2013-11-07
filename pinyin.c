/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_pinyin.h"

static int le_pinyin;

const zend_function_entry pinyin_functions[] = {
	PHP_FE(pinyin,	NULL)
	{NULL,NULL,NULL}	/* Must be the last line in pinyin_functions[] */
};

zend_module_entry pinyin_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"pinyin",
	pinyin_functions,
	PHP_MINIT(pinyin),
	PHP_MSHUTDOWN(pinyin),
	PHP_RINIT(pinyin),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(pinyin),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(pinyin),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_PINYIN
ZEND_GET_MODULE(pinyin)
#endif


PHP_MINIT_FUNCTION(pinyin)
{
	zval dict;
	ZEND_SET_GLOBAL_VAR(name, dict)
	return SUCCESS;
}


PHP_MSHUTDOWN_FUNCTION(pinyin)
{
	return SUCCESS;
}

PHP_RINIT_FUNCTION(pinyin)
{
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(pinyin)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(pinyin)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "pinyin support", "enabled");
	php_info_print_table_row(2, "author", "Rex Lee"); 
	php_info_print_table_row(2, "version", "0.1");
	php_info_print_table_end();

}

PHP_FUNCTION(pinyin)
{
	pinyin_init(return_value);	
}


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
