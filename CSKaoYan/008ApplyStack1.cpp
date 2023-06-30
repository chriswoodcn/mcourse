/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-06-29 15:55:52
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-06-30 09:46:57
 * @Description: 栈在括号匹配中的应用 p27
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
// -----------------------------栈在括号匹配中的应用-----------------------------------
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_left_bracket(char c)
{
        char left[3] = {'{', '[', '('};
        char *match = strchr(left, c);
        return match != NULL;
}
bool is_right_bracket(char c)
{
        char right[3] = {'}', ']', ')'};
        char *match = strchr(right, c);
        return match != NULL;
}

bool bracket_match(char *str)
{
        int len = strlen(str);
        char stack[len];
        int top = -1;
        for (int i = 0; i < len; i++)
        {
                if (is_left_bracket(str[i]))
                {
                        stack[++top] = str[i];
                }
                else if (is_right_bracket(str[i]))
                {
                        if (top == -1)
                        {
                                return false;
                        }
                        char c = stack[top--];
                        if (str[i] == ']' && c != '[')
                                return false;
                        if (str[i] == ')' && c != '(')
                                return false;
                        if (str[i] == '}' && c != '{')
                                return false;
                }
        }
        return top == -1;
}
int main()
{
        printf("%d\n", '{'); // 123
        printf("%d\n", '}'); // 125
        printf("%d\n", '['); // 91
        printf("%d\n", ']'); // 93
        printf("%d\n", '('); // 40
        printf("%d\n", ')'); // 41
        char to_match_str[] = "{this is one[a,[0],(b),{c},d],(hello),{one:(inner:aaa)}}";
        bool flag = bracket_match(to_match_str);
        printf("%d\n", flag);
        return 0;
}
