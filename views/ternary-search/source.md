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

Embed: `sol.cpp`

## References

<table border="0">
  <tr><td>1</td> <td>[Ternary search](http://en.wikipedia.org/wiki/Ternary_search)</td></tr>
  <tr><td>2</td> <td>[Codeforces discussion about ternary search](http://codeforces.com/blog/entry/3560#comment-71935)</td></tr>
  <tr><td>3</td> <td>[Topcoder discussion about ternary search](http://apps.topcoder.com/forums/?module=Thread&threadID=506787&start=0&mc=27#507870)</td></tr>
</table>
