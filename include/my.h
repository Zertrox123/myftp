/*
** EPITECH PROJECT, 2026
** 2nd_year
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

typedef struct client_s {
    int fd;
    int logged;
    char *user;
    char *home;
    char *cwd;
    int pasv_fd;
} client_t;

typedef struct srv_ctx_s {
    struct pollfd *fds;
    client_t *clients;
    const char *home;
} srv_ctx_t;

int user_cmd(client_t *client, char **cmd);
int pass_cmd(client_t *client, char **cmd);
int pwd_cmd(client_t *client);
int cwd_cmd(client_t *client, char **cmd);
int cdup_cmd(client_t *client);
int noop_cmd(client_t *client);
int type_cmd(client_t *client, char **cmd);
int pasv_cmd(client_t *client);
int exec_ftp_cmd(client_t *client, char **cmd);
void handle_client(client_t *client, char *buffer);
int server_run(int fd_server, const char *home);
int init_server(int port);
void init_poll_clients(struct pollfd *nb, client_t *client, int size);
int list_cmd(client_t *client);

#endif /* !MY_H_ */
