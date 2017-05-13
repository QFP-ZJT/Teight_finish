//
// Created by ZJT on 2017/4/25.
//

#ifndef TEIGHT_TREE_H
#define TEIGHT_TREE_H


#include "node.hpp"
#include <queue>
#include <set>
#include <string>
#include <sstream>


class tree : public node {
public:
    tree() {};

    tree(node *ori, node *ob);

    node *onestep(node *a, int whatSim);

    void findpath();

    bool findpath_d(node *a);

    void findpath_depth() {
        cout<<"深度优先搜索"<<endl;
        level_ini();
        findpath_d(original);
    }

    vector<node *> onestepfortwoLR(node *a);

    vector<node *> onestepfortwoRL(node *b);

    void findpathfortwo();

    void plpf(vector<node *> pl) {
        stringstream a1, a2, a3, a4, a5;
        string aa1, aa2, aa3, aa4, aa5;
        for (int i = 0; i < pl.size(); i++) {
            a1 << "*******  ";
            a5 << "*******  ";
            a2 << "*" << pl[i]->P[0] << " " << pl[i]->P[1] << " " << pl[i]->P[2] << "*  ";
            a3 << "*" << pl[i]->P[3] << " " << pl[i]->P[4] << " " << pl[i]->P[5] << "*  ";
            a4 << "*" << pl[i]->P[6] << " " << pl[i]->P[7] << " " << pl[i]->P[8] << "*  ";
//           释放
            if(i%10==9){
                aa1 = a1.str();
                aa2 = a2.str();
                aa3 = a3.str();
                aa4 = a4.str();
                aa5 = a5.str();
                cout << aa1 << endl << aa2 << endl << aa3 << endl << aa4 << endl << aa5 << endl;
                a1.str("");a2.str("");a3.str("");a4.str("");a5.str("");
            }
        }
        aa1 = a1.str();
        aa2 = a2.str();
        aa3 = a3.str();
        aa4 = a4.str();
        aa5 = a5.str();
        if(aa1!="")
        cout << aa1 << endl << aa2 << endl << aa3 << endl << aa4 << endl << aa5 << endl;
};

//    vector<node *> onestep(node *b);
    //根据一一对应的相似度，优先选择相似度高的
    void findpathbysim_same();

    //根据距离差的相似度，优先选择相似度高的
    void findpathbysim_dis();

    bool hasSolution();

//protected:
    //层次跟踪记录
    void level_log(int who, int how) {
        if (how == check) {
            if (ori_next) {
                ori_leavel.push_back(ori_next);
            }
            if (ob_next) {
                ob_leavel.push_back(ob_next);
            }
        }

        if (who == ori) {
            if (how == del) {
//            衰减
                if (!ori_current) {
                    ori_leavel.push_back(ori_next);
                    ori_current = ori_next;
                    ori_next = 0;

                }
                ori_current--;
            } else {
                ori_next++;
            }
        } else {
            if (how == del) {
                //            衰减
                if (!ob_current) {
                    ob_leavel.push_back(ob_next);
                    ob_current = ob_next;
                    ob_next = 0;

                }
                ob_current--;
            } else {
                ob_next++;
            }
        }
    }

    void level_check() {
        cout << "正方向：" << endl << "层:";
        for (int i = 1; i <= ori_leavel.size(); i++)
            cout << i << "\t";
        cout << endl << "量:";
        for (int i : ori_leavel)
            cout << i << "\t";
        if (!ob_leavel.empty()) {
            cout << endl << "反方向：" << endl << "层:";
            for (int i = 1; i <= ob_leavel.size(); i++)
                cout << i << "\t";
            cout << endl << "量:";
        }
        for (int i : ob_leavel)
            cout << i << "\t";
        cout << endl;
    };

    void level_ini() {
        size = 0;
        re_size = 0;
        ori_current = 1;
        ori_next = 0;
        ob_current = 1;
        ob_next = 0;
        cishu = 0;
        ori_leavel.clear();
        ob_leavel.clear();
        depth = 0;
        re_node_tree.clear();
        node_tree.push_back(original);
        re_node_tree.push_back(object);
        int_node_tree.clear();
        int_re_node_tree.clear();
        int_node_tree.insert(original->hash);
        int_re_node_tree.insert(object->hash);
        while (!node_tree_sortbysim_same.empty())
            node_tree_sortbysim_same.pop();
        while (!node_tree_sortbysim_dis.empty())
            node_tree_sortbysim_dis.pop();
    }

    void path_checkfortwo(vector<node *> re) {
        vector<node *> path = re[0]->getPath();
        vector<node *> path1 = re[1]->getRePath();
        path.insert(path.end(), path1.begin(), path1.end());//数组合并
        cout<<"变化轨迹"<<endl;
        plpf(path);
//        cout << "原数组" << endl;
//        original->Printf();
//        cout << "目标数组" << endl;
//        object->Printf();
//        cout << "经";
//        for (node *p : path) {
//            cout << lan(p->via) << "(" << p->Similarity << ")  ";
////            p->Printf();
//        }
//        cout << "变化得到(" << path.size() << ")" << endl;
    };

    void path_check(node *re) {
        cout << endl;
        vector<node *> path = re->getPath();
//        cout << "原数组" << endl;
//        original->Printf();
//        cout << "目标数组" << endl;
//        object->Printf();
        plpf(path);
    };
    vector<node *> node_tree;
    vector<node *> re_node_tree;
    set<int> int_node_tree;
    set<int> int_re_node_tree;
//    标志符
    static const int ori = 1;
    static const int ob = 2;
    static const int add = 1;
    static const int del = -1;
    static const int check = 2;
    static const int onestep_ori = 0;
    static const int onestep_same = 1;
    static const int onestep_distance = 2;
//    *****
    node *original;
    node *object;
//    层次记录
    int ori_current = 1, ob_current = 1;
    int ori_next = 0, ob_next = 0;
    vector<int> ori_leavel;
    vector<int> ob_leavel;
//    *******
    int size = 0;
    int re_size = 0;
    int depth = 0;
    int cishu = 0;
//    re_size 的合理性等待确认
//    记录层数与每一层的数量
//记录大根堆
    priority_queue<node *, vector<node *>, node::cmp_des> node_tree_sortbysim_same;
    priority_queue<node *, vector<node *>, node::cmp_inc> node_tree_sortbysim_dis;
};


#endif //TEIGHT_TREE_H
