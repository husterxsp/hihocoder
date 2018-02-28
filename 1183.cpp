连通性一·割边与割点, tarjan 算法

dfn[u] 为深度优先搜索序数
low[u] 为u及其后代所能连回的最早的祖先的dfn值

参考《算法竞赛入门经典》

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int N, M, u, v, num = 1;

struct compare {
    bool operator() (const vector<int>& a, const vector<int>& b) const {
        return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0];
    }
};

vector<int> dfn(20001), low(20001);
vector<vector<int>> graph(20001);
set<vector<int>, compare> edge;
set<int> vertex;

void dfs(int u, int parent) {
    dfn[u] = low[u] = num++;

    int child = 0;
    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];

        if (!dfn[v]) {
            child++;
            dfs(v, u);

            low[u] = min(low[u], low[v]);

            // 根节点
            if (parent == 0 && child > 1) {
                vertex.insert(u);
            }
            // 非根节点
            if (parent != 0 && low[v] >= dfn[u]) {
                vertex.insert(u);
            }

            // 割边
            if(low[v] > dfn[u]) {
                // 注意这里的min, max
                // 因为并不知道 u,v的大小比较，能得到的其实是 dfn(u),dfn(v)的大小比较，dfn(v)>dfn(u)
                // 还有就是 割点可能重复，割边不会重复吗？。用vector也能AC？
                // 恩，对于u，可能它的多个子节点都能得到u是割点，所以有重复，而对于割边，对于u的多个子节点，得到的边也是各不相同
                edge.insert({min(u,v), max(u,v)});
            }

        }
        else if (v != parent) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main(){
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1,0);

    if (vertex.empty()) cout << "Null" << endl;
    else {
        for (auto it : vertex) {
            cout << it << " ";
        }
        cout << endl;
    }

    for (auto it : edge) {
        cout << it[0] << " " << it[1] << endl;
    }

    return 0;
}
