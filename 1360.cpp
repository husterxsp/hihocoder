// #1360 : 凸多边形
// 动态规划

#include <bits/stdc++.h>
#define ld long double

using namespace std;

int N, M;
/**
 已知三点坐标，求面积
 1. 海伦公式 A = sqrt[s(s-a)(s-b)(s-b)], s = (a + b + c)/2
 2. https://en.wikipedia.org/wiki/Shoelace_formula
 A = abs[( x3(y1-y2) + x1(y2-y3) + x2(y3-y1))/2]
 
 参考：https://hihocoder.com/discuss/question/5158
 把凸多边形的N个顶点按顺序编号0~N-1。
 f[i][j][k]表示起点是i，最后一个点是j的k边形，面积最大是多少。
 转移方程:
 f[i][j][k] = max{f[i][l][k-1] + S(i, l, j) | i < l < j}
 其中S(i, l, j)是三角形ilj的面积。l是我们枚举的第k-1个点。
 复杂度O(N^4)。
 
 需要注意的点：dp数组的初始值如何设定。
 */
ld area(vector<vector<int>> coord, int i, int l, int j) {
    int x0 = coord[i][0], y0 = coord[i][1];
    int x1 = coord[l][0], y1 = coord[l][1];
    int x2 = coord[j][0], y2 = coord[j][1];
    
    ld ret = abs((y0-y1)*x2 + (y1-y2)*x0 + (y2-y0)*x1) / 2.0 ;
    return ret;
}
int main() {
    scanf("%d %d", &N, &M);
    
    vector<vector<int>> coord(N, vector<int>(2));
    vector<vector<vector<ld>>> dp(N, vector<vector<ld>>(N, vector<ld>(M + 1)));
        
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &coord[i][0], &coord[i][1]);
    }
    
    // i < l < j
    for (int i = 0; i < N; i++) {
        for (int j = i + 2; j < N; j++) {
            for (int k = 3; k <= M; k++) {
                for (int l = i + 1; l < j; l++) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i][l][k - 1] + area(coord, i, l, j));
                }
            }
        }
    }
    
    printf("%.2Lf", dp[0][N-1][M]);
    
    return 0;
}
