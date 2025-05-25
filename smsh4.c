// smsh4.c — Part 3：加入 globbing、sequence、pipe、redir
// 参考当前版本：file :contentReference[oaicite:1]{index=1}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <glob.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "smsh.h"

// trim() 同上…

static char *trim(char *s) {
    /* 与 smsh3.c 一致 */
}

// split_pipes() 同上…

static char ***split_pipes(char **tokens, int *ncmds) {
    /* 与 smsh3.c 一致 */
}

// 通配符展开
static char **expand_wildcards(char **tokens) {
    char **out = NULL;
    size_t cap = 0, len = 0;
    for (char **t = tokens; *t; ++t) {
        if (strpbrk(*t, "*?[") != NULL) {
            glob_t res;
            glob(*t, 0, NULL, &res);
            for (size_t i = 0; i < res.gl_pathc; ++i) {
                if (len+1 >= cap)
                    out = realloc(out, (cap = cap*2+4) * sizeof(char*));
                out[len++] = strdup(res.gl_pathv[i]);
            }
            globfree(&res);
        } else {
            if (len+1 >= cap)
                out = realloc(out, (cap = cap*2+4) * sizeof(char*));
            out[len++] = strdup(*t);
        }
    }
    if (len+1 >= cap)
        out = realloc(out, (cap = cap*2+4) * sizeof(char*));
    out[len] = NULL;
    return out;
}

int main() {
    char *line, *segment, *rest;
    char **tokens, **expanded;

    while ((line = next_cmd("> ", stdin)) != NULL) {
        rest = line;
        while ((segment = strsep(&rest, ";")) != NULL) {
            char *cmd = trim(segment);
            if (*cmd == '\0') continue;

            // 1) 分词
            if (!(tokens = splitline(cmd))) continue;
            // 2) 通配符展开
            expanded = expand_wildcards(tokens);
            freelist(tokens);
            tokens = expanded;

            // 3) 余下逻辑完全同 smsh3.c
            int n; char ***cmds = split_pipes(tokens, &n);
            if (n == 1) {
                // 单命令 fork+redir+exec
                pid_t pid = fork();
                if (pid == 0) {
                    /* 与 smsh3.c 单命令子进程重定向相同 */
                } else {
                    wait(NULL);
                }
            } else {
                // 多命令管道 + 子进程重定向
                /* 与 smsh3.c 管道分支完全相同 */
            }

            freelist(tokens);
            free(cmds);
        }
        free(line);
    }
    return EXIT_SUCCESS;
}

