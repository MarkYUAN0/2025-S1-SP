/* user_info.c
 * 本程序实现了用户信息的录入，并根据用户输入的年龄判断是否成年。
 */

#include <stdio.h>

int main() {
    char name[50];  // 用于存储用户姓名的字符数组，假定姓名不超过 49 个字符
    int age;        // 用于存储用户年龄的整数

    // 提示用户输入姓名
    printf("Enter your name: ");
    scanf("%s", name);  // 使用 scanf 读取用户输入的字符串，注意遇空格则结束

    // 提示用户输入年龄
    printf("Enter your age: ");
    scanf("%d", &age);

    // 输出用户输入的信息
    printf("Hello, %s! You are %d years old.\n", name, age);

    // 判断用户是否为成年人（年龄大于等于 18）
    if (age >= 18) {
        printf("The user is an adult.\n");
    } else {
        printf("The user is not an adult.\n");
    }

    return 0;
}
