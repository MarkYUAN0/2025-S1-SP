/* pointer_basics.c
 * 本程序演示如何使用指针来获取并打印变量的地址以及通过指针解引用来打印变量的值
 */

#include <stdio.h>

int main() {
    int num = 1;        // 声明一个整数变量并赋初值
    int *ptr = &num;    // 声明一个指向整数的指针并将其指向 num 的地址

    // 直接使用变量名打印变量值
    printf("Value of num: %d\n", num);
    // 使用指针打印 num 的地址（注意要将指针强制转换为 void* 以符合 C 标准）
    printf("Address of num: %p\n", (void*)ptr);
    // 解引用指针，打印所指向的值
    printf("Value stored at ptr: %d\n", *ptr);

    return 0;
}
