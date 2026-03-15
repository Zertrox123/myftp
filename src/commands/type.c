/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** type.c
*/

#include "../../include/my.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int type_cmd(client_t *client, char **cmd)
{
    if (cmd[1] == NULL) {
        write(client->fd, "501 Missing parameter.\r\n", 24);
        return 0;
    }
    if (strcmp(cmd[1], "I") == 0 || strcmp(cmd[1], "i") == 0) {
        write(client->fd, "200 Switching to Binary mode.\r\n", 31);
        return 0;
    }
    if (strcmp(cmd[1], "A") == 0 || strcmp(cmd[1], "a") == 0) {
        write(client->fd, "200 Switching to ASCII mode.\r\n", 30);
        return 0;
    }
    write(client->fd, "504 Command not implemented.\r\n", 30);
    return 0;
}
