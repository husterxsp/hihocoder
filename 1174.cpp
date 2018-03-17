拓扑排序一

思路：queue。每次入队 入度为0的节点

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int N, M;
vector<vector<int>> graph(100001);
vector<int> indegree(100001);

bool solve() {
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto v : graph[u]) {
            indegree[v]--;
            if (indegree[v] == 0) q.push(v);
        }
    }

    for (int i = 1; i <= N; i++) {
        if (indegree[i] != 0) return false;
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> N >> M;
        fill(graph.begin(), graph.end(), vector<int>());
        fill(indegree.begin(), indegree.end(), 0);

        int u, v;
        for (int j = 0; j < M; j++) {
            cin >> u >> v;
            graph[u].push_back(v);
            indegree[v]++;
        }

        cout << (solve() ? "Correct" : "Wrong") << endl;
    }
    return 0;
}
