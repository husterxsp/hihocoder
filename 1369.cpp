网络流一·Ford-Fulkerson算法

沿着增广路径重复增加路径上的流量，当残存网络不存在增广路径时，即是最大流。

注意题目中的输入 “可能有重复的边”！！！， 所以在输入的时候 用 graph[u][v] += c; 而不是 graph[u][v] = c;

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

int bfs(int s, int t) {
    pre.assign(N + 1, 0);
    pre[s] = -1;
    flow[s] = 1e9;

    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
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
int fordFulkerson(int s, int t) {
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
    return maxFlow;
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
    cout << fordFulkerson(1, N) << endl;
    return 0;
}
