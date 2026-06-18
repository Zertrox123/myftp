/*
** EPITECH PROJECT, 2026
** 2nd_year
** File description:
** server_init
*/

#include "../include/my.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>

int init_server(int port)
{
    int server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adress;
    int op = 1;

    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op)) < 0) {
        close(server);
        return -1;
    }
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = INADDR_ANY;
    adress.sin_port = htons(port);
    if (bind(server, (struct sockaddr *)&adress, sizeof(adress)) < 0) {
        close(server);
        return -1;
    }
    if (listen(server, 10) < 0) {
        close(server);
        return -1;
    }
    return server;
}

void init_poll_clients(struct pollfd *nb, client_t *client, int size)
{
    for (int i = 0; i < size; i++) {
        nb[i].fd = -1;
        client[i].fd = -1;
        client[i].logged = 0;
        client[i].user = NULL;
        client[i].home = NULL;
        client[i].cwd = NULL;
        client[i].pasv_fd = -1;
        client[i].port_mode = 0;
        client[i].buf_len = 0;
    }
}
