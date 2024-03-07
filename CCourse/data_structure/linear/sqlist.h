//
// Created by wyg on 2024/3/7.
//

#ifndef SQLIST_H
#define SQLIST_H
#endif //SQLIST_H

#define sqlist_max_len 100
typedef int data_t;
typedef struct {
    data_t data[sqlist_max_len];
    int last;
} sqlist, *sqlist_p;

sqlist_p create();
int clear(sqlist_p l);
int empty(sqlist_p l);
int length(sqlist_p l);
int locate(sqlist_p l, data_t d);
int insert(sqlist_p l, data_t d,int pos);
void show(sqlist_p l);