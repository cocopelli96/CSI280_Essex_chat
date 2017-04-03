
#ifndef chatUI_hpp
#define chatUI_hpp

#include <curses.h>

void resetInputWindow(WINDOW *inputWindow, const char *username);

void setupWindow(int &lines, int &columns);

void scrollWindowUp(WINDOW *win, int &line, int maxLines);

void scrollWindowDown(WINDOW *win, int &line, int maxLines);

void addChatLine(const char* username, const char* message, int color);

void simChat(const char *message);

bool compareArrays(char *array1, const char *array2, int length1, int length2);

void helpWindow(WINDOW *chatWindow, int columns, int lines);

void sendNormalMessage(const Message* message);

void helpMessage(const Message* message);

void receiveNormalMessage(const Message* message);

void chatLog(char *text);

void chatLog(const char *text);

void startChat();

#endif
