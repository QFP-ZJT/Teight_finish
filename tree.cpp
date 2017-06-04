//
// Created by ZJT on 2017/4/25.
//

#include <iostream>
#include "tree.hpp"

tree::tree(node *ori, node *ob) {
    original = ori;
    object = ob;
    node_tree.push_back(ori);
    re_node_tree.push_back(ob);
}//添加初始化数据

node *tree::onestep(node *a, int whatSim) {
    if (!a) {
        cout << "单步查找，输入为空" << endl;
        return NULL;
    }
    vector<node *> b = move(a);
//    删除的位置
    if (whatSim == onestep_same)
        node_tree_sortbysim_same.pop();
    if (whatSim == onestep_distance)
        node_tree_sortbysim_dis.pop();
    auto temp = int_node_tree.begin();
    for (int i = 0; i < b.size(); i++) {
//        for (int j = 0; j < node_tree.size(); j++) {
//            if (equal(b[i], node_tree[j]))
//                temp = false;
//        }
        temp = int_node_tree.find(b[i]->hash);
        if (temp == int_node_tree.end())//没有重复的向其中添加
        {
            int_node_tree.insert(b[i]->hash);
            //**********************************************************************************
            b[i]->Printf();
            if (whatSim == onestep_same) {
                b[i]->getSimilarity_same(object,a->h);
                node_tree_sortbysim_same.push(b[i]);
            } else if (whatSim == onestep_distance) {
                b[i]->getSimilarity_distance(object,a->h)/*+b[i]->getSimilarity_distance(original)*/;
                node_tree_sortbysim_dis.push(b[i]);
            } else;
            //            TODO 刷新判断是否相等
//
            if (whatSim == onestep_ori)
                node_tree.push_back(b[i]);
            size++;
            level_log(ori, add);
            if (b[i]->hash == object->hash) {
                return b[i];
            }
        }
    }
    return NULL;
}

//单方向查找
void tree::findpath() {
    if (!hasSolution()) {
        cout << "无解" << endl;
        return;
    }
    level_ini();
    //初始化
    cout << "单向广度搜索:" << endl;
    int i = 0;
    if (equal(original, object)) {
        cout << "初始化即目标" << endl;
        return;
    }
    while (1) {
        if (i < node_tree.size()) {
            level_log(ori, del);
            node *re = onestep(node_tree[i], onestep_ori);
            if (re) {
                level_log(0, check);
                cout << "第" << i << "次" << "遍历,找到结果" << endl;
                cout << "共打开了:" << size + re_size << "次";
                path_check(re);
                level_check();
                break;
            }
            i++;
        }
    }
}

bool tree::findpath_d(node *next) {
    cishu++;
    if(cishu > 9000){
        cout<<"爆栈"<<endl;
        return true;}
    if(depth>=40){
        depth--;
        return false;
    }
    depth++;
    vector<node *> re = move(next);
    auto temp = int_node_tree.begin();
    for (int i = 0; i < re.size(); i++) {
        temp = int_node_tree.find(re[i]->hash);
        if (temp == int_node_tree.end())//没有重复的向其中添加
        {
            int_node_tree.insert(re[i]->hash);
            if (re[i]->hash == object->hash) {
                path_check(re[i]);
                depth--;
                return true;
            }
            if(findpath_d(re[i]))return true;
        }
    }
    depth--;
    return false;
}

//LR
vector<node *> tree::onestepfortwoLR(node *a) {
    vector<node *> va = move(a);
    vector<node *> re;
//    va先进行探测
    auto temp = int_node_tree.begin();
    int j;
    for (int i = 0; i < va.size(); i++) {
        //    TODO 检测是否重复
//        for (int j = 0; j < node_tree.size(); j++) {
//            if (equal(va[i], node_tree[j]))
//                temp = false;
//        }
//        TODO 刷新检测方法
        temp = int_node_tree.find(va[i]->hash);
        if (temp == int_node_tree.end())//没有重复的向其中添加
        {
            int_node_tree.insert(va[i]->hash);
//TODO 更改相似度的判断条件
            va[i]->getSimilarity_same(object,a->h);
            node_tree.push_back(va[i]);
            level_log(ori, add);
            size++;
        }
        temp = int_re_node_tree.find(va[i]->hash);
        if (temp != int_re_node_tree.end()) {
//                找到了重合部分  ori => va[i] => re_node_tree[j] => ob
            //TODO 将路径探测出来
            re.push_back(va[i]);
            for (j = 0; j < re_node_tree.size() && re_node_tree[j]->hash != va[i]->hash; j++);
            re.push_back(re_node_tree[j]);
        }
    }
    return re;
}

//RL
vector<node *> tree::onestepfortwoRL(node *b) {
    vector<node *> vb = move(b);
    vector<node *> re;
    auto temp = int_node_tree.begin();//没有一样的
    int j;
    for (int i = 0; i < vb.size(); i++) {
//        TODO 判断是否存在   方法刷新
//        for (int j = 0; j < re_node_tree.size(); j++) {
//            if (equal(vb[i], re_node_tree[j]))
//                temp = false;
//        }
        temp = int_re_node_tree.find(vb[i]->hash);
        if (temp == int_re_node_tree.end())//没有重复的向其中添加
        {
//            TODO 更改相似度的判断条件
            int_re_node_tree.insert(vb[i]->hash);
            vb[i]->getSimilarity_same(object,b->h);
            re_node_tree.push_back(vb[i]);
            level_log(ob, add);
            re_size++;

            temp = int_node_tree.find(vb[i]->hash);
            if (temp != int_node_tree.end()) {
                //                找到了重合部分  ori => va[i] => re_node_tree[j] => ob
                //TODO 将路径探测出来
                for (j = 0; j < node_tree.size() && node_tree[j]->hash != vb[i]->hash; j++);
                re.push_back(node_tree[j]);
                re.push_back(vb[i]);
            }
        }
    }
    return re;
}

void tree::findpathfortwo() {
    if (!hasSolution()) {
        cout << "无解" << endl;
        return;
    }
    level_ini();
    //TODO 一一对应
    object->Similarity = 9;
    //初始化
    cout << "双向广度搜索:" << endl;
    int i = 0, j = 0;
    if (original->hash == object->hash) {
        cout << "初始化即目标" << endl;
        return;
    }
    while (1) {
        if (i < node_tree.size()) {
            level_log(ori, del);
            vector<node *> re = onestepfortwoLR(node_tree[i]);
            if (!re.empty()) {
                level_log(0, check);
                cout << endl << "第" << i + j << "次" << "遍历,找到结果" << endl;
                cout << "共打开了:" << size + re_size << "次" << endl;
                path_checkfortwo(re);
                level_check();
                break;
            }
            i++;
        } else;
        if (j < re_node_tree.size()) {
            level_log(ob, del);
            vector<node *> re = onestepfortwoRL(re_node_tree[j]);
            if (!re.empty()) {
                level_log(0, check);
                cout << endl << "第" << i + j << "次" << "遍历,找到结果" << endl;
                cout << "共打开了:" << size + re_size << "次" << endl;
                path_checkfortwo(re);
                level_check();
                break;
            }
            j++;
        }

    }

}

//
void tree::findpathbysim_same() {
    if (!hasSolution()) {
        cout << "无解" << endl;
        return;
    }
    cout << "一对一相似度比较法:" << endl;
    level_ini();
//    TODO *node 的含义
    original->getSimilarity_same(object,0);
    node_tree_sortbysim_same.push(original);
    while (!node_tree_sortbysim_same.empty()) {
        node *re = onestep(node_tree_sortbysim_same.top(), onestep_same);
        if (re) {
            level_log(0, check);
            cout << "共打开了:" << size + re_size << "次";
            path_check(re);
            level_check();
            break;
        }
    }
}

void tree::findpathbysim_dis() {
    if (!hasSolution()) {
        cout << "无解" << endl;
        return;
    }
    cout << "距离相似度比较法:" << endl;
    level_ini();
//    TODO *node 的含义
    original->getSimilarity_distance(object,0);
    node_tree_sortbysim_dis.push(original);
    while (!node_tree_sortbysim_dis.empty()) {
        node *re = onestep(node_tree_sortbysim_dis.top(), onestep_distance);
        if (re) {
            level_log(0, check);
            cout << "共打开了:" << size << "次";
            path_check(re);
            level_check();
            break;
        }
    }
}

bool tree::hasSolution() {
    int x = 0, y = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < i; j++) {
            if (original->P[j] < original->P[i])
                x++;
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < i; j++) {
            if (object->P[j] < object->P[i])
                y++;
        }
    }
    if (x % 2 == y % 2)
        return true;
    return false;
}
