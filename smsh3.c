// smsh3.c — 支持 sequence(;) 和 I/O 重定向

#define _POSIX_C_SOURCE 200809L  // 启用 strtok 等 POSIX 接口
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#include "smsh.h"

// 自定义 strdup，避免隐式声明
static char *xstrdup(const char *s) {
    char *d = malloc(strlen(s) + 1);
    if (d) strcpy(d, s);
    return d;
}

// 去除两端空白
static char *trim(char *s) {
    char *end;
    while (*s && isspace((unsigned char)*s)) s++;
    if (*s == '\0') return s;
    end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) *end-- = '\0';
    return s;
}

// 拆管道函数（只定义一次）
static char ***split_pipes(char **tokens, int *ncmds) {
    int cnt = 1;
    for (char **p = tokens; *p; ++p)
        if (strcmp(*p, "|") == 0) cnt++;
    char ***cmds = malloc((cnt + 1) * sizeof(char **));
    int idx = 0;
    cmds[idx] = tokens;
    for (char **p = tokens; *p; ++p) {
        if (strcmp(*p, "|") == 0) {
            *p = NULL;
            cmds[++idx] = p + 1;
        }
    }
    cmds[cnt] = NULL;
    *ncmds = cnt;
    return cmds;
}

int main() {
    char *line;
    while ((line = next_cmd("> ", stdin)) != NULL) {
        // 用 strtok 拆分 ';'，避免 strsep 隐式声明
        char *saveptr, *segment = strtok_r(line, ";", &saveptr);
        while (segment) {
            char *cmd = trim(segment);
            if (*cmd) {
                char **tokens = splitline(cmd);
                if (tokens) {
                    int n; 
                    char ***cmds = split_pipes(tokens, &n);

                    if (n == 1) {
                        // 单命令：fork + 重定向 + execvp
                        pid_t pid = fork();
                        if (pid == 0) {
                            // child: 处理 < 和 >
                            for (char **p = tokens; *p; ++p) {
                                if (strcmp(*p, "<") == 0) {
                                    int fd = open(p[1], O_RDONLY);
                                    if (fd < 0) fatal("open", "", 1);
                                    dup2(fd, STDIN_FILENO);
                                    close(fd);
                                    *p = NULL;
                                } else if (strcmp(*p, ">") == 0) {
                                    int fd = open(p[1],
                                        O_WRONLY|O_CREAT|O_TRUNC, 0666);
                                    if (fd < 0) fatal("open", "", 1);
                                    dup2(fd, STDOUT_FILENO);
                                    close(fd);
                                    *p = NULL;
                                }
                            }
                            execvp(tokens[0], tokens);
                            perror("execvp");
                            exit(EXIT_FAILURE);
                        } else if (pid > 0) {
                            wait(NULL);
                        } else {
                            perror("fork");
                        }

                    } else {
                        // 多命令管道：每个子进程都做自己的重定向
                        int pipes[n-1][2];
                        for (int i = 0; i < n-1; ++i) pipe(pipes[i]);
                        for (int i = 0; i < n; ++i) {
                            pid_t pid = fork();
                            if (pid == 0) {
                                // child: 重定向管道
                                if (i > 0) dup2(pipes[i-1][0], STDIN_FILENO);
                                if (i < n-1) dup2(pipes[i][1], STDOUT_FILENO);
                                for (int j = 0; j < n-1; ++j)
                                    close(pipes[j][0]), close(pipes[j][1]);
                                // child: 处理重定向符号
                                for (char **q = cmds[i]; *q; ++q) {
                                    if (strcmp(*q, "<") == 0) {
                                        int fd = open(q[1], O_RDONLY);
                                        if (fd < 0) fatal("open", "", 1);
                                        dup2(fd, STDIN_FILENO);
                                        close(fd);
                                        *q = NULL;
                                    } else if (strcmp(*q, ">") == 0) {
                                        int fd = open(q[1],
                                            O_WRONLY|O_CREAT|O_TRUNC, 0666);
                                        if (fd < 0) fatal("open", "", 1);
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
                        // parent 关闭管道并等待
                        for (int i = 0; i < n-1; ++i)
                            close(pipes[i][0]), close(pipes[i][1]);
                        while (wait(NULL) > 0);
                    }

                    freelist(tokens);
                    free(cmds);
                }
            }
            segment = strtok_r(NULL, ";", &saveptr);
        }
        free(line);
    }
    return EXIT_SUCCESS;
}

