#include "chatUI.hpp"
#include "message_handler.h"
#include <string.h>
#include <functional>

tacopie::tcp_client client;

WINDOW* chatWindow;
WINDOW *inputWindow;
WINDOW *menuWindow;

ITEM *menuItems[10];

MENU *chatMenu;

int chatLine, chatMaxLines;
int lines, columns, menuColumns;
int logLines = 0;
const int inputMaxLines = 2;

MessageHandler* outgoingHandler;
MessageHandler* incomingHandler;

char *username = NULL;
const char *EXIT = "/exit";
const char *HELP = "/help";
const char *EMPTY = "";
char fileName[1024];

char* hostname;

bool ending = false;

int main(int argc, char* argv[])
{
    if(argc < 2) {
        fprintf(stderr, "USAGE: %s HOSTNAME\n", argv[0]);
        return 1;
    } else {
        hostname = argv[1];
    }
    time_t timestamp;
    time (&timestamp);
    struct tm *local_timestamp = localtime(&timestamp);
    strftime(fileName, 1024, "chatter_log_%T_%F.txt", local_timestamp);
    username = strdup("<guest>");
    startChat();
    return 0;
}


void addChatLine(const char* username, const char* message, int color)
{
    char text[255];
    scrollWindowUp(chatWindow, chatLine, chatMaxLines);
    
    wmove(chatWindow, chatLine, 0);
    wattron(chatWindow, COLOR_PAIR(color));
    if(username)
    {
        //waddstr(chatWindow, username);
        //waddstr(chatWindow, ": ");
        
        chatLog(username);
        chatLog(": ");
    }
    //waddstr(chatWindow, message);
    
    chatLog(message);
    chatLog("\n");
    
    getChatLine(fileName, logLines - 1, text);
    waddstr(chatWindow, text);
    wrefresh(chatWindow);
    
    chatLine++;
}


void chatLog(char *text)
{
    logChatLine(text, fileName);
    logLines++;
}


void chatLog(const char *text)
{
    logChatLine(text, fileName);
    logLines++;
}


void createMenu()
{
    menuItems[0] = new_item("Lobby", "");
    //menuItems[1] = new_item("chat 2", "");
    chatMenu = new_menu(menuItems);
    
    menuWindow = menu_win(chatMenu);
    wresize(menuWindow, lines, menuColumns);
    box(menuWindow, 0, 0);
    wbkgd(menuWindow, COLOR_PAIR(1));
    set_menu_sub(chatMenu, derwin(menuWindow, lines - 2, menuColumns - 2, 1, 1));
    set_menu_mark(chatMenu, "");
    
    post_menu(chatMenu);
    refresh();
}


void deleteMenu()
{
    unpost_menu(chatMenu);
    free_menu(chatMenu);
    
    for (int i = 0; i < 10; i++)
    {
        free_item(menuItems[i]);
    }
}

void helpMessage(const Message* message)
{
    helpWindow(chatWindow, columns, lines, chatMaxLines);
}

void setUsername(const Message* message)
{
    free(username);
    username = strdup(message->getText());
}

void exitChatter(const Message* message)
{
    ending = true;
}

void helpWindow(WINDOW *chatWindow, int columns, int lines, int chatMaxLines)
{
    //initialize variables
    int windowColumns = columns / 2;
    
    //create the help window
    WINDOW *helpWindow = newwin(chatMaxLines, windowColumns, 0, windowColumns / 2);
    wbkgd(helpWindow, COLOR_PAIR(4));
    wborder(helpWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    wattron(helpWindow, A_BOLD);
    
    //create panel for the window
    PANEL *helpPanel = new_panel(helpWindow);
    
    //provide text for the help window
    wmove(helpWindow, 1, 1);
    waddstr(helpWindow, "Welcome to the Help Menu");
    wmove(helpWindow, 3, 1);
    waddstr(helpWindow, "Command     |   Effect");
    wmove(helpWindow, 4, 1);
    waddstr(helpWindow, "/help       |   presents the help window");
    wmove(helpWindow, 5, 1);
    waddstr(helpWindow, "/login NAME |   sets your username to NAME");
    wmove(helpWindow, 6, 1);
    waddstr(helpWindow, "/exit       |   exit the chat");
    wmove(helpWindow, chatMaxLines - 2, 1);
    waddstr(helpWindow, "Press any key to close this window...");
    wrefresh(helpWindow);
    
    //update panels
    update_panels();
    doupdate();
    
    //delete the help window the next time the user presses a button
    wgetch(helpWindow);
    del_panel(helpPanel);
    delwin(helpWindow);
    
    //update panels
    update_panels();
    doupdate();
}


void receiveNormalMessage(const Message* message)
{
    int userID = message->getUserID();
    int color = getColorID(userID);
    char* user = getUsername(username, userID);
    const char* text = message->getText();
    addChatLine(user, text, color);
}


void resetInputWindow(WINDOW *inputWindow, const char *username)
{
    //clear the current text of the input window
    wclear(inputWindow);
    
    //reset the input window text to display username
    wmove(inputWindow, 0, 0);
    wattron(inputWindow, COLOR_PAIR(5));
    waddstr(inputWindow, username);
    waddstr(inputWindow, ": ");
    wrefresh(inputWindow);
}


void sendNormalMessage(const Message* message)
{
    std::string text = username;
    text += ": ";
    text += std::string{message->getText()};
    writeToServer(client, text);
}


void setupWindow(int &lines, int &columns)
{
    //the dimensions of the terminal
    getmaxyx(stdscr, lines, columns);
    menuColumns = columns / 5;
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


void simChat(const char *message)
{
    addChatLine(NULL, message, 2);
}



void scrollWindowDown(WINDOW *win, int &line, int maxLines)
{
    if (line >= maxLines) {
        wscrl(win, -1);
    }
}


void scrollWindowUp(WINDOW *win, int &line, int maxLines)
{
    if (line >= maxLines) {
        wscrl(win, 1);
        line = maxLines - 1;
    }
}


void startChat()
{
    //initialize variables
    int count = 0;
    char input[255];
    
    //start using ncurses windows
    initscr();
    setupWindow(lines, columns);
    
    //create chat window
    chatMaxLines = lines - inputMaxLines;
    chatWindow = newwin(chatMaxLines, menuColumns * 4, 0, menuColumns);
    
    PANEL *chatPanel = new_panel(chatWindow);
    
    //create input window
    inputWindow = newwin(inputMaxLines, menuColumns * 4, chatMaxLines, menuColumns);
    
    //apply settings to windows
    wbkgd(chatWindow, COLOR_PAIR(1));
    wbkgd(inputWindow, COLOR_PAIR(5));
    
    scrollok(chatWindow, TRUE);
    scrollok(inputWindow, TRUE);
    
    createMenu();

    //setup message handlers
    outgoingHandler = new MessageHandler();
    outgoingHandler->nameTrigger("help", 'H');
    outgoingHandler->registerCallback(helpMessage, 'H');
    outgoingHandler->nameTrigger("login", 'L');
    outgoingHandler->registerCallback(setUsername, 'L');
    outgoingHandler->nameTrigger("exit", 'E');
    outgoingHandler->registerCallback(exitChatter, 'E');
    outgoingHandler->registerCallback(sendNormalMessage, DEFAULT_TRIGGER);

    incomingHandler = new MessageHandler();
    incomingHandler->registerCallback(receiveNormalMessage, DEFAULT_TRIGGER);

    try
    {
        initNetcode(client, hostname);
        // dirty hack to try to see if we can get early
        // reporting working
        writeToServer(client, "A user has connected!");
        simChat("We were successful in initting the TCP connection");
	simChat("Type /help for help, or /login USERNAME to set a username");
    }
    catch(std::exception &err)
    {
        simChat(err.what());
    }
    
    //start chat loop, waiting for user responses
    while (!ending)
    {
        //reset the input window
        resetInputWindow(inputWindow, username);
        
        //grab user input
        wgetstr(inputWindow, input);
        outgoingHandler->accept(0, 0, input);
        
        count++;
    }
    
    deleteMenu();
    
    //delete windows and stop using ncurses
    del_panel(chatPanel);
    delwin(chatWindow);
    delwin(inputWindow);
    endwin();
    delete outgoingHandler;
    delete incomingHandler;
}
