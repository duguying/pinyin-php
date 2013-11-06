#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*=================hash table start=========================================*/
#define HASH_TABLE_MAX_SIZE 10000
typedef struct HashNode_Struct HashNode;
struct HashNode_Struct
{
	char *sKey;
	int nValue;
	HashNode *pNext;
};
HashNode *hashTable[HASH_TABLE_MAX_SIZE];	// hash table data strcutrue
int hash_table_size;			// the number of key-value pairs in the hash
								// table!
// initialize hash table
void hash_table_init()
{
	hash_table_size = 0;
	memset(hashTable, 0, sizeof(HashNode *) * HASH_TABLE_MAX_SIZE);
}

// string hash function
unsigned int hash_table_hash_str(const char *skey)
{
	const signed char *p = (const signed char *)skey;
	unsigned int h = *p;
	if (h)
	{
		for (p += 1; *p != '\0'; ++p)
			h = (h << 5) - h + *p;
	}
	return h;
}

// insert key-value into hash table
void hash_table_insert(const char *skey, int nvalue)
{
	if (hash_table_size >= HASH_TABLE_MAX_SIZE)
	{
		printf("out of hash table memory!\n");
		return;
	}
	unsigned int pos = hash_table_hash_str(skey) % HASH_TABLE_MAX_SIZE;
	HashNode *pHead = hashTable[pos];
	while (pHead)
	{
		if (strcmp(pHead->sKey, skey) == 0)
		{
			printf("%s already exists!\n", skey);
			return;
		}
		pHead = pHead->pNext;
	}
	HashNode *pNewNode = (HashNode *) malloc(sizeof(HashNode));
	memset(pNewNode, 0, sizeof(HashNode));
	pNewNode->sKey = (char *)malloc(sizeof(char) * (strlen(skey) + 1));
	strcpy(pNewNode->sKey, skey);
	pNewNode->nValue = nvalue;
	pNewNode->pNext = hashTable[pos];
	hashTable[pos] = pNewNode;

	hash_table_size++;
}

// remove key-value frome the hash table
void hash_table_remove(const char *skey)
{
	unsigned int pos = hash_table_hash_str(skey) % HASH_TABLE_MAX_SIZE;
	if (hashTable[pos])
	{
		HashNode *pHead = hashTable[pos];
		HashNode *pLast = NULL;
		HashNode *pRemove = NULL;
		while (pHead)
		{
			if (strcmp(skey, pHead->sKey) == 0)
			{
				pRemove = pHead;
				break;
			}
			pLast = pHead;
			pHead = pHead->pNext;
		}
		if (pRemove)
		{
			if (pLast)
				pLast->pNext = pRemove->pNext;
			else
				hashTable[pos] = NULL;
			free(pRemove->sKey);
			free(pRemove);
		}
	}
}

// lookup a key in the hash table
HashNode *hash_table_lookup(const char *skey)
{
	unsigned int pos = hash_table_hash_str(skey) % HASH_TABLE_MAX_SIZE;
	if (hashTable[pos])
	{
		HashNode *pHead = hashTable[pos];
		while (pHead)
		{
			if (strcmp(skey, pHead->sKey) == 0)
				return pHead;
			pHead = pHead->pNext;
		}
	}
	return NULL;
}

// free the memory of the hash table
void hash_table_release()
{
	int i;
	for (i = 0; i < HASH_TABLE_MAX_SIZE; ++i)
	{
		if (hashTable[i])
		{
			HashNode *pHead = hashTable[i];
			while (pHead)
			{
				HashNode *pTemp = pHead;
				pHead = pHead->pNext;
				if (pTemp)
				{
					free(pTemp->sKey);
					free(pTemp);
				}
			}
		}
	}
}

/* ===============================hash table end========================= */
