// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
using namespace std;
typedef struct information
{
    int number;//编号
    char name[50];//名称
    char lntroduction[50];//简介
    information** path[10];//路径
    int distance[10];//距离
    int key;
}inform;
class Figure
{
private:
    char a[50];
    char s[5];
    int i, k, j , m;
    int h, g[10];
public:
    int min, max, g1[10];//路径，距离
    inform* p[10];
	Figure(const char *ss);//从文件读取数据
	~Figure();
    int _path(inform* p1, inform* p2);//最短路径
    void enquiry_path(inform* p1, inform* p2);
    void enquiry(int i);
};
Figure::Figure(const char *ss){
    i = 0, k = 0, j = 14, m = 0;
    memset(p, 0, 10 * 4);
    memset(a, 0, 50);
    memset(s, 0, 5);
    ifstream inFile(ss, ios::in);
    while (!inFile.eof()) {
        k = 0, j = 0, m = 0;
        p[i] = new inform();
        memset(a, 0, 50);
        inFile.getline(a, 100);
        for (unsigned int ii = 6; ii <= strlen(a); ii++)
            s[ii - 6] = a[ii];
        p[i]->number = atoi(s);
        memset(s, 0, 5);
        memset(a, 0, 50);
        inFile.getline(a, 100);
        memcpy(p[i]->name, a, 50);
        memset(a, 0, 50);
        inFile.getline(a, 100);
        memcpy(p[i]->lntroduction, a, 50);
        memset(a, 0, 50);
        inFile.getline(a, 100);
        for (unsigned int ii = 12; ii <= strlen(a); ii++)
        {
            if (a[ii] > 0) {
                s[k] = a[ii];
                k++;
            }
            else {
                k = 0;
                p[i]->path[j++] = &p[atoi(s) - 1];
                memset(s, 0, 5);
                ii++;
            }
        }
        j = 0;
        memset(a, 0, 50);
        inFile.getline(a, 100);
        for (unsigned int ii = 14; ii <= strlen(a); ii++)
        {
            if (a[ii] > 0) {
                s[k] = a[ii];
                k++;
            }
            else {
                k = 0;
                p[i]->distance[j++] = atoi(s);
                memset(s, 0, 5);
                ii++;
            }
        }
        memset(a, 0, 50);
        inFile.getline(a, 100);
        i++;
    }
}
Figure::~Figure()
{
    for (int ii = 0; ii < i; ii++)
    {
        delete p[ii];
    }
}
void Figure::enquiry(int i) {
    cout << "编号：" << p[i]->number << endl;
    cout << p[i]->name << endl;
    cout << p[i]->lntroduction << endl;
}
void Figure::enquiry_path(inform* p1, inform* p2) {
    min = 0, max = 999, h = 0;
    memset(g, 0, 10 * sizeof(int));
    memset(g1, 0, 10 * sizeof(int));
    _path(p1,p2);
    cout << "最短距离：" << max << endl;
    cout << "路径编号：" << p1->number;
    for (int i = 0; g1[i] != 0; i++)
        cout << "---" << g1[i];
    cout << endl;
}
int Figure::_path(inform* p1, inform* p2)
{
    if (p1->key == 1)return 0;//判断是否访问过
    p1->key = 1;
    for (int i = 0; p1->path[i] != 0; i++)
    {
        if ((*(p1->path[i]))->key == 1)continue;
        min = min + p1->distance[i];       //
        g[h++] = (*(p1->path[i]))->number;//添加路径
        if ((*(p1->path[i])) == p2){
            if (min < max) {
                max = min;
                memcpy(g1, g, 10 * sizeof(int));
            };
            min = min - p1->distance[i];//
            g[--h] = 0;                //返回路径
            continue;
        }
        _path((*(p1->path[i])), p2);
        min = min - p1->distance[i];//
        g[h--] = 0;                //返回路径
    }
    p1->key = 0;
    return 0;
}
int main()
{
    int a = 0, i = 0, j = 0;
    Figure aa("a.txt");
    cout << "输入1查询路径" << endl;
    cout << "输入2查询信息" << endl;
    cout << "输入3退出" << endl;
    cout << "-------------" << endl;
    while (true)
    {
        cout << "输入选项" << endl;
        cout << "-------------" << endl;
        cin >> a;
        if (a == 3)break;
        switch (a)
        {
        case 1:
            cout << "输入起点和终点编号" << endl;
            cin >> i >> j;
            aa.enquiry_path(aa.p[i-1], aa.p[j-1]);
            break;
        case 2:
            cin >> i;
            aa.enquiry(i-1);
            break;
        default:
            break;
        }
    }
    return 0;
}

/*
队列具有以下两个特点：
数据从队列的一端进，另一端出；
数据的入队和出队遵循"先进先出"的原则；
链式队列的实现，只需创建两个指针（命名为 top 和 rear）分别指向链表中队列的队头元素和队尾元素；
链队队列中，当有新的数据元素入队，只需进行以下 3 步操作：
1.将该数据元素用节点包裹，例如新节点名称为 elem；
2.与 rear 指针指向的节点建立逻辑关系，即执行 rear->next=elem；
3.最后移动 rear 指针指向该新节点，即 rear=elem；
链式队列中队头元素出队，需要做以下 3 步操作：
1.通过 top 指针直接找到队头节点，创建一个新指针 p 指向此即将出队的节点；
2.将 p 节点（即要出队的队头节点）从链表中摘除；
3.释放节点 p，回收其所占的内存空间
*/

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

