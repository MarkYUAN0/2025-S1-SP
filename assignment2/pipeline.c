#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_CMDS   100
#define MAX_LINE   256
#define MAX_ARGS   11
struct Cmd {
    char *argv[MAX_ARGS];
};

static void trim_newline(char *s)
{
    size_t len = strlen(s);
    if (len && s[len - 1] == '\n') s[len - 1] = '\0';
}

static int parse_line(char *line, struct Cmd *cmd)
{
    int argc = 0;
    char *tok = strtok(line, " \t");
    while (tok && argc < MAX_ARGS - 1) {
        cmd->argv[argc++] = tok;
        tok = strtok(NULL, " \t");
    }
    cmd->argv[argc] = NULL;
    return argc;
}

int main(void)
{
    struct Cmd cmds[MAX_CMDS];
    char   lines[MAX_CMDS][MAX_LINE];
    int    ncmd = 0;

    /* 先一次性读完命令，便于预知总数 */
    while (ncmd < MAX_CMDS && fgets(lines[ncmd], sizeof lines[0], stdin)) {
        trim_newline(lines[ncmd]);
        if (lines[ncmd][0] == '\0') continue;
        parse_line(lines[ncmd], &cmds[ncmd]);
        ncmd++;
    }
    if (ncmd == 0) return 0;

    int prev_pipe[2] = {-1, -1};

    for (int i = 0; i < ncmd; i++) {
        int new_pipe[2] = {-1, -1};
        int is_last = (i == ncmd - 1);

        if (!is_last && pipe(new_pipe) < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {                 /* child */
            /* stdin ← prev_pipe[0] */
            if (prev_pipe[0] != -1) {
                dup2(prev_pipe[0], STDIN_FILENO);
            }
            /* stdout → new_pipe[1] */
            if (!is_last) {
                dup2(new_pipe[1], STDOUT_FILENO);
            }

            /* 关掉不再用到的描述符，避免死锁 */
            if (prev_pipe[0] != -1) {
                close(prev_pipe[0]);
                close(prev_pipe[1]);
            }
            if (!is_last) {
                close(new_pipe[0]);
                close(new_pipe[1]);
            }

            execvp(cmds[i].argv[0], cmds[i].argv);
            perror(cmds[i].argv[0]);
            _exit(127);
        }

        /* parent 只需保留 new_pipe[0] 作为下一轮的 prev_pipe */
        if (prev_pipe[0] != -1) {
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }
        prev_pipe[0] = new_pipe[0];
        prev_pipe[1] = new_pipe[1];     /* 未来可能关闭 */
        if (!is_last) {                 /* 父进程只需读端，写端已给子 */
            close(new_pipe[1]);
        }
    }

    /* 结尾*/
    for (int i = 0; i < ncmd; i++) {
        wait(NULL);
    }
    return 0;
}
