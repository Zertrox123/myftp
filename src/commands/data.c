/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** data.c
*/

#include "../../include/my.h"
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void build_path(client_t *client, const char *name, char *out)
{
    out[0] = '\0';
    strcat(out, client->home);
    strcat(out, client->cwd);
    if (name != NULL) {
        if (out[strlen(out) - 1] != '/')
            strcat(out, "/");
        strcat(out, name);
    }
}

int verif_data_mode(client_t *client)
{
    if (client->pasv_fd == -1 && client->port_mode != 1) {
        write(client->fd, "425 Use PASV first.\r\n", 21);
        return 0;
    }
    return 1;
}

int data_connexion(client_t *client)
{
    int data_fd;

    if (client->pasv_fd != -1) {
        data_fd = accept(client->pasv_fd, NULL, NULL);
        close(client->pasv_fd);
        client->pasv_fd = -1;
        return data_fd;
    }
    if (client->port_mode == 1) {
        data_fd = socket(AF_INET, SOCK_STREAM, 0);
        connect(data_fd, (struct sockaddr *)&client->port_addr,
            sizeof(client->port_addr));
        client->port_mode = 0;
        return data_fd;
    }
    write(client->fd, "425 Use PASV first.\r\n", 21);
    return -1;
}
