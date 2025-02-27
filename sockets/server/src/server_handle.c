#include "server_handle.h"
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>


void Setup(char *port,int serv_sock) {
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_port = htons(atoi(port));

    // Set the Socket as Reusable.
    int len=1;
    if (setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &len, sizeof(len)) < 0)
        error_handling("setsockopt() error!");

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error_handling("bind() error");

    if (listen(serv_sock, MAX_QUEUE) < 0)
        error_handling("listen() error");

}

void error_handling(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

