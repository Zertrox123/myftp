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

static int data_connection(client_t *client)
{
    int data_fd;

    if (client->pasv_fd == -1) {
        write(client->fd, "425 Use PASV first.\r\n", 21);
        return -1;
    }
    data_fd = accept(client->pasv_fd, NULL, NULL);
    close(client->pasv_fd);
    client->pasv_fd = -1;
    return data_fd;
}

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
    int data_fd = data_connection(client);

    if (data_fd < 0)
        return 0;
    strcat(full_path, client->home);
    strcat(full_path, client->cwd);
    write(client->fd, "150 Here comes the directory listing.\r\n", 39);
    send_listing(data_fd, full_path);
    close(data_fd);
    return write(client->fd, "226 Directory send OK.\r\n", 24);
}
