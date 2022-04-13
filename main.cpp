#include "stdio.h"
#include "logsLib.h"
#include "List.h"
#include "reader.h"
#include "table.h"
#include "string.h"

int main()
{
    FILE *fp = fopen("FILE1", "r");
    if (!fp)    
    {
        printf("Can't open file\n"); 
        return 0;
    }

    Text text = {};
    textCtor(&text);
    
    fillText(fp, &text);

    for (int i = 0; i < text.size; ++i)
    {
        if (strlen(text.words[i]) >= 20)    printf("Long long\n");
    }

    printf("text size = %d\n", text.size);

    Hash_Table table = {};
    tableCtor(&table, 1024);

    table.hash = hashRol;

    fillTable (&table, &text);
    checkTable(&table, &text);

    int sum = 0,
        nulls = 0;
    for (int i = 0; i < table.capacity; ++i)
    {
        sum += table.data[i].size;

        if (!table.data[i].size)    nulls++;
    }

    printf("sum = %d, avg = %lg, nulls = %d\n", sum, (double) sum / 1024, nulls);

    tableDtor(&table);
    printf("%p\n", table.data);
    textDtor(&text);
    fclose(fp);
    return 0;
}
