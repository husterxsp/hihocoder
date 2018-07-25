/**
 注意延伸。
 区间选择问题。如区间最值，都可以考虑二分

 另外。输入部分用C++的cin. cout 会超时。。。改成C输入AC
 
https://www.byvoid.com/zhs/blog/fast-readfile
 */
#include <bits/stdc++.h>

using namespace std;

int n, q;
vector<int> w;

vector<vector<int>> vec;
void initRMQ() {
    vec.assign(n, vector<int>(20));
    for (int i = 0; i < n; i++) vec[i][0] = w[i];

    for (int j = 1; (1<<j) <= n; j++) {
        for(int i=0; i + (1<<(j-1)) < n;i++) {
            vec[i][j] = min(vec[i][j - 1], vec[i + (1<<(j-1))][j - 1]);
        }
    }
}

int query(int l, int r) {
    int k = 0;
    while ((1<<(k+1)) < r - l + 1) k++;
    return  min(vec[l][k], vec[r - (1<<k) + 1][k]);
}

int main() {
//    std::ios::sync_with_stdio(false);
    cin >> n;
    w.assign(n, 0);

    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    initRMQ();
    cin >> q;

    int L, R;

    for (int i = 0; i < q; i++) {
        // 超时
//        cin >> L >> R;
//        cout << query(L - 1, R - 1) << endl;
        scanf("%d%d", &L, &R);
        printf("%d\n", query(L - 1, R - 1));
    }

    return 0;
}
