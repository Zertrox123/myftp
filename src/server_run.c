/*
** EPITECH PROJECT, 2026
** 2nd_year
** File description:
** server_run
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <stdlib.h>
#include "../include/my.h"

static int new_client(int s_fd, int total_client, srv_ctx_t *ctx)
{
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int fd = accept(s_fd, (struct sockaddr *)&client_addr, &len);

    if (fd < 0)
        return total_client;
    ctx->fds[total_client].fd = fd;
    ctx->fds[total_client].events = POLLIN;
    ctx->clients[total_client].fd = fd;
    ctx->clients[total_client].logged = 0;
    ctx->clients[total_client].user = NULL;
    ctx->clients[total_client].home = strdup(ctx->home);
    ctx->clients[total_client].cwd = strdup("/");
    write(fd, "220 Welcome here !\r\n", 20);
    return total_client + 1;
}

static void read_one_client(struct pollfd *nb, client_t *client, int i)
{
    char buffer[1024] = {0};

    if (read(nb[i].fd, buffer, 1024) <= 0) {
        close(nb[i].fd);
        nb[i].fd = -1;
        if (client[i].user != NULL) {
            free(client[i].user);
            client[i].user = NULL;
        }
        if (client[i].home != NULL) {
            free(client[i].home);
            client[i].home = NULL;
        }
        if (client[i].cwd != NULL) {
            free(client[i].cwd);
            client[i].cwd = NULL;
        }
    } else {
        handle_client(&client[i], buffer);
        nb[i].fd = client[i].fd;
    }
}

static void read_all_clients(struct pollfd *nb, int total_client,
    client_t *client)
{
    for (int i = 1; i < total_client; i++) {
        if (nb[i].fd != -1 && (nb[i].revents == POLLIN))
            read_one_client(nb, client, i);
    }
}

static void run_server_loop(struct pollfd *nb, client_t *client, srv_ctx_t *ctx,
    int fd_server)
{
    int total_client = 1;

    nb[0].fd = fd_server;
    nb[0].events = POLLIN;
    while (poll(nb, total_client, -1) != -1) {
        if (nb[0].revents == POLLIN)
            total_client = new_client(fd_server, total_client, ctx);
        read_all_clients(nb, total_client, client);
    }
}

int server_run(int fd_server, const char *home)
{
    struct pollfd nb[1000];
    client_t client[100];
    srv_ctx_t ctx;

    init_poll_clients(nb, client, 100);
    ctx.fds = nb;
    ctx.clients = client;
    ctx.home = home;
    run_server_loop(nb, client, &ctx, fd_server);
    return 0;
}
