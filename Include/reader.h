struct Text
{
    char **words;
    int    size;
    int    status;
    int    capacity;
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

int textCtor(Text *text, int capacity = 1000);
int textDtor(Text *text);
