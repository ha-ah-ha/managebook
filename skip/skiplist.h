#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <cmath>
using namespace std;

#define int_min -2147483648
#define int_max 2147483647

//跳表节点
template <class T>
struct skipnode
{
    int key;            //索引
    T value;            //值
    skipnode<T>** next; //各级链表

    //初始化跳表节点
    skipnode(int k, T v, int size)
        : key(k), value(v)
    {
        next = new skipnode<T> *[size];
    }
};

//跳表
template <class T>
class skiplist
{
public:
    int maxlevel;    //最大级数
    int empty_level; //当前最大的非空链表级数
    int size;        //字典数
    int max_key;     //最大节点key
    int min_key;     //最小节点key
    int in_timer;    //当前插入操作次数
    int de_timer;    //当前删除操作次数
    int fi_timer;    //当前查找操作次数
    int te_timer;    // search所用操作次数
    int re_timer;    //当前整理操作次数

    skipnode<T>* head;  //头结点指针
    skipnode<T>* tail;  //尾结点指针
    skipnode<T>** last; //记录第i层的最后节点（用于search,便于插入和删除）

    //初始化
    skiplist(int the_maxlevel);
    ~skiplist()
    {
        delete[] head;
        delete[] tail;
    }
    //随机获取等级
    int getlevel();

    //有输出查找
    void find(int the_key);

    //无输出查找（便于插入与删除）
    skipnode<T>* search(int the_key);

    //插入
    void insert(int the_key, T the_value);

    //删除
    void remove(int the_key);

    //删除最大元素所调用的remove函数
    void removing_max(int the_key);

    //删除最小元素所调用的remove函数
    void removing_min(int the_key);

    //删除最小key元素
    void remove_min();

    //删除最大key元素
    void remove_max();

    //用于调整跳表结构
    void resize();

    //输出timer
    void timer_print();

    // timer清0
    void timer_zero();

    //显示size大小
    int get_size();
};
