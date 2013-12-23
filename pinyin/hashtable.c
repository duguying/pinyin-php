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
#include <string.h>
#include "hashtable.h"

/**
 * @brief initial the hashtable
 * @details this function not alloc memory for HashTable pointer
 * 
 * @param HashTable the pointer of hashtable
 */
void ht_init(i_HashTable* hash_table)
{
    memset(hash_table, 0, sizeof(i_HashTable));
    hash_table->ht_size= 0;  //the number of key-value pairs in the hash table!
}

/**
 * string hash function
 * @param  skey [description]
 * @return      [description]
 */
unsigned int ht_hash_str(const char* skey)
{
    const signed char *p = (const signed char*)skey;
    unsigned int h = *p;

    if(h)
    {
        for(p += 1; *p != '\0'; ++p)
            h = (h << 5) - h + *p;
    }
    return h;
}


/**
 * @brief insert key-value into hash table
 * @details [long description]
 * 
 * @param HashTable the hashtable
 * @param skey key
 * @param nvalue value
 */
void ht_insert(i_HashTable* hash_table, const char* skey, void* nvalue)
{
	unsigned int pos;
	HashNode* pHead;
	HashNode* pNewNode;

    if(hash_table->ht_size >= HASH_TABLE_MAX_SIZE)
    {
        printf("out of hash table memory!\n");
        return;
    }
    pos = ht_hash_str(skey) % HASH_TABLE_MAX_SIZE;
    pHead =  hash_table->table[pos];
    while(pHead)
    {
        if(strcmp(pHead->sKey, skey) == 0)
        {
            printf("%s already exists!\n", skey);
            return ;
        }
        pHead = pHead->pNext;
    }
    pNewNode = (HashNode*)malloc(sizeof(HashNode));
    memset(pNewNode, 0, sizeof(HashNode));
    pNewNode->sKey = (char*)malloc(sizeof(char) * (strlen(skey) + 1));
    strcpy(pNewNode->sKey, skey);
    pNewNode->nValue = nvalue;
    pNewNode->pNext = hash_table->table[pos];
    hash_table->table[pos] = pNewNode;

    hash_table->ht_size++;
}


void ht_print(i_HashTable* hash_table){
	int i;

    printf("===========content of hash table=================\n");
    for (i = 0; i < HASH_TABLE_MAX_SIZE; ++i)
        if (hash_table->table[i])
        {
            HashNode *pHead = hash_table->table[i];
            printf("%d=>", i);
            while (pHead)
            {
                printf("%s:%s  ", pHead->sKey, (char*)pHead->nValue);
                pHead = pHead->pNext;
            }
            printf("\n");
        }
}


/**
 * @brief remove the hash node from hashtable
 * @details [long description]
 * 
 * @param HashTable the hashtable
 * @param skey the key of hashtable you'll remove
 */
void ht_remove(i_HashTable* hash_table, const char* skey){
    unsigned int pos = ht_hash_str(skey) % HASH_TABLE_MAX_SIZE;

    if(hash_table->table[pos])
    {
        HashNode* pHead = hash_table->table[pos];
        HashNode* pLast = NULL;
        HashNode* pRemove = NULL;
        while(pHead)
        {
            if(strcmp(skey, pHead->sKey) == 0)
            {
                pRemove = pHead;
                break;
            }
            pLast = pHead;
            pHead = pHead->pNext;
        }
        if(pRemove)
        {
            if(pLast)
                pLast->pNext = pRemove->pNext;
            else
                hash_table->table[pos] = NULL;
            free(pRemove->sKey);
            free(pRemove);
        }
    }
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param HashTable [description]
 * @param skey [description]
 * @return [description]
 */
HashNode* ht_lookup(i_HashTable* hash_table, const char* skey){
    HashNode* pHead;
    unsigned int pos = ht_hash_str(skey) % HASH_TABLE_MAX_SIZE;
    
    if(hash_table->table[pos])
    {
        pHead = hash_table->table[pos];
        while(pHead)
        {
            if(strcmp(skey, pHead->sKey) == 0){
                return hash_table->table[pos];
            }else{
                pHead = pHead->pNext;
            }
            
        }
    }
    return NULL;
}

/**
 * @brief release the hashtable
 * @details [long description]
 * 
 * @param hash_table the hashtable
 */
void ht_release(i_HashTable* hash_table){
    int i;
    HashNode* pTemp;
    HashNode* pHead;

    for(i = 0; i < HASH_TABLE_MAX_SIZE; ++i)
    {
        if(hash_table->table[i])
        {
            pHead = hash_table->table[i];
            while(pHead)
            {
                pTemp = pHead;
                pHead = pHead->pNext;
                if(pTemp)
                {
                    free(pTemp->sKey);
                    free(pTemp);
                }
            }
        }
    }

    memset(hash_table, 0, sizeof(i_HashTable));
}

