/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** commands.c
*/

#include "../include/my.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int exec_ftp_cmd2(client_t *client, char **cmd)
{
    if (strcmp(cmd[0], "TYPE") == 0)
        return type_cmd(client, cmd);
    if (strcmp(cmd[0], "PWD") == 0)
        return pwd_cmd(client);
    if (strcmp(cmd[0], "CWD") == 0)
        return cwd_cmd(client, cmd);
    if (strcmp(cmd[0], "PASV") == 0)
        return pasv_cmd(client);
    if (strcmp(cmd[0], "CDUP") == 0)
        return cdup_cmd(client);
    if (strcmp(cmd[0], "NOOP") == 0) {
        write(client->fd, "200 NOOP ok.\r\n", 14);
        return 0;
    }
    if (strcmp(cmd[0], "LIST") == 0)
        return list_cmd(client);
    write(client->fd, "500 Unknown command.\r\n", 22);
    return 0;
}

int exec_ftp_cmd(client_t *client, char **cmd)
{
    if (cmd[0] == NULL)
        return 0;
    if (strcmp(cmd[0], "USER") == 0)
        return user_cmd(client, cmd);
    if (strcmp(cmd[0], "PASS") == 0)
        return pass_cmd(client, cmd);
    if (strcmp(cmd[0], "QUIT") == 0) {
        write(client->fd, "221 Goodbye.\r\n", 14);
        return 1;
    }
    if (client->logged == 0) {
        write(client->fd, "530 Please login with USER and PASS.\r\n", 38);
        return 0;
    }
    return exec_ftp_cmd2(client, cmd);
}

void handle_client(client_t *client, char *buffer)
{
    char **cmd = malloc(sizeof(char *) * 15);
    char *tok = strtok(buffer, " \r\n");
    int i = 0;

    for (; tok != NULL; i++) {
        cmd[i] = tok;
        tok = strtok(NULL, " \r\n");
    }
    cmd[i] = NULL;
    if (exec_ftp_cmd(client, cmd) == 1) {
        close(client->fd);
        client->fd = -1;
    }
}
