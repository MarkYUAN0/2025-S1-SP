/*solutions.c*/
#include <stdio.h>   
#include <math.h>  

// 定义 PI 为宏常量，值为 3.14159
#define PI 3.14159

int main() {
    /* Part 1: Basic Printing
       打印 "Hello, World!" 与 "Welcome to C"，并换行 */
    printf("Hello, World!\n");
    printf("Welcome to C\n");
    
    /* Part 2: Defining Variables
       声明并初始化变量 */
    int age = 25;          // 整型变量，年龄为 25
    float height = 1.75;   // 浮点型变量，身高为 1.75
    double weight = 68.5;  // 双精度浮点型变量，体重为 68.5
    char grade = 'A';      // 字符型变量，成绩为 'A'
    
    /* Part 3: Printing Variables
       使用printf打印变量，要求格式为：
       Age: 25, Height: 1.75 m, Weight: 68.5 kg, Grade: A
       注意对应数据类型的格式控制符 */
    printf("Age: %d, Height: %.2f m, Weight: %.1f kg, Grade: %c\n", age, height, weight, grade);
    
    /* Part 4: Constants and Macros
       使用宏常量定义 PI，并打印其值，保留 3 位小数 */
    printf("PI值为: %.3f\n", PI);
    
    /* Part 5: Sizeof Operator
       使用 sizeof 运算符打印 int, float, double 和 char 数据类型在内存中的大小
       注意: %zu 为 size_t 类型的格式控制符 */
    printf("int 类型的大小: %zu 字节\n", sizeof(int));
    printf("float 类型的大小: %zu 字节\n", sizeof(float));
    printf("double 类型的大小: %zu 字节\n", sizeof(double));
    printf("char 类型的大小: %zu 字节\n", sizeof(char));
    
    /* Part 6: Basic Arithmetic
       声明变量并计算各种算术运算 */
    int a = 5;
    int b = 3;
    float c = 2.5;
    // 整数运算：加、减、乘、除（整数除法）和求余
    printf("a + b = %d\n", a + b);
    printf("a - b = %d\n", a - b);
    printf("a * b = %d\n", a * b);
    printf("a / b = %d\n", a / b);     // 整数除法：结果为 1
    printf("a %% b = %d\n", a % b);     // 取模运算：注意 %% 用于打印 % 符号
    // 混合类型运算（整数与浮点数相加）
    printf("a + c = %.2f\n", a + c);
    // 使用 pow() 函数求 a 的 b 次幂
    printf("a^b = %.2f\n", pow(a, b));
    
    /* Part 7: Type Conversion and Math Functions
       定义一个浮点数并转换为整数（截断），然后使用 math.h 中的函数进行计算 */
    float decimal = 3.7;
    int truncated = (int) decimal;  // 显式类型转换：截断小数部分
    printf("decimal 值为: %.2f, 截断后的值为: %d\n", decimal, truncated);
    // 使用 floor(), ceil(), round() 函数进行运算，注意这些函数返回的是 double 类型
    printf("floor(decimal) = %.2f\n", floor(decimal));
    printf("ceil(decimal) = %.2f\n", ceil(decimal));
    printf("round(decimal) = %.0f\n", round(decimal));
    
    // 程序结束，返回 0 表示正常退出
    return 0;
}
