网络流四·最小路径覆盖
求最大匹配，最小路径覆盖 = N - 最大匹配


解法1: 直接匈牙利算法求二分匹配
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
    for (int i = 1; i <= 2 * N; i++) {
        vis.assign(2 * N + 1, 0);
        ret += dfs(i);
    }
    // 对于二部图的两个部分，从任意一部分来计算都是一样的。
    return N - ret / 2;
}

int main() {
    cin >> N >> M;
    graph.assign(2 * N + 1, vector<int>());
    match.assign(2 * N + 1, 0);

    int u, v;
    for (int j = 0; j < M; j++) {
        cin >> u >> v;
        graph[u].push_back(v + N);
        graph[v + N].push_back(u);
    }

    cout << solve() << endl;
    return 0;
}

解法二：网络流，Edmonds-Karp算法
TLE...

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

    pre.assign(2 * N + 2, -1);
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
    cout << N - maxFlow << endl;
}

int main() {
    cin >> N >> M;

    graph.assign(2 * N + 2, vector<int>(2 * N + 2, 0));
    pre.assign(2 * N + 2, 0);
    flow.assign(2 * N + 2, 0);

    int u, v;
    for (int j = 1; j <= M; j++) {
        cin >> u >> v;
        graph[u][v + N] = 1;

        graph[0][u] = graph[v + N][2 * N + 1] = 1;
    }
    fordFulkerson(0, 2 * N + 1);

    return 0;
}

解法三，网络流 Dinic算法。参考：https://comzyh.com/blog/archives/568/

Dinic算法的基本思路:
根据残量网络计算层次图。
在层次图中使用DFS进行增广直到不存在增广路
重复以上步骤直到无法增广

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

vector<int> level;
int N, M, maxN;

int bfs(int s) {
    level.assign(maxN, -1);

    queue<int> q;

    q.push(0);
    level[0] = 0;

    while (!q.empty()) {
        int size = q.size();
        for (int l = 0; l < size; l++) {
            int u = q.front();
            q.pop();
            for (int i = 1; i <= N + M + 1; i++) {
                if (level[i] == -1 && graph[u][i] > 0) {
                    level[i] = level[u] + 1;
                    q.push(i);
                }
            }
        }
    }

    if (level[maxN - 1] >= 0) return 1;
    // 汇点的level小于0，表示bfs无法到达
    return 0;
}

int dfs(int u, int flow) {
    int add;
    if (u == maxN - 1) return flow;
    for (int i = 0; i <= maxN - 1; i++) {
        if (graph[u][i] > 0 &&
            level[i] == level[u] + 1 &&
            (add = dfs(i, min(flow, graph[u][i]))) ) {
            graph[u][i] -= add;
            graph[i][u] += add;
            return add;
        }
    }
    return 0;
}

void dinic(int s, int t) {
    int maxFlow = 0, add;
    while (bfs(s)) {
        while (add = dfs(s, 1e10)) {
            maxFlow += add;
        }
    }

    cout << N - maxFlow << endl;
}

int main() {
    cin >> N >> M;

    maxN = 2 * N + 2;
    graph.assign(maxN, vector<int>(maxN, 0));
    pre.assign(maxN, 0);
    flow.assign(maxN, 0);

    int u, v;
    for (int j = 1; j <= M; j++) {
        cin >> u >> v;
        graph[u][v + N] = 1;

        graph[0][u] = graph[v + N][maxN - 1] = 1;
    }
    dinic(0, maxN - 1);

    return 0;
}
