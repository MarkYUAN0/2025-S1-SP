/*
 * sequence.c  – COMP SCI 2005, S1 2025 Assignment 2
 * Author: Junyuan Guan (a1883125)
 * Read commands from stdin and run them one-by-one.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE   256
#define MAX_ARGS   11      /* 10 args + NULL */

static void trim_newline(char *s)
{
    size_t len = strlen(s);
    if (len && s[len - 1] == '\n') s[len - 1] = '\0';
}

static int parse_line(char *line, char *argv[])
{
    int argc = 0;
    char *tok = strtok(line, " \t");
    while (tok && argc < MAX_ARGS - 1) {
        argv[argc++] = tok;
        tok = strtok(NULL, " \t");
    }
    argv[argc] = NULL;          /* execvp 需要以 NULL 终止 */
    return argc;
}

int main(void)
{
    char  line[MAX_LINE];
    char *argv[MAX_ARGS];

    while (fgets(line, sizeof line, stdin)) {
        trim_newline(line);
        if (line[0] == '\0')    /* 跳过空行 */
            continue;

        parse_line(line, argv);

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {         /* child */
            execvp(argv[0], argv);
            perror(argv[0]);    /* execvp 只在失败时返回 */
            _exit(127);
        }
        /* parent */
        if (waitpid(pid, NULL, 0) < 0) {
            perror("waitpid");
        }
    }
    return 0;
}
