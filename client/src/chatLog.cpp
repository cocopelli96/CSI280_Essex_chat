
#include "chatLog.hpp"
#include <stdio.h>

void logChatLine(char *text, const char *fileName)
{
    FILE *file = fopen(fileName, "a");
    
    if (file != NULL)
    {
        fputs(text, file);
    }
    
    fclose(file);
}

void logChatLine(const char *text, const char *fileName)
{
    FILE *file = fopen(fileName, "a");
    
    if (file != NULL)
    {
        fputs(text, file);
    }
    
    fclose(file);
}

void getChatLine(const char *fileName, int lineNum, char *text)
{
    int count = 0;
    
    FILE *file = fopen(fileName, "r");
    
    if (file != NULL)
    {
        while (!feof(file))
        {
            fgets(text, 255, file);
            
            if (count == lineNum)
            {
                break;
            }
            
            count++;
        }
    }
    
    fclose(file);
}

void deleteChatLog(const char *fileName)
{
    remove(fileName);
}
