#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sqlist.h"

/**
 * 创建顺序表
 * @return sqlist_p 顺序表指针的值
 */
sqlist_p create() {
    sqlist_p l = (sqlist_p) malloc(sizeof(sqlist));
    if (l == NULL) {
        printf("sqlist malloc failed\n");
        return l;
    }
    memset(l, 0, sizeof(sqlist));
    l->last = -1;
    return l;
}

/**
 * 清空順序表
 * @param l 顺序表指针的值
 * @return 1 成功 0 失败
 */
int clear(sqlist_p l) {
    if (l == NULL) {
        printf("sqlist is NULL\n");
        return 0;
    }
    memset(l, 0, sizeof(sqlist));
    l->last = -1;
    return 1;
}

/**
 * 是否为空
 * @param l 顺序表指针的值
 * @return 1 是 0 否
 */
int empty(sqlist_p l) {
    if (l == NULL) {
        printf("sqlist is NULL\n");
        return 1;
    }
    return l->last > -1 ? 0 : 1;
}

/**
 * 顺序表长度
 * @param l 顺序表指针的值
 * @return 长度
 */
int length(sqlist_p l) {
    if (l == NULL) {
        printf("sqlist is NULL\n");
        return 0;
    }
    return l->last + 1;
}

/**
 * 元素的位置
 * @param l 顺序表指针的值
 * @param d 元素
 * @return 位置 -1 不存在
 */
int locate(sqlist_p l, data_t d) {
    if (l == NULL) {
        printf("sqlist is NULL\n");
        return -1;
    }
    if (l->last == -1)
        return -1;
    for (int i = 0; i <= l->last; ++i) {
        if (l->data[i] == d) {
            return i;
        }
    }
    return -1;
}

/**
 * 插入元素
 * @param l 顺序表指针的值
 * @param d 元素
 * @param pos 位置
 * @return 1 成功 0 失败
 */
int insert(sqlist_p l, data_t d, int pos) {
    if (l == NULL) {
        printf("sqlist is NULL\n");
        return 0;
    }
    if (l->last == sqlist_max_len - 1) {
        printf("sqlist is full\n");
        return 0;
    }
    if (pos < 0 || pos > l->last + 1) {
        printf("pos is invalid, must between 0 and %d\n", l->last + 1);
        return 0;
    }
    // 0 0
    if (pos <= l->last) {
        // 已有数据全部向后移动一位,从后向前顺序
        int index = l->last;
        while (index >= pos) {
            l->data[index + 1] = l->data[index];
            index--;
        }
    }
    // pos位置赋值
    l->data[pos] = d;
    l->last = l->last + 1;
    return 1;
}

void show(sqlist_p l) {
    if (l == NULL) {
        printf("sqlist is NULL\n");
    }
    printf(">>>>>>>>>> sqlist show start >>>>>>>>>>\n");
    for (int i = 0; i <= l->last; i++) {
        printf("%d-----%d\n", i, l->data[i]);
    }
    printf(">>>>>>>>>> sqlist show end >>>>>>>>>>\n");
}

/**
 * 释放顺序表
 * @param l 顺序表指针的值
 * @return 1 成功 0 失败
 */
int delete(sqlist_p l) {
    if (l == NULL) {
        printf("sqlist is NULL");
    }
    free(l);
    return 1;
}

/**
 * 合并顺序表
 * @param target 目标顺序表
 * @param source 来源顺序表
 * @return 1 成功 0 失败
 */
int merge(sqlist_p target, sqlist_p source) {
    if (target == NULL) {
        printf("target sqlist is NULL\n");
        return 0;
    }
    if (source == NULL) return 1;
    int temp_last = target->last;
    for (int i = 0; i < source->last + 1; ++i) {
        int idx = locate(target, source->data[i]);
        if (target->last + 1 >= sqlist_max_len) {
            printf("target sqlist capacity not enough\n");
            //恢复target的元素数量
            target->last = temp_last;
            return 0;
        }
        // target中不存在的元素
        if (idx == -1) {
            insert(target, source->data[i], target->last + 1);
        }
    }
    return 1;
}

int removeByIndex(sqlist_p l, int pos) {
    if (l == NULL) {
        printf("sqlist is NULL\n");
        return 0;
    }
    if (pos < 0 || pos > l->last) {
        printf("pos is invalid,must between 0 and %d\n", l->last);
        return 0;
    }
    if (empty(l) == 1) return 1;
    l->data[pos] = 0;
    l->last--;
    return 1;
}

/**
 * 刪除顺序表中的重复元素
 * @param l 顺序表指针的值
 * @return 1 成功 0 失败
 */
int purge(sqlist_p l) {
    if (l == NULL) {
        printf("sqlist is NULL\n");
        return 0;
    }
    if (l->last == 0) return 1;
    int i = 1, j;
    while (i <= l->last) {
        j = i - 1;
        while (j >= 0) {
            if (l->data[j] == l->data[i]) {
                //删除l->data[i]
                removeByIndex(l, i);
                break;
            } else {
                j--;
            }
        }
    }
    if (j < 0) {
        i++;
    }
}