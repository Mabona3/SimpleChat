#ifndef SERVER_HANDLE_H
#define SERVER_HANDLE_H

#define MAX_QUEUE 5

void error_handling(char *msg);
void Setup(char *port,int serv_sock);

#endif // !SERVER_HANDLE