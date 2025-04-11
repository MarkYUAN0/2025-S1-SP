/* weekdays.c
 * 本程序提示用户输入 1~7 之间的一个数字，并利用 switch 语句输出对应的星期名称。
 */

#include <stdio.h>

int main() {
    int day;
    printf("Enter a day of the week (1-7): ");
    scanf("%d", &day);

    // 使用 switch 语句匹配不同的输入数字
    switch (day) {
        case 1:
            printf("Monday\n");
            break;
        case 2:
            printf("Tuesday\n");
            break;
        case 3:
            printf("Wednesday\n");
            break;
        case 4:
            printf("Thursday\n");
            break;
        case 5:
            printf("Friday\n");
            break;
        case 6:
            printf("Saturday\n");
            break;
        case 7:
            printf("Sunday\n");
            break;
        default:
            printf("Invalid input\n");
            break;
    }

    return 0;
}
