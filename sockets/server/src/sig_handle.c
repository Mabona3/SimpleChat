#include "sig_handle.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void assign_intr() {
  struct sigaction *act = malloc(sizeof(struct sigaction));
  act->sa_flags = SA_INTERRUPT;

  sigaction(SIGINT, act, act);
}
