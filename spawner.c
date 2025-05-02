#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "用法：%s \"command param1 param2 ...\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    // 拷贝输入字符串，避免修改 argv[1]
    char *input = strdup(argv[1]);
    if (!input) {
        perror("strdup");
        return EXIT_FAILURE;
    }

    // 估算参数个数（最坏情况下，每个字符后都是一个参数）
    size_t max_args = strlen(input) / 2 + 2;
    char **args = malloc(max_args * sizeof(char *));
    if (!args) {
        perror("malloc");
        free(input);
        return EXIT_FAILURE;
    }

    // 用 strtok 拆分，以空白字符（空格、制表符等）为分隔
    size_t idx = 0;
    char *token = strtok(input, " \t\n");
    while (token != NULL) {
        args[idx++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[idx] = NULL;  // execvp 要求最后一个元素为 NULL

    if (idx == 0) {
        fprintf(stderr, "没有可执行的命令。\n");
        free(input);
        free(args);
        return EXIT_FAILURE;
    }

    // 执行命令
    execvp(args[0], args);

    // execvp 只有出错时才会返回
    fprintf(stderr, "无法执行 '%s': %s\n", args[0], strerror(errno));
    free(input);
    free(args);
    return EXIT_FAILURE;
}
