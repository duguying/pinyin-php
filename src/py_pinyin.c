#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "hashtable.h"
#include "py_pinyin.h"

char* result_buffer = 0;

/**
 * get the size of text file
 * @param filename
 * @return size of file
 */
long file_size_count(const char* filename){
	FILE* fp;
	long long_bytes = 0;

	fp = fopen(filename, "rb");
	
    if(fp){
        fseek(fp, 0, SEEK_SET);
	    fseek(fp, 0, SEEK_END);
	    long_bytes = ftell(fp);
    }else{
        printf("open file failed.\n");
    }

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
	if (buffer != NULL){
		free(buffer);
		buffer = NULL;
	}
	
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
			char* tmp_value = 0;

            content[idx] = 0;
			value = content;
			content = content + idx + 1;
			i++;
			idx = 0;

            tmp_value = (char*)malloc(strlen(value) + 1);
            memset(tmp_value, 0, strlen(value) + 1);
            memcpy(tmp_value, value, strlen(value));

			ht_insert(dict, key, tmp_value);
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
	buffer[len-1] = 0;

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
 * shift zero for buffer
 * @param  buffer     buffer
 * @param  buffer_len buffer length
 * @return            string after shift
 */
wchar_t* buffer_shift(wchar_t* buffer, int buffer_len){
	int i = 0;
	int char_idx = 0;

	while(1){
		if (buffer[0] == 0){
			buffer++;
		}else{
			return buffer;
		}

		if (i == buffer_len - 1){
			break;
		}

		i++;
	}

	return buffer;
}

/**
 * append a string seg before tail
 * @param appendage appendage -- just a string
 * @param tail      tail -- tail buffer should be create by malloc
 */
char* head_append(char* appendage, char* tail){
	int tail_len = 0;
	int appendage_len = 0;
	int total_len = 0;
	char* new_string = 0;
    char* exchange_buffer = 0;

	tail_len = strlen(tail);
	appendage_len = strlen(appendage);
	total_len = tail_len + appendage_len;

    exchange_buffer = (char*)malloc(tail_len+1);
    memset(exchange_buffer, 0, tail_len+1);
    memcpy(exchange_buffer, tail, tail_len);

	new_string = realloc(tail, total_len + 1);
	// memcpy(new_string + appendage_len, new_string, tail_len);
	memcpy(new_string, appendage, appendage_len);
    memcpy(new_string + appendage_len, exchange_buffer, tail_len);
	new_string[total_len] = 0;

    free(exchange_buffer);
    // printf("[%s|%s]\n", appendage, tail);
	
	return new_string;
}

// match the words
int match_word(wchar_t* buffer, PinTable * dict){
	HashNode* result = NULL;
	int length = 0;
	int idx = 0;
	int back = 0;

	length = wcslen(buffer);

	for (idx = 0; idx < length; ++idx){
		char* cbuf = 0;

		cbuf = (char*)malloc(length * sizeof(wchar_t));
		memset(cbuf, 0, length * sizeof(wchar_t));
		wcstombs(cbuf, buffer + idx, length * sizeof(wchar_t));
		result = ht_lookup(dict, cbuf);
		
        //printf("[s:%s]\n", cbuf);

		if (result != NULL){
			char* trans_result = 0;

			buffer = buffer + idx;
			trans_result = result->nValue;
			
            // printf("[%s:%s]\n", cbuf, trans_result);

			result_buffer = head_append(trans_result, result_buffer);

			return idx;
		}

		if (idx == length - 1){
			buffer = buffer + (length - 1);
			back = length - 1;

			memset(cbuf, 0, length * sizeof(wchar_t));
			wcstombs(cbuf, buffer, length * sizeof(wchar_t));
			result_buffer = head_append(cbuf, result_buffer);

			return back;
		}

		free(cbuf);
		cbuf = 0;
	}

	return 0;
}

/**
 * translate chinese sentence into pinyin
 * @param  raw raw string
 * @return     pinyin string
 */
char* pinyin_translate(char* raw, PinTable * dict){
	int max_cut_len = MAX_CUT_LEN;
	int length = strlen(raw);
	int idx = 0;
	int chr_idx = 0;
	int flag_idx = 0;
	int back = 0;
	wchar_t* buffer = 0;
	wchar_t* wraw = 0;
	int wlen = 0;

	wraw = (wchar_t*)malloc(sizeof(wchar_t) * length);
	memset(wraw, 0, sizeof(wchar_t) * length);

	wlen = mbstowcs(wraw, raw, length);

	buffer = (wchar_t*)malloc((max_cut_len + 1) * sizeof(wchar_t));
	memset(buffer, 0, (max_cut_len + 1) * sizeof(wchar_t));
	result_buffer = (char*)malloc(1);
	memset(result_buffer, 0, 1);

	for(idx = 0; idx < wlen; idx++){
		flag_idx = idx % max_cut_len;
		
		chr_idx = wlen - 1 - idx;
		buffer[max_cut_len - 1 - flag_idx] = wraw[chr_idx];
		
		// get the fragment string
		if (flag_idx == max_cut_len - 1 || idx == wlen - 1){
			wchar_t* tmp_buffer = 0;

			tmp_buffer = buffer_shift(buffer, max_cut_len);
			back = match_word(tmp_buffer, dict);
			idx = idx - back;

			if (idx == wlen - 1){
				// 
			}
			
			memset(buffer, 0, (max_cut_len + 1) * sizeof(wchar_t));

		}
	}

	free(buffer);
	buffer = 0;
	free(wraw);
	wraw = 0;

    result_buffer[strlen(result_buffer)] = 0;

	return result_buffer;
}

/**
 * initialize pinyin
 * @return
 */
PinTable *pinyin_init(PinTable * dict)
{
	// int cn_count, pinyin_arr_count, pinyin_index, i, j, index[MAX_LEN];
	// char tmp[4];
	// char* test = "hello world";

	memset(dict, 0, sizeof(PinTable));
	ht_init(dict);

	
	setlocale(LC_ALL,"zh_CN.UTF-8");

	return dict;
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
