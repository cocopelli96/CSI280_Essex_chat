#include "command_names.h"

#define TRIGGER(t) do { current_trigger = t; } while(0)
#define NAME(n) do { handler->nameTrigger(n, current_trigger); } while(0)

uint8_t current_trigger = 0;

void COMMANDS(MessageHandler* handler) {

//register command names here...

}
