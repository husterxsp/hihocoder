连通性三·有向图的强连通分量

参考《算法竞赛入门经典》，有两种解法
1. Kosaraju算法，按照拓扑排序的逆序进行dfs
2. Tarjan

疑问：暂不理解 instack 的作用？

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>

using namespace std;

int N, M, num = 1;

vector<int> dfn(20001), low(20001);
vector<vector<int>> graph(20001);
vector<vector<int>> regraph(20001);
vector<vector<int>> edge;
vector<int> weight(20001);

vector<int> instack(20001);
stack<int> s;
vector<int> belong(20001);

void dfs(int u, int parent) {
    s.push(u);
    instack[u] = 1;

    dfn[u] = low[u] = num++;

    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];

        if (!dfn[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        }
        // else {
        else if (instack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (low[u] == dfn[u]) {
        set<int> bcc;

        while (1) {
            int cur = s.top();
            s.pop();

            instack[cur] = 0;

            bcc.insert(cur);

            if (cur == u) break;
        }
        for (auto it : bcc) {
            belong[it] = *bcc.begin();

            if (it != *bcc.begin()) {
                weight[*bcc.begin()] += weight[it];
            }
        }
    }
}

void createGraph() {
    for (int i = 0; i < M; i++) {
        int u = belong[edge[i][0]];
        int v = belong[edge[i][1]];

        if (u == v) continue;

        regraph[u].push_back(v);
    }
}

int solve(int u) {
    int ret = 0;

    for (int i = 0; i < regraph[u].size(); i++) {
        int v = regraph[u][i];
        ret = max(ret, solve(v));
    }
    return ret + weight[u];
}

int main(){
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        cin >> weight[i];
    }

    int u, v;
    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        edge.push_back({u, v});
        graph[u].push_back(v);
    }

    dfs(1, 0);

    createGraph();

    cout << solve(1) << endl;

    return 0;
}
