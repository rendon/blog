# CF 172
2016-02-18 2024-05-07 #algorithms #data-structures #post

![](/cf-172/codeforces_logo.png)

<p>I took part in Codeforces 172 Division II and here are my solutions for some of the problems.</p>

## A. Word capitalization

<a href="http://www.codeforces.com/contest/281/problem/A" title="Word capitalization">Problem description</a>
### Solution:

<p>Read the string and change the first character to uppercase.</p>

Embed: `a.cpp`

## B. Nearest fraction

<a href="http://www.codeforces.com/contest/281/problem/B" title="Nearest fraction">Problem description</a>

### Solution:

<p>I could not solve the problem in the contest. My implementation is based on other contestants' solutions. Sincerely my idea was similar but I avoided the use of floating point(supposedly to avoid precision problems) and it didn't work well.</p>

Embed: `b.cpp`

## C. Rectangle puzzle

<a href="http://codeforces.com/contest/281/problem/C" title="Rectangle puzzle">Problem description</a>.

### Solution:

<p>Let's call $R$ and $S$ the original and the rotated rectangle respectively, with corner points $R_{a}$, $R_{b}$, $R_{c}$, $R_{d}$, $S_{a}$, $S_{b}$, $S_{c}$ and $S_{d}$. Initially $R$ and $S$ are the same.</p>

<p>Rotate $S$ $\alpha$ degrees(take care of the special cases $\alpha = 0$ and $\alpha = 180$) and, for each line segment of $S$ check if it do intersect with any side of $R$(`isX()` method in the code), if so, compute the intersection point(`intersection()` method in the code) and add it to a list of point, lets call it P. Finally compute the area of the polygon formed by P(the points need to be sorted in clockwise or counterclockwise  order) and, since the area is computed using cross product take the absolute value divided by two.</p>

Embed: `c.cpp`

<p>These are my own solutions, feel free to comment or use the code for your own needs.</p>
