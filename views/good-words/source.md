# Good words
2016-02-18 2024-05-07 #algorithms #post

Hi! Welcome to my first post in English :).

Today was held the first World Finals Warmup 2012 and I was reading(don't solving) the problems and I found a very interesting fact in [problem E](http://uva.onlinejudge.org/contests/296-e6f9c1dc/12437.html), Good Words, and well that is what I'll write in this post.

<blockquote>
Suppose a word consisting of only 0 and 1 is called good if there is no adjacent one in the word. We are asked to find good words of length n.
</blockquote>

At first the problem may appear difficult but actually it can be solved with a little insight: initially we have *n* spaces, the first good word is the one formed by only '0's, ok?, if you decide the first digit to be '0' then you can fill up the remaining *n-1* as we like respecting the condition of no two adjacent '1's, now if you decide the first digit to be '1' then the second digit must be '0' and now we face with the problem of the first case but with *n-2*. If we are able to find all possible good words for *n = 1* and *n = 2* we'll be able to get the answer for any *n* greater that two with W<sub>n</sub> = W<sub>n-1</sub> + W<sub>n-2</sub>.

<table class="table">
  <tr><th>**n**</th><th>**Good words**</th></tr>
  <tr><td>1</td><td>0, 1</td></tr>
  <tr><td>2</td><td>00, 01, 10</td></tr>
  <tr><td>3</td><td>000, 001, 010, 100, 101000, 001, 010, 100, 101</td></tr>
</table>

The first thing that came to my mind was use dynamic programming but all indicates that in many occasions is very important don't rush out with the first idea since is very likely  isn't the best. Well, this is all for this post, I will see you in next post!The first thing that came to my mind was use dynamic programming but all indicates that in many occasions is very important don't rush out with the first idea since is very likely  isn't the best. Well, this is all for this post, I will see you in next post!
