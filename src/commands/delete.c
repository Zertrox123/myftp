/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** delete.c
*/

#include "../../include/my.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int delete_cmd(client_t *client, char **cmd)
{
    char full_path[1024] = {0};

    if (cmd[1] == NULL) {
        write(client->fd, "550 Requested action not taken.\r\n", 33);
        return 0;
    }
    build_path(client, cmd[1], full_path);
    if (remove(full_path) != 0) {
        write(client->fd, "550 Requested action not taken.\r\n", 33);
        return 0;
    }
    write(client->fd, "250 Requested file action okay, completed.\r\n", 44);
    return 0;
}
