最短路径·一

解法一：BellmanFord
因为所有的边都会用来松弛，所以两点之间多条边也不影响。

#include <iostream>
#include <vector>

using namespace std;

class Edge {
public:
    int u, v, weight;
    Edge(int u, int v, int w)
    :u(u), v(v), weight(w) {}
};
int N, M, S, T;
vector<int> dis;
vector<Edge*> edges;

int BellmanFord() {
    for (int i = 1; i <= N - 1; i++) {
        bool flag = 0;
        for (int j = 1; j <= M; j++) {
            int u = edges[j]->u, v = edges[j]->v, weight = edges[j]->weight;

            if (dis[u] > dis[v] + weight) {
                dis[u] = dis[v] + weight;
                flag = 1;
            }
            if (dis[v] > dis[u] + weight) {
                dis[v] = dis[u] + weight;
                flag = 1;
            }
        }
        if (!flag) break;
    }

    return 1;
}

int main () {
    cin >> N >> M >> S >> T;

    edges.assign(M + 1, NULL);
    dis.assign(N + 1, 1e9);
    dis[S] = 0;

    for (int i = 1; i <= M; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        edges[i] = new Edge(u, v, weight);
    }

    BellmanFord();

    cout << dis[T] << endl;
    return 0;
}

解法二：Dijkstra

注意这个题两点之前可能有多条路径，所以在输入的时候处理一下只取最短的。

#include <iostream>
#include <vector>

using namespace std;

int N, M, S, T;
vector<vector<int>> graph;
vector<int> dis;

void Dijkstra() {
    vector<int> s(N + 1);

    for (int i = 1; i <= N; i++) {
        int u = 1, dist = 1e9;
        for (int j = 1; j <= N; j++) {
            if (!s[j] && dis[j] < dist) {
                u = j;
                dist = dis[j];
            }
        }
        s[u] = 1;
        for (int v = 1; v <= N; v++)
            if (!s[v] && graph[u][v] != -1) dis[v] = min(dis[v], dis[u] + graph[u][v]);
    }
}

int main () {
    cin >> N >> M >> S >> T;

    graph.assign(N + 1, vector<int>(N + 1, 1e9));
    dis.assign(N + 1, 1e9);

    dis[S] = 0;

    int u, v, weight;
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> weight;
        // 多条路径
        graph[u][v] = graph[v][u] = min(graph[u][v], weight);
    }

    Dijkstra();

    cout << dis[T] << endl;

    return 0;
}
