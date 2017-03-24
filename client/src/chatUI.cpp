#include "placeholder.h"
#include "../../generic/message.h"
#include "../../generic/message_handler.h"

#include "chatUI.hpp"
#include "chatNetcode.cpp"

#include <exception>

tacopie::tcp_client client;

WINDOW* chatWindow;
int chatLine, chatMaxLines;
int lines, columns;

MessageHandler* outgoingHandler;
MessageHandler* incomingHandler;

const char *username = "User3";
const char *EXIT = "/exit";
const char *HELP = "/help";
const char *EMPTY = "";

int main(int argc, char* argv[])
{
    startChat();
    return 0;
}

void resetInputWindow(WINDOW *inputWindow, const char *username) {
    //clear the current text of the input window
    wclear(inputWindow);
    
    //reset the input window text to display username
    wmove(inputWindow, 0, 0);
    wattron(inputWindow, COLOR_PAIR(5));
    waddstr(inputWindow, username);
    waddstr(inputWindow, ": ");
    wrefresh(inputWindow);
}

void setupWindow(int &lines, int &columns) {
    //the dimensions of the terminal
    getmaxyx(stdscr, lines, columns);
    scrollok(stdscr, true);
    
    //start using ncurses colors and set color pairs.
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLACK, -1);
    init_pair(2, COLOR_CYAN, -1);
    init_pair(3, COLOR_MAGENTA, -1);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    bkgd(COLOR_PAIR(1));
}

void scrollWindowUp(WINDOW *win, int &line, int maxLines) {
    if (line >= maxLines) {
        wscrl(win, 1);
        line = maxLines - 1;
    }
}

void scrollWindowDown(WINDOW *win, int &line, int maxLines) {
    if (line >= maxLines) {
        wscrl(win, -1);
    }
}

void addChatLine(const char* username, const char* message, int color) {
    scrollWindowUp(chatWindow, chatLine, chatMaxLines);
    
    wmove(chatWindow, chatLine, 0);
    wattron(chatWindow, COLOR_PAIR(color));
    if(username) {
        waddstr(chatWindow, username);
        waddstr(chatWindow, ": ");
    }
    waddstr(chatWindow, message);
    wrefresh(chatWindow);
    
    chatLine++;
}

void simChat(const char *message) {
    addChatLine(NULL, message, 2);
}

bool compareArrays(char *array1, const char *array2, int length1, int length2) {
    bool equal = true;
    
    for (int i = 0; i < length1; i++) {
        for (int j = 0; j < length2; j++) {
            if (i == j and array1[i] != array2[j]) {
                equal = false;
            } else if (j > i) {
                break;
            }
        }
    }
    
    return equal;
}

void helpWindow(WINDOW *chatWindow, int columns, int lines, int chatMaxLines) {
    //initialize variables
    int windowColumns = columns / 2;
    
    //shrink the chat window so the help window can be displayed
    wresize(chatWindow, chatMaxLines, windowColumns);
    wrefresh(chatWindow);
    
    //create the help window
    WINDOW *helpWindow = newwin(chatMaxLines, windowColumns, 0, windowColumns);
    wbkgd(helpWindow, COLOR_PAIR(4));
    wborder(helpWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    wattron(helpWindow, A_BOLD);
    
    //provide text for the help window
    wmove(helpWindow, 1, 1);
    waddstr(helpWindow, "Welcome to the Help Menu");
    wmove(helpWindow, 3, 1);
    waddstr(helpWindow, "Command   |   Effect");
    wmove(helpWindow, 4, 1);
    waddstr(helpWindow, "/help     |   presents the help window");
    wmove(helpWindow, 5, 1);
    waddstr(helpWindow, "/exit     |   exit the chat");
    wmove(helpWindow, chatMaxLines - 2, 1);
    waddstr(helpWindow, "Press any key to close this window...");
    wrefresh(helpWindow);
    
    //delete the help window the next time the user presses a button
    wgetch(helpWindow);
    delwin(helpWindow);
    
    //enlarge the chat window to fill the screen again
    wresize(chatWindow, chatMaxLines, columns);
    wrefresh(chatWindow);
}

void sendNormalMessage(const Message* message) {
    fakeServer(message, incomingHandler);
}

void helpMessage(const Message* message) {
    helpWindow(chatWindow, columns, lines, chatMaxLines);
}

void receiveNormalMessage(const Message* message) {
    int userID = message->getUserID();
    int color = getColorID(userID);
    char* user = getUsername(username, userID);
    const char* text = message->getText();
    addChatLine(user, text, color);
}

void startChat() {
    //initialize variables
    int count = 0;
    int inputMaxLines;
    char input[255];
    bool ending = false;
    
    //start using ncurses windows
    initscr();
    setupWindow(lines, columns);
    
    //create chat window
    chatWindow = newwin(lines - 2, columns, 0, 0);
    chatMaxLines = lines - 2;
    
    //create input window
    WINDOW *inputWindow = newwin(2, columns, lines - 2, 0);
    inputMaxLines = 2;
    
    //apply settings to windows
    wbkgd(chatWindow, COLOR_PAIR(1));
    wbkgd(inputWindow, COLOR_PAIR(5));
    
    scrollok(chatWindow, TRUE);
    scrollok(inputWindow, TRUE);

    //setup message handlers
    outgoingHandler = new MessageHandler();
    outgoingHandler->nameTrigger("help", 'H');
    outgoingHandler->registerCallback(helpMessage, 'H');
    outgoingHandler->registerCallback(sendNormalMessage, DEFAULT_TRIGGER);

    incomingHandler = new MessageHandler();
    incomingHandler->registerCallback(receiveNormalMessage, DEFAULT_TRIGGER);

    try
    {
        initNetcode(client, "127.0.0.1");
        // dirty hack to try to see if we can get early
        // reporting working
        simChat("We were successful in initting the TCP connection");
        writeToServer(client, "Test Test 1 2 3");
    }
    catch(std::exception &err)
    {
        simChat(err.what());
    }
    
    //start chat loop, waiting for user responses
    while (!ending) {
        //simulated other user chats
        if (count == 2) {
            simChat("User1: hey Paul");
        } else if (count == 3) {
            simChat("User2: whats up mike");
        } else if (count == 5) {
            simChat("User1: where r u today");
        } else if (count == 6) {
            simChat("User2: at the park");
        }
        
        //reset the input window
        resetInputWindow(inputWindow, username);
        
        //grab user input
        wgetstr(inputWindow, input);
        
        if (compareArrays(input, EXIT, 255, 5)) {
            ending = true;
        } else {
            outgoingHandler->accept(0, 0, input);
        }
        
        count++;
    }
    
    //delete windows and stop using ncurses
    delwin(chatWindow);
    delwin(inputWindow);
    endwin();
    delete outgoingHandler;
    delete incomingHandler;
}
