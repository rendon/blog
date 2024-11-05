---
tags:
    - algorithms
    - kotlin
    - post
created: 2023-11-15
updated: 2024-11-04
---
# Generate permutations in sorted order

Let's talk about permutations. They’re an interesting topic in combinatorics and come up in programming puzzles from time to time. There is a relatively intuitive recursive algorithm for generating all permutations for a list of elements, which goes like this:

```kt
fun permutate(elements: Array<Int>, n: Int) {
    if (n == 0) {
        println(elements.toList())
        return
    }
    for (i in 0..<n) {
        // "remove" the current element from the collection and
        // generate the permutations for the remaining n - 1
        // elements. Then, put the element back and repeat for the next element.
        swap(elements, i, n - 1)
        permutate(elements, n - 1)
        swap(elements, i, n - 1)
    }
}
```

Full code: [https://pl.kotl.in/nK_VtUpvn](https://pl.kotl.in/nK_VtUpvn)

This algorithm is succinct and elegant, but the permutations are generated in no particular order. We could certainly generate all the permutations and sort them, but that might be too costly. Fortunately, there is an algorithm (attributed to Donald Knuth) for generating permutations in ascending order.

```kt
fun permutate(elements: Array<Int>): Boolean {
    val n = elements.size;
    for (i in (n - 1).downTo(1)) {
        // Continue if the elements are sorted in descending order
        if (elements[i-1] >= elements[i]) continue

        // elements[i-1] is smaller than one of the elements to the right. Lets' find the right-most element that
        // meets the condition and swap.
        for (j in (n - 1).downTo(i)) {
            if (elements[i-1] < elements[j]) {
                swap(elements, i - 1, j)

                // elements[i-1] now has a higher value than before, sorting the rest of the
                // elements ensures that we'll obtain the smallest lexicographical permutation.
                elements.sort(i)
                return true
            }
        }
    }
    return false
}

fun permutateInOrder(elements: Array<Int>) {
    elements.sort()
    do {
        println(elements.toList())
    } while (permutate(elements))
    permutate(elements)
}
```

Full code: [https://pl.kotl.in/O9avWCqPu](https://pl.kotl.in/O9avWCqPu)

All right, there it is.

## Practice problems

- [https://leetcode.com/problems/permutations/](https://leetcode.com/problems/permutations/)
- [https://leetcode.com/problems/permutations-ii/](https://leetcode.com/problems/permutations-ii/)
- [https://leetcode.com/problems/permutation-sequence/](https://leetcode.com/problems/permutation-sequence/)

