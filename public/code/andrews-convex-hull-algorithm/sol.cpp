#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#define x() first
#define y() second
 
using namespace std;
 
typedef pair<int, int> point;
 
const double PI = acos(-1);
 
vector<point> P;
vector<point> H;
 
double cross(const point &o, const point &a, const point &b)
{
    double a1 = a.x() - o.x();
    double b1 = a.y() - o.y();
    double a2 = b.x() - o.x();
    double b2 = b.y() - o.y();

    return a1 *  b2 - a2 * b1;
}

double dist(const point &a, const point &b)
{
    double dx = b.x() - a.x();
    double dy = b.y() - a.y();

    return sqrt(dx * dx + dy * dy);
}

int main(int argc, char **argv)
{
    int t, tc, n, i, k, pos, next, prev, x, y, sign;
    char ch;
    double ans, a, b, c;
    vector<point>::iterator it;

    scanf("%d\n", &t);

    for (tc = 1; tc <= t; tc++) {
        scanf("%d\n", &n);

        P.resize(n);
        for (i = 0; i < n; i++) {
            sign = 1;
            x = y = 0;
            while ((ch = getchar()) != ' ') {
                if (ch == '-')
                    sign = -1;
                else
                    x = x * 10 + ch - '0';
            }

            x *= sign;

            sign = 1;

            while ((ch = getchar()) != '\n') {
                if (ch == '-')
                    sign = -1;
                else
                    y = y * 10 + ch - '0';
            }

            y *= sign;

            P[i].first  = x;
            P[i].second = y;
        }

        sort(P.begin(), P.end());
        it = unique(P.begin(), P.end());
        P.resize(it - P.begin());
        n = P.size();

        if (n < 3) {
            printf("Case %d: 0.0000000\n", tc);
            continue;
        }

        H.resize(n + n);

        k = 0;
        for (i = 0; i < n; i++) {
            while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
            H[k++] = P[i];
        }

        for (i = n - 2, pos = k + 1;  i >= 0; i--) {
            while (k >= pos && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
            H[k++] = P[i];
        }

        k--;
        H.resize(k);
        ans = PI;

        for (i = 0; i < k; i++) {
            next = (i+1)%k;
            prev = (k+i-1)%k;
            a = dist(H[prev], H[next]);
            b = dist(H[prev], H[i]);
            c = dist(H[next], H[i]);

            double beta = acos((b*b + c*c - a*a)/(2*b*c));
            ans = min(ans, beta);
        }

        printf("Case %d: %.10lf\n", tc, ans*180/PI);
    }

    return 0;
}
