#ifndef MSG_HANDLE_H
#define MSG_HANDLE_H

#define BUF_SIZE 100
#define NAME_SIZE 20

static char name[NAME_SIZE];
static char msg[BUF_SIZE];

typedef struct {
  char *msg_from;
  char *msg;
} message_parsed;


int parse_msg(char *msg);

#endif // MSG_HANDLE_H
