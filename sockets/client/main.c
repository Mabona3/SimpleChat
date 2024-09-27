#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUF_SIZE 100
#define NAME_SIZE 20

void *send_msg(void *args);
void *recv_msg(void *args);
void error_handling(char *msg);

char name[NAME_SIZE];
char msg[BUF_SIZE];

int main(int argc,char *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    pthread_t send_thread,recv_thread;
    void *thread_return;
    if (argc != 4)
    {
        printf("Usage : %s <IP> <port> <name>\n",argv[0]);
        exit(1);
    }
    sprintf(name,"%s",argv[3]);

    sock = socket(PF_INET,SOCK_STREAM,SOL_IP);

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
        error_handling("connect() error");

    write(sock,name,strlen(name));

    pthread_create(&send_thread,NULL,send_msg,(void *)&sock);
    pthread_create(&recv_thread,NULL,recv_msg,(void *)&sock);
    
    pthread_join(send_thread,&thread_return);
    pthread_join(recv_thread,&thread_return);
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

void *send_msg(void *args)
{
    int sock = *((int *)args);
    char name_msg[NAME_SIZE+BUF_SIZE + 2];

    while (1)
    {
        fgets(msg,BUF_SIZE,stdin);
        if (!strcmp(msg,"q\n") || !strcmp(msg,"Q\n") )
        {
            close(sock);
            exit(0);
        }
        sprintf(name_msg,"%s",msg);
        write(sock,name_msg,strlen(name_msg));
    }
    return NULL;
}

void *recv_msg(void *args)
{
    int sock = *((int *)args);
    char name_msg[NAME_SIZE+BUF_SIZE];
    int len;
    while (1)
    {
        len = read(sock,name_msg,NAME_SIZE + BUF_SIZE - 1);
        if (len == -1)
            return (void*)-1;
        name_msg[len] = '\0';
        fputs(name_msg,stdout);
    }
    return NULL;
}
