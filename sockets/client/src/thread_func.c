#include "thread_func.h"
#include "msg_handle.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void *send_msg(void *args) {
  int sock = *((int *)args);
  char name_msg[NAME_SIZE + BUF_SIZE + 2];

  while (1) {
    fgets(msg, BUF_SIZE, stdin);
    if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) {
      close(sock);
      exit(0);
    }
    sprintf(name_msg, "%s", msg);
    write(sock, name_msg, strlen(name_msg));
  }
  return NULL;
}

void *recv_msg(void *args) {
  int sock = *((int *)args);
  char name_msg[NAME_SIZE + BUF_SIZE];
  int len;
  while (1) {
    len = read(sock, name_msg, NAME_SIZE + BUF_SIZE - 1);
    if (len == -1)
      return (void *)-1;
    name_msg[len] = '\0';
    fputs(name_msg, stdout);
  }
  return NULL;
}
