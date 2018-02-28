连通性四·点的双连通分量

这题和边的双连通分量类似，也有两种解法，即也可以先求出所有割点，然后从非割点dfs，不经过割点

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>

using namespace std;

int N, M, num = 1;

vector<int> dfn(20001), low(20001);
vector<vector<int>> graph(20001);

stack<vector<int>> s;

map<vector<int>, int> m;

int bccCnt = 0;

void dfs(int u, int parent) {

    dfn[u] = low[u] = num++;

    int child = 0;
    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];

        if (!dfn[v]) {
            s.push({min(u, v), max(u, v)});

            child++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            // 根节点 & 非根节点, 割点，点连通分量是割点数量加1
            // emmm，这里好像不用区分考虑根节点和非根节点
            if (low[v] >= dfn[u]) {

                bccCnt++;

                set<vector<int>> bcc;
                while (1) {
                    vector<int> tmp = s.top();
                    s.pop();
                    bcc.insert(tmp);

                    if (tmp[0] == min(u,v) && tmp[1] == max(u, v)) {
                        break;
                    }
                }

                // 标记
                int flag = 100005;
                for (auto v : bcc) {
                    flag = min(flag, m[v]);
                }
                for (auto v : bcc) {
                    m[v] = flag;
                }

            }
        }
        // dfn[v] < dfn[u] 是必要的，避免重复访问，删掉的话，栈里会加入重复的边
        else if (v != parent && dfn[v] < dfn[u]) {
            s.push({min(u, v), max(u, v)});
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    cin >> N >> M;

    int u, v;

    vector<vector<int>> vec;
    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);

        m[{u, v}] = i + 1;
        vec.push_back({u, v});
    }

    dfs(1, 0);

    cout << bccCnt << endl;
    for (auto it : vec) {
        cout << m[it] << " ";
    }
    return 0;
}
