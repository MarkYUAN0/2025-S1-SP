/* pointer_arithmetic.c
 * 本程序通过使用指针遍历整型数组，演示指针运算的基本概念
 */

#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};  // 声明一个包含 5 个元素的整型数组
    int *ptr = arr;                    // 将指针指向数组的首元素（等价于 &arr[0]）

    // 使用指针运算访问并打印数组的每个元素
    // *(ptr + i) 等价于 arr[i]
    for (int i = 0; i < 5; i++) {
        printf("Element %d: %d\n", i, *(ptr + i));
    }

    return 0;
}
