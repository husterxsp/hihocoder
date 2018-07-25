最小生成树三·堆优化的Prim算法

#include <bits/stdc++.h>

using namespace std;
int N, M;

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) :u(u), v(v), w(w) {}
};

auto cmp = [](Edge const & a, Edge const & b) {
    return a.w > b.w;
};
priority_queue<Edge, vector<Edge>, decltype(cmp)> que(cmp);

vector<vector<Edge>> graph;

int prim() {
    vector<int> vis(N + 1, 0);
    int ret = 0, cnt = 0;

    que.push(Edge(1, 1, 0));
    while (cnt < N) {
        Edge e = que.top();
        que.pop();

        if (vis[e.v]) continue;

        vis[e.v] = 1;
        cnt++;

        ret += e.w;
        for (int i = 0; i < graph[e.v].size(); i++) {
            Edge tmp = graph[e.v][i];
            que.push(Edge(1, tmp.v, tmp.w));
        }
    }
    return ret;
}
int main () {
    cin >> N >> M;

    graph.assign(N + 1, vector<Edge>());

    int u, v, w;
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> w;
        graph[u].push_back(Edge(u, v, w));
        graph[v].push_back(Edge(v, u, w));
    }

    cout << prim() << endl;
    return 0;
}
