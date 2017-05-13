//
// Created by ZJT on 2017/4/25.
//

#include <iostream>
#include <stack>
#include "node.hpp"

#define random(x) (rand()%x)

//节点的构造方法
node::node(int time) {
    int a[9];
    bool temp;
    for (int i = 0; i < 9;) {
        temp = 0;
        int x = random(9);
        for (int j = 0; j < i; j++)
            if (x == a[j]) {
                temp = true;
                break;
            }
        if (temp)
            continue;
        a[i] = x;
        i++;
    }
    for (int i = 0; i < 9; i++) {
        P[i] = a[i];
        if (a[i] == 0) {
            z = i;
        }
        cout << a[i] << "  ";
    }
    int count = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++)
            if (P[j] < P[i])
                count++;
        hash += (count * Hash[i]);
    }
    cout << endl;
}

node::node(int *a, node *fa, int via) {
    //    P = a;
    //    TODO 值得思考存储是几份
    father = fa;
    for (int i = 0; i < 9; i++) {
        P[i] = a[i];
        if (a[i] == 0) {
            z = i;
        }
    }
    int count = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++)
            if (P[j] < P[i])
                count++;
        hash += (count * Hash[i]);
    }
    father = fa;
    this->via = via;
}

int *node::newP() {
    int *re = new int[9];
    for (int i = 0; i < 9; i++) {
        re[i] = P[i];
    }
    return re;
}

//节点是都是一样的
bool node::equal(node *a, node *b) {
    for (int i = 0; i < 9; i++) {
        if (a->P[i] != b->P[i])
            return false;
    }
    return true;
}

//正向数组
vector<node *> node::getPath() {
    stack<node *> temp;
    vector<node *> re;
    node *node_temp = this;
    while (node_temp->father) {
        temp.push(node_temp);
        node_temp = node_temp->father;
    }
    while (!temp.empty()) {
//TODO 直接放入，为什么不行？
        node *a = temp.top();
        re.push_back(a);
//        cout<<temp.top()<<"  ";
        temp.pop();
    }
    return re;
}

//逻辑真的很重要
vector<node *> node::getRePath() {
    vector<node *> re;
    node *node_temp = this;
    int aa = node_temp->via, bb;
    while (node_temp->father) {
        bb = node_temp->father->via;
        node_temp->father->via = re_d[aa];
        aa = bb;
        node_temp = node_temp->father;
    }
    node_temp = this;
    if (node_temp->father) {
        node_temp = node_temp->father;
        while (node_temp->father) {
            re.push_back(node_temp);
            node_temp = node_temp->father;
        }
        re.push_back(node_temp);
    }
    return re;
}

//节点输出
void node::Printf() {
    cout << "*********" << endl;
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0)
            cout << "*";
        cout << this->P[i];
        if (i % 3 == 2)
            cout << "*" << endl;
        else
            cout << "  ";

    }
    //TODO 暂时取消
    //    for (int i = 0; i < this->path.size(); i++) {
    //        switch (this->path[i]) {
    //            case 0:
    //                cout << "上" << "  ";
    //                break;
    //            case 1:
    //                cout << "下" << "  ";
    //                break;
    //            case 2:
    //                cout << "左" << "  ";
    //                break;
    //            case 3:
    //                cout << "右" << "  ";
    //                break;
    //        }
    //    }
    //TODO 通过父节点的方式寻找遍历路径
    cout << "*********" << endl;
//    stack<int> temp;
//    node *node_temp = this;
//    temp.push(node_temp->via);
//    if (node_temp->father)
//        node_temp = node_temp->father;
//    while (node_temp->father != NULL) {
//        temp.push(node_temp->via);
//        node_temp = node_temp->father;
//    }
//    while (!temp.empty()) {
//        cout<<lan(temp.top())<<"  ";
//        temp.pop();
//    }
//    cout << "变化得来" << endl;
}

//
void node::getSimilarity_same(node *another) {
    for (int i = 0; i < 9; i++) {
        if (this->P[i] == another->P[i])
            Similarity++;
    }
}

void node::getSimilarity_distance(node *another) {
    int j = 0;
    node *node = this;
    while (node->father) {
        Similarity++;
        node = node->father;
    }
    temp_dis = Similarity;
    for (int i = 0; i < 9; i++) {
        if (this->P[i] == 0)
            continue;
        for (j = 0; j < 9; j++) {
            if (this->P[i] == another->P[j]) {
                Similarity += dis[i][j];
            }
        }
    }
}

//可能的移动方式
vector<node *> node::move(node *a) {
    vector<node *> re;
    int temp;

    if (a->z % 3 > 0) {
        //        左
        int *t2 = a->newP();
        temp = t2[a->z];
        t2[a->z] = t2[a->z + d[2]];
        t2[a->z + d[2]] = temp;
        node *r2 = new node(t2, a, 2);
        re.push_back(r2);
    }
    if (a->z % 3 < 2) {
        //        右
        int *t3 = a->newP();
        temp = t3[a->z];
        t3[a->z] = t3[a->z + d[3]];
        t3[a->z + d[3]] = temp;
        node *r3 = new node(t3, a, 3);
        re.push_back(r3);
    }
    if (a->z > 2) {
        //        上
        int *t0 = a->newP();
        temp = t0[a->z];
        t0[a->z] = t0[a->z + d[0]];
        t0[a->z + d[0]] = temp;
        node *r0 = new node(t0, a, 0);
        re.push_back(r0);
    }
    if (a->z < 6) {
        //        下
        int *t1 = a->newP();
        temp = t1[a->z];
        t1[a->z] = t1[a->z + d[1]];
        t1[a->z + d[1]] = temp;
        node *r1 = new node(t1, a, 1);
        re.push_back(r1);
    }
    return re;
}



