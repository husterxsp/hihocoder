连通性二·边的双连通分量。
思路：
1. 先找出所有的割边，然后再dfs，保证第二次dfs的时候不经过割边即可
2. 用栈

注意区分：点的双连通分量

解法1：两次dfs

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int N, M, u, v, num = 1;

struct compare {
    bool operator() (const vector<int>& a, const vector<int>& b) const {
        return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0];
    }
};

vector<int> dfn(20001), low(20001);
vector<vector<int>> graph(20001);
set<vector<int>, compare> edge;
set<int> vertex;

void dfs(int u, int parent) {
    dfn[u] = low[u] = num++;

    int child = 0;
    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];

        if (!dfn[v]) {
            child++;
            dfs(v, u);

            low[u] = min(low[u], low[v]);

            // 根节点
            if (parent == 0 && child > 1) {
                vertex.insert(u);
            }
            // 非根节点
            if (parent != 0 && low[v] >= dfn[u]) {
                vertex.insert(u);
            }

            // 割边
            if(low[v] > dfn[u]) {
                edge.insert({min(u,v), max(u,v)});
            }
        }
        else if (v != parent) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void edgeBiconected(int u, set<int>& bcc) {
    // 标记已访问
    dfn[u] = 1;
    bcc.insert(u);

    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];

        if (edge.find({min(u, v), max(u, v)}) != edge.end()) continue;

        if (!dfn[v]) {
            edgeBiconected(v, bcc);
        }
    }
}

int main(){
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 求割边
    dfs(1,0);

    // 再次dfs, 此时dfn用作标记数组
    fill(dfn.begin(), dfn.end(), 0);

    vector<int> ret(20001);
    int bccCnt = 0;
    for (int i = 1; i <= N; i++) {
        if (!dfn[i]) {
            bccCnt++;

            set<int> bcc;
            edgeBiconected(i, bcc);
            for (auto it : bcc) {
                ret[it] = *bcc.begin();
            }
        }
    }
    cout << bccCnt << endl;
    for (int i = 1; i <= N; i++) {
        cout << ret[i] << " ";
    }
    return 0;
}


解法二：用栈保存

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>

using namespace std;

int N, M, u, v, num = 1;

vector<int> dfn(20001), low(20001);
vector<vector<int>> graph(20001);

stack<int> s;
vector<int> ret(20001);
int bccCnt = 0;

void dfs(int u, int parent) {
    s.push(u);

    dfn[u] = low[u] = num++;

    int child = 0;
    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];

        if (!dfn[v]) {
            child++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if (v != parent) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (low[u] == dfn[u]) {
        set<int> bcc;
        bccCnt++;

        while (1) {
            int cur = s.top();
            s.pop();

            bcc.insert(cur);

            if (cur == u) break;
        }
        for (auto it : bcc) {
            ret[it] = *bcc.begin();
        }
    }
}


int main(){
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, 0);

    cout << bccCnt << endl;
    for (int i = 1; i <= N; i++) {
        cout << ret[i] << " ";
    }
    return 0;
}
