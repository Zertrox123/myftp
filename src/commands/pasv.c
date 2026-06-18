/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** pasv.c
*/

#include "../../include/my.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int pasv_cmd(client_t *client)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    char msg[128];

    if (client->pasv_fd != -1)
        close(client->pasv_fd);
    client->port_mode = 0;
    client->pasv_fd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = 0;
    bind(client->pasv_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(client->pasv_fd, 1);
    getsockname(client->pasv_fd, (struct sockaddr *)&addr, &len);
    sprintf(msg, "227 Entering Passive Mode (127,0,0,1,%d,%d).\r\n",
        ntohs(addr.sin_port) / 256, ntohs(addr.sin_port) % 256);
    write(client->fd, msg, strlen(msg));
    return 0;
}
