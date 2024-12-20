---
tags:
    - algorithms
    - data-structures
    - post
created: 2016-02-18
updated: 2024-05-14
---
# CODEFORCES 172

I took part in Codeforces 172, Division II, and here are my solutions for some of the problems.

## [A. Word capitalization](http://codeforces.com/contest/281/problem/A)
Read the string and change the first character to uppercase.

```cpp
#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char *argv[])
{
    string word;
    cin >> word;
    word[0] = toupper(word[0]);
    cout << word << endl;
    return EXIT_SUCCESS;
}
```

## [B. Nearest fraction](http://codeforces.com/contest/281/problem/B)
I could not solve the problem in the contest. My implementation is based on other contestants' solutions. Sincerely, my idea was similar but I avoided the use of floating point(supposedly to avoid precision problems) and it didn't work well.

```cpp
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
```

## [C. Rectangle puzzle](http://codeforces.com/contest/281/problem/C)
Let's call $R$ and $S$ the original and the rotated rectangle respectively, with corner points $R_{a}$, $R_{b}$, $R_{c}$, $R_{d}$, $S_{a}$, $S_{b}$, $S_{c}$ and $S_{d}$. Initially $R$ and $S$ are the same.

Rotate $S$ $\alpha$ degrees(take care of the special cases $\alpha = 0$ and $\alpha = 180$) and, for each line segment of $S$ check if it do intersect with any side of $R$(`isX()` method in the code), if so, compute the intersection point(`intersection()` method in the code) and add it to a list of point, lets call it P. Finally compute the area of the polygon formed by P(the points need to be sorted in clockwise or counterclockwise  order) and, since the area is computed using cross product take the absolute value divided by two.

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <complex>
#include <algorithm>

#define x() real()
#define y() imag()
using namespace std;

typedef complex<double> point;

point rotate(point p, double angle)
{
    double x = cos(angle) * p.x() - sin(angle) * p.y();
    double y = sin(angle) * p.x() + cos(angle) * p.y();

    return point(x, y);
}

point intersection(point a, point b, point c, point d)
{
    double A1 = b.y() - a.y();
    double B1 = a.x() - b.x();
    double C1 = A1 * a.x() + B1 * a.y();

    double A2 = d.y() - c.y();
    double B2 = c.x() - d.x(); 
    double C2 = A2 * c.x() + B2 * c.y();

    double det = A1 * B2 - A2 * B1;
    double x = (B2 * C1 - B1 * C2)/det;
    double y = (A1 * C2 - A2 * C1)/det;

    return point(x, y);
}

// Determines if the two segments do intersect.
bool isX(point a, point b, point c, point d)
{
    point u = b - a;
    point v = c - a;
    point w = a - b;
    point x = d - b;

    double crossA = u.x() * v.y() - u.y() * v.x();
    double crossB = w.x() * x.y() - w.y() * x.x();

    return (crossA * crossB) > 0;
}

// Sort points in clockwise order.
// Not the best algorithm but the easiest.
bool compare(const point& a, const point& b)
{
    double alfa = atan2(a.y(), a.x());
    double beta = atan2(b.y(), b.x());

    if (alfa < 0)
        alfa += 2 * M_PI;

    if (beta < 0)
        beta += 2 * M_PI;

    return alfa > beta;
}

int main(int argc, char *argv[])
{
    double w, h, alfa;

    cin >> w >> h >> alfa;

    double angle = (alfa * M_PI)/180;

    point Ra(-w/2, h/2);
    point Rb(w/2, h/2);
    point Rc(w/2, -h/2);
    point Rd(-w/2, -h/2);

    point Sa = rotate(Ra, angle);
    point Sb = rotate(Rb, angle);
    point Sc = rotate(Rc, angle);
    point Sd = rotate(Rd, angle);

    vector<point> P;

    if (isX(Sa, Sb, Ra, Rb))
        P.push_back(intersection(Sa, Sb, Ra, Rb));
    if (isX(Sa, Sb, Rb, Rc))
        P.push_back(intersection(Sa, Sb, Rb, Rc));
    if (isX(Sa, Sb, Rc, Rd))
        P.push_back(intersection(Sa, Sb, Rc, Rd));
    if (isX(Sa, Sb, Rd, Ra))
        P.push_back(intersection(Sa, Sb, Rd, Ra));

    if (isX(Sb, Sc, Ra, Rb))
        P.push_back(intersection(Sb, Sc, Ra, Rb));
    if (isX(Sb, Sc, Rb, Rc))
        P.push_back(intersection(Sb, Sc, Rb, Rc));
    if (isX(Sb, Sc, Rc, Rd))
        P.push_back(intersection(Sb, Sc, Rc, Rd));
    if (isX(Sb, Sc, Rd, Ra))
        P.push_back(intersection(Sb, Sc, Rd, Ra));

    if (isX(Sc, Sd, Ra, Rb))
        P.push_back(intersection(Sc, Sd, Ra, Rb));
    if (isX(Sc, Sd, Rb, Rc))
        P.push_back(intersection(Sc, Sd, Rb, Rc));
    if (isX(Sc, Sd, Rc, Rd))
        P.push_back(intersection(Sc, Sd, Rc, Rd));
    if (isX(Sc, Sd, Rd, Ra))
        P.push_back(intersection(Sc, Sd, Rd, Ra));

    if (isX(Sd, Sa, Ra, Rb))
        P.push_back(intersection(Sd, Sa, Ra, Rb));
    if (isX(Sd, Sa, Rb, Rc))
        P.push_back(intersection(Sd, Sa, Rb, Rc));
    if (isX(Sd, Sa, Rc, Rd))
        P.push_back(intersection(Sd, Sa, Rc, Rd));
    if (isX(Sd, Sa, Rd, Ra))
        P.push_back(intersection(Sd, Sa, Rd, Ra));

    sort(P.begin(), P.end(), compare);

    double area = 0;
    int n = P.size();

    for (int i = 1; i + 1 < n; i++) {
        double Sa = P[i].x() - P[0].x();
        double Sb = P[i].y() - P[0].y();
        double a2 = P[i+1].x() - P[0].x();
        double b2 = P[i+1].y() - P[0].y();
        area += Sa * b2 - a2 * Sb;
    }

    if (alfa == 0 || alfa == 180)
        printf("%.12lf\n", w * h);
    else
        printf("%.12lf\n", abs(area/2));

    return EXIT_SUCCESS;
}
```

That was it for CF 172. Until next time.
