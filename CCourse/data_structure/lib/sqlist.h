#ifndef SQLIST_H
#define SQLIST_H

#define sqlist_max_len 100
typedef int data_t;
typedef struct {
    data_t data[sqlist_max_len];
    int last;
} sqlist, *sqlist_p;

sqlist_p create();

void show(sqlist_p l);

int clear(sqlist_p l);

int empty(sqlist_p l);

int length(sqlist_p l);

int locate(sqlist_p l, data_t d);

int insert(sqlist_p l, data_t d, int pos);

int purge(sqlist_p l);

int sqlist_delete(sqlist_p l);

int merge(sqlist_p target, sqlist_p source);

int removeByIndex(sqlist_p l, int pos);

#endif //SQLIST_H