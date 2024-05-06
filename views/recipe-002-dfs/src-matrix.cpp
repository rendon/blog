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
