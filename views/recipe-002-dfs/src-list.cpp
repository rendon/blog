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
