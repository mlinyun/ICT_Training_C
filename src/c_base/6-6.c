#include <stdio.h>
#include <string.h> // 在使用字符串函数时，在程序文件的开头用 #include <string.h>

int main(void) {
    char str1[30] = "People's Republic of'";
    char str2[] = " China";
    // ① strcat() 字符串连接函数 strcat（字符数组 1，字符数组 2）
    printf("%s\n", strcat(str1, str2));
    // ② strlen() 测字符串长度的函数 strlen(字符数组)
    printf("str2 的长度为 %ld\n", strlen(str2));
    // ③ strcpy() 字符串复制函数 strcpy（字符串 1，字符串 2）
    char str3[10];
    // 将字符串 str2 复制到字符串 str3 中
    strcpy(str3, str2);
    // 打印字符串 str3
    printf("%s\n", str3);
    // ④ strcmp 字符串比较函数 strcmp（字符串 1，字符串 2）
    int flag = strcmp(str2, str3);
    printf("%d\n", flag);
    return 0;
}