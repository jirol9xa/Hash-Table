#include "stdio.h"
#include "logsLib.h"
#include "List.h"
#include "reader.h"
#include "table.h"
#include "string.h"
#include <ctime>

extern "C" unsigned int crc32(char *elem);

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

    table.hash = crc32;
;

    fillTable (&table, &text);
    checkTable(&table, &text);

    unsigned int end_time = clock();

    printf("run time = %d\n", end_time - start_time);

    //int sum  = 0;
    //for (int i = 0; i < table.capacity; ++i)
    //{
    //    sum += table.data[i].size - 1;
    //    //printf("size = %d\n", table.data[i].size);
    //}
    //
    //printf("Words amnt = %d\n", sum);
    //printf("text size = %d, table size = %d\n", text.size, table.size);
    //
    //FILE *output = fopen("Table hashRol.txt", "w");
    //for (int i = 0; i < 1024; ++i)
    //    fprintf(output, "%d %d\n", i, table.data[i].size - 1);
    //fclose(output);

    tableDtor(&table);
    textDtor(&text);
    fclose(fp);
    return 0;
}
