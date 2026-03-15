/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** pwd.c
*/

#include "../../include/my.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int pwd_cmd(client_t *client)
{
    char *res = malloc(sizeof(char) * (strlen(client->cwd) + 50));

    res[0] = '\0';
    strcat(res, "257 \"");
    strcat(res, client->cwd);
    strcat(res, "\" is the current directory.\r\n");
    write(client->fd, res, strlen(res));
    free(res);
    return 0;
}
