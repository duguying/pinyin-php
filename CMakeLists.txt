project(php_pinyin)

# SET(CMAKE_C_COMPILER "C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin/cl.exe")

add_definitions(
	"-D _CRT_SECURE_NO_DEPRECATE"
	"-D WIN32"
	# "-D _DEBUG"
	"-D _WINDOWS"
	"-D _USRDLL"
	"-D PHP_PINYIN_EXPORTS"
	"-D COMPILE_DL_PINYIN"
	"-D PHP_WIN32"
	"-D ZEND_WIN32"
	"-D ZTS=1"
	"-D ZEND_DEBUG=0"
	"-D _USE_32BIT_TIME_T=1"
	"-D _UNICODE"
	"-D UNICODE"
)

set(PHPSDK "C:/php/SDK")

link_directories(
	"${PHPSDK}/lib"
	# "D:/wamp/bin/php/php5.3.10/dev"
)
include_directories(
	"${PHPSDK}/include"
	"${PHPSDK}/include/main"
	"${PHPSDK}/include/TSRM"
	"${PHPSDK}/include/win32"
	"${PHPSDK}/include/Zend"
)

set(
	PY_LIST
	./src/pinyin.c
	./src/hashtable.c
	./src/py_pinyin.c
)

set(
    PY_TEST
    ./src/hashtable.c
    ./src/py_pinyin.c
    ./src/test_pinyin.c
)

# add_library(php_pinyin SHARED ${PY_LIST})
# target_link_libraries(php_pinyin php5ts)

add_executable(pinyin_test ${PY_TEST})

