#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMDS 100
#define MAX_LINE 256
#define MAX_ARGS 11

struct Cmd {
    char *argv[MAX_ARGS];
};

static void trim_eol(char *s)
{
    size_t len = strlen(s);
    while (len && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }
}

static void parse_line(char *line, struct Cmd *cmd)
{
    int argc = 0;
    char *tok = strtok(line, " \t");
    while (tok && argc < MAX_ARGS - 1) {
        cmd->argv[argc++] = tok;
        tok = strtok(NULL, " \t");
    }
    cmd->argv[argc] = NULL;
}

int main(void)
{
    struct Cmd cmds[MAX_CMDS];
    char   lines[MAX_CMDS][MAX_LINE];
    int    ncmd = 0;

    /* 预读所有命令 */
    while (ncmd < MAX_CMDS && fgets(lines[ncmd], sizeof lines[0], stdin)) {
        trim_eol(lines[ncmd]);
        if (strspn(lines[ncmd], " \t") == strlen(lines[ncmd]))   /* 空行 */
            continue;
        parse_line(lines[ncmd], &cmds[ncmd]);
        ++ncmd;
    }
    if (ncmd == 0) return 0;

    int prev_read_fd = -1;  /* 上一条命令的读端 */

    for (int i = 0; i < ncmd; ++i) {
        int pipefd[2] = {-1, -1};
        int is_last = (i == ncmd - 1);

        if (!is_last && pipe(pipefd) < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {                     /* child */
            /* 若不是第一条，stdin ← prev_read_fd */
            if (prev_read_fd != -1) {
                dup2(prev_read_fd, STDIN_FILENO);
            }
            /* 若不是最后一条，stdout → pipefd[1] */
            if (!is_last) {
                dup2(pipefd[1], STDOUT_FILENO);
            }

            /* 子进程关闭不再需要的描述符，避免死锁 */
            if (prev_read_fd != -1) close(prev_read_fd);
            if (!is_last) {
                close(pipefd[0]);
                close(pipefd[1]);
            }

            execvp(cmds[i].argv[0], cmds[i].argv);
            perror(cmds[i].argv[0]);
            _exit(127);
        }

        /* parent */
        if (prev_read_fd != -1) close(prev_read_fd); /* 关闭上一轮读端 */
        if (!is_last) {
            close(pipefd[1]);       /* 父只需读端，写端交给子 */
            prev_read_fd = pipefd[0];
        }
    }

    /* 等待所有子进程 */
    while (wait(NULL) > 0)
        ;
    return 0;
}
