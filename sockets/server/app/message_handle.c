#include "message_handle.h"
#include <stdlib.h>
#include <stdio.h>

void parseMessage(message *msg,char *sent_message)
{
    int size = strlen(sent_message);
    if (sent_message[0] != '@') {
        msg->name_to = "all";
        msg->msg = sent_message;
        return;
    }
    for (int i = 0;i < size;i++) {
        if (sent_message[i] == ' ') {
            msg->name_to = (char *)malloc(sizeof(char) * i);
            strncpy(msg->name_to,sent_message + 1,i - 1);
            msg->msg = (sent_message + i + 1);
            return;
        }
    }
    msg->name_to = sent_message + 1;
    msg->msg = "\n";
}