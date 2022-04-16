#include "stdio.h"
#include "logsLib.h"
#include <immintrin.h>
#include "List.h"
#include "readerAVX.h"
#include "tableAVX.h"
#include "string.h"

int main()
{
    FILE *fp = fopen("FILE1", "r");
    if (!fp)    
    {
        fprintf(stderr, "Can't open file\n"); 
        return 0;
    }

    Text text = {};
    textCtor(&text);
    
    fillText(fp, &text);

    Hash_Table table = {};
    tableCtor(&table, 1024);

    fillTable (&table, &text);
    checkTable(&table, &text);

    int sum  = 0;
    for (int i = 0; i < table.capacity; ++i)
    {
        sum += table.data[i].size;
        //printf("size = %d\n", table.data[i].size);
    }

    printf("Words amnt = %d\n", sum);
    printf("text size = %d, table size = %d\n", text.size, table.size);

    tableDtor(&table);
    textDtor(&text);
    fclose(fp);
    return 0;
}
