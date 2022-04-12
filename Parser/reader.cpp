#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "reader.h"


#define PRINT_LINE printf("[%s:%d]\n", __func__, __LINE__);

#define IS_RESIZE(text)                                             \
{                                                                   \
    int size     = text->size;                                      \
    int capacity = text->capacity;                                  \
    bool upper   = size >= capacity - 1;                            \
    bool lower   = size < capacity / 2;                             \
                                                                    \
    if (upper || lower)     textResize(text, upper + !lower);       \
}                               


const char BAD_SYMBS[] = "'!@#$%^&*()_+-?></.,,\"";


static long fileLength(FILE *fp);
static int  readFile(FILE *fp, long length, Text *text);
static int  textResize(Text *text, int is_upper);
static void printErr(int error);


int  fillText(FILE *fp, Text *text)
{    
    if (!fp || !text)   return INVALID_PTR;

    readFile(fp, fileLength(fp), text);

    return 0;
}


static long fileLength(FILE *fp)
{
    if (!fp)    return INVALID_PTR;

    long length = 0;

    #define FSEEK(param)                                \
    {                                                   \
        if (fseek(fp, 0L, SEEK_##param))                \
        {                                               \
            printf("In %s fseek failed\n", __func__);   \
            return FUNC_FAILED;                         \
        }                                               \
    }

    FSEEK(END);
    length = ftell(fp);
    FSEEK(SET);

    #undef FSEEK

    return length;
}


static int  readFile(FILE *fp, long length, Text *text)
{
    if (!fp || !text)     return INVALID_PTR;

    char *buffer = (char *) calloc(length + 1, sizeof(char));

    length = fread(buffer, sizeof(char), length, fp);
    buffer[length] = '\0';

    IS_RESIZE(text);
    text->words[text->size] = buffer;
    text->size++;

    for (int i = 1; i < length; ++i)
    {
        if (strchr(BAD_SYMBS, buffer[i]))   buffer[i] = ' ';
        if (buffer[i] == ' ' || buffer[i] == '\n')
        {
            buffer[i] = '\0';

            if (i + 1 < length && buffer[i + 1] != ' ' && buffer[i + 1] != '\n')
            {
                IS_RESIZE(text);
                text->words[text->size] = buffer + i + 1;
                text->size++;
                ++i;
            }
        }
    }

    return text->size;
};


static int textResize(Text *text, int is_upper)
{
    if (!text)  return INVALID_PTR;

    int capacity   = text->capacity;
    capacity       = (capacity * 2 + !capacity) * is_upper + !is_upper * (capacity / 2);
    text->capacity = capacity;

    void *temp_ptr = realloc(text->words, capacity * sizeof(char *));
    if (!temp_ptr)  return MEM_OVEFLOW;
        
    text->words = (char **) temp_ptr;

    return 0;
}


int textCtor(Text *text, int capacity)
{
    if (!text)          return INVALID_PTR;
    if (text->status)   return ALRDY_EXST;

    text->capacity = capacity;

    text->words = (char **) calloc (capacity, sizeof(char *));

    text->status |= EXIST;

    return 0;
}


int textDtor(Text *text)
{
    if (!text)                  return INVALID_PTR;
    if (text->status & DESTR)   return ALRDY_DSTR;

    //for (int i = 0; i < text->size; ++i)
    //{
    //    free(text->words[i]);
    //}

    free(text->words[0]);
    free(text->words);

    text->status |= DESTR;
    return 0;
}


static void printErr(int error)
{
    switch (error)
    {
    case INVALID_PTR:
        printf("INVALID PTR in ");
        PRINT_LINE;
        break;
    case INVALID_FILE:
        printf("INVALID FILE in ");
        PRINT_LINE;
        break;
    case FUNC_FAILED:
        printf("FUNC FAILED in ");
        PRINT_LINE;
        break;    
    case MEM_OVEFLOW:
        printf("MEM OVERFLOW in ");
        PRINT_LINE;
        break;
    case ALRDY_EXST:
        printf("ALRDY_EXST in ");
        PRINT_LINE;
        break;
    case ALRDY_DSTR:
        printf("ALRDY_DSTR in ");
        PRINT_LINE;
        break;
    }
}