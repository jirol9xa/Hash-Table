#include "stdio.h"
#include "stdlib.h"
#include <immintrin.h>
#include "ListAVX.h"
#include "readerAVX.h"
#include "tableAVX.h"
#include "string.h"


#define ERR(param)                              \
{                                               \
    fprintf(stderr, "!!!ERROR %s!!! ", #param); \
    PRINT_LINE;                                 \
    return param;                               \
}
#define TABLE_ASSERT(table)                                     \
{                                                               \
    tableVerify(table);                                         \
    if (table->status > (IS_OK | CRTD | DESTR)) ERR(IS_BRKN);   \
}   


static inline int makeRor(int hash);

static int tableVerify(Hash_Table *table);


u_int32_t hash1(char *elem) 
{
    if (!elem)  ERR(ERRS::WRONG_PTR);
    
    return 1; 
}


u_int32_t hashAscii(char *elem)
{
    if (!elem)  ERR(ERRS::WRONG_PTR);

    return elem[0];
}


u_int32_t hashLength(char *elem)
{
    if (!elem)  ERR(ERRS::WRONG_PTR);

    int i = 0;

    while (elem[i] != '\0') ++i;

    return i;
}


u_int32_t hashSum(char *elem)
{
    if (!elem)  ERR(ERRS::WRONG_PTR);

    int sum = 0, 
        i   = 0;
    
    while (elem[i] != '\0')
    {
        i++;
        sum += elem[i];
        //fprintf(stderr, "symb = %c, code = %u\n", elem[i], elem[i]);
    }

    //fprintf(stderr, "word = %s, i = %d\n", elem, i);

    return sum;
}


u_int32_t hashRol(char *elem)
{
    if (!elem)  ERR(ERRS::WRONG_PTR);

    int i    = 1,
        hash = elem[0];
    while (elem[i] != '\0')
    {
        int temp_hash = hash;
        
        makeRor(hash);
        
        i++;
    }

    return hash;
}

static inline int makeRor(int hash)
{
    int temp_hash = hash;
    
    return ((hash >> 1) | (temp_hash << 31));
}


SrchStrct findHTElem(Hash_Table *table, __m256i word)
{
    SrchStrct res = {};

    if (!table)
    {
        fprintf(stderr, "!!!ERROR WRONG_PTR!!! in [%s:%d]\n", __func__, __LINE__);
        res.position = -1;
        
        return res;
    }

    u_int32_t hash =  0xFFFFFFFF;
    hash = (_mm_crc32_u64(hash, _mm256_extract_epi64(word, 0)));
    hash = (_mm_crc32_u64(hash, _mm256_extract_epi64(word, 1)));
    hash = (_mm_crc32_u64(hash, _mm256_extract_epi64(word, 2)));
    hash = (_mm_crc32_u64(hash, _mm256_extract_epi64(word, 3)));

    hash %= table->capacity;

    //if (hash == 1)  printf("XUIXUIXUI\n");
    //printf("hash = %d\n", hash);

    //u_int32_t hash = (_mm_crc32_u8(_mm256_extract_epi8(word, 0),  8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 1),  8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 2),  8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 3),  8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 4),  8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 5),  8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 6),  8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 7),  8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 8),  8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 9),  8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 10), 8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 11), 8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 12), 8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 13), 8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 14), 8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 15), 8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 16), 8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 17), 8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 18), 8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 19), 8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 20), 8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 21), 8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 22), 8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 23), 8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 24), 8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 25), 8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 26), 8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 27), 8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 28), 8) +
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 29), 8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 30), 8) + 
    //                  _mm_crc32_u8(_mm256_extract_epi8(word, 31), 8)
    //                  ) % (table->capacity);
    //                  
    if (hash > table->capacity)
    {
        // mb expand the hash table, but not now
        fprintf(stderr, "!!!ERROR HASH OUT OF RANGE!!! in ");
        res.position = -1;
        
        return res;
    }

    res.list = &(table->data[hash]);
    res.position = findElemStr(res.list, word);

    return res;
}


inline int insertTable(SrchStrct *res, __m256i word)
{
    if (!res)    ERR(ERRS::WRONG_PTR);

    listPushBack(res->list, word);

    return 0;
}


int fillTable(Hash_Table *table, Text *text)
{
    if (!table || !text)    ERR(ERRS::WRONG_PTR);
    TABLE_ASSERT(table);

    SrchStrct   place = {};

    for (int i = 0; i < text->size; ++i)
    {
        place = findHTElem(table, text->words[i]);  // now we have list and place of elem

        if (place.position == -1)                   // if it's new elem -> add to table
        {   
            insertTable(&place, text->words[i]);
            table->size++;
        }    
    }

    return 0;
}


int checkTable(Hash_Table *table, Text *text)
{
    if (!table || !text)    ERR(ERRS::WRONG_PTR);
    TABLE_ASSERT(table);

    SrchStrct   place;

    for (int i = 0; i < text->size; ++i)
    {
        place = findHTElem(table, text->words[i]);

        if (place.position == -1)   
        {
            ERR(WRONG_FILL_HT);
        }
    }

    fprintf(stderr, "Table is ok\n");

    return 0;
}


int tableCtor(Hash_Table *table, int capacity)
{
    if (!table)     ERR(ERRS::WRONG_PTR);
    if (table->status & CRTD)   ERR(ERRS::SCND_CREATION);
    
    table->capacity = capacity;

    table->data = (List *) aligned_alloc(32, capacity * sizeof(List));

    for (int i = 0; i < capacity; ++i)
    {
        listCtor(&(table->data[i]), 1024);
    }

    table->status |= STATS::CRTD;

    TABLE_ASSERT(table);
    return 0;
}


int tableDtor(Hash_Table *table)
{
    if (!table)     ERR(ERRS::WRONG_PTR);
    if (table->status & STATS::DSTR)    ERR(ERRS::SCND_DESTR);

    for (int i = 0; i < table->capacity; ++i)
    {
        listDtor(&(table->data[i]));
    }

    free(table->data);
    table->status = STATS::DSTR;

    TABLE_ASSERT(table);
    return 0;
}


int tableVerify(Hash_Table *table)
{
    if (!table)     ERR(ERRS::WRONG_PTR);

    List lst    = {};
    int  status = 0;

    //for (int i = 0; i < table->capacity; ++i)
    //{
    //    lst = table->data[i];
    //
    //    verifyList(&lst);
    //
    //    status = lst.status;
    //
    //    if (status & (DISJOINTED_LIST | NOT_RESIZED | EMPTY_ELEM_ERROR))
    //        table->status |= LIST_ERR | IS_BRKN;
    //}

    //if (table->size > table->capacity)          table->status |= NOT_RESIZED | IS_BRKN;
    //if (table->size > 0 && !table->hash)        table->status |= WRONG_HFUNC | IS_BRKN;
    if (table->status & CRTD && !table->data)   table->status |= CTOR_ERR    | IS_BRKN;   

    return 0;
}