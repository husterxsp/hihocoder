拓扑排序二
需要注意的是 及时取MOD，否则肯能溢出无法AC

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <numeric>

using namespace std;

int N, M, K;
vector<vector<int>> graph(100001);
vector<int> virus(100001);
vector<int> indegree(100001);

int solve() {
    int ret = 0;
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        ret += virus[u];
        ret %= 142857;

        for (auto v : graph[u]) {
            indegree[v]--;
            virus[v] += virus[u];
            virus[v] %= 142857;
            if (indegree[v] == 0) q.push(v);
        }
    }
    return ret;
}

int main() {
    cin >> N >> M >> K;

    int pos;
    for (int i = 1; i <= K; i++) {
        cin >> pos;
        virus[pos]++;
    }

    int u, v;
    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        indegree[v]++;
    }

    cout << solve() << endl;

    return 0;
}
