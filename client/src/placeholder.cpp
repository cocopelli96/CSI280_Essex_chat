#include "placeholder.h"


int getColorID(int user_id)
{
    return user_id ? 2 : 3;
}


char* getUsername(const char* local_username, int user_id)
{
    static char buf[50];
    
    if(user_id)
    {
        snprintf(buf, 50, "User%d", user_id);
    }
    else
    {
        snprintf(buf, 50, "%s", local_username);
    }
    
    return buf;
}


void fakeServer(const Message* message, MessageHandler* handler)
{
    handler->accept(message);
}
