欧拉路·三

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <numeric>
#include <cmath>

using namespace std;

int maxn = (1<<14) + 10;

vector<vector<int>> graph(maxn);
vector<int> path;

void dfs(int u) {
    for (int i = 0; i < 2; i++) {
        int v = graph[u][i];
        if (v >= 0) {
            graph[u][i] = -1;
//            path.push_back((u << 1)+(v & 1));
            dfs(v);
        }

    }
    path.push_back(u);
}

int main() {
    int n;
    cin >> n;

    int N = 1 << (n-1);
    for (int i = 0; i < N; i++) {
        int j = i << 1;

        j &= (N - 1);
        graph[i].push_back(j);
        graph[i].push_back(j + 1);
    }

    dfs(0);
    for (int i = path.size() - 1; i > 0; i--) {
        cout << (path[i] & 1);
    }

    return 0;
}
