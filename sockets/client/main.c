#include "msg_handle.h"
#include "thread_func.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void error_handling(char *msg);

int main(int argc, char *argv[]) {
  int sock;
  struct sockaddr_in serv_addr;
  pthread_t send_thread, recv_thread;
  void *thread_return;
  if (argc != 4) {
    printf("Usage : %s <IP> <port> <name>\n", argv[0]);
    exit(1);
  }
  sprintf(name, "%s", argv[3]);

  sock = socket(PF_INET, SOCK_STREAM, SOL_IP);

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_family = PF_INET;
  serv_addr.sin_port = htons(atoi(argv[2]));

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    error_handling("connect() error");

  write(sock, name, strlen(name));
  read(sock, msg, BUF_SIZE);

  if (!strcmp(msg, "[Server] : Name is already used.")) {
    close(sock);
    error_handling(msg);
  } else if (!strcmp(msg, "[Server] : Name should be more than 3.")) {
    close(sock);
    error_handling(msg);
  }
  pthread_create(&send_thread, NULL, send_msg, (void *)&sock);
  pthread_create(&recv_thread, NULL, recv_msg, (void *)&sock);

  pthread_join(send_thread, &thread_return);
  pthread_join(recv_thread, &thread_return);
  close(sock);
  return 0;
}

void error_handling(char *msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}
