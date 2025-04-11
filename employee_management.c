/* employee_management.c
 * 本程序用于录入员工信息，并根据员工的工资判断其薪资水平。
 * 用户可循环输入多个员工信息，直到选择不再继续。
 */

#include <stdio.h>

// 定义一个 Employee 结构体，包含员工姓名、年龄和工资
typedef struct {
    char name[50];
    int age;
    float salary;
} Employee;

int main() {
    char choice; // 用于存储用户是否继续输入的选择

    do {
        Employee emp;

        // 输入员工信息
        printf("Enter employee details:\n");
        
        // 输入员工姓名
        printf("Name: ");
        scanf("%s", emp.name);

        // 输入员工年龄
        printf("Age: ");
        scanf("%d", &emp.age);

        // 输入员工工资
        printf("Salary: ");
        scanf("%f", &emp.salary);

        // 检查工资是否高于 $50000，并打印相应提示
        if (emp.salary > 50000) {
            printf("Employee %s is highly paid.\n", emp.name);
        } else {
            printf("Employee %s is not highly paid.\n", emp.name);
        }

        // 询问用户是否继续录入下一个员工信息
        printf("Do you want to enter another employee? (y/n): ");
        // 在格式串前加一个空格以跳过前一次输入后残留的换行符
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
