//
// Created by wyg on 2024/3/7.
//
#include <stdio.h>
#include "sqlist.h"

int main()
{
    sqlist_p p = create();
    int empty_res = empty(p);
    printf("empty_res: %d\n", empty_res);
    insert(p, 100, 0);
    insert(p, 200, 0);
    insert(p, 300, 0);
    show(p);
    return 0;
}