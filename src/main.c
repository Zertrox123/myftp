/*
** EPITECH PROJECT, 2026
** 2nd_year
** File description:
** main
*/

#include "../include/my.h"
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int check_path(const char *path)
{
    struct stat s;

    if (stat(path, &s) != 0)
        return 0;
    return S_ISDIR(s.st_mode);
}

int main(int argc, char **argv)
{
    int port = 0;
    char *path;

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        printf("USAGE: ./myftp port path\n");
        printf("\tport is the port number on which the server ");
        printf("socket listens\n\tpath is the path ");
        printf("to the home directory for the Anonymous user\n");
        return 0;
    }
    if (argc != 3)
        return 84;
    if (atoi(argv[1]) > 65535 || atoi(argv[1]) < 1)
        return 84;
    port = atoi(argv[1]);
    path = argv[2];
    if (!check_path(path))
        return 84;
    server_run(init_server(port), path);
    return 0;
}
