"=========== Meta ============
"StrID : 1703
"Title : Recipe 001: Floyd-Warshall
"Slug  : recipe-001-floyd-warshall
"Cats  : Sin categoría
"Tags  : 
"=============================
"EditType   : post
"EditFormat : Markdown
"TextAttach : wpid1714-vimpress_54206b18_mkd.txt
"========== Content ==========

Compute the minimum distance between all the nodes in a graph.

<pre lang="cpp" theme="slate">
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
</pre>

Quickly determine if node _i_ can reach node _j_ directly or by using some intermediate nodes, the answer is in _R[i][j]_.

<pre lang="cpp" theme="slate">
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
</pre>

<p>Algorithm complexity: <strong>O(n<sup>3</sup>)</strong></p>.
