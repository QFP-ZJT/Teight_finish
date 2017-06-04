//
// Created by ZJT on 2017/5/8.
//

#ifndef TEIGHT_IDA_H
#define TEIGHT_IDA_H

class IDA {
public:
    int dis[9][9] = {{0, 1, 2, 1, 2, 3, 2, 3, 4},
                            {1, 0, 1, 2, 1, 2, 3, 2, 3},
                            {2, 1, 0, 3, 2, 1, 4, 3, 2},
                            {1, 2, 3, 0, 1, 2, 1, 2, 3},
                            {2, 1, 2, 1, 0, 1, 2, 1, 2},
                            {3, 2, 1, 2, 1, 0, 3, 2, 1},
                            {2, 3, 4, 1, 2, 3, 0, 1, 2},
                            {3, 2, 3, 2, 1, 2, 1, 0, 1},
                            {4, 3, 2, 3, 2, 1, 2, 1, 0}};
    int dir[4] = {-3, 3, -1, 1};
// 上 下 左 右
//int dirCode[4] = {1, 0, 2, 3};
//int rDirCode[4] = {0, 1, 3, 2};
    int path[1001];
    int MaxF = 0;
    typedef struct node {
        int arr[9];
        int r;//O的位置
    } node;
    node be, en;

    //生成曼哈顿距离
    int h(const node &cur) {
        int h = 0;
        for (int i = 0; i < 9; i++) {
            if (i == cur.r)
                continue;
            for (int j = 0; j < 9; j++)
                if (cur.arr[i] == en.arr[j]) {
                    h += dis[i][j];
                    break;
                }
        }
        return h;
    }

    bool dfs(node &cur, int g, int h, int preDir) {
        //    g当前的深度     h估值
        if (memcmp(&cur, &en, sizeof(node)) == 0) {
            path[g] = -1;
            return true;
        }
        //该状态
        if (g + h > MaxF)
            return false;
        node nxt;
        if (cur.r > 2 && preDir != 1) {
            //        上
            nxt = cur;
            swap(nxt.arr[cur.r], nxt.arr[cur.r + dir[0]]);
            nxt.r += dir[0];
            path[g] = 0;
            int k;
            for (k = 0; k < 9 && en.arr[k] != nxt.arr[cur.r]; k++);
            if (dfs(nxt, g + 1, h - dis[nxt.r][k] + dis[cur.r][k], 0))
                return true;
        }
        if (cur.r < 6 && preDir != 0) {
            nxt = cur;
            swap(nxt.arr[cur.r], nxt.arr[cur.r + dir[1]]);
            nxt.r += dir[1];
            path[g] = 1;
            int k;
            for (k = 0; k < 9 && en.arr[k] != nxt.arr[cur.r]; k++);
            if (dfs(nxt, g + 1, h - dis[nxt.r][k] + dis[cur.r][k], 1))
                return true;
        }
        if (cur.r % 3 > 0 && preDir != 3) {
            nxt = cur;
            swap(nxt.arr[cur.r], nxt.arr[cur.r + dir[2]]);
            nxt.r += dir[2];
            path[g] = 2;
            int k;
            for (k = 0; k < 9 && en.arr[k] != nxt.arr[cur.r]; k++);
            if (dfs(nxt, g + 1, h - dis[nxt.r][k] + dis[cur.r][k], 2))
                return true;
        }
        if (cur.r % 3 < 2 && preDir != 2) {
            nxt = cur;
            swap(nxt.arr[cur.r], nxt.arr[cur.r + dir[3]]);
            nxt.r += dir[3];
            path[g] = 3;
            int k;
            for (k = 0; k < 9 && en.arr[k] != nxt.arr[cur.r]; k++);
            if (dfs(nxt, g + 1, h - dis[nxt.r][k] + dis[cur.r][k], 3))
                return true;
        }
        return false;
    }

    int IDAstar() {
        int nh = h(be);
        MaxF = nh;
        while (!dfs(be, 0, nh, -1)) {
            MaxF++;
        }
        return MaxF;
    }

    bool IsSolvable(const node &cur) {
        int i, j, k = 0, s = 0;
        int a[8];
        for (i = 0; i < 9; i++) {
            if (cur.arr[i] == 0) continue;
            a[k++] = cur.arr[i];
        }
        for (i = 0; i < 8; i++) {
            for (j = i + 1; j < 8; j++) {
                if (a[j] < a[i])
                    s++;
            }
        }
        return (s % 2 == 0);
    }
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

    int find() {
        cout<<"IDA*"<<endl;
        int i;
        for (i = 0; i < 9 && be.arr[i] != 0; i++);
        be.r = i;
        for (i = 0; i < 9 && en.arr[i] != 0; i++);
        en.r = i;
        if (IsSolvable(be) == IsSolvable(en)) {
            IDAstar();
            
//            vector<node*> container;
//            container.push_back(new node(be.arr,NULL,0));
            int i = 0 ;
            for (i = 0; path[i] != -1; i++){
                cout << lan(path[i]) << " ";
//                container.push_back(new node());
            }
            cout << endl;
        } else
            cout << "unsolvable/n";
        return 0;
    }
};


#endif //TEIGHT_IDA_H
