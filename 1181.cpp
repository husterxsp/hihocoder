欧拉路·二 求欧拉路径

...为啥A不过！！！

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <numeric>

using namespace std;

int N, M;
vector<vector<int>> graph(10001);
set<vector<int>> edge;

vector<int> vis(10001);
vector<int> degree(10001);
vector<int> path;

void dfs(int u) {
    for (int i = 0; i < graph.size(); i++) {
        int v = graph[u][i];
        vector<int> e = {min(u,v), max(u,v)};
        if (edge.find(e) != edge.end()) {
            edge.erase(e);
            dfs(v);
        }
    }
    path.push_back(u);
}
bool solve() {
    // 查找奇数度的节点作为dfs起点
    int start = 1;
    for (int i = 1; i <= N; i++) {
        if (degree[i] % 2 == 1) {
            start = i;
            break;
        }
    }
    dfs(start);

    return true;
}

int main() {
    cin >> N >> M;

    int u, v;
    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        degree[u]++;
        degree[v]++;

        edge.insert({min(u,v), max(u,v)});
    }

    solve();
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }

    return 0;
}
