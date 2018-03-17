网络流二·最大流最小割定理

最小割限制了一个网络的流f上界
对于任一个网络流图来说，其最大流一定是小于等于最小割的

最大流最小割定理
对于一个网络流图G=(V,E)，其中有源点s和汇点t，那么下面三个条件是等价的：
1. 流f是图G的最大流
2. 残留网络Gf不存在增广路
3. 对于G的某一个割(S,T)，此时f = C(S,T)

//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <queue>
#include <unordered_map>

using namespace std;

vector<vector<int>> graph;
// pre 用来记录增广路径，flow 用来记录增广路径上的最小流量。
vector<int> pre, flow;
int N, M;

set<int> minCut;
int bfs(int s, int t) {
    // minCut 用来保存最后一次dfs 遍历过的节点，即 S 集合
    minCut.clear();

    pre.assign(N + 1, 0);
    pre[s] = -1;
    flow[s] = 1e9;

    queue<int> q;
    q.push(s);
    minCut.insert(s);

    while (!q.empty()) {
        int u = q.front();
        minCut.insert(u);
        q.pop();

        if (u == t) break;

        for (int i = 1; i <= N; i++) {
            if (pre[i] == 0 && graph[u][i] > 0) {
                pre[i] = u;
                flow[i] = min(flow[u], graph[u][i]);
                q.push(i);
            }
        }
    }

    if (pre[t] == 0) return -1;
    return flow[t];
}
void fordFulkerson(int s, int t) {
    int maxFlow = 0;
    while (1) {
        int add = bfs(s, t);
        if (add == -1) break;

        int u = pre[t], v = t;
        while (u != -1) {
            graph[u][v] -= add;
            graph[v][u] += add;

            v = u;
            u = pre[v];
        }
        maxFlow += add;
    }
    cout << maxFlow << " " << minCut.size() << endl;
    for (int v : minCut) {
        cout << v << " ";
    }
}

int main() {
    cin >> N >> M;
    graph.assign(N + 1, vector<int>(N + 1, 0));
    pre.assign(N + 1, 0);
    flow.assign(N + 1, 0);

    int u, v, c;
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> c;
        graph[u][v] += c;
    }
    fordFulkerson(1, N);

    return 0;
}
