"=========== Meta ============
"StrID : 1736
"Title : Recipe 002: Depth-First Search
"Slug  : recipe-002-dfs
"Cats  : Sin categoría
"Tags  : 
"=============================
"EditType   : post
"EditFormat : Markdown
"TextAttach : wpid-wpid-vimpress_54727713_mkd.txt
"========== Content ==========
[Depth-First Search](http://en.wikipedia.org/wiki/Depth-first_search) is one of the fundamental algorithms in [graph theory](http://en.wikipedia.org/wiki/Graph_%28mathematics%29). It's a must to know!

Nowadays it's a piece of cake, but I did struggle a bit to get my head around this and other graph theory algorithms.

[php]figure('graph','A graph.', 'graph', 'svg', 'EN');[/php]

[php]section("Common ways to represent graphs in a computer");[/php] 

The most common representations for graphs are [Adjacency matrix](http://en.wikipedia.org/wiki/Adjacency_matrix) and [Adjacency list](http://en.wikipedia.org/wiki/Adjacency_list).

<pre lang="cpp" theme="slate">
#include <iostream>
#include <cstdlib>
using namespace std;
// The maximum number of nodes in the graph.
// If this number is not known beforhand, dynamic allocation is a  better idea.
const int N = 10;

/*
 * Perform a Depth-First Search.
 * Nodes are identified by integers from 0 to n - 1.
 * 
 * graph[u][v] is true if node u and v are connected, false otherwise.
 */
void dfs(int u, bool graph[][N], bool visited[], int n) {
    // Mark node u to avoid entering in an infinite loop.
    visited[u] = true;

    // Do something with u, e.g., print it out.
    cout << u << " ";

    // Visit each adjacent node of u.
    for (int v = 0; v < n; v++)  {
        if (graph[u][v] && !visited[v]) {
            dfs(v, graph, visited, n);
        }
    }

    // This step is optional, unmark u if you want to travel all the possible
    // tours, otherwise leave it marked.
    //visited[u] = false;
}

int main() {
    bool graph[N][N];
    bool visited[N];

    // A common way to express graphs is by specifiying the number for nodes n,
    // and the number of edges m.
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            graph[i][j] = false;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // An undirected graph.
        graph[u][v] = true;
        graph[v][u] = true;
    }

    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    for (int u = 0; u < n; u++) {
        if (!visited[u]) {
            dfs(u, graph, visited, n);
        }
    }
    return 0;
}
</pre>

Example input (figure 1):

<pre theme="slate">
5 4
0 1
0 2
2 3
2 4
</pre>

Example output:
<pre theme="slate">
0 1 2 3 4
</pre>

Here is the version using adjacency "lists" (not necessarily linked lists).

<pre lang="cpp" theme="slate">
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
// The maximum number of nodes in the graph.
// If this number is not known beforhand, dynamic allocation is a  better idea.
const int N = 10;

/*
 * Perform a Depth-First Search.
 * Nodes are identified by integers from 0 to n - 1.
 * 
 * graph[u] contains v if node v is a neighbor of u.
 */
void dfs(int u, vector<int> graph[], bool visited[]) {
    // Mark node u to avoid entering in an infinite loop.
    visited[u] = true;

    // Do something with u, e.g., print it out.
    cout << u << " ";

    // Visit each adjacent node of u.
    for (int v : graph[u]) {
        if (!visited[v]) {
            dfs(v, graph, visited);
        }
    }

    // This step is optional, unmark u if you want to travel all the possible
    // tours, otherwise leave it marked.
    //visited[u] = false;
}

int main() {
    vector<int> graph[N];
    bool visited[N];

    // A common way to express graphs is by specifiying the number for nodes n,
    // and the number of edges m.
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // An undirected graph.
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    for (int u = 0; u < n; u++) {
        if (!visited[u]) {
            dfs(u, graph, visited);
        }
    }
    return 0;
}
</pre>
