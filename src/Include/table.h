#ifndef TABLE_H
    #define TABLE_H
    
    struct Hash_Table
    {
        List       *data;
        int        size;
        int        capacity = 512;
        __uint32_t (*hash) (char *word);
        int        status;
    };

    struct SrchStrct
    {
        List *list;
        int   position;
    };

    enum ERRS
    {
        WRONG_PTR      = -1,
        HASH_OUTOF_RNG = -2, 
        WRONG_FILL_HT  = -3,
        SCND_CREATION  = -4,
        SCND_DESTR     = -5,
    };

    enum STATS
    {
        CRTD        = 1,
        DSTR        = 1 << 1,
        IS_OK       = 1 << 2,
        IS_BRKN     = 1 << 3,
        FILL_ERR    = 1 << 4,
        LIST_ERR    = 1 << 5,
        WRONG_HFUNC = 1 << 6,
        DTOR_ERR    = 1 << 7,
        CTOR_ERR    = 1 << 8,
    };

    __uint32_t hash1     (char *elem);
    __uint32_t hashAscii (char *elem);
    __uint32_t hashLength(char *elem);
    __uint32_t hashSum   (char *elem);
    __uint32_t hashRol   (char *elem);
    __uint32_t hashCrc32 (char *elem);


    int tableCtor(Hash_Table *table, int capacity = 512);
    int tableDtor(Hash_Table *table);

    inline int insertTable(SrchStrct *res, char *word);
    SrchStrct  findHTElem (Hash_Table *table, char *word);
    int        fillTable  (Hash_Table *table, Text *text);
    int        checkTable (Hash_Table *table, Text *text);

#endif