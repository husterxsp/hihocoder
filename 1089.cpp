最短路径·二：Floyd算法

虽然也可以运行N次单源最短路，但是这个Floyd写的代码看起来还是少一点。。

#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> graph;

void Floyd() {
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
}

int main () {
    cin >> N >> M;

    graph.assign(N + 1, vector<int>(N + 1, 1e9));

    int u, v, weight;
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> weight;
        // 多条路径
        graph[u][v] = graph[v][u] = min(graph[u][v], weight);
    }
    for (int i = 0; i <= N; i++) {
        graph[i][i] = 0;
    }

    Floyd();

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
