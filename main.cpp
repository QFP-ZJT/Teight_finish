#include <iostream>
#include <fstream>
#include "node.hpp"
#include "tree.hpp"
#include "IDA.h"

using namespace std;

void ini(int *a) {
    for (int i = 0; i < 9; i++)
        a[i] = -1;
}

bool check_cf(int *a) {
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (a[i] != -1 && a[i] == a[j])
                return false;
        }
    }
    return true;
}

int main() {
    int ori[9], object[9];
    int goon;
    cout << "**欢迎使用8数码答案查找工具**" << endl;
    bool temp = false;
    tree *tr = new tree();
    node *a, *b;
    while (1) {
        ini(ori);
        ini(object);
        cout << "请输入您的初始状态(按行输入):" << endl;
        int i = 0;
        while (i < 9) {
            //提示
            cout << "请从";
            for (int j = 0; j < 9; j++) {
                for (int k = 0; k < 9; k++) {
                    if (j == ori[k]) {
                        temp = true;
                        break;
                    }
                }
                if (!temp)
                    cout << j << ",";
                temp = false;
            }
            cout << "中继续填写" << endl;
            //提示
            cin >> ori[i];
            if (ori[i] < 0 || ori[i] > 8) {
                ori[i] = -1;
                cout << "您的输入不在范围内" << endl;
                break;
            }
            if (!check_cf(ori)) {
                cout << "您的输入重复" << endl;
                object[i] = -1;
                break;
            }
            i++;
        }
        cout << "请输入您的目标状态(按行输入):" << endl;
        i = 0;
        while (i < 9) {
            //提示
            cout << "请从";
            for (int j = 0; j < 9; j++) {
                for (int k = 0; k < 9; k++) {
                    if (j == object[k]) {
                        temp = true;
                        break;
                    }
                }
                if (!temp)
                    cout << j << ",";
                temp = false;
            }
            cout << "中继续填写" << endl;
            //提示
            cin >> object[i];
            if (object[i] < 0 || object[i] > 8) {
                object[i] = -1;
                cout << "您的输入不在范围内" << endl;
                break;
            }
            if (!check_cf(object)) {
                cout << "您的输入重复" << endl;
                object[i] = -1;
                break;
            }
            i++;
        }
        a = new node(ori, NULL, 0);
        tr->original = a;
        b = new node(object, NULL, 0);
        tr->object = b;
        cout<<"****************************************************************************************************************"<<endl;
        tr->findpath();
        cout<<"****************************************************************************************************************"<<endl;
        tr->findpathfortwo();
        cout<<"****************************************************************************************************************"<<endl;
        tr->findpath_depth();
        cout<<"****************************************************************************************************************"<<endl;
        tr->findpathbysim_same();
        cout<<"****************************************************************************************************************"<<endl;
        tr->findpathbysim_dis();
        cout<<"****************************************************************************************************************"<<endl;
        IDA *ida = new IDA();
        for(int i =0 ;i<9;i++){
            ida->be.arr[i] = ori[i];
            ida->en.arr[i] = object[i];
        }
        ida->find();
        cout<<"****************************************************************************************************************"<<endl;
        cout<<"继续请输1,退出请输0"<<endl;
        cin>>goon;
        if(!goon)
            break;
    }
    cout<<"下次再见"<<endl;
}
