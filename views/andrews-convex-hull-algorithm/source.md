# Andrew's Convex Hull Algorithm
2016-02-23 2024-05-06 #algorithms #data-structures #post

Convex hull is a classical problem in computational geometry and often used in programming contests. Today I present to you  the Andrew's algorithm to compute the convex hull from a set of 2D points. 

![Convex Hull](/andrews-convex-hull-algorithm/convex_hull_0.svg)

## Convex Hull
Here a definition from Robert Sedgewick lecture notes.

<div class="box">
A set of point is **convex** if for any two points *p* and *q* is the set, the line segment *pq* is completely in the set.
  
**Convex hull**. Smallest convex set containing all the points.
</div>

## Andrew's algorithm
The Andrews's Algorithm splits the convex hull in two parts parts, upper hull and lower hull, here the algorithm.

<ol>
  <li>L and U are lists of points.</li>
  <li>Sort the set of point by x coordinate in ascending order.</li>
  <li>Construct the upper hull:</li>
  <ol>
    <li>start from the point with smallest x coordinate, if two points has equal x coordinate take the one with the largest y coordinate.</li>
    <li>Taking the point with the largest y coordinate may cause the hull to become concave, so, check if the current point and the last two in U form a convex triangle, if not, remove the last point in U and try again with the last two, an so on till a convex triangle is found.</li>
    <li>Add the current pont to U</li>
  </ol>
  <li>Construct the lower hull:</li>
  <ol>
    <li>start from the point with largest x coordinate, if two points has equal x coordinate take the one with the smallest y coordinate.</li>
    <li>Taking the point with the smallest y coordinate may cause the hull to become concave, so, check if the current point and the last two in L form a convex triangle, if not, remove the last point in L and try again with the last two, an so on till a convex triangle is found.</li>
    <li>Add the current pont to L</li>
  </ol>
  <li>Join the upper and the lower convex hull.</li>
</ol>

<table>
<tr>
<td>![Step 1](/andrews-convex-hull-algorithm/convex_hull_1.png)
<td>![Step 2](/andrews-convex-hull-algorithm/convex_hull_2.png)
</tr>
<tr>
<td>![Step 3](/andrews-convex-hull-algorithm/convex_hull_3.png)
<td>![Step 4](/andrews-convex-hull-algorithm/convex_hull_4.png)
</tr>
<tr>
<td>![Step 5](/andrews-convex-hull-algorithm/convex_hull_5.png)
<td>![Step 6](/andrews-convex-hull-algorithm/convex_hull_6.png)
</tr>
</table>

## Sample problem

A easy problem where you can put in practice this topic is with [1203 - Guarding Bananas](http://lightoj.com/volume_showproblem.php?problem=1203) from [lightoj.com](http://lightoj.com/).

To check if three point are convex you can use a vector cross product.

<table>
<tr>
<td>![Clockwise](/andrews-convex-hull-algorithm/convex_hull_7.png)
<td>![Anticlockwise](/andrews-convex-hull-algorithm/convex_hull_8.png)
</tr>
</table>

If points A, O and B are in clockwise orientation then $ v \times u$ will be greater than zero, otherwise the result will be less than  zero.

## Solution to sample problem

Apply the algorithm to find the convex hull and then, for each point that form the convex hull, compute the angle between it and its left and right points, take the minimum.

```cpp
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
```

## References
1. [Line Sweep Algorithms, bmerry](http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=lineSweep)
2. [Geometry Lecture, Robert Sedgewick](http://www.cs.princeton.edu/courses/archive/fall05/cos226/lectures/geometry.pdf)
