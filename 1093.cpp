最短路径·三：SPFA算法

稀疏图，所以可以用最短路的bellman-ford
SPFA是bellman-ford的优化版

一开始用邻接矩阵MLE, 改用邻接表

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Edge {
public:
    int u, v, weight;
    Edge(int u, int v, int w)
    :u(u), v(v), weight(w) {}
};
int N, M, S, T;
vector<int> dis;
vector<vector<Edge>> graph;

queue<int> que;
vector<int> inQue;

void SPFA() {
    que.push(S);
    inQue.assign(N + 1, 0);
    inQue[S] = 1;

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        inQue[u] = 0;

        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i].v, weight = graph[u][i].weight;

            if (dis[v] > dis[u] + weight) {
                dis[v] = dis[u] + weight;
                if (!inQue[v]) que.push(v);
            }
        }
    }
}

int main () {
    cin >> N >> M >> S >> T;

    graph.assign(N + 1, vector<Edge>());
    dis.assign(N + 1, 1e9);
    dis[S] = 0;

    for (int i = 1; i <= M; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;

        graph[u].push_back(Edge(u, v, weight));
        graph[v].push_back(Edge(v, u, weight));

    }

    SPFA();

    cout << dis[T] << endl;
    return 0;
}
