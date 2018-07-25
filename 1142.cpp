三分·三分求极值

思路：本题求最短距离，可以想到该点到该曲线上的点的距离是由远到近再到远。中间有个最短距离。
所以跟那个曲线应该没啥关系？不对。好像也不能说没关系。。。
这个点如果在曲线内部？感觉题解有点模糊。
还有：
1. 起始的时候 左右端点应该是多少？
2. 迭代次数。网上的解答均是 right-left >= 0.001？应该是前后两次dis的差值小于 0.001？

AC

#include <bits/stdc++.h>

using namespace std;

int a, b, c, x, y;
double dis(double p) {
    return sqrt(pow(p - x, 2) + pow(a * p * p + b * p + c - y, 2));
}
int main() {
    cin >> a >> b >> c >> x >> y;

    double left = -200, right = 200;
    while (right - left >= 0.001) {
        double p1 = left + (right - left) / 3;
        double p2 = left + 2 * (right - left) / 3;

        if (dis(p1) > dis(p2)) left = p1;
        else right = p2;
    }

    printf("%.3f", dis(left));
    return 0;
}

或者换成迭代次数

#include <bits/stdc++.h>

using namespace std;

int a, b, c, x, y;
double dis(double p) {
    return sqrt(pow(p - x, 2) + pow(a * p * p + b * p + c - y, 2));
}
int main() {
    cin >> a >> b >> c >> x >> y;

    double left = -200, right = 200;
    for (int i = 0; i < 200; i++) {
        double p1 = left + (right - left) / 3;
        double p2 = left + 2 * (right - left) / 3;

        if (dis(p1) > dis(p2)) left = p1;
        else right = p2;
    }

    printf("%.3f", dis(left));
    return 0;
}

但是以下这种写法因为迭代次数不够 WA了 。  ？？？可能是四舍五入导致的？
#include <bits/stdc++.h>

using namespace std;

int a, b, c, x, y;
double dis(double p) {
    return sqrt(pow(p - x, 2) + pow(a * p * p + b * p + c - y, 2));
}
int main() {
    cin >> a >> b >> c >> x >> y;

    double left = -200, right = 200, p1, p2;
    while (true) {
        p1 = left + (right - left) / 3;
        p2 = left + 2 * (right - left) / 3;

        double mistake = dis(p1) - dis(p2);
        if (mistake > 0) left = p1;
        else right = p2;

        if (abs(mistake) < 0.001) break;
    }

    printf("%.3f", dis(p1));
    return 0;
}
