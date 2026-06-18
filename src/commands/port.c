/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** port.c
*/

#include "../../include/my.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int port_cmd(client_t *client, char **cmd)
{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int p1 = 0;
    int p2 = 0;

    if (cmd[1] == NULL ||
        sscanf(cmd[1], "%d,%d,%d,%d,%d,%d", &a, &b, &c, &d, &p1, &p2) != 6) {
        write(client->fd, "501 Syntax error in parameters.\r\n", 33);
        return 0;
    }
    if (client->pasv_fd != -1) {
        close(client->pasv_fd);
        client->pasv_fd = -1;
    }
    client->port_addr.sin_family = AF_INET;
    client->port_addr.sin_addr.s_addr = htonl((a << 24) | (b << 16) |
        (c << 8) | d);
    client->port_addr.sin_port = htons(p1 * 256 + p2);
    client->port_mode = 1;
    write(client->fd, "200 Port command successful.\r\n", 30);
    return 0;
}
