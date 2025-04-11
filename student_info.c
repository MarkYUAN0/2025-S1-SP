/* student_info.c
 * 本程序定义一个学生结构体 (Student)，该结构体包含姓名、年龄和 GPA 三个字段。
 * 程序通过用户输入初始化结构体变量，并输出学生信息。
 */

#include <stdio.h>

// 定义一个 Student 结构体
typedef struct {
    char name[50];  // 学生姓名，假设不超过 49 个字符
    int age;        // 学生年龄
    float gpa;      // 学生 GPA
} Student;

int main() {
    Student student;

    // 提示用户输入学生姓名
    printf("Enter Student Name: ");
    scanf("%s", student.name);

    // 提示用户输入学生年龄
    printf("Enter Student Age: ");
    scanf("%d", &student.age);

    // 提示用户输入学生 GPA
    printf("Enter Student GPA: ");
    scanf("%f", &student.gpa);

    // 按照指定格式输出学生信息
    printf("Name: %s, Age: %d, GPA: %.2f\n", student.name, student.age, student.gpa);

    return 0;
}
