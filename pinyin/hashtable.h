/**
 * Azalea Chatting Server
 *
 * Copyright (C) 2013-2015 Rex Lee <duguying2008@gmail.com>
 *
 * This program is free and opensource software; 
 * you can redistribute it and/or modify
 * it under the terms of the GNU General Public License
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_


#define HASH_TABLE_MAX_SIZE 10000

typedef struct HashNode HashNode;

struct HashNode
{
    char* sKey;
    int nValue;
    HashNode* pNext;
} ;

typedef struct HashTable HashTable;

struct HashTable
{
	int ht_size;
	HashNode* table[HASH_TABLE_MAX_SIZE];
};

/**
 * @brief initial the hashtable
 * @details this function not alloc memory for HashTable pointer
 * 
 * @param HashTable the pointer of hashtable
 */
void ht_init(HashTable* hash_table);

/**
 * @brief insert key-value into hash table
 * @details [long description]
 * 
 * @param HashTable the hashtable
 * @param skey key
 * @param nvalue value
 */
void ht_insert(HashTable* hash_table, const char* skey, int nvalue);

/**
 * @brief remove the hash node from hashtable
 * @details [long description]
 * 
 * @param HashTable the hashtable
 * @param skey the key of hashtable you'll remove
 */
void ht_remove(HashTable* hash_table, const char* skey);

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param HashTable [description]
 * @param skey [description]
 * @return [description]
 */
HashNode* ht_lookup(HashTable* hash_table, const char* skey);

/**
 * @brief release the hashtable
 * @details [long description]
 * 
 * @param hash_table the hashtable
 */
void ht_release(HashTable* hash_table);

#endif