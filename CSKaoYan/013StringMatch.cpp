/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-06-30 15:28:01
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-03 17:16:08
 * @Description: 串的模式匹配
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
using namespace std;
// ---------------------------------------------串的模式匹配---------------------------------------------------
// 模式匹配：子串的定位操作称为串的模式，它求的是子串（常称模式串）在主串中的位置。
#define MAXLEN 255 // 预定义最大串长为255

typedef struct
{
        char ch[MAXLEN]; // 静态数组实现（定长顺序存储）
                         // 每个分量存储一个字符
                         // 每个char字符占1B
        int length;      // 串的实际长度
} SString;
// 朴素模式匹配算法
int Index(SString S, SString T)
{
        int i = 1; // 扫描主串S
        int j = 1; // 扫描模式串T
        while (i <= S.length && j <= T.length)
        {
                if (S.ch[i] == T.ch[j])
                {
                        ++i;
                        ++j; // 继续比较后继字符
                }
                else
                {
                        i = i - j + 2;
                        j = 1; // 指针后退重新开始匹配
                }
        }
        if (j > T.length)
                return i - T.length;
        else
                return 0;
}
// 时间复杂度分析：
// 主串长度为n，模式串长度为m
// 最多比较n-m+1个子串
// 最坏时间复杂度 = O(nm)
//      每个子串都要对比m个字符(对比到最后一个字符才匹配不上)，共要对比n-m+1个子串，
//      复杂度 = O((n-m+1)m) = O(nm - m^2 + m) = O(nm)
// PS:大多数时候，n>>m
// 最好时间复杂度 = O(n)
//      每个子串的第一个字符就匹配失败，共要对比n-m+1个子串，复杂度 = O(n-m+1) = O(n)

// 改进的模式匹配算法——KMP算法
// 原理参考 https://programmercarl.com/0028.%E5%AE%9E%E7%8E%B0strStr.html
// 关键理解 前缀表 最长相等前缀后缀
//      前缀是指不包含最后一个字符的所有以第一个字符开头的连续子串；
//      后缀是指不包含第一个字符的所有以最后一个字符结尾的连续子串
// 原理
//      不匹配的字符之前，一定是和模式串一致的；
//      根据模式串T，求出next数组（只与模式串有关，与主串无关），利用next数组进行匹配，当匹配失败时，
//              主串的指针 i 不再回溯！next数组是根据子串求出来的，当前面的字符串已知时如果有重复的，
//              从当前的字符匹配即可
// 1.求next数组
// 作用：当模式串的第j个字符失配时，从模式串的第next[j]继续往后匹配;
// 对于任何模式串，当第1个字符不匹配时，只能匹配下一个子串，因此，next[1] = 0——表示模式串应右移一位，主串当前指针后移一位，再和模式串的第一字符进行比较；
// 对于任何模式串，当第2个字符不匹配时，应尝试匹配模式串的第一个字符，因此，next[2] = 0;
// 例：对于串 T = 'abaabc'
// next[0]  next[1]  next[2]  next[3] next[4] next[5] next[6]
//    -1        0        1        1       2       2       3
void cal_next(char *str, int *next, int len)
{
        next[0] = -1; // next[0]初始化为-1，-1表示不存在相同的最大前缀和最大后缀
        int k = -1;   // k初始化为-1
        for (int q = 1; q <= len - 1; q++)
        {
                while (k > -1 && str[k + 1] != str[q]) // 如果下一个不同，那么k就变成next[k]，注意next[k]是小于k的，无论k取任何值。
                {
                        k = next[k]; // 往前回溯
                }
                if (str[k + 1] == str[q]) // 如果相同，k++
                {
                        k = k + 1;
                }
                next[q] = k; // 这个是把算的k的值（就是相同的最大前缀和最大后缀长）赋给next[q]
        }
}
int KMP(char *str, char *ptr)
{
        int slen = strlen(str);
        int plen = strlen(ptr);
        int *next = new int[plen];
        cal_next(ptr, next, plen); // 计算next数组
        int k = -1;
        for (int i = 0; i < slen; i++)
        {
                while (k > -1 && ptr[k + 1] != str[i]) // ptr和str不匹配，且k>-1（表示ptr和str有部分匹配）
                        k = next[k];                   // 往前回溯
                if (ptr[k + 1] == str[i])
                        k = k + 1;
                if (k == plen - 1) // 说明k移动到ptr的最末端
                {
                        // cout << "在位置" << i-plen+1<< endl;
                        // k = -1;//重新初始化，寻找下一个
                        // i = i - plen + 1;//i定位到该位置，外层for循环i++可以继续找下一个（这里默认存在两个匹配字符串可以部分重叠），感谢评论中同学指出错误。
                        return i - plen + 1; // 返回相应的位置
                }
        }
        return -1;
}
// -1 -1 0 1 2 -1 0
void getNext(int *next, const string &s)
{
        next[0] = -1;
        int j = -1;
        for (int i = 1; i < s.size(); i++)
        {                                          // 注意i从1开始
                while (j >= 0 && s[i] != s[j + 1]) // 前后缀不相同了
                {
                        j = next[j]; // 向前回退
                }
                if (s[i] == s[j + 1]) // 找到相同的前后缀
                {
                        j++;
                }
                next[i] = j; // 将j（前缀的长度）赋给next[i]
        }
        // str ababaca
        // 当q=1时 str[0]!=str[1] next[1]=-1
        // 当q=2时 str[0]==str[2] k=0 next[2]=0
        // 当q=3时 k>-1&&str[1]==str[3] str[1]==str[3] k=1 next[3]=1
        // 当q=4时 k>-1&&str[2]==str[4] str[2]==str[4] k=2 next[4]=2
        // 当q=5时 k>-1&&str[3]!=str[5] k=next[2]=0; k>-1&&str[1]!=str[5]  k=next[0]=-1; next[5]=-1
        // 当q=6时 str[1]==str[6] k=0 next[6]=0

        // str abacaca
        // 当q=1时 str[0]!=str[1] next[1]=-1
        // 当q=2时 str[0]==str[2] k=0 next[2]=0
        // 当q=3时 k>-1&&str[1]!=str[3] k=next[0]=-1; next[3]=-1
        // 当q=4时 str[0]==str[4] k=0 next[4]=0
        // 当q=5时 k>-1&&str[1]!=str[5] k=next[0]=-1; next[5]=-1
        // 当q=6时 str[0]==str[6] k=0 next[6]=0
}
void getNextWithoutMinus(int *next, const string &s)
{
        next[0] = 0;
        int j = 0;
        for (int i = 1; i < s.size(); i++)
        {
                while (j > 0 && s[j] != s[i]) // j要保证大于0，因为下面有取j-1作为数组下标的操作
                {
                        j = next[j - 1]; // 注意这里，是要找前一位的对应的回退位置了
                }
                if (s[j] == s[i])
                {
                        j++;
                }
                next[i] = j; // 将j（前缀的长度）赋给next[i]
        }
}

int strStr(string haystack, string needle)
{
        if (needle.size() == 0)
        {
                return 0;
        }
        int next[needle.size()];
        getNext(next, needle);
        int j = -1;                               // 因为next数组里记录的起始位置为-1
        for (int i = 0; i < haystack.size(); i++) // 注意i就从0开始
        {
                while (j >= 0 && haystack[i] != needle[j + 1])
                {                    // 不匹配
                        j = next[j]; // j 寻找之前匹配的位置
                }
                if (haystack[i] == needle[j + 1]) // 匹配，j和i同时向后移动
                {
                        j++; // i的增加在for循环里
                }
                if (j == (needle.size() - 1))
                { // 文本串s里出现了模式串t
                        return (i - needle.size() + 1);
                }
        }
        return -1;
}
int strStr2(string haystack, string needle)
{
        if (needle.size() == 0)
        {
                return 0;
        }
        int next[needle.size()];
        getNextWithoutMinus(next, needle);
        int j = 0;                                // 因为next数组里记录的起始位置为0
        for (int i = 0; i < haystack.size(); i++) // 注意i就从0开始
        {
                while (j >= 0 && haystack[i] != needle[j])
                {
                        j = needle[j - 1];
                }
                if (haystack[i] == needle[j]) // 匹配，j和i同时向后移动
                {
                        j++; // i的增加在for循环里
                }
                if (j == needle.size())
                {
                        return (i - needle.size() + 1);
                }
        }
        return -1;
}
int main()
{
        // char *str = "bacbababadababacambabacaddababacasdsd";
        // char *ptr = "ababaca";
        // 计算一个长度为m(7)的转移函数next
        // next数组的含义就是一个固定字符串的最长前缀和最长后缀相同的长度
        // 比如：abcjkdabc，那么这个数组的最长前缀和最长后缀相同必然是abc。
        // cbcbc，最长前缀和最长后缀相同是cbc。
        // abcbc，最长前缀和最长后缀相同不存在
        // ababaca
        // 注意最长前缀：是说以第一个字符开始，但是不包含最后一个字符
        // 计算 next[0]，next[1]，next[2]，next[3]，next[4]，next[5]，next[6]
        //       a，      ab，      aba，    abab，  ababa，  ababac， ababaca
        //      -1       -1        0         1      2        -1       0
        // 这里-1表示不存在，0表示存在长度为1，2表示存在长度为3
        // int r = KMP(str, ptr);
        // printf("KMP r: %d", r);

        string s = "abacaca";
        string h = "bacbababadababacambabacaddababacasdsd";
        int res1 = strStr(h, s);
        int res2 = strStr2(h, s);
        cout << "res1: " << res1 << endl;
        cout << "res2: " <<res2 << endl;
        return 0;
}
