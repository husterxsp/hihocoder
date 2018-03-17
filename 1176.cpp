欧拉路·一

给定无孤立结点图G，若存在一条路，经过图中每边一次且仅一次，该条路称为欧拉路
欧拉路判定条件：一个无向图存在欧拉路当且仅当该图是连通的且有且只有2个点的度数是奇数，此时这两个点只能作为欧拉路径的起点和终点。
若图中没有奇数度的点，那么起点和终点一定是同一个点，这样的欧拉路叫做欧拉回路

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <numeric>

using namespace std;

int N, M;
vector<vector<int>> graph(10001);
vector<int> vis(10001);
vector<int> degree(10001);

bool solve() {
    queue<int> q;
    q.push(1);
    vis[1] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i];
            if (!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        if (!vis[i]) return false;
    }

    int oddNum = 0;
    for (int i = 1; i <= N; i++) {
        if (degree[i] % 2 == 1) oddNum++;
    }
    // 都可以。。 没有 奇数个奇数度，因为所有的度的和为边的二倍，为偶数。 也就是说 oddNum == 1 不存在
    if (oddNum > 2) return false;
//    if (oddNum != 0 && oddNum != 2) return false;
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
    }

    cout << (solve() ? "Full" : "Part") << endl;

    return 0;
}
