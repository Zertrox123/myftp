/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** cdup.c
*/

#include "../../include/my.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int cdup_cmd(client_t *client)
{
    int i = strlen(client->cwd) - 1;

    if (strcmp(client->cwd, "/") == 0) {
        write(client->fd, "250 Directory successfully changed.\r\n", 37);
        return 0;
    }
    while (i > 0 && client->cwd[i] != '/')
        i--;
    if (i == 0)
        client->cwd[1] = '\0';
    else
        client->cwd[i] = '\0';
    write(client->fd, "250 Directory successfully changed.\r\n", 37);
    return 0;
}
