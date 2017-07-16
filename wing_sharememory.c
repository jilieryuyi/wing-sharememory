/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
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
#include "php_wing_sharememory.h"

/* If you declare any globals in php_wing_sharememory.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(wing_sharememory)
*/

/* True global resources - no need for thread safety here */
static int le_wing_sharememory;
zend_class_entry *wing_sharememory_ce;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("wing_sharememory.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_wing_sharememory_globals, wing_sharememory_globals)
    STD_PHP_INI_ENTRY("wing_sharememory.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_wing_sharememory_globals, wing_sharememory_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_wing_sharememory_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_wing_sharememory_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "wing_sharememory", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_wing_sharememory_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_wing_sharememory_init_globals(zend_wing_sharememory_globals *wing_sharememory_globals)
{
	wing_sharememory_globals->global_value = 0;
	wing_sharememory_globals->global_string = NULL;
}
*/
/* }}} */

ZEND_METHOD(wing_sharememory, __construct) {
	//打开共享的文件对象。 
	HANDLE m_hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, ("TestFileMap"));
	if (m_hMapFile)
	{
		//显示共享的文件数据。 
		LPTSTR lpMapAddr = (LPTSTR)MapViewOfFile(m_hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		OutputDebugString(lpMapAddr);
	}
	else
	{
		//创建共享文件。 
		m_hMapFile = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL,
			PAGE_READWRITE, 0, 1024, ("TestFileMap"));
		//拷贝数据到共享文件里。 
		LPTSTR lpMapAddr = (LPTSTR)MapViewOfFile(m_hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		//std::wstring strTest(_T("TestFileMap"));
		//wcscpy(lpMapAddr, "TestFileMap");

		//FlushViewOfFile(lpMapAddr, strTest.length() + 1);
	}
}

ZEND_METHOD(wing_sharememory, __destruct) {

}

static zend_function_entry wing_sharememory_methods[] = {
	ZEND_ME(wing_sharememory, __construct,NULL,ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	ZEND_ME(wing_sharememory, __destruct, NULL,ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
{
	NULL,NULL,NULL
}
};


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(wing_sharememory)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/

	zend_class_entry _wing_sharememory_ce;
	//INIT_CLASS_ENTRY(_wing_process_ce, "wing_process", wing_process_methods);
	INIT_NS_CLASS_ENTRY(_wing_sharememory_ce, "wing", "wing_sharememory", wing_sharememory_methods);
	wing_sharememory_ce = zend_register_internal_class(&_wing_sharememory_ce TSRMLS_CC);

	//zend_declare_property_string(wing_process_ce, "file", strlen("file"), "", ZEND_ACC_PRIVATE TSRMLS_CC);
	////zend_declare_property_string(wing_process_ce, "output_file", strlen("output_file"), "", ZEND_ACC_PRIVATE TSRMLS_CC);
	//zend_declare_property_long(wing_process_ce, "process_info_pointer", strlen("process_info_pointer"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);
	//zend_declare_property_long(wing_process_ce, "redirect_handler", strlen("redirect_handler"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);
	//zend_declare_property_string(wing_process_ce, "command_line", strlen("command_line"), "", ZEND_ACC_PRIVATE TSRMLS_CC);
	//zend_declare_property_long(wing_process_ce, "process_id", strlen("process_id"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);
	//zend_declare_property_long(wing_process_ce, "thread_id", strlen("thread_id"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);


	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(wing_sharememory)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(wing_sharememory)
{
#if defined(COMPILE_DL_WING_SHAREMEMORY) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(wing_sharememory)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(wing_sharememory)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "wing_sharememory support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ wing_sharememory_functions[]
 *
 * Every user visible function must have an entry in wing_sharememory_functions[].
 */
const zend_function_entry wing_sharememory_functions[] = {
	PHP_FE(confirm_wing_sharememory_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in wing_sharememory_functions[] */
};
/* }}} */

/* {{{ wing_sharememory_module_entry
 */
zend_module_entry wing_sharememory_module_entry = {
	STANDARD_MODULE_HEADER,
	"wing_sharememory",
	wing_sharememory_functions,
	PHP_MINIT(wing_sharememory),
	PHP_MSHUTDOWN(wing_sharememory),
	PHP_RINIT(wing_sharememory),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(wing_sharememory),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(wing_sharememory),
	PHP_WING_SHAREMEMORY_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_WING_SHAREMEMORY
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(wing_sharememory)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
