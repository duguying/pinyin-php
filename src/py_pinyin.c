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
 * shift zero for buffer
 * @param  buffer     buffer
 * @param  buffer_len buffer length
 * @return            string after shift
 */
char* buffer_shift(char* buffer, int buffer_len){
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

int match_word(char* buffer, PinTable * dict){
	HashNode* result = NULL;
	int length = 0;
	int idx = 0;
	int back = 0;

	length = strlen(buffer);
	// printf("will match: %s\n", buffer);
	for (idx = 0; idx < length; ++idx){
		result = ht_lookup(dict, buffer + idx);
		if (result != NULL){
			buffer = buffer + idx;
			printf("[matched:%d] %s\n", idx, buffer);
			return idx;
		}

		if (idx == length - 1){
			buffer = buffer + (length - 1);
			back = length - 1;
			printf("[back:%d] %s\n", back, buffer);

			return back;
		}
	}

	return 0;
}

/**
 * translate chinese sentence into pinyin
 * @param  raw raw string
 * @return     pinyin string
 */
char* pinyin_translate(char* raw, PinTable * dict){
	int max_cut_len = MAX_CUT_LEN * 2;
	int length = strlen(raw);
	int idx = 0;
	int chr_idx = 0;
	int flag_idx = 0;
	int back = 0;
	char* buffer = 0;

	buffer = (char*)malloc(max_cut_len + 1);
	memset(buffer, 0, max_cut_len + 1);

	for(idx = 0; idx < length; idx++){
		flag_idx = idx % max_cut_len;
		
		chr_idx = length - 1 - idx;
		buffer[max_cut_len - 1 - flag_idx] = raw[chr_idx];
		
		// get the fragment string
		if (flag_idx == max_cut_len - 1 || idx == length - 1){
			buffer_shift(buffer, max_cut_len);
			// printf("[%d] %s\n", flag_idx, buffer_shift(buffer, max_cut_len));

			back = match_word(buffer, dict);
			idx = idx - back;

			// deal with fragment
			// ht_lookup(dict, buffer); //TODO

			if (idx == length - 1){
				// printf("[%s]\n", "end");
			}
			
			memset(buffer, 0, max_cut_len);
		}
	}

	return 0;
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
