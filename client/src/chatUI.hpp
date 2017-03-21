
#ifndef chatUI_hpp
#define chatUI_hpp

#include <ncurses.h>

void resetInputWindow(WINDOW *inputWindow, const char *username);

void setupWindow(int &lines, int &columns);

void scrollWindowUp(WINDOW *win, int &line, int maxLines);

void scrollWindowDown(WINDOW *win, int &line, int maxLines);

void simChat(WINDOW *chatWindow, int &chatLine, int maxLines, char *text);

bool compareArrays(char *array1, const char *array2, int length1, int length2);

void helpWindow(WINDOW *chatWindow, int columns, int lines);

void startChat();

#endif
