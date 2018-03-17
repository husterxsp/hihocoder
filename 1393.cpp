网络流三·二分图多重匹配

主要代码结构参考网络流一
需要注意的是 pre数组初始化为 -1，前面的两题初始化为0没有问题是因为没有编号0的节点。
本题中编号为0的节点为起始节点。
另外效率不高 AC/3537ms

还有 Dinic算法 和Edmonds–Karp算法 什么的。

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
int N, M, flowDemand = 0;

int bfs(int s, int t) {

    pre.assign(N + M + 2, -1);
    pre[s] = -1;
    flow[s] = 1e9;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == t) break;

        for (int i = 1; i <= N + M + 1; i++) {
            if (pre[i] == -1 && graph[u][i] > 0) {
                pre[i] = u;
                flow[i] = min(flow[u], graph[u][i]);
                q.push(i);
            }
        }
    }

    if (pre[t] == -1) return -1;
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

    if (maxFlow == flowDemand) cout << "Yes" << endl;
    else cout << "No" << endl;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> N >> M;

        graph.assign(N + M + 2, vector<int>(N + M + 2, 0));
        pre.assign(N + M + 2, 0);
        flow.assign(N + M + 2, 0);

        flowDemand = 0;

        for (int j = 1; j <= M; j++) {
            cin >> graph[N + j][N + M + 1];
            flowDemand += graph[N + j][N + M + 1];
        }

        int ai, bi;
        for (int j = 1; j <= N; j++) {
            cin >> ai >> bi;
            graph[0][j] = ai;

            int project;
            for (int k = 1; k <= bi; k++) {
                cin >> project;
                graph[j][N + project] = 1;
            }
        }
        fordFulkerson(0, N + M + 1);
    }

    return 0;
}
