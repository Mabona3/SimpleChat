#include "../common/logger.h"
#include "client_handle.h"
#include "message_handle.h"
#include "server_handle.h"
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *handle_clnt(void *args);

int main(int argc, char *argv[]) {
  int serv_sock, clnt_cnt = 0, clnt_sock;
  clnt clnt_socks[MAX_CLNT];
  pthread_mutex_t mutex;
  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_sz;

  pthread_t t_id;
  if (argc != 2) {
    LOG_ERROR("Usage : %s <port>\n", argv[0]);
    exit(1);
  }
  pthread_mutex_init(&mutex, NULL);
  serv_sock = socket(PF_INET, SOCK_STREAM, SOL_IP);
  if (serv_sock == -1)
    error_handling("socket() error");

  Setup(argv[1], serv_sock);

  int len;
  const char *error;

  while (1) {
    clnt_addr_sz = sizeof(clnt_addr);

    if (clnt_cnt != MAX_CLNT) {
      clnt_sock =
          accept(serv_sock, ((struct sockaddr *)&clnt_addr), &clnt_addr_sz);
      if (clnt_sock == -1)
        error_handling("accept() error!");

      pthread_mutex_lock(&mutex);

      clnt_socks[clnt_cnt].socket = clnt_sock;

      len = read(clnt_sock, clnt_socks[clnt_cnt++].name, MAX_NAME);
      switch (
          check_name(clnt_socks[clnt_cnt - 1].name, clnt_cnt - 1, clnt_socks)) {
      case 1:
        error = "[Server] : name is too long used.";
      case 2:
        error = "[Server] : name is too long used.";
        break;
      case 3:
        error = "[Server] : 'all' is not a valid name";
        break;
      case 4:
        error = "[Server] : 'help' is not a valid name";
        break;
      case 5:
        error = "[Server] : 'server' is not a valid name";
        break;
      case 6:
        error = "[Server] : name is already used.";
        break;
      default:
        error = NULL;
      }

      if (error != NULL) {
        write(clnt_sock, error, strlen(error));
        close(clnt_sock);
        clnt_cnt--;
        pthread_mutex_unlock(&mutex);
        continue;
      }

      if (len == -1)
        error_handling("read() error");

      clnt_socks[clnt_cnt - 1].name[len] = '\0';
      clnt_socks[clnt_cnt - 1].name_size = len;
      LOG_INFO("%s joined the chat\n", clnt_socks[clnt_cnt - 1].name);

      pthread_mutex_unlock(&mutex);
    }

    pthread_create(&t_id, NULL, handle_clnt, (void *)&clnt_socks[clnt_cnt - 1]);
    pthread_detach(t_id);
  }
  pthread_mutex_destroy(&mutex);
  close(serv_sock);
  return 0;
}

void *handle_clnt(void *args) {
  clnt *clnt_sock = (clnt *)args;
  int len = 0;
  char msg[BUF_SIZE];

  message *message_obj = (message *)malloc(sizeof(message));

  message_obj->sock_from = clnt_sock->socket;

  while ((len = read(clnt_sock->socket, msg, BUF_SIZE))) {
    if (len == -1)
      error_handling("read() error");

    msg[len] = '\0';

    parseMessage(message_obj, msg);

    send_msg(message_obj, &mutex, clnt_cnt, clnt_socks);
  }
  LOG_INFO("%s left the chat\n", clnt_sock->name);
  delete_client(clnt_sock->socket, clnt_socks, &clnt_cnt, &mutex);
  close(clnt_sock->socket);
  return NULL;
}
