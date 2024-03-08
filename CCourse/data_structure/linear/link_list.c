//
// Created by wyg on 2024/3/8.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "link_List.h"

link_list create() {
    link_list l = (link_list) malloc(sizeof(link_list_node));
    if (l == NULL) {
        printf("link_list malloc failed\n");
        return l;
    }
    memset(l, 0, sizeof(link_list_node));
    l->next = NULL;
    return l;
}

void show(link_list head) {
    if (head == NULL) {
        printf("link_list is NULL ");
        return;
    }
    link_list p = head;
    printf(" %d ", p->data);
    while (p->next != NULL) {
        printf(" %d ", p->next->data);
        p = p->next;
    }
    puts("");
}

int tail_insert(link_list head, data_t d) {
    while (head->next != NULL) {
        head = head->next;
    }
    link_list l = create();
    if (l != NULL) {
        l->data = d;
        head->next = l;
        return 0;
    } else {
        return -1;
    }
}

link_list head_insert(link_list head, data_t d) {
    link_list l = create();
    if (l != NULL) {
        l->data = d;
        l->next = head;
        return l;
    } else {
        return head;
    }
}

link_list get_link_list(link_list head, int pos) {
    link_list node = head;
    link_list find = NULL;
    int i = 0;
    while (node != NULL) {
        if (pos == i) {
            find = node;
            break;
        }
        node = node->next;
        i++;
    }
    return find;
}

int locate(link_list head, data_t d) {
    link_list node = head;
    int i = 0;
    while (node != NULL) {
        if (node->next == NULL)
            return -1;
        if (node->data == d)
            break;
        node = node->next;
        i++;
    }
    return i;
}

int insertByPos(link_list head, data_t d, int pos) {
//    link_list pre = NULL;
//    link_list node = head;
//    int i = 0;
//    while (i < pos) {
//        if (node->next == NULL) {
//            link_list newNode = create();
//            node->next = newNode;
//        }
//        pre = node;
//        node = node->next;
//        i++;
//    }
//    link_list insert = create();
//    if (insert == NULL) {
//        return -1;
//    }
//    insert->data = d;
//    insert->next = node;
//    if (pre != NULL)pre->next = insert;
//    获取前一个节点
    if (pos == 0) return -1;
    link_list pre = get_link_list(head, pos - 1);
    if (pre == NULL) return -1;
    link_list insert = create();
    insert->data = d;
    insert->next = pre->next;
    pre->next = insert;
    return 0;

}

int removeByPos(link_list head, int pos) {
//    link_list pre = NULL;
//    link_list node = head;
//    int i = 0;
//    while (i < pos && node->next != NULL) {
//        pre = node;
//        node = node->next;
//        i++;
//    }
//    if (i == pos && pre != NULL) {
//        pre->next = node->next;
//        return 0;
//    }
//    return -1;
    if (pos == 0) return -1;
    link_list pre = get_link_list(head, pos - 1);
    if (pre == NULL) {
        printf("%d node is NULL\n", pos - 1);
        return -1;
    }
    link_list hit = pre->next;
    if (hit == NULL) {
        printf("%d node is NULL\n", pos);
        return -1;
    }
    pre->next = hit->next;
    free(hit);
    return 0;
}

int clear(link_list head) {
    if (head == NULL) return -1;
    //记录下一个节点
    link_list next = head->next;
    free(head);
    //当下一个节点不是NULL时进行操作
    while (next != NULL) {
        //记录当前节点
        link_list hit = next;
        //重新赋值下一个节点
        next = next->next;
        //释放当前节点
        free(hit);
    }
    return 0;
}

link_list find_last_pre_node(link_list head) {
    link_list node = head;
    link_list pre = NULL;
    while (node->next != NULL) {
        pre = node;
        node = node->next;
    }
    return pre;
}

link_list reverse(link_list head) {
    if (head == NULL) {
        printf("link_list is NULL\n");
        return NULL;
    }
    link_list p = head;
    link_list node = NULL;
    while (1) {
        link_list next = p->next;
        //p是最后一个了
        if (next == NULL) {
            return node;
        }
        //p不是最后一个
        p->next = next->next;
        if (node == NULL) {
            next->next = p;
        } else{
            next->next = node;
        }
        node = next;
    }
}