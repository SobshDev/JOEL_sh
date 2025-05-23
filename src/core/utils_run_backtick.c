/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** run_backtick_command
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "my.h"

static void run_backtick_child(const char *cmd, int *pipefd)
{
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    execl("/bin/sh", "sh", "-c", cmd, (char *)NULL);
    _exit(127);
}

static ssize_t read_pipe_to_buffer(int fd, char *buffer, size_t size)
{
    ssize_t n;

    n = read(fd, buffer, size - 1);
    if (n > 0) {
        buffer[n] = '\0';
    } else if (n == 0) {
        buffer[0] = '\0';
    }
    return n;
}

static void trim_trailing_newlines(char *buffer, ssize_t *n)
{
    while (*n > 0 && (buffer[*n - 1] == '\n' || buffer[*n - 1] == '\r')) {
        buffer[*n - 1] = '\0';
        (*n) -= 1;
    }
}

static int run_backtick_parent(int *pipefd, char *buffer, size_t bufsize)
{
    ssize_t n;
    int status;

    close(pipefd[1]);
    n = read_pipe_to_buffer(pipefd[0], buffer, bufsize);
    close(pipefd[0]);
    waitpid(-1, &status, 0);
    return n;
}

char *run_backtick_command(const char *cmd)
{
    int pipefd[2];
    pid_t pid;
    char buffer[4096];
    ssize_t n;
    char *result;

    if (pipe(pipefd) == -1)
        return NULL;
    pid = fork();
    if (pid == -1)
        return NULL;
    if (pid == 0)
        run_backtick_child(cmd, pipefd);
    n = run_backtick_parent(pipefd, buffer, sizeof(buffer));
    if (n <= 0)
        return my_strdup("");
    trim_trailing_newlines(buffer, &n);
    result = my_strdup(buffer);
    return (result == NULL) ? my_strdup("") : result;
}
