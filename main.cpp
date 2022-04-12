#include "stdio.h"
#include "logsLib.h"
#include "List.h"
#include "reader.h"
#include "table.h"

int main()
{
    openLogs("logs.txt");
    FILE *fp = fopen("FILE1", "r");
    if (!fp)    
    {
        printf("Can't open file\n"); 
        return 0;
    }

    Text text = {};
    textCtor(&text);
    
    fillText(fp, &text);

    Hash_Table table = {};
    tableCtor(&table, 10000);

    table.hash = hashRol;

    fillTable (&table, &text);
    checkTable(&table, &text);

    tableDtor(&table);
    textDtor(&text);
    fclose(fp);
    closeLogs();
    return 0;
}
