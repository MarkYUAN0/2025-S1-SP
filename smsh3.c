// smsh3.c — 在 smsh2 基础上添加 < 和 > 重定向

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#include "smsh.h"

// trim leading/trailing whitespace
static char *trim(char *s) {
    char *end;
    while (*s && isspace((unsigned char)*s)) s++;
    if (*s == '\0') return s;
    end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) *end-- = '\0';
    return s;
}

// same split_pipes as before :contentReference[oaicite:1]{index=1}
static char ***split_pipes(char **tokens, int *ncmds) {
    int count = 1;
    for (char **p = tokens; *p; ++p)
        if (strcmp(*p, "|") == 0) count++;
    char ***cmds = malloc((count+1)*sizeof(char**));
    int idx = 0;
    cmds[idx] = tokens;
    for (char **p = tokens; *p; ++p) {
        if (strcmp(*p, "|") == 0) {
            *p = NULL;
            cmds[++idx] = p+1;
        }
    }
    cmds[count] = NULL;
    *ncmds = count;
    return cmds;
}

int main() {
    char *line, *segment, *rest;
    char **tokens;
    while ((line = next_cmd("> ", stdin)) != NULL) {
        // split on ';'
        rest = line;
        while ((segment = strsep(&rest, ";")) != NULL) {
            char *cmd = trim(segment);
            if (*cmd == '\0') continue;

            if (!(tokens = splitline(cmd))) continue;
            int n; char ***cmds = split_pipes(tokens, &n);

            if (n == 1) {
                // /* 单命令：处理重定向 */single segment: handle < and > :contentReference[oaicite:2]{index=2}
                for (char **p = tokens; *p; ++p) {
                    if (strcmp(*p, "<") == 0) {
                        int fd = open(p[1], O_RDONLY);
                        dup2(fd, STDIN_FILENO);
                        close(fd);
                        *p = NULL;
                    } else if (strcmp(*p, ">") == 0) {
                        int fd = open(p[1],
                            O_WRONLY|O_CREAT|O_TRUNC, 0666);
                        dup2(fd, STDOUT_FILENO);
                        close(fd);
                        *p = NULL;
                    }
                }
                execute(tokens);
            } else {
                /* 多命令管道：在每个子进程中也要检测重定向 */
                int pipes[n-1][2];
                for (int i = 0; i < n-1; ++i) pipe(pipes[i]);
                for (int i = 0; i < n; ++i) {
                    if (fork() == 0) {
                        if (i>0) dup2(pipes[i-1][0], STDIN_FILENO);
                        if (i<n-1) dup2(pipes[i][1], STDOUT_FILENO);
                        for (int j=0; j<n-1; ++j)
                            close(pipes[j][0]), close(pipes[j][1]);
                       /* 子进程重定向检测 */
                        for (char **q = cmds[i]; *q; ++q) {
                            if (strcmp(*q, "<")==0) {
                                int fd = open(q[1], O_RDONLY);
                                dup2(fd, STDIN_FILENO);
                                close(fd);
                                *q = NULL;
                            } else if (strcmp(*q, ">")==0) {
                                int fd = open(q[1],
                                    O_WRONLY|O_CREAT|O_TRUNC, 0666);
                                dup2(fd, STDOUT_FILENO);
                                close(fd);
                                *q = NULL;
                            }
                        }
                        execvp(cmds[i][0], cmds[i]);
                        perror("execvp");
                        exit(EXIT_FAILURE);
                    }
                }
                for (int i = 0; i < n-1; ++i)
                    close(pipes[i][0]), close(pipes[i][1]);
                while (wait(NULL) > 0) {}
            }
            freelist(tokens);
            free(cmds);
        }
        free(line);
    }
    return EXIT_SUCCESS;
}

