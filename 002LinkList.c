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
        LNode *node;
        int j = 0;
        node = list;
        while (node != NULL && j < i - 1) // 找到位序i前面一个节点
        {
                node = node->next;
                j++;
        }
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
bool InsertPreNodeUnilateralLinkList(LinkList list, LNode *p, ElemType e)
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
        int a;
        HeadNodeUnilateralLinkListDelete(list, 3, &a);
        printf("delete a: %d\n", a);
        HeadNodeUnilateralLinkListPrint(list);
}

// 双链表
// 循环链表
// 静态链表
int main()
{
        // int* p = NULL;
        // printf("%p\n", p); 指向NULL的指针地址值为 0000000000000000 16位进制 长度16 代表8个字节 64位系统
        // TestHeadNodeUnilateralLinkList();
        TestNoHeadUnilateralLinkList();

        return 0;
}
