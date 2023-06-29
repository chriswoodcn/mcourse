/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-06-28 07:52:53
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-06-29 09:10:43
 * @Description: 数据结构-链表
 * 
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int
// -------------------------------------------线性表之链表------------------------------------------------------
// 单链表
// 两种实现: 带头结点  不带头结点
struct LNode
{
        ElemType data;      // 每个节点存放一个数据
        struct LNode *next; // 指向下一个节点
};
typedef struct LNode LNode;
typedef struct LNode *LinkList;

// 上面的等价于
// typedef struct LNode {
//   ElemType data;
//   struct LNode* next;
// }LNode, * LinkList;

/**
 * @brief 逆向建立单链表
 * @param {LinkList} list 表指针
 */
LinkList ListHeadInsert(LinkList list)
{
        LNode *s;
        int x;
        list = (LinkList)malloc(sizeof(LNode));
        list->next = NULL;
        scanf("%d", &x);
        while (x != 999)
        {
                s = (LNode *)malloc(sizeof(LNode));
                s->data = x;
                s->next = list->next;
                list->next = s;
                scanf("%d", &x);
        }
        return list;
}
void TestListHeadInsert()
{
        LinkList list;
        LinkList list2 = ListHeadInsert(list);

        LNode *start = list2;
        ElemType i = start->data;
        printf("start value: %d next: %p\n", i, start->next);
        while (start->next != NULL)
        {
                start = start->next;
                ElemType i = start->data;
                printf("node value: %d next: %p\n", i, start->next);
        }
}

/**
 * @description: 不带头单链表初始化 指针指向NULL或者指向数据节点
 * @brief 不带头单链表初始化 指针指向NULL或者指向数据节点
 * @param {LinkList*} list 二级指针
 * @return {bool}
 */
bool InitNoHeadNodeUnilateralLinkList(LinkList *list)
{
        *list = NULL;
        return true;
}

/**
 * @description: 不带头单链表打印
 * @brief 不带头单链表打印
 * @param {LinkList} list 表指针
 * @return {*}
 */
void NoHeadUnilateralLinkListPrint(LinkList list)
{
        if (list == NULL)
        {
                printf("list is NULL\n");
                return;
        }
        LNode *node = list;
        do
        {
                printf("%d ", node->data);
                node = node->next;
        } while (node != NULL);
        printf("\n");
}

/**
 * @description: 不带头单链表插入
 * @brief 不带头单链表插入
 * @param {LinkList*} L  二级指针
 * @param {int} i 位序
 * @param {ElemType} e 元素
 * @return {bool}
 */
bool NoHeadNodeUnilateralLinkListInsert(LinkList *L, int i, ElemType e)
{
        if (i < 1)
                return false;
        if (i == 1)
        {
                LNode *s = (LNode *)malloc(sizeof(LNode));
                s->data = e;
                s->next = *L;
                *L = s;
                return true;
        }
        LNode *node;
        int j = 1;
        node = (*L);
        while (node != NULL && j < i - 1)
        {
                node = node->next;
                j++;
        }
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = e;
        if (node == NULL)     // 节点为NULL
                return false; // i值不合法
        s->next = node->next;
        node->next = s;
        return true;
}

/**
 * @description: 带头单链表初始化 指针指向一个无数据的节点
 * @brief:
 * @param {LinkList*} list 二级指针
 * @return {*}
 */
bool InitHeadNodeUnilateralLinkList(LinkList *list)
{
        LNode *node = (LNode *)malloc(sizeof(LNode));
        node->next = NULL;
        *list = node;
        return true;
}

/**
 * @description: 带头单链表打印
 * @brief 带头单链表打印
 * @param {LinkList} list 表指针
 * @return {*}
 */
void HeadNodeUnilateralLinkListPrint(LinkList list)
{
        while (list->next != NULL)
        {
                list = list->next;
                printf("%d ", list->data);
        }
        printf("\n");
}
/**
 * @description: 找到位序i前面一个节点
 * @brief 找到位序i前面一个节点
 * @param {LinkList} *list 链表指针
 * @param {int} start 开始节点位序
 * @param {int} i 位序
 * @return {LNode*} 节点指针
 */
LNode *FindNodeUnilateralLinkList(LinkList *list, int start, int i)
{
        if (start < 1 || i < 1)
        {
                return NULL;
        }
        LNode *node;
        int j = start - 1;
        node = *list;
        while (node != NULL && j < i) // 找到位序i节点
        {
                node = node->next;
                j++;
        }
        return node;
}
/**
 * @description: 向节点后插入一个元素
 * @brief 向节点后插入一个元素
 * @param {LNode} *p 节点指针
 * @param {ElemType} e 元素
 * @return {bool}
 */
bool InsertNextNodeUnilateralLinkList(LNode *p, ElemType e)
{
        if (p == NULL)
                return false;
        LNode *s = (LNode *)malloc(sizeof(LNode));
        if (s == NULL)
                return false;
        s->data = e;
        s->next = p->next;
        p->next = s;
        return true;
}
/**
 * @description: 向节点前插入一个元素,本质上依旧是向后面插入一个节点,但是把前后连个节点的数据交换下
 * @brief 向节点前插入一个元素
 * @param {LNode} *p 节点指针
 * @param {ElemType} e 元素
 * @return {bool}
 */
bool InsertPreNodeUnilateralLinkList(LNode *p, ElemType e)
{

        if (p == NULL)
                return false;
        LNode *s = (LNode *)malloc(sizeof(LNode));
        if (s == NULL)
                return false;
        s->next = p->next;
        p->next = s;
        s->data = p->data;
        p->data = e;
        return true;
}
/**
 * @description: 删除节点后一个节点
 * @brief 删除节点后一个节点
 * @param {LNode} *p 节点指针
 * @param {ElemType} e 元素
 * @return {bool}
 */
bool DeleteNextNodeUnilateralLinkList(LNode *p, ElemType *e)
{
        if (p == NULL)
        {
                (*e) = NULL;
                return false;
        }
        LNode *next = p->next;
        if (next == NULL)
        {
                (*e) = NULL;
                return false;
        }
        p->next = next->next;
        *e = next->data;
        free(next);
        return true;
}
/**
 * @description: 删除位序节点的前一个节点
 * @brief 删除位序节点的前一个节点
 * @param {LinkList} list 链表指针
 * @param {int} i 位序
 * @param {ElemType} e 元素
 * @return {bool}
 */
bool DeletePreNodeUnilateralLinkList(LinkList list, int i, ElemType *e)
{
        LNode *preNode = FindNodeUnilateralLinkList(&list, 1, i - 1);
        if (preNode == NULL)
        {
                (*e) = NULL;
                return false;
        }
        LNode *next = preNode->next;
        if (next == NULL)
        {
                (*e) = NULL;
                return false;
        }
        preNode->next = next->next;
        free(next);
        (*e) = preNode->data;
        return true;
}
/**
 * @description: 带头单链表的插入
 * @brief 带头单链表的插入
 * @param {LinkList} list 表指针
 * @param {int} i 位序
 * @param {ElemType} e 元素
 * @return {bool}
 */
bool HeadNodeUnilateralLinkListInsert(LinkList list, int i, ElemType e)
{
        if (i < 1)
                return false;
        LNode *node;
        int j = 0;
        node = list;
        while (node != NULL && j < i - 1) // 找到位序i前面一个节点
        {
                node = node->next;
                j++;
        }
        if (node == NULL)     // 节点为NULL
                return false; // i值不合法
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = e;
        s->next = node->next;
        node->next = s;
        return true;
}

/**
 * @description: 带头单链表的删除
 * @brief 带头单链表的删除
 * @param {LinkList} list 表指针
 * @param {int} i 位序
 * @param {ElemType*} e 指针
 * @return {bool}
 */
bool HeadNodeUnilateralLinkListDelete(LinkList list, int i, ElemType *e)
{
        if (i < 1)
                return false;
        // LNode *node;
        // int j = 0;
        // node = list;
        // while (node != NULL && j < i - 1) // 找到位序i前面一个节点
        // {
        //         node = node->next;
        //         j++;
        // }
        LNode *node = FindNodeUnilateralLinkList(&list, 1, i - 1);
        if (node == NULL)     // 前一位节点为NULL
                return false; // i值不合法
        LNode *current = node->next;
        if (current == NULL)
                return false; // i值不合法
        LNode *next = current->next;
        node->next = next;
        (*e) = current->data;
        return true;
}
/**
 * @description: 带头单链表按位查找
 * @brief 带头单链表按位查找
 * @param {LinkList} list 链表指针
 * @param {int} i 位序
 * @return {LNode*} 节点指针
 */
LNode *HeadNodeUnilateralLinkListGetElem(LinkList list, int i)
{
        if (i < 1)
                return NULL;
        LNode *node = list;
        int j = 0;
        while (node != NULL && j < i)
        {
                node = node->next;
                j++;
        }
        return node;
}
/**
 * @description: 带头单链表按值查找
 * @brief 带头单链表按值查找
 * @param {LinkList} list 链表指针
 * @param {ElemType} e 值
 * @param {int*} count 次数
 * @return {LNode*} 节点指针
 */
LNode *HeadNodeUnilateralLinkListLocateElem(LinkList list, ElemType e, int *count)
{
        LNode *node = list;
        int j = 0;
        while (node != NULL && node->data != e)
        {
                node = node->next;
                j++; // 一共找了j次
                if (node->data == e)
                {
                        break;
                }
        }
        *count = j;
        return node;
}

/**
 * 测试不带头单链表API
 */
void TestNoHeadUnilateralLinkList()
{
        LinkList list;
        InitNoHeadNodeUnilateralLinkList(&list);
        NoHeadNodeUnilateralLinkListInsert(&list, 1, 10);
        NoHeadNodeUnilateralLinkListInsert(&list, 2, 20);
        NoHeadNodeUnilateralLinkListInsert(&list, 3, 30);
        NoHeadUnilateralLinkListPrint(list);
}
/**
 * 测试带头单链表API
 */
void TestHeadNodeUnilateralLinkList()
{
        LinkList list;
        InitHeadNodeUnilateralLinkList(&list);
        HeadNodeUnilateralLinkListInsert(list, 1, 1);
        HeadNodeUnilateralLinkListInsert(list, 2, 10);
        HeadNodeUnilateralLinkListInsert(list, 3, 100);
        HeadNodeUnilateralLinkListInsert(list, 4, 1000);
        HeadNodeUnilateralLinkListInsert(list, 3, 999);
        HeadNodeUnilateralLinkListInsert(list, 10, 1000);
        HeadNodeUnilateralLinkListPrint(list);
        int count1 = 0;
        LNode *locate1 = HeadNodeUnilateralLinkListLocateElem(list, 1000, &count1);
        printf("locate data: %d find count: %d\n", locate1->data, count1);
        int a;
        HeadNodeUnilateralLinkListDelete(list, 3, &a);
        printf("delete a: %d\n", a);
        HeadNodeUnilateralLinkListPrint(list);
        int count2 = 0;
        LNode *locate2 = HeadNodeUnilateralLinkListLocateElem(list, 1000, &count2);
        printf("locate data: %d find count: %d\n", locate2->data, count2);
}
// 单链表的建立 尾插法建立单链表
bool InitHeadNodeLinkList(LinkList *list)
{
        *list = (LNode *)malloc(sizeof(LNode));
        if (*list == NULL)
                return false;
        (*list)->next = NULL; // 头结点后暂时没有节点
        return true;
}
bool InsertHeadNodeLinkList(LinkList list, int i, ElemType e)
{
        if (i < 1)
                return false;
        LNode *p;
        int j = 0;
        p = list;
        while (p != NULL && j < i - 1)
        {
                p = p->next;
                j++;
        }
        if (p == NULL)
        {
                return false;
        }
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = e;
        s->next = p->next;
        p->next = s;
        return true;
}
// 双链表
// 双链表节点定义
/**
 * @description:
 * @brief:
 * @return {*}
 */
typedef struct DNode
{
        ElemType data;
        struct DNode *prior, *next;
} DNode, *DLinkList;
/**
 * @description: 带头双链表初始化
 * @brief 带头双链表初始化
 * @param {DLinkList*} list 链表指针
 * @return {bool}
 */
bool InitDLinkList(DLinkList *list)
{
        (*list) = (DNode *)malloc(sizeof(DNode));
        if ((*list) == NULL)
                return false;
        (*list)->prior = NULL;
        (*list)->next = NULL;
        return true;
}
/**
 * @description: 双链表插入节点
 * @brief 双链表插入节点
 * @param {DNode*} p p节点
 * @param {DNode*} q 后面插入的节点
 * @return {bool}
 */
bool InsertNextDNode(DNode *p, DNode *q)
{
        if (p == NULL || q == NULL)
                return false;
        q->next = p->next;   // 节点q插入到节点p之后,一共需要修改4个指针的值
        if (p->next != NULL) // 如果p节点有后一个节点的话
                p->next->prior = q;
        q->prior = q;
        p->next = q;
}
/**
 * @description: 双链表删除p节点
 * @brief 双链表删除p节点
 * @param {DNode*} p p节点
 * @return {bool}
 */
bool deleteDNode(DNode *p)
{
        if (p == NULL)
                return false;
        if (p->prior != NULL)
                p->prior->next = p->next;
        if (p->next != NULL)
                p->next->prior = p->prior;
        free(p);
        return true;
}
/**
 * @description: 双链表删除p节点的后继节点
 * @brief 双链表删除p节点的后继节点
 * @param {DNode*} p p节点
 * @return {bool}
 */
bool deleteNextDNode(DNode *p)
{
        if (p == NULL)
                return false;
        DNode *del = p->next;
        if (del == NULL)
                return false;
        p->next = del->next;
        if (del->next != NULL)
                del->next->prior = p;
        free(del);
        return true;
}
bool destroyDLinkList(DLinkList list)
{
        while (list->next != NULL)
                deleteNextDNode(list); // 循环删除后继结点
        free(list);                    // 释放头结点
        list = NULL;
}
// 循环链表
// 循环单链表 普通单链表最后一个节点的next指向头结点
// 从一个节点出发,可以找到其他任何一个节点
bool InitCircleLinkList(LinkList *list)
{
        (*list) = (LNode *)malloc(sizeof(LNode));
        if ((*list) == NULL)
                return false;
        (*list)->next = (*list);
        return true;
}
bool EmptyCircleLinkList(LinkList list)
{
        if (list->next == list)
                return true;
        else
                return false;
}
bool TailCircleLinkList(LinkList list, LNode *node)
{
        if (node->next == list)
                return true;
        else
                return false;
}

// 循环双链表 普通双链表最后一个节点的next指向头结点,头节点的prior指向尾节点
bool InitCircleDLinkList(DLinkList *list)
{
        (*list) = (DNode *)malloc(sizeof(DNode));
        if ((*list) == NULL)
                return false;
        (*list)->next = (*list);
        (*list)->prior = (*list);
        return true;
}
bool EmptyCircleDLinkList(DLinkList list)
{
        if (list->next == list)
                return true;
        else
                return false;
}
bool TailCircleDLinkList(DLinkList list, DNode *node)
{
        if (node->next == list)
                return true;
        else
                return false;
}
// 静态链表 分配一整片连续的内存空间,各个节点集中安置
// 数组下标0的节点充当头结点,每个节点除数据元素外还存储下一个节点的数组下标
#define MaxSize 10
typedef struct Node
{
        ElemType data;
        int next;
} Node;
typedef Node SLinkList[MaxSize];
int main()
{
        // int* p = NULL;
        // printf("%p\n", p); 指向NULL的指针地址值为 0000000000000000 16位进制 长度16 代表8个字节 64位系统
        // TestHeadNodeUnilateralLinkList();
        TestNoHeadUnilateralLinkList();
        return 0;
}
