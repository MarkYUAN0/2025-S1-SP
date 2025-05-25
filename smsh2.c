// smsh2.c — 简单 Shell，支持 | 管道

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "smsh.h"

static char ***split_pipes(char **tokens, int *ncmds) {
    int count = 1;
    for (char **p = tokens; *p; ++p) {
        if (strcmp(*p, "|") == 0) count++;
    }
    char ***cmds = malloc((count + 1) * sizeof(char **));
    int idx = 0;
    cmds[idx] = tokens;
    for (char **p = tokens; *p; ++p) {
        if (strcmp(*p, "|") == 0) {
            *p = NULL;
            cmds[++idx] = p + 1;
        }
    }
    cmds[count] = NULL;
    *ncmds = count;
    return cmds;
}


int main() {
    char *line;
    char **tokens;
    while ((line = next_cmd("> ", stdin)) != NULL) {
        if (!(tokens = splitline(line))) {
            free(line);
            continue;
        }
        int n;
        char ***cmds = split_pipes(tokens, &n);
        if (n == 1) {
            execute(tokens);  // 单命令执行
        } else {
            int pipes[n-1][2];
            for (int i = 0; i < n-1; ++i) pipe(pipes[i]);
            for (int i = 0; i < n; ++i) {
                pid_t pid = fork();
                if (pid == 0) {
                    if (i > 0)
                        dup2(pipes[i-1][0], STDIN_FILENO);   // 重定向输入 
                    if (i < n-1)
                        dup2(pipes[i][1], STDOUT_FILENO);     // 重定向输出 
                    for (int j = 0; j < n-1; ++j) {
                        close(pipes[j][0]);
                        close(pipes[j][1]);
                    }
                    execvp(cmds[i][0], cmds[i]);
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }
            }
            for (int i = 0; i < n-1; ++i) {
                close(pipes[i][0]);
                close(pipes[i][1]);
            }
            while (wait(NULL) > 0) {}  // 等待所有子进程
        }
        freelist(tokens);
        free(cmds);
        free(line);
    }
    return EXIT_SUCCESS;
}
