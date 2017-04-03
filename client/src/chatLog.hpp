
#ifndef chatLog_hpp
#define chatLog_hpp

#include <stdio.h>

void logChatLine(char *text, const char *fileName);

void logChatLine(const char *text, const char *fileName);

void getChatLine(const char *fileName, int lineNum, char *text);

void deleteChatLog(const char *fileName);

#endif /* chatLog_hpp */
