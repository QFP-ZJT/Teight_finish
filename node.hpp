//
// Created by ZJT on 2017/4/25.
//

#ifndef TEIGHT_NODE_H
#define TEIGHT_NODE_H

#include <vector>

using namespace std;

class node {
public:
    //缺省构造方法
    node() {};

    ~node() {
    };

    node(int time);

    //从文件中读取
    node(char *filename);

    //从根据数组构造
    node(int *a, node *fa, int via);

    //探索新的路径
    static vector<node *> move(node *a);

    //返回一个P
    int *newP();

    //判断两个node时候是一致的
    static bool equal(node *a, node *b);

    //打印节点
    void Printf();

    //得到正向的路径
    vector<node *> getPath();

    //得到反向的路径
    vector<node *> getRePath();

    //数字转转文字
    char *lan(int a) {
        char *re = "error";
        switch (a) {
            case 0:
                re = "上";
                break;
            case 1:
                re = "下";
                break;
            case 2:
                re = "左";
                break;
            case 3:
                re = "右";
                break;
        }
        return re;
    }

    //提供相似度
    void getSimilarity_same(node *another,int hh);

    void getSimilarity_distance(node *another,int hh);

//自定义排序方式
    struct cmp_des {
        bool operator()(const node *a, const node *b) const {
            return a->Similarity < b->Similarity;      //大顶堆
        }
    };

    struct cmp_inc {
        bool operator()(const node *a, const node *b) const {
            return a->Similarity > b->Similarity;      //小顶堆
        }
    };

//protected:

    //    用一位数组的方式村春矩阵
    int *P = new int[9];
    //    0的位置
    int z;

    int hash = 0;

    //    如何变化得到的    TODO 感觉效率太低  暂时取消   由下面的方式代替
    vector<int> path;
    //    从父节点到当前节点的变化方式
    int via;
    //    父节点
    node *father = NULL;

    int Similarity=0;
    //深度
    int h=0;

    int temp_dis;
};

//    上 下 左 右  需要移动的矢量
static const int d[4] = {-3, 3, -1, 1};
static const int re_d[4] = {1, 0, 3, 2};
static int dis[9][9] = {{0, 1, 2, 1, 2, 3, 2, 3, 4},
                        {1, 0, 1, 2, 1, 2, 3, 2, 3},
                        {2, 1, 0, 3, 2, 1, 4, 3, 2},
                        {1, 2, 3, 0, 1, 2, 1, 2, 3},
                        {2, 1, 2, 1, 0, 1, 2, 1, 2},
                        {3, 2, 1, 2, 1, 0, 3, 2, 1},
                        {2, 3, 4, 1, 2, 3, 0, 1, 2},
                        {3, 2, 3, 2, 1, 2, 1, 0, 1},
                        {4, 3, 2, 3, 2, 1, 2, 1, 0}};
static const int Hash[9] = {40320, 5040, 720, 120, 24, 6, 2, 1, 0};

#endif //TEIGHT_NODE_H
