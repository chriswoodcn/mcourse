#include <stdio.h>
#include "sqlist.h"

void test_sample_operate();

void test_sample_merge();

void test_sample_purge();

int main() {
    test_sample_purge();
    return 0;
}

void test_sample_operate() {
    sqlist_p p = create();
    int empty_res = empty(p);
    printf("empty_res: %d\n", empty_res);
    insert(p, 100, 0);
    insert(p, 200, 0);
    insert(p, 300, 10);
    show(p);
    int len = length(p);
    printf("length: %d\n", len);
    delete(p);
}

void test_sample_merge() {
    sqlist_p p1 = create();
    insert(p1, 100, 0);
    insert(p1, 200, 0);

    sqlist_p p2 = create();
    insert(p2, 200, 0);
    insert(p2, 300, 0);
    insert(p2, 400, 0);

    merge(p1, p2);
    show(p1);

    delete(p1);
    delete(p2);
}

void test_sample_purge() {
    sqlist_p p = create();
    insert(p, 100, 0);
    insert(p, 100, 0);
    insert(p, 100, 0);
    insert(p, 100, 0);
    insert(p, 100, 0);
    insert(p, 100, 0);
    insert(p, 100, 0);
    insert(p, 100, 0);
    purge(p);
    show(p);
}