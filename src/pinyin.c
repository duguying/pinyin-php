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
#include "py_pinyin.h"

static int le_pinyin;
PinTable dict;

const zend_function_entry pinyin_functions[] = {
	PHP_FE(pinyin, NULL) {NULL, NULL, NULL}	/* Must be the last line in pinyin_functions[] */
};

zend_module_entry pinyin_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"pinyin",
	pinyin_functions,
	PHP_MINIT(pinyin),
	PHP_MSHUTDOWN(pinyin),
	PHP_RINIT(pinyin),			/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(pinyin),		/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(pinyin),
#if ZEND_MODULE_API_NO >= 20010901
	"0.3",						/* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PINYIN
ZEND_GET_MODULE(pinyin)
#endif

PHP_INI_BEGIN()
    PHP_INI_ENTRY("pinyin.chars", "chars.csv", PHP_INI_ALL, NULL)
    PHP_INI_ENTRY("pinyin.words", "words.csv", PHP_INI_ALL, NULL)
PHP_INI_END()

PHP_MINIT_FUNCTION(pinyin)
{
	REGISTER_INI_ENTRIES();

	pinyin_init(&dict);

	if(!access(INI_STR("pinyin.locale"), 4)){
		pinyin_set_locale(INI_STR("pinyin.locale"));
	}else{
		pinyin_set_locale("zh_CN.UTF-8");
	}
	
	if(!access(INI_STR("pinyin.words"), 4)){
		load_word(INI_STR("pinyin.words"), &dict);
	}

	if(!access(INI_STR("pinyin.chars"), 4)){
		load_char(INI_STR("pinyin.chars"), &dict);
	}

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(pinyin)
{
    UNREGISTER_INI_ENTRIES();
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
	php_info_print_table_row(2, "version", "0.4.0");
	php_info_print_table_row(2, "function", "string pinyin(string)");
	php_info_print_table_end();

}

PHP_FUNCTION(pinyin)
{
	char *cn_word;
	char *pyr;
	int int_hello_str_length;

	if (zend_parse_parameters
		(ZEND_NUM_ARGS()TSRMLS_CC, "s", &cn_word,
		 &int_hello_str_length) == FAILURE) {
		RETURN_NULL();
	}

	if(!access(INI_STR("pinyin.words"), 4) && !access(INI_STR("pinyin.chars"), 4)){
		pyr = pinyin_translate(cn_word, &dict);
	}else{
		pyr = cn_word;
	}
	
	ZVAL_STRING(return_value, pyr, 1);
}
