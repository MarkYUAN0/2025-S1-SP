/* fibonacci.c
 * 本程序根据用户输入的数字 n，打印斐波那契数列的前 n 个数字。
 * 斐波那契数列前两个数字为 0 和 1，后续数字为前两个数字之和。
 */

#include <stdio.h>

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    // 若用户输入的数字小于等于 0，则提示错误信息后结束程序
    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 0;
    }

    int a = 0, b = 1;

    // 如果 n >= 1，则先输出第一个数字
    if (n >= 1) {
        printf("%d\n", a);
    }
    // 如果 n >= 2，则输出第二个数字
    if (n >= 2) {
        printf("%d\n", b);
    }

    // 从第三个数字开始利用循环计算后续斐波那契数字
    for (int i = 3; i <= n; i++) {
        int next = a + b;
        printf("%d\n", next);
        a = b;
        b = next;
    }

    return 0;
}
