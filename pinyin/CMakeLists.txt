project(pinyin-lib)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -fPIC")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -fPIC")

set(SRC_LIST "./pinyin.c" "./hashtable.c")

# include_directories("../")

add_library(pinyin STATIC ${SRC_LIST})

add_executable(test_pinyin "./test.c")

target_link_libraries(test_pinyin pinyin)
