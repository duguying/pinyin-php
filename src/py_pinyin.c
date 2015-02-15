#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "py_pinyin.h"

char cnchar[] = "汉";
char pinyin[] = "hello";

/**
 * get the size of text file
 * @param filename
 * @return size of file
 */
long file_size_count(const char* filename){
	FILE* fp;
	long long_bytes = 0;

	fp = fopen(filename, "rb");
	fseek(fp, 0, SEEK_SET);
	fseek(fp, 0, SEEK_END);
	long_bytes = ftell(fp);
	
	return long_bytes;
}

/**
 * open an file and get content into buffer
 * @param filename
 * @return file length
 */
char* file_open(const char* filename){
	char *buffer = NULL;
	int string_size,read_size;
	FILE *handler = fopen(filename,"r");

	if (handler){
		fseek(handler,0,SEEK_END);
		string_size = ftell (handler);
		rewind(handler);

		buffer = (char*) malloc (sizeof(char) * (string_size + 1) );
		read_size = fread(buffer,sizeof(char),string_size,handler);
		buffer[string_size+1] = '\0';

		if (string_size != read_size) {
		   free(buffer);
		   buffer = NULL;
		}
	}
  
    return buffer;
}

/**
 * free the string buffer
 * @param buffer pointer
 * @return
 */
int free_buffer(char* buffer){
	free(buffer);
	buffer = NULL;
	return 0;
}

/**
 * load char dictionary
 */
void load_char(const char* filename, PinTable * dict){
	long length = 0;
	char* content = NULL;
	char* buffer = NULL;
	long idx = 0;
	long i = 0;
	char cur_char = 0;
	char* key = 0;
	char* value = 0;
	char* value_container = 0;

	length = file_size_count(filename);
	buffer = file_open(filename);
	content = buffer;

	while(1){
		cur_char = content[idx];

		if (',' == cur_char){
			content[idx] = 0;
			key = content;
			content = content + idx + 1;
			i++;
			idx = 0;
		}

		if ('\n' == cur_char){
			content[idx] = 0;
			value = content;
			content = content + idx + 1;
			i++;
			idx = 0;

			ht_insert(dict, key, value);
		}

		idx++;
		i++;

		if (i > length){
			break;
		}
	}

	free_buffer(buffer);
}

/**
 * filt comma in the string
 * this will alloc a string buffer, please free after use
 * @param string [description]
 */
char* filt_comma(char* string){
	char cur_char = 0;
	int idx = 0;
	int i = 0;
	char* buffer = 0;
	int len = 0;

	len = strlen(string) * sizeof(char) + 1;
	buffer = (char*)malloc(len);
	memset(buffer, 0, len);
	strncpy(buffer, string, len);
	buffer[len] = 0;

	while(1){
		cur_char = string[idx++];

		if (',' != cur_char){
			buffer[i++] = cur_char;
		}

		if (idx > strlen(string)){
			break;
		}
	}

	return buffer;
}

/**
 * load words dictionary
 */
void load_word(const char* filename, PinTable * dict){
	long length = 0;
	char* content = NULL;
	char* buffer = NULL;
	long idx = 0;
	long i = 0;
	char cur_char = 0;
	char* key = 0;
	char* value = 0;
	char* value_container = 0;
	int comma_flag = 0;

	length = file_size_count(filename);
	buffer = file_open(filename);
	content = buffer;

	while(1){

		cur_char = content[idx];

		if (cur_char == '\n'){
			comma_flag = 0;
			content[idx] = 0;
			value = content;

			// insert into hashtable
			value = filt_comma(value);
			ht_insert(dict, key, value);

			content = content + idx + 1;
			i++;
			idx = 0;
		};

		if (cur_char == ','){
			if (comma_flag == 0){
				/* the 1st comma */
				content[idx] = 0;
				key = content;

				content = content + idx + 1;
				i++;
				idx = 0;
			}
			comma_flag = 1;
		}

		idx++;
		i++;

		if (i > length){
			break;
		}
	}



	free_buffer(buffer);
}

/**
 * initialize pinyin
 * @return
 */
PinTable *pinyin_init(PinTable * dict)
{
	int cn_count, pinyin_arr_count, pinyin_index, i, j, index[MAX_LEN];
	char tmp[4];

	memset(dict, 0, sizeof(PinTable));
	ht_init(dict);

	load_char("/Users/rex/code/pinyin-php/data/chars.csv", dict);
	load_word("/Users/rex/code/pinyin-php/data/words.csv", dict);

	// char buf[100] = "hello,words,not,world";
	// char* rst = filt_comma(buf);

	// printf("[%s]\n", rst);

	return dict;
}

/**
 * get pinyin by chinese char
 * @param  cn chinese char
 * @return pinyin string
 */
char *pinyin_get(PinTable * dict, char *cn)
{
	char single_cn_buf[JMP + 1];
	unsigned int len = 0;
	unsigned int len_pybuf = 0;
	unsigned int flag_cnchar_buf = 0;
	char *pybuf = NULL;
	char *pybuf_pos = NULL;
	unsigned int i = 0;

	len = strlen(cn);
	len_pybuf = (len / 2) * 7 + 1;
	pybuf_pos = pybuf = (char *)malloc(len_pybuf);
	memset(pybuf, 0, len_pybuf);
	memset(single_cn_buf, 0, JMP + 1);

	// strip ascii
	for (i = 0; i < len; ++i) {

		if (cn[i] < 0) {		// chinese char
			if ((JMP - 1) != flag_cnchar_buf) {
				single_cn_buf[flag_cnchar_buf] = cn[i];
				++flag_cnchar_buf;
			} else {
				char *single_cn_pinyin = NULL;
				unsigned int len_of_py = 0;
				HashNode *result_node = NULL;

				single_cn_buf[flag_cnchar_buf] = cn[i];
				flag_cnchar_buf = 0;
				// translate

				result_node = (HashNode *) ht_lookup(dict, single_cn_buf);

				if (NULL == result_node) {
					len_of_py = strlen(single_cn_buf);
					strncpy(pybuf_pos, single_cn_buf, len_of_py);
					pybuf_pos += len_of_py;
				} else {
					single_cn_pinyin = (char *)result_node->nValue;
					len_of_py = strlen(single_cn_pinyin);
					strncpy(pybuf_pos, single_cn_pinyin, len_of_py);
					pybuf_pos += len_of_py;
				}

				memset(single_cn_buf, 0, JMP + 1);
			}
		} else {				// other
			memset(pybuf_pos, cn[i], 1);
			++pybuf_pos;
		}
	}

	return pybuf;
}

/**
 * @brief release the pinyin dictionary
 * @details [long description]
 * 
 */
void pinyin_destroy(PinTable * dict)
{
	ht_release(dict);
}
