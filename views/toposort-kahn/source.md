---
tags:
    - algorithms
    - topological-sorting
    - post
created: 2024-11-15
updated: 2024-11-15
---
# Topological sorting - Kahn's algorithm

WORK IN PROGRESS

Problem: [course-schedule-ii](https://leetcode.com/problems/course-schedule-ii/)

Solution:
```java
// Khan's algorithm for topological sorting
import java.util.*;

class Solution {
    public int[] findOrder(int n, int[][] prerequisites) {
        var graph = new ArrayList<List<Integer>>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        var in = new int[n];
        for (var p : prerequisites) {
            graph.get(p[1]).add(p[0]);
            in[p[0]]++;
        }

        var queue = new ArrayDeque<Integer>();
        for (int i = 0; i < n; i++) {
            if (in[i] == 0) {
                queue.add(i);
            }
        }

        var taken = new ArrayList<Integer>();
        while (!queue.isEmpty()) {
            var node = queue.remove();
            taken.add(node);

            for (var v : graph.get(node)) {
                in[v]--;
                if (in[v] == 0) {
                    queue.add(v);
                }
            }
        }

        if (taken.size() < n) return new int[]{};
        var res = new int[taken.size()];
        for (int i = 0; i < taken.size(); i++) {
            res[i] = taken.get(i);
        }
        return res;
    }
}
```
