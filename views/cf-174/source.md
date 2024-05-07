#  CF-174
2016-03-04 2024-05-06 #algorithms #data-structures #post

I took part in Codeforces 174 Division II and here are my solutions for some of the problems.

## A. Cows and primitive roots

<a href="http://www.codeforces.com/contest/284/problem/A" title="Cows and primitive roots">Problem description</a>.

### Solution:

#### Complicated version:

<p>Stick to the problem definition and make the tests, we need a modpow function. Complexity: $O(n^2)$.</p>

Embed: `a.cpp`

<p>This problem took me about an hour, I am out of practice, I didn't remember well how to implement the modpow function and I wanted to do it by myself.</p>

#### Simplified version:

<p>I found this formula in <a href="http://en.wikipedia.org/wiki/Primitive_root_modulo_n#Finding_primitive_roots" title="Primitive roots">wikipedia</a>:</p>

<blockquote>
The number of primitive roots modulo n, if there are any, is equal to
$ \varphi\left(\varphi\left(n\right)\right) $
</blockquote>

<p>Where $\varphi\left(n\right) $ is defined as: How many numbers $m$($1 \leq m < n$) are relatively prime to $n$, i.e. $gcd(n, m) = 1$. Since $p$ in the problem is guaranteed to be prime then $\varphi\left(p\right) = p - 1$ and we only need to compute $\varphi\left(p - 1\right)$, this can be done easily in $O(n)$.</p>

Embed: `a-simple.cpp`

## B. Cows and Poker Game

<a href="http://www.codeforces.com/contest/284/problem/B" title="Cows and Poker Game">Problem description</a>.

### Solution:

<p>Count the occurrences of 'F's and 'A's. If the occurrences of 'I' is 0 the answer is the number of occurences of 'A's, if the occurrences of 'I' is exactly 1 the answer is 1, in other case the answer is 0. This is the solution that I sent during the contest. Complexity: $O(n)$.</p>

Embed: `b.cpp`

## C. Cows and Sequence

<a href="http://www.codeforces.com/contest/284/problem/C" title="Cows and Sequence">Problem description</a>.

### Solution:

<p>I wasn't able to solve this problem during the contest, the idea described here is from the editorial and my implementation is based on <a href="http://www.codeforces.com/profile/Efremov_licesos" target="_blank">Efremov_licesos</a>'s solution.</p>

<p>**Q**: If the solution is described in the editorial Why to write about it again? </p>

<p>**A**: Because sometimes the solutions described in the editorials are very abstract and it's almost always hard to understand other contestants' solutions(many contestants are very intelligent but their code is cryptic and ugly ...no offense).</p>

<p>If the operations were only 1 and 2 you can solve the problem keeping the sum of the additions to existing elements or new elements. The hard part is operation 3, How to know what is the value of the last element after some aditions? The idea is to use two arrays, an array B to store the new values($k_i$), and an array A to store the additions(operation 1). A picture is worth a thousand words.</p>

![](/cf-174/cf174d2_c_0.png)

<p>The value of the last element is `(A[n] * n) - (A[n] * (n-1)) + B[n]`, or graphically.</p>

![](/cf-174/cf174d2_c_1.png)

<p>I hope with this the code be more understandable.</p>
<p>Complexity: $O(n)$.</p>

Embed: `c.cpp`

### D. Not solved yet.

### E. Not solved yet.

Comments of corrections are welcome.
