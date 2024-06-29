#ifndef MESSAGE_HANDLE_H
#define MESSAGE_HANDLE_H
#include <string.h>

#define BUF_SIZE 100

typedef struct {
    char *msg;
    char *name_to;
    int sock_from;
} message;

void parseMessage(message *msg,char *sent_message);

#endif