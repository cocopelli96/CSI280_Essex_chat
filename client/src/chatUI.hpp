#ifndef chatUI_hpp
#define chatUI_hpp

#include <curses.h>
#include "placeholder.h"
#include "message.h"
#include "message_handler.h"
#include "chatNetcode.hpp"
#include "chatLog.hpp"
#include <exception>
#include <panel.h>
#include <menu.h>

void addChatLine(const char* username, const char* message, int color);
void chatLog(char *text);
void chatLog(const char *text);
bool compareArrays(char *array1, const char *array2, int length1, int length2);
void createMenu();
void deleteMenu();
void helpMessage(const Message* message);
void helpWindow(WINDOW *chatWindow, int columns, int lines, int chatMaxLines);
void receiveNormalMessage(const Message* message);
void resetInputWindow(WINDOW *inputWindow, const char *username);
void sendNormalMessage(const Message* message);
void setupWindow(int &lines, int &columns);
void simChat(const char *message);
void scrollWindowDown(WINDOW *win, int &line, int maxLines);
void scrollWindowUp(WINDOW *win, int &line, int maxLines);
void startChat();


#endif
