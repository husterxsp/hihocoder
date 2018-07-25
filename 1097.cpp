最小生成树一·Prim算法

#include <bits/stdc++.h>

#define FOR(i,s,e) for (int i=s;i<e;i++)
#define FOE(i,s,e) for (int i=s;i<=e;i++)
#define FOD(i,s,e) for (int i=s;i>=e;i--)
#define SET(a,e) memset(a,e,sizeof(a))
#define LL long long
#define LD long double
#define pb push_back
#define x first
#define y second
#define PII pair<int,int>
#define PLI pair<LL,int>
#define PIL pair<int,LL>
#define PLL pair<LL,LL>
#define PDD pair<LD,LD>
#define eps 1e-9
#define HH1 402653189
#define HH2 1610612741

using namespace std;
int N;
vector<vector<int>> graph;

/*
 算法执行过程将已找到的点都合并到节点1
 dis数组表示其他点到节点1的最短距离
 */
int prim() {
    vector<int> dis(N + 1, 1e9), vis(N + 1, 0);
    int ret = 0;

    // 初始时假设1节点也没访问
    dis[1] = 0;

    // 外层循环，合并N次
    for (int i = 1; i <= N; i++) {

        int v = -1;
        for (int j = 1; j <= N; j++) {
            if (vis[j]) continue;
            if (v == -1 || dis[j] < dis[v]) v = j;
        }

        //没合并 n 条边就已经要结束了，说明图不联通
        if (v == -1) return -1;

        vis[v] = 1;
        ret += dis[v];

        // 合并v节点的过程
        for (int j = 1; j <= N; j++) {
            dis[j] = min(dis[j], graph[v][j]);
        }
    }
    return ret;
}
int main () {
    cin >> N;

    graph.assign(N + 1, vector<int>(N + 1));

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> graph[i][j];
        }
    }

    cout << prim() << endl;
    return 0;
}
