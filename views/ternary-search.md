"=========== Meta ============
"StrID : 147
"Title : Ternary search
"Slug  : ternary-search
"Cats  : Sin categoría
"Tags  : Algorithms, Math, Programming contests
"=============================
"EditType   : post
"EditFormat : HTML
"TextAttach : 
"========== Content ==========
[php]
initialize();
set_setting("show_numbers_in_sections", false);
set_setting("show_numbers_in_subsections", false);
[/php]

Hi! This time I going to talk you about a new technique I've just learned, <a href="http://en.wikipedia.org/wiki/Ternary_search" target="_blank">Ternary Search</a>.

[php]section("Ternary search");[/php]

Ternary search is a technique similar to <a href="http://en.wikipedia.org/wiki/Binary_search_algorithm" target="_blank">Binary Search</a> and is important since ternary search could success in situations where the binary search would fail. Time ago I was very criticized in the <a href="http://codeforces.com" target="_blank">Codeforces</a> forum for arguing that has no sense to use ternary search if it is not more efficient than binary search. Is not about efficiency but --said the others. Actually I meant to ternary search in arrays, to reduce the search space to a third part, etc. Now I understand what they were talking about.

[php]section("Sample problem");[/php]

You can solve the <a href="http://lightoj.com/volume_showproblem.php?problem=1146" target="_blank">1146 - Closest Distance</a> problem from <a href="http://lightoj.com" target="_blank">lightoj.com</a> with this technique.

[php]section("Solution to sample problem");[/php]

[php]subsection("Basic idea");[/php]

Compute the distance between the two men as they move and take the minimum distance.

[php]figure('ternary_search_1', 'Termnary search example', 'ternary_search_1', 'png', 'EN');[/php]

Obviously , we can only take discrete points, and, since the problem ask for an answer with an error less than 1e-6, a brute force approach would take much time, very much. So the strategy is to use ternary search:

[php]figure('ternary_search_2', 'Step 1', 'ternary_search_2', 'png', 'EN');[/php]
[php]figure('ternary_search_3', 'Step 2', 'ternary_search_3', 'png', 'EN');[/php]
[php]figure('ternary_search_4', 'Step 3', 'ternary_search_4', 'png', 'EN');[/php]
[php]figure('ternary_search_5', 'Step 4', 'ternary_search_5', 'png', 'EN');[/php]

And so on. Here is my solution:

<pre lang="cpp" theme="slate">
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

</pre>

[php]section("References");[/php]

<table border="0">
  <tr><td>1</td> <td><a href="http://en.wikipedia.org/wiki/Ternary_search" target="_blank">Ternary search</a></td></tr>
  <tr><td>2</td> <td><a href="http://codeforces.com/blog/entry/3560#comment-71935" target="_blank">Codeforces discussion about ternary search</a></td></tr>
  <tr><td>3</td> <td><a href="http://apps.topcoder.com/forums/?module=Thread&threadID=506787&start=0&mc=27#507870" target="_blank">Topcoder discussion about ternary search</a></td></tr>
</table>
