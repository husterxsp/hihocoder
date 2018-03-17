 二分图三·二分图最小点覆盖和最大独立集

参考：http://www.matrix67.com/blog/archives/116
二分图最大匹配的König定理: 一个二分图中的最大匹配数等于这个图中的最小点覆盖数。

最大独立集 = 顶点数 - 最小顶点覆盖数

想到了之前算法课里的NP问题。同一个图的最大独立集和最小顶点覆盖对应的子图互补

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int N, M;
vector<vector<int>> graph;
// vis 表示是否在当前增广路径中
vector<int> vis;
// 匹配的节点
vector<int> match;

int dfs(int u) {
    for (auto v : graph[u]) {
        if (!vis[v]) {
            vis[v] = 1;
            if (!match[v] || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

// 匈牙利算法
int hungarian() {
    int ret = 0;
    // 循环以免非连通
    for (int i = 1; i <= N; i++) {
        vis.assign(N + 1, 0);
        ret += dfs(i);
    }
    // 对于二部图的两个部分，从任意一部分来计算都是一样的。
    return ret / 2;
}

int main() {
    cin >> N >> M;
    graph.assign(N + 1, vector<int>());
    match.assign(N + 1, 0);

    int u, v;
    for (int j = 0; j < M; j++) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int minVertex = hungarian();
    cout << minVertex << endl;
    cout << N - minVertex << endl;
    return 0;
}
