二分图一•二分图判定
leetcode785 

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int N, M;
vector<vector<int>> graph(10001);
vector<int> color(10001);

bool dfs(int u, int colorV) {
    color[u] = colorV;
    for (auto v : graph[u]) {
        if (color[v] == 0 && !dfs(v, -colorV)) return false;
        else if (color[v] == color[u]) return false;
    }
    return true;
}
bool solve() {
    // 循环以免非连通
    for (int i = 1; i <= N; i++) {
        if (color[i] == 0 && !dfs(i, 1)) return false;
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> N >> M;
        fill(graph.begin(), graph.end(), vector<int>());
        fill(color.begin(), color.end(), 0);

        int u, v;
        for (int j = 0; j < M; j++) {
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        cout << (solve() ? "Correct" : "Wrong") << endl;
    }
    return 0;
}
