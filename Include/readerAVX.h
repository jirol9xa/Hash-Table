struct Text
{
    alignas(32) __m256i words[250000];
    int    size;
    int    status;
    int    capacity;
    alignas(32) char   buffer[32];
};


enum ERRORS
{
    INVALID_PTR  = -1,
    INVALID_FILE = -2,
    FUNC_FAILED  = -3,
    MEM_OVEFLOW  = -4,
    ALRDY_EXST   = -5,
    ALRDY_DSTR   = -6,
};


enum STATUSES
{
    EXIST = 1,
    DESTR = 1 << 1,
};


int  fillText(FILE *fp, Text *text);

int textCtor(Text *text, int capacity = 243808);
int textDtor(Text *text);
