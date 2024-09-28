#include "../../src/message_handle/message_handle.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char message1[] = "@usernotification";
    message *msg = (message *)malloc(sizeof(message));
    parseMessage(msg, message1);
    printf("---------------------For message '%s'--------------------------------\n", message1);
    printf("The user is '%s'\nThe message is '%s'\n", msg->name_to, msg->msg);

    char message2[] = "@testingwhenthenameismorethansixtyfourletterthisshouldoverflowornothingwillhappen";
    parseMessage(msg, message2);
    printf("---------------------For message '%s'--------------------------------\n", message2);
    printf("The user is '%s'\nThe message is '%s'\n", msg->name_to, msg->msg);

    char message3[] = "@someone message";
    parseMessage(msg, message3);
    printf("---------------------For message '%s'--------------------------------\n", message3);
    printf("The user is '%s'\nThe message is '%s'\n", msg->name_to, msg->msg);

    char message4[] = "This is a broadcast message";
    parseMessage(msg, message4);
    printf("---------------------For message '%s'--------------------------------\n", message4);
    printf("The user is '%s'\nThe message is '%s'\n", msg->name_to, msg->msg);

    char message5[] = "@someone testingwhenthenameismorethansixtyfourletterthisshouldoverflowornothingwillhappen";
    parseMessage(msg, message5);
    printf("---------------------For message '%s'--------------------------------\n", message5);
    printf("The user is '%s'\nThe message is '%s'\n", msg->name_to, msg->msg);

    return 0;
}
