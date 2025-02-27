#include <string.h>
#include <stdlib.h>
#include "message_handle.h"

void parseMessage(message *msg,char *sent_message) {
    // Setting the broadcast messages.
    if (sent_message[0] != '@') {
        msg->name_to = "all";
        msg->msg = sent_message;
        return;
    }

    char *name_end = strstr(sent_message, " ");
    if (name_end != NULL) {
        *(name_end) = '\0';
        msg->name_to= strstr(sent_message, "") + 1;
        msg->msg= name_end + 1; 
    } else {
        msg->name_to = sent_message + 1;
        msg->msg = NEW_LINE;
    }
}
