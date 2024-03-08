//
// Created by wyg on 2024/3/8.
//

#ifndef LINKLIST_H
#define LINKLIST_H
#endif
typedef int data_t;
typedef struct node
{
    data_t data;
    struct node *next;
} link_list_node, *link_list;

/**
 * 创建单链表
 * @return link_list 单链表的指针
 */
link_list create();

/**
 * 从头打印单链表的数据
 * @param head 单链表的头指针
 */
void show(link_list head);

/**
 * 尾部插入数据
 * @param head 单链表的头指针
 * @param d 数据
 * @return -1失败 0成功
 */
int tail_insert(link_list head, data_t d);

/**
 * 头插法
 * @param head 单链表的头指针
 * @param d 数据
 * @return 单链表的头指针
 */
link_list head_insert(link_list head, data_t d);

/**
 * 按序号查找
 * @param head 单链表的头指针
 * @param pos 序号 0~n-1
 * @return 单链表的头指针
 */
link_list get_link_list(link_list head, int pos);

/**
 * 查找元素的序号
 * @param head 单链表的头指针
 * @param d 元素
 * @return -1失败
 */
int locate(link_list head, data_t d);

/**
 * 按序号插入
 * @param head 单链表的头指针
 * @param d 元素
 * @param pos 序号 0~n-1
 * @return -1失败
 */
int insertByPos(link_list head, data_t d, int pos);

/**
 * 按序号删除
 * @param head 单链表的头指针
 * @param pos 序号 0~n-1
 * @return -1失败
 */
int removeByPos(link_list head, int pos);

/**
 * 清空链表
 * @param head 单链表的头指针
 * @return -1失败
 */
int clear(link_list head);

/**
 * 链表反转
 * @param head 单链表的头指针
 * @return 新的头指针
 */
link_list reverse(link_list head);

/**
 * 计算相邻两个节点元素数值之和最大的第一个节点的指针
 * @param head 单链表的头指针
 */
link_list compute_max_value_pre_node(link_list head);