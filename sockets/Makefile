#!/usr/bin/bash

CC = gcc
LDFLAGS = -pthread -g -Wall -Wextra -pedantic

SRV_DIR := server
SRC_DIR := src

SRV_HEADER := $(shell find ./$(SRV_DIR)/$(SRC_DIR) -name '*.c' -or -name "*.cpp") 

CLNT_DIR := client

CLNT_HEADER := $(shell find ./$(CLNT_DIR)/$(SRC_DIR) -name '*.c' -or -name "*.cpp") 

.PHONY: server client
.SILENT:

build: server client

server: $(SRV_DIR)/main.c
	echo "Making server"
	$(CC) $< $(SRV_HEADER) -o server/server ${LDFLAGS}

client: $(CLNT_DIR)/main.c
	echo "Making client"
	$(CC) $< -o client/client ${LDFLAGS}

