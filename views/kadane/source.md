---
tags:
    - algorithms
    - post
created: 2024-11-04
---
# Kadane’s algorithm

I just learned about this algorithm, which is considered a dynamic programming approach. However, depending on the implementation, it might not resemble dynamic programming at all.

Check out the implementation presented on Wikipedia:
```python
def max_subarray(numbers):
    """Find the largest sum of any contiguous subarray."""
    best_sum = 0
    current_sum = 0
    for x in numbers:
        current_sum = max(0, current_sum + x)
        best_sum = max(best_sum, current_sum)
    return best_sum
```

That does not look like dynamic programming to me. Now let’s look at the following implementation:
```cpp
// Kadane's algorithm
// f(i) stores the max sub array sum ending at i
// Base case: f(0) = A[0]
// f(i) = max(f(i - 1) + A[i], A[i]);
int maxSubArray(vector<int>& A) {
    int n = static_cast<int>(A.size());
    vector<int> dp(n + 1);
    dp[0] = A[0];
    int max = dp[0];
    for (int i = 1; i < n; i++) {
        dp[i] = std::max(dp[i-1] + A[i], A[i]);
        max = std::max(max, dp[i]);
    }
    return max;
}
```

Can you see it now? I’m sure you do.

Of course, the second implementation uses additional space, the purpose is to show the recurrence function (thus DP).
Practice

Try solving the following problem using Kadane’s algorithm: [Maximum subarray](https://leetcode.com/problems/maximum-subarray).
