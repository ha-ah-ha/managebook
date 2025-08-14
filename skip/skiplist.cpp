#include "skiplist.h"

//初始化跳表
template <class T>
skiplist<T>::skiplist(int the_maxlevel)
    : maxlevel(the_maxlevel), size(0), empty_level(0), max_key(int_min), min_key(int_max),
    in_timer(0), te_timer(0), de_timer(0), fi_timer(0), re_timer(0)
{
    head = new skipnode<T>(int_max, int_max, the_maxlevel + 1);
    tail = new skipnode<T>(int_max, int_max, 0);
    last = new skipnode<T> *[maxlevel + 1];
    for (int i = 0; i <= maxlevel; ++i)
    {
        head->next[i] = tail;
    }
}

//随机获取等级
template <class T>
int skiplist<T>::getlevel()
{
    //以毫秒为种子获取随机数，等级分配更贴近理想情况
    LARGE_INTEGER seed;
    QueryPerformanceFrequency(&seed);
    QueryPerformanceCounter(&seed);
    srand(seed.QuadPart);
    int k = 1;
    while (rand() % 2)
    {
        ++k;
    }
    return k > maxlevel ? maxlevel : k;
}

//查找函数（有输出）
template <class T>
void skiplist<T>::find(int the_key)
{
    if (the_key > max_key || the_key < min_key)
    {
        printf("Not Found!\n");
        return;
    }
    skipnode<T>* before = head;
    int level = empty_level;
    //逐级寻找
    for (int i = level; i >= 0; --i)
    {
        while (before->next[i]->key < the_key)
        {
            ++fi_timer;
            before = before->next[i];
        }
    }
    //之前返回的是待验证的元素的前一个
    if (before->next[0]->key == the_key)
    {
        printf("Found It!\n");
        return;
    }
    else
    {
        printf("Not Found!\n");
        return;
    }
}

//查找函数（无输出）
//用于插入删除函数
template <class T>
skipnode<T>* skiplist<T>::search(int the_key)
{
    skipnode<T>* before = head;
    // empty_level为最大非空链表等级
    int level = empty_level;
    //逐级查找
    for (int i = level; i >= 0; --i)
    {
        while (before->next[i] != tail && before->next[i]->key < the_key)
        {
            ++te_timer;
            before = before->next[i];
        }
        // last[i]表示的是第i层要查找元素的前一个元素
        last[i] = before;
    }
    //返回待查找元素的前一个
    return before->next[0];
}

//插入函数
template <class T>
void skiplist<T>::insert(int the_key, T the_value)
{
    te_timer = 0;
    if (the_key >= int_max)
    {
        printf("The element is too large!please change!\n");
        return;
    }
    skipnode<T>* temp = search(the_key);
    in_timer += te_timer;
    if (temp->key == the_key)
    {
        printf("The element has existed!\n");
        return;
    }
    //判断当前插入元素会不会成为新最大值或最小值
    max_key = the_key > max_key ? the_key : max_key;
    min_key = the_key < min_key ? the_key : min_key;
    //随机获取等级，开始插入
    int this_level = getlevel();
    //如果该等级大于当前最大非空等级，则最大非空等级+1
    if (this_level > empty_level)
    {
        this_level = ++empty_level;
        last[this_level] = head;
    }
    //开始插入
    skipnode<T>* node = new skipnode<T>(the_key, the_value, this_level + 1);
    ++in_timer;
    for (int i = 0; i <= this_level; ++i)
    {
        node->next[i] = last[i]->next[i];
        last[i]->next[i] = node;
    }
    ++size;
    printf("The node has been insert!\n");
    printf("The level of it is ");
    cout << this_level << endl;
    return;
}

//删除函数
template <class T>
void skiplist<T>::remove(int the_key)
{
    te_timer = 0;
    if (the_key == max_key)
    {
        removing_max(the_key);
        cout << "Successfully!\n";
        return;
    }
    else if (the_key == min_key)
    {
        removing_min(the_key);
        cout << "Successfully!\n";
        return;
    }
    if (size == 1)
    {
        removing_min(the_key);
        cout << "Successfully!";
        return;
    }
    if (the_key > max_key || the_key < min_key)
    {
        printf("The element didn't exist!\n");
        return;
    }
    skipnode<T>* temp = search(the_key);
    de_timer += te_timer;
    //判断是否有该元素
    ++de_timer;
    if (temp->key != the_key)
    {
        printf("The element didn't exist!\n");
        return;
    }

    //更改该元素前一个的next指针，指向该元素的下一个
    for (int i = 0; i <= empty_level && last[i]->next[i] == temp; ++i)
    {
        last[i]->next[i] = temp->next[i];
    }

    //判断是不是最高非空等级链中的唯一一个，如果是，则empty_level（最大非空链表等级）-1
    while (empty_level > 0 && head->next[empty_level] == tail)
    {
        --empty_level;
    }
    delete temp;
    cout << "Successfully!" << endl;
    --size;
}

//删除最大元素函数（被调用函数）
template <class T>
void skiplist<T>::removing_max(int the_key)
{
    te_timer = 0;
    //如果只有一个元素，则需要更改最大值和最小值（单独进行判断）
    if (size == 1)
    {
        max_key = int_min;
        min_key = int_max;
        ++de_timer;
        for (int i = 0; i <= empty_level; ++i)
        {
            head->next[i] = tail;
        }
        empty_level = 0;
        --size;
        return;
    }
    skipnode<T>* temp = search(the_key);
    de_timer += te_timer;
    int the_temp_max_key = int_min;
    //获得新的最大元素的索引
    ++de_timer;
    for (int i = 0; i <= empty_level && last[i]->next[i] == temp; ++i)
    {
        last[i]->next[i] = temp->next[i];
        if (last[i]->key > the_temp_max_key && last[i]->key != int_max)
        {
            the_temp_max_key = last[i]->key;
        }
    }
    max_key = the_temp_max_key;

    //更改最大非空链表等级（类似remove函数）
    while (empty_level > 0 && head->next[empty_level] == tail)
    {
        --empty_level;
    }
    delete temp;
    --size;
}

//删除最小元素函数
template <class T>
void skiplist<T>::removing_min(int the_key)
{
    te_timer = 0;
    skipnode<T>* temp = search(the_key);
    de_timer += te_timer;
    //如果只有一个元素
    if (size == 1)
    {
        max_key = int_min;
        min_key = int_max;
        ++de_timer;
        for (int i = 0; i <= empty_level; ++i)
        {
            head->next[i] = tail;
        }
        delete temp;
        --size;
        empty_level = 0;
        return;
    }
    //开始删除
    ++de_timer;
    for (int i = 0; i <= empty_level && last[i]->next[i] == temp; ++i)
    {
        last[i]->next[i] = temp->next[i];
    }

    skipnode<T>* before = head;
    int level = empty_level;
    min_key = int_max;
    //获得新的最小元素索引
    for (int i = level; i >= 0; --i)
    {
        ++de_timer;
        if (before->next[i]->key < min_key)
        {
            min_key = before->next[i]->key;
        }
    }
    //更改最大非空跳表等级
    while (empty_level > 0 && head->next[empty_level] == tail)
    {
        --empty_level;
    }
    delete temp;
    --size;
}

//删除最小元素函数（直接使用的函数）
template <class T>
void skiplist<T>::remove_min()
{
    if (size == 0)
    {
        printf("The element didn't exist!\n");
        return;
    }
    //如果不为空
    removing_min(min_key);
    cout << "Successfully!" << endl;
    return;
}

//删除最大元素函数（直接使用的函数）
template <class T>
void skiplist<T>::remove_max()
{
    if (size == 0)
    {
        printf("The key was not found!\n");
        return;
    }
    //如果不为空
    removing_max(max_key);
    cout << "Successfully!" << endl;
    return;
}

template <class T>
void skiplist<T>::resize()
{
    bool reing = false;
    int now = empty_level;
    int timing = 2;
    //要删除类似下图情况
    // high1 ----- > high2
    // low1  ----- > low2
    while (timing && now >= 1)
    {
        --timing;
        skipnode<T>* low = head;
        skipnode<T>* high = head;
        while (low->next[now] != tail && low->next[now]->next[now] != tail &&
            high->next[now + 1] != tail && high->next[now + 1]->next[now + 1] != tail)
        {
            reing = true;
            ++re_timer;
            //符合要删除情况说明高层链的这条链有些冗余
            if (low->next[now]->key == high->next[now + 1]->key &&
                low->next[now]->next[now]->key == high->next[now + 1]->next[now + 1]->key)
            {
                ++re_timer;
                skipnode<T>* temp = high->next[now + 1]->next[now + 1];
                high->next[now + 1]->next[now + 1] = temp->next[now + 1];
                temp->next[now + 1] = tail;
            }

            //此时为这种情况
            //                       high1 ----- > high2
            // low1  ----- > low2
            //此时将low1指针移动到high1位置
            else if (low->next[now]->key < high->next[now + 1]->key)
            {
                while (low->next[now]->key < high->next[now + 1]->key)
                {
                    ++re_timer;
                    low = low->next[now];
                }
            }

            //此时为这种情况
            // high1 ----- >  ------>  high2
            // low1  ----- > low2
            //将low1移动到high2位置，将high1移动到high2
            else
            {
                while (low->next[now]->next[now]->key < high->next[now + 1]->next[now + 1]->key)
                {
                    ++re_timer;
                    low = low->next[now];
                }
                low = low->next[now];
                high = high->next[now + 1];
            }
        }
        --now;
    }
    for (int i = empty_level; i >= 0; --i)
    {
        ++re_timer;
        if (head->next[i] == tail)
        {
            --empty_level;
        }
        else
        {
            break;
        }
    }
    if (reing)
    {
        printf("OK!\n");
    }
    else
    {
        printf("No working!\n");
    }
}

template <class T>
void skiplist<T>::timer_print()
{
    string num;
    printf("请输入指令\n");
    printf("1->输出插入操作操作数\n");
    printf("2->输出查找操作操作数\n");
    printf("3->输出删除操作操作数\n");
    printf("4->输出整理操作操作数\n");
    printf("5->输出所有操作操作数\n");
    printf("其他->退出\n");
    cin >> num;
    if (num.length() > 1)
    {
        printf("Successfully\n");
        return;
    }
    switch (num[0] - '0')
    {
    case 1:
    {
        printf("%d次\n", in_timer);
        break;
    }

    case 2:
    {
        printf("%d次\n", fi_timer);
        break;
    }

    case 3:
    {
        printf("%d次\n", de_timer);
        break;
    }

    case 4:
    {
        printf("%d次\n", re_timer);
        break;
    }

    case 5:
    {
        printf("插入：%d次\n", in_timer);
        printf("删除：%d次\n", de_timer);
        printf("查询：%d次\n", fi_timer);
        printf("整理：%d次\n", re_timer);
        break;
    }

    default:
    {
        printf("Successfully\n");
        return;
    }
    }
}

template <class T>
void skiplist<T>::timer_zero()
{
    in_timer = 0;
    de_timer = 0;
    te_timer = 0;
    fi_timer = 0;
    re_timer = 0;
    printf("All clear!\n");
}

template <class T>
int skiplist<T>::get_size()
{
    return size;
}

//判断数字是否超过2*1e9或超过-9e8
bool judging(string& str)
{
    if (str.length() > 10)
    {
        return false;
    }
    if (str[0] == '-')
    {
        return true;
    }
    bool temp = false;
    if (str[0] > '2')
    {
        temp = true;
    }
    for (int i = 1; i < str.length(); ++i)
    {
        if (temp)
        {
            if (str[i] > '0')
            {
                return false;
            }
        }
    }
    return true;
}


int main()
{
    char order;
    skiplist<int> list(10);
    printf("                		   ************************************\n");
    printf("                		   * Welcome To The Skiplist System!  *\n");
    printf("                		   *        Creator: Mac-hawk         *\n");
    printf("                		   *       Created Time:2022/3/20     *\n");
    printf("                		   *       Thanks For Your Using!     *\n");
    printf("                		   ************************************\n");
    while (true)
    {
        printf("请输入指令进行操作\n");
        printf("0->退出\n");
        printf("1->查询\n");
        printf("2->插入\n");
        printf("3->删除\n");
        printf("4->删除最小关键字元素\n");
        printf("5->删除最大关键字元素\n");
        printf("6->输出操作比较次数\n");
        printf("7->清除操作比较次数\n");
        printf("8->跳表整理\n");
        printf("9->输出当前元素个数\n");
        printf("\n");
        cin >> order;
        if (order - '0' < 0 || order - '0' > 9)
        {
            cout << "指令无效!\n";
        }
        else
        {
            switch (order - '0')
            {
                //查找
            case 1:
            {
                string numing;
                int num;
                printf("请输入待查找元素关键字\n");
                cin >> numing;
                //利用judging函数，防止给出的数字越界（界线为-9e8~2e9）
                if (judging(numing))
                {
                    num = atoi(numing.c_str());
                    list.find(num);
                }
                else
                {
                    cout << "The key is too large!\n";
                }
                break;
            }

            //插入
            case 2:
            {
                string numing;
                int num;
                printf("请输入待插入元素关键字\n");
                cin >> numing;
                if (judging(numing))
                {
                    num = atoi(numing.c_str());
                    list.insert(num, num);
                }
                else
                {
                    cout << "The key is too large!\n";
                }
                break;
            }

            //删除
            case 3:
            {
                string numing;
                int num;
                printf("请输入待删除元素关键字\n");
                cin >> numing;
                if (judging(numing))
                {
                    num = atoi(numing.c_str());
                    list.remove(num);
                }
                else
                {
                    cout << "The key is too large!\n";
                }
                break;
            }

            //删除min
            case 4:
            {
                list.remove_min();
                break;
            }

            //删除max
            case 5:
            {
                list.remove_max();
                break;
            }

            // timer（比较次数）输出
            case 6:
            {
                list.timer_print();
                break;
            }

            // timer（比较次数）清空
            case 7:
            {
                list.timer_zero();
                break;
            }

            //进行调整跳表结构
            case 8:
            {
                list.resize();
                break;
            }

            case 9:
            {
                printf("当前元素");
                printf("%d", list.get_size());
                printf("个\n");
                break;
            }

            case 0:
            {
                printf("Thanks for using!\n");
                system("pause");
                return 0;
            }
            }
        }
        printf("\n\n\n");
    }
    return 0;
}