最小生成树二·Kruscal算法

从题意也可以看出，Kruscal 从边的角度考虑，适合稀疏图（城市数目更加，prim无法使用）

WA？？？？？

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

int kruscal() {
    set<int> vis;
    int ret = 0;

    while (vis.size() < N) {
        Edge e = que.top();
        que.pop();

        if (vis.find(e.u) != vis.end() && vis.find(e.v) != vis.end()) continue;
        vis.insert(e.u);
        vis.insert(e.v);

        ret += e.w;
    }

    return ret;
}
int main () {
    cin >> N >> M;

    int u, v, w;
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> w;
        que.push(Edge(u, v, w));
    }

    cout << kruscal() << endl;
    return 0;
}
