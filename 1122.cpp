二分图二•二分图最大匹配之匈牙利算法
参考解释：https://www.renfei.org/blog/bipartite-matching.html

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

int solve() {
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

    cout << solve() << endl;
    return 0;
}
