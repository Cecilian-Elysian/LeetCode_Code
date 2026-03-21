#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isValid(char* s) {
    int n = strlen(s);
    if (n % 2 != 0) return false;

    // 用数组模拟栈，top 指向栈顶
    char stack[100000];
    int top = 0;

    for (int i = 0; i < n; i++) {
        char c = s[i];

        // 如果是左括号，入栈
        if (c == '(' || c == '{' || c == '[') {
            stack[top++] = c;
        }
        // 如果是右括号
        else if (c == ')' || c == '}' || c == ']') {
            if (top == 0) return false;  // 栈空，无法匹配

            char topChar = stack[--top];

            // 检查是否匹配
            if (c == ')' && topChar != '(') return false;
            if (c == '}' && topChar != '{') return false;
            if (c == ']' && topChar != '[') return false;
        }
    }

    // 栈必须为空，才算有效
    return top == 0;
}

int main() {
    char s[1000];  // 分配足够空间

    printf("请输入括号字符串: ");
    scanf("%s", s);  // 读取整个字符串

    bool result = isValid(s);
    printf("%s -> %s\n", s, result ? "true" : "false");

    return 0;
}