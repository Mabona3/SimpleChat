#include "test.h"
#include <stdlib.h>
#include <stdio.h>

void parseTest() {
    message *msg = (message *)malloc(sizeof(message));
    char *sent_message = "@JohnDoe This the message body";
    parseMessage(msg,sent_message);
    printf("Sending message to  '%s'\n",msg->name_to);
    printf("The Message is '%s'\n",msg->msg);
}

// int main()
// {
//     parseTest();
// }