/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** list.c
*/

#include "../../include/my.h"
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

static void send_listing(int data_fd, const char *full_path)
{
    DIR *dir = opendir(full_path);
    struct dirent *entry;

    if (dir == NULL)
        return;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.')
            continue;
        write(data_fd, entry->d_name, strlen(entry->d_name));
        write(data_fd, "\r\n", 2);
    }
    closedir(dir);
}

int list_cmd(client_t *client)
{
    char full_path[1024] = {0};
    int data_fd = 0;

    if (verif_data_mode(client) == 0)
        return 0;
    write(client->fd, "150 Here comes the directory listing.\r\n", 39);
    data_fd = data_connexion(client);
    if (data_fd < 0)
        return 0;
    build_path(client, NULL, full_path);
    send_listing(data_fd, full_path);
    close(data_fd);
    return write(client->fd, "226 Directory send OK.\r\n", 24);
}
