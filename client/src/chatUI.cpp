
#include "chatUI.hpp"

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

void simChat(WINDOW *chatWindow, int &chatLine, int maxLines, char *text) {
    scrollWindowUp(chatWindow, chatLine, maxLines);
    
    wmove(chatWindow, chatLine, 0);
    wattron(chatWindow, COLOR_PAIR(2));
    waddstr(chatWindow, text);
    wrefresh(chatWindow);
    
    chatLine++;
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
    waddstr(helpWindow, "\\help     |   presents the help window");
    wmove(helpWindow, 5, 1);
    waddstr(helpWindow, "\\exit     |   exit the chat");
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

void startChat() {
    //initialize variables
    int chatLine = 0;
    int count = 0;
    int lines, columns;
    int chatMaxLines, inputMaxLines;
    char input[255];
    const char *username = "User3";
    const char *exit = "\\exit";
    const char *help = "\\help";
    const char *empty = "";
    bool ending = false;
    
    //start using ncurses windows
    initscr();
    setupWindow(lines, columns);
    
    //create chat window
    WINDOW *chatWindow = newwin(lines - 2, columns, 0, 0);
    chatMaxLines = lines - 2;
    
    //create input window
    WINDOW *inputWindow = newwin(2, columns, lines - 2, 0);
    inputMaxLines = 2;
    
    //apply settings to windows
    wbkgd(chatWindow, COLOR_PAIR(1));
    wbkgd(inputWindow, COLOR_PAIR(5));
    
    scrollok(chatWindow, TRUE);
    scrollok(inputWindow, TRUE);
    
    //start chat loop, waiting for user responses
    while (!ending) {
        //simulated other user chats
        if (count == 2) {
            simChat(chatWindow, chatLine, chatMaxLines, "User1: hey Paul");
        } else if (count == 3) {
            simChat(chatWindow, chatLine, chatMaxLines, "User2: whats up mike");
        } else if (count == 5) {
            simChat(chatWindow, chatLine, chatMaxLines, "User1: where r u today");
        } else if (count == 6) {
            simChat(chatWindow, chatLine, chatMaxLines, "User2: at the park");
        }
        
        //reset the input window
        resetInputWindow(inputWindow, username);
        
        //grab user input
        wgetstr(inputWindow, input);
        
        //determine what to do with user input
        if (!compareArrays(input, exit, 255, 5) and !compareArrays(input, help, 255, 5) and *input != *empty) {
            //this is a message for the chat
            
            //scroll chat if needed
            scrollWindowUp(chatWindow, chatLine, chatMaxLines);
            
            //add new message to the chat
            wmove(chatWindow, chatLine, 0);
            wattron(chatWindow, COLOR_PAIR(3));
            waddstr(chatWindow, username);
            waddstr(chatWindow, ": ");
            waddstr(chatWindow, input);
            wrefresh(chatWindow);
            
            chatLine++;
        } else if (compareArrays(input, help, 255, 5)) {
            //this is a request to use the help window
            helpWindow(chatWindow, columns, lines, chatMaxLines);
        } else if (compareArrays(input, exit, 255, 5)) {
            //this is a request to exit the chat
            ending = true;
        }
        
        count++;
    }
    
    //delete windows and stop using ncurses
    delwin(chatWindow);
    delwin(inputWindow);
    endwin();
}
