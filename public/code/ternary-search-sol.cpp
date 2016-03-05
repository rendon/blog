#include <iostream>
#include <cstdio>
#include <cmath>
#include <complex>
#include <algorithm>
#define x() real()
#define y() imag()

using namespace std;

typedef complex<double> Vector;
typedef complex<double> point;
point points[5];

double closest()
{
    Vector A = points[1] - points[0];
    Vector B = points[3] - points[2];
    Vector unita = A/abs(A);
    Vector unitb = B/abs(B);
    point startA = points[0];
    point startB = points[2];

    double maxa = abs(A);
    double mina = 0;
    double maxb = abs(B);
    double minb = 0;
    double ta, tb, ans = 1000;
    point a, b, c, d;

    int count = 500;
    while (count--) {
        ta = abs(maxa - mina)/3;
        tb = abs(maxb - minb)/3;
        a = (unita * (mina + ta)) + startA;
        b = (unitb * (minb + tb)) + startB;

        ta += ta;
        tb += tb;
        c = (unita * (mina + ta)) + startA;
        d = (unitb * (minb + tb)) + startB;

        if (abs(b - a) < abs(d - c)) {
            maxa = maxa - ta/2;
            maxb = maxb - tb/2;
            ans = std::min(ans, abs(b - a));
        } else {
            mina = mina + ta/2;
            minb = minb + tb/2;
            ans = std::min(ans, abs(d - c));
        }
    }

    return ans;
}

int main(int argc, char **argv)
{
    int t, tc, i;
    double x, y;

    scanf("%d", &t);

    for (tc = 1; tc <= t; tc++) {
        for (i = 0; i < 4; i++) {
            scanf("%lf %lf", &x, &y);
            points[i] = point(x, y);
        }

        printf("Case %d: %.10lf\n", tc, closest());
    }

    return 0;
}

