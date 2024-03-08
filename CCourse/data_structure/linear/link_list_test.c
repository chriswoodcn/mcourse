//
// Created by wyg on 2024/3/8.
//
#include <stdio.h>
#include "link_list.h"


void test_sample_operate();

int main() {
    test_sample_operate();
    return 0;
}

void test_sample_operate() {
    link_list head = create();
    head->data = 0;
    tail_insert(head, 100);
    tail_insert(head, 200);
    tail_insert(head, 300);
    head = head_insert(head, 400);
    printf(">>>>>>>>>> print head:\n");
    show(head);
    printf(">>>>>>>>>> locate 100:\n");
    int pos = locate(head, 100);
    printf("100 pos is %d\n", pos);
    link_list find = get_link_list(head, 2);
    printf(">>>>>>>>>> find pos 2:\n");
    if (find != NULL) {
        printf("1 find data: %d\n", find->data);
    } else {
        printf("1 find is NULL\n");
    }
    printf(">>>>>>>>>> find pos 10:\n");
    find = get_link_list(head, 10);
    if (find != NULL) {
        printf("2 find data: %d\n", find->data);
    } else {
        printf("2 find is NULL\n");
    }
    printf(">>>>>>>>>> print head:\n");
    show(head);
    printf(">>>>>>>>>> insertByPos 10000 4:\n");
    int res = insertByPos(head, 10000, 4);
    if (res == 0) show(head);
    printf(">>>>>>>>>> removeByPos 3:\n");
    res = removeByPos(head, 3);
    if (res == 0) show(head);
    printf(">>>>>>>>>> reverse head:\n");
    head = reverse(head);
    show(head);
    printf(">>>>>>>>>> print head:\n");
    res = clear(head);
    if (res == 0)head = NULL;
    show(head);
}