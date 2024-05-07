# Ternary search
2016-02-18 2024-05-07 #algorithms #post

Hi! This time I going to talk about a new technique I've just learned, [Ternary Search](http://en.wikipedia.org/wiki/Ternary_search).

## Ternary search

Ternary search is a technique similar to [Binary Search](http://en.wikipedia.org/wiki/Binary_search_algorithm) and is important since ternary search could success in situations where the binary search would fail. Time ago I was very criticized in the [Codeforces](http://codeforces.com) forum for arguing that has no sense to use ternary search if it is not more efficient than binary search. Is not about efficiency but --said the others. Actually I meant to ternary search in arrays, to reduce the search space to a third part, etc. Now I understand what they were talking about.

## Sample problem

You can solve the [1146 - Closest Distance](http://lightoj.com/volume_showproblem.php?problem=1146) problem from [lightoj.com](http://lightoj.com) with this technique.

## Solution to sample problem

### Basic idea

Compute the distance between the two men as they move and take the minimum distance.

![Termnary search example](/ternary-search/ternary_search_1.png)

Obviously, we can only take discrete points, and, since the problem ask for an answer with an error less than 1e-6, a brute force approach would take much time, very much. So the strategy is to use ternary search:

![Step 1](/ternary-search/ternary_search_2.png)
![Step 2](/ternary-search/ternary_search_3.png)
![Step 3](/ternary-search/ternary_search_4.png)
![Step 4](/ternary-search/ternary_search_5.png)

And so on. Here is my solution:


```cpp
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


```

## References

<table border="0">
  <tr><td>1</td> <td>[Ternary search](http://en.wikipedia.org/wiki/Ternary_search)</td></tr>
  <tr><td>2</td> <td>[Codeforces discussion about ternary search](http://codeforces.com/blog/entry/3560#comment-71935)</td></tr>
  <tr><td>3</td> <td>[Topcoder discussion about ternary search](http://apps.topcoder.com/forums/?module=Thread&threadID=506787&start=0&mc=27#507870)</td></tr>
</table>
