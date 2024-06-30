#include "client_handle.h"
#include "message_handle.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *get_sender_name(int socket,int clnt_cnt,clnt *clnt_socks)
{
    for (int i = 0;i < clnt_cnt;i++) {
        if (socket == clnt_socks[i].socket) {
            return clnt_socks[i].name;
        }
    }
    return NULL;
}

void send_msg_for_all(message *msg,int clnt_cnt,clnt *clnt_socks) {
    
    char messages[BUF_SIZE + MAX_NAME];

    char *name_from = get_sender_name(msg->sock_from,clnt_cnt,clnt_socks);

    sprintf(messages,"[%s] %s",name_from,msg->msg);

    int len = strlen(messages);

    for (int i = 0;i < clnt_cnt;i++)
    {   
        write((clnt_socks + i)->socket,messages,len);
    }
}

void send_server_responses(message *msg,int clnt_cnt,clnt *clnt_socks) {
    char *message;
    if (strcmp(msg->msg,"-u\n") == 0) {
        for (int i = 0;i < clnt_cnt;i++) {
            message = clnt_socks[i].name;
            
            write(msg->sock_from,message,strlen(message));
            write(msg->sock_from,NEW_LINE,strlen(NEW_LINE));
        }
    }
    else {
        message = "-u: get all users on the servers\n";
        write(msg->sock_from,message,strlen(message));
    }
}

void send_private_msg(message *msg,int clnt_cnt,clnt *clnt_socks) {
    
    char messages[BUF_SIZE + (MAX_NAME << 1) + 3];

    char *name_from = get_sender_name(msg->sock_from,clnt_cnt,clnt_socks);

    sprintf(messages,"%s->%s %s",name_from,msg->name_to,msg->msg);

    int len = strlen(messages);

    for (int i = 0;i < clnt_cnt;i++) {
        if (strcmp((clnt_socks + i)->name,msg->name_to) == 0) {
            write((clnt_socks + i)->socket,messages,len);
            return;
        }
    }
    // If the user not found nothing will happen 
}

void send_msg(message *msg,pthread_mutex_t *mutex,int clnt_cnt,clnt *clnt_socks) {
    pthread_mutex_lock(mutex);
    if (strcmp(msg->name_to,"all") == 0) {
        send_msg_for_all(msg,clnt_cnt,clnt_socks);
    }
    else if (strncmp(msg->name_to,"server",strlen("server")) == 0) {
        send_server_responses(msg,clnt_cnt,clnt_socks);
    }
    else {
        send_private_msg(msg,clnt_cnt,clnt_socks);
    }
    pthread_mutex_unlock(mutex);
}


void delete_client(int socket,clnt *clnt_socks,int *clnt_cnt,pthread_mutex_t *mutex)
{   
    pthread_mutex_lock(mutex);
    
    for (int i = 0;i < *clnt_cnt;i++)
    {
        if (socket == clnt_socks[i].socket)
        {
            while (i < *clnt_cnt-1)
            {
                clnt_socks[i] = clnt_socks[i+1];
                i++;
            }
            break;
        }
    }
    (*clnt_cnt)--;
    pthread_mutex_unlock(mutex);
}