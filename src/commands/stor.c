/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** stor.c
*/

#include "../../include/my.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

static int recv_file(int data_fd, const char *path)
{
    int file_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char buffer[1024] = {0};
    ssize_t n = 0;

    if (file_fd < 0)
        return -1;
    while ((n = read(data_fd, buffer, 1024)) > 0)
        write(file_fd, buffer, n);
    close(file_fd);
    return 0;
}

int stor_cmd(client_t *client, char **cmd)
{
    char full_path[1024] = {0};
    int data_fd = 0;

    if (cmd[1] == NULL) {
        write(client->fd, "550 Failed to open file.\r\n", 26);
        return 0;
    }
    build_path(client, cmd[1], full_path);
    if (verif_data_mode(client) == 0)
        return 0;
    write(client->fd, "150 Opening BINARY mode data connection.\r\n", 42);
    data_fd = data_connexion(client);
    if (data_fd < 0)
        return 0;
    if (recv_file(data_fd, full_path) != 0) {
        close(data_fd);
        write(client->fd, "550 Failed to open file.\r\n", 26);
        return 0;
    }
    close(data_fd);
    write(client->fd, "226 Closing data connection. Requested file "
        "action successful.\r\n", 64);
    return 0;
}
