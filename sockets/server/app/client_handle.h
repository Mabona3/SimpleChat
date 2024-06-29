#ifndef CLIENT_HANDLE_H
#define CLIENT_HANDLE_H

#include <pthread.h>
#include "message_handle.h"

#define MAX_NAME 20
#define MAX_CLNT 25


typedef struct {
    int socket;
    char name[MAX_NAME];
    int name_size;
} clnt;


void send_msg(message *msg,pthread_mutex_t *mutex,int clnt_cnt,clnt *clnt_socks);
char *get_sender_name(int socket,int clnt_cnt,clnt *clnt_socks);
void delete_client(int socket,clnt *clnt_sock,int *clnt_cnt,pthread_mutex_t *mutex);

#endif