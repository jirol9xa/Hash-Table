#include <stdio.h>
#include "./reader.hpp"

int main()
{
    FILE *fp = fopen("FILE", "r");
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
        printf("word = %s\n", text.words[i]);
    }

    textDtor(&text);
    fclose(fp);
    return 0;
}