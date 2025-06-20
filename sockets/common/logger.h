#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define LOG_ERROR(msg, ...)                                                    \
  do {                                                                         \
    fprintf(stderr, "ERROR: ");                                                \
    fprintf(stderr, msg, __VA_ARGS__);                                         \
    fprintf(stderr, "\n");                                                     \
    fflush(stderr);                                                            \
  } while (0)

#define LOG_INFO(msg, ...)                                                     \
  do {                                                                         \
    printf("INFO: ");                                                          \
    printf(msg, __VA_ARGS__);                                                  \
    printf("\n");                                                              \
    fflush(stdout);                                                            \
  } while (0)

#define LOG_DEBUG(msg, ...)                                                    \
  do {                                                                         \
    printf("DEBUG: ");                                                         \
    printf(msg, __VA_ARGS__);                                                  \
    printf("\n");                                                              \
    fflush(stdout);                                                            \
  } while (0)

#endif // LOGGER_H
