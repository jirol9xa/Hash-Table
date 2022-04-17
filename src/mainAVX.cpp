#include "stdio.h"
#include "logsLib.h"
#include <immintrin.h>
#include "List.h"
#include "readerAVX.h"
#include "tableAVX.h"
#include "string.h"
#include <ctime>

int main()
{
    FILE *fp = fopen("src/FILE1", "r");
    if (!fp)    
    {
        fprintf(stderr, "Can't open file\n"); 
        return 0;
    }

    unsigned int start_time = clock();

    Text text = {};
    textCtor(&text);
    
    fillText(fp, &text);

    Hash_Table table = {};
    tableCtor(&table, 1024);

    fillTable (&table, &text);
    checkTable(&table, &text);

    unsigned int end_time = clock();

    printf("time =  %d\n", end_time - start_time);

    //int sum  = 0;
    //for (int i = 0; i < table.capacity; ++i)
    //{
    //    sum += table.data[i].size;
    //    //printf("size = %d\n", table.data[i].size);
    //}
    //
    //printf("Words amnt = %d\n", sum);
    //printf("text size = %d, table size = %d\n", text.size, table.size);

    tableDtor(&table);
    textDtor(&text);
    fclose(fp);
    return 0;
}
