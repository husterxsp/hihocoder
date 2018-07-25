/**
 线段树模板，求解...WA。。。
 */
#include <bits/stdc++.h>

using namespace std;
int n, q;
vector<int> w;

struct SegmentTree {
    SegmentTree *left = NULL, *right = NULL;
    int minimum;
    vector<int> interval;
    SegmentTree(vector<int> interval)
    :interval(interval) {}
};

SegmentTree* root;
SegmentTree* initTree(int l, int r) {
    SegmentTree* root = new SegmentTree({l, r});
    if (l > r) return NULL;
    else if (l == r) {
        root->minimum = w[l];
    }
    else {
        int mid = l + (r - l) / 2;
        root->left = initTree(l, mid);
        root->right = initTree(mid + 1, r);
        root->minimum = min(root->left->minimum, root->right->minimum);
    }
    return root;
}

int query(SegmentTree* root, int l, int r) {
    if (l == r) return w[l];
    if (root->interval[0] == l && root->interval[1] == r)  return root->minimum;

    int mid = root->interval[0] + (root->interval[1] - root->interval[0]) / 2;

    if (l > mid) return query(root->right, l, r);
    else if (r <= mid) return query(root->left, l, r);

    return min(query(root->left, l, mid), query(root->right, mid + 1, r));
}

void update(SegmentTree* root, int pos, int val) {
    if (root->interval[0] == pos && root->interval[1] == pos) {
        root->minimum = val;
        w[pos] = val;
        return;
    }
    root->minimum = min(root->minimum, val);

    int mid = root->interval[0] + (root->interval[1] - root->interval[0]) / 2;
    if (pos > mid) update(root->right, pos, val);
    else {
        update(root->left, pos, val);
    }
}
int main() {
//    srand(time(NULL));
//    for (int i = 0;i < 100; i++) cout << rand() % 100 << " ";
//    cout << endl;
//    for (int i = 0;i < 10; i++) cout << rand() % 2 << " " << rand() % 50 << " "<< rand() % 50 + 49 << endl;
//
    scanf("%d\n", &n);
    w.assign(n, 0);

    root = new SegmentTree({0, n - 1});
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }

    root = initTree(0, n - 1);

    scanf("%d\n", &q);

    int a, b, c;
    for (int i = 0; i < q; i++) {
        scanf("%d %d %d\n", &a, &b, &c);
        if (a == 0) printf("%d\n", query(root, b - 1, c - 1));
        else update(root, b - 1, c);
    }
    return 0;
}
