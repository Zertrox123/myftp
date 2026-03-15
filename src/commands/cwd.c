/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** cwd.c
*/

#include "../../include/my.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int cwd_cmd(client_t *client, char **cmd)
{
    char *new_cwd;

    if (cmd[1] == NULL) {
        write(client->fd, "550 Failed to change directory.\r\n", 33);
        return 0;
    }
    new_cwd = malloc(sizeof(char) * (strlen(client->cwd) + strlen(cmd[1]) + 2));
    new_cwd[0] = '\0';
    if (cmd[1][0] != '/') {
        strcat(new_cwd, client->cwd);
        if (strcmp(client->cwd, "/") != 0)
            strcat(new_cwd, "/");
    }
    strcat(new_cwd, cmd[1]);
    client->cwd = new_cwd;
    write(client->fd, "250 Directory successfully changed.\r\n", 37);
    return 0;
}
