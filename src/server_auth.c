/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** auth.c
*/

#include "../include/my.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int user_cmd(client_t *client, char **cmd)
{
    if (client->user != NULL)
        free(client->user);
    if (cmd[1] != NULL)
        client->user = strdup(cmd[1]);
    else
        client->user = strdup("");
    write(client->fd, "331 Please specify the password.\r\n", 34);
    return 0;
}

int pass_cmd(client_t *client, char **cmd)
{
    (void)cmd;

    if (client->logged == 1) {
        write(client->fd, "230 Already logged in.\r\n", 24);
        return 0;
    }
    if (client->user != NULL && strcasecmp(client->user, "anonymous") == 0) {
        client->logged = 1;
        write(client->fd, "230 Login successful.\r\n", 23);
        return 0;
    }
    write(client->fd, "530 Login incorrect.\r\n", 22);
    return 0;
}
