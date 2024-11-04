---
tags:
    - algorithms
    - data-structures
    - post
created: 2016-02-18
updated: 2024-05-07
---
# Recipe 001: Floyd-Warshall

Compute the minimum distance between all the nodes in a graph.


```cpp
// n is the number of nodes in the graph, numbered from 0 to n - 1.
// Set D[i][j] = infinity for each (i, j).

// The distance of a node with itself is 0.
for (int i = 0; i < n; i++) {
    D[i][i] = 0;
}

// W[i][j] is cost of the edge going from node i to j. 
// Infinity if such edge doesn't exist.
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        D[i][j] = W[i][j];
    }
}


for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Check if it is cheaper to travel from node i to node k
            // and then from node k to node j, than traveling directly
            // from i to j, update D if that's the case.
            if (D[i][k] + D[k][j] < D[i][j]) {
                D[i][j] = D[i][k] + D[k][j];
            }
        }
    }
}

```

Quickly determine if node $i$ can reach node $j$ directly or by using some intermediate nodes, the answer is in $R[i][j]$.


```cpp
// R is a copy of the adjacency matrix.
for (int k = 0; k < n; k++) {
    R[k][k] = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (R[i][k] && R[k][j]) {
                R[i][j] = true;
            }
        }
    }
}

```

Algorithm complexity: $O(n^3)$.
