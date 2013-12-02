project(pinyin-lib)

#SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_CXX_FLAGS "-fPIC")

#include_directories("/usr/include/php5")
#include_directories("/usr/include/php5/Zend")
#include_directories("/usr/include/php5/TSRM")

set(SRC_LIST ./test.c)

add_library(test STATIC ${SRC_LIST})
