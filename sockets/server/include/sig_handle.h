#ifndef SIG_HANDLE_H
#define SIG_HANDLE_H

/*
 * Handles the interrupt signal to close all the clients connected to it before
 * closing by sending the closing flag
 */
void intr_handle(int sig);

#endif // SIG_HANDLE_H
