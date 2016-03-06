#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
    long long x, y, n, A, B;
    long double a, b, minn = 1e12, f;

    cin >> x >> y >> n;

    f = x / (long double)y;
    for (b = 1; b <= n; b++) {
        a = floor((b * x) / y);

        if (abs(f - a/b) < minn) {
            minn = abs(f - a / b);
            A = a;
            B = b;
        }

        a = ceil((b * x) / y);
        if (abs(f - a/b) < minn) {
            minn = abs(f - a / b);
            A = a;
            B = b;
        }

    }

    cout << A << "/" << B << endl;

    return EXIT_SUCCESS;
}
