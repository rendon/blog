#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;
// Maximum number of nodes.
const int N = 10;

void bfs(vector<int> graph[], int root) {
    vector<bool> visited(N, false);
    queue<int> Q;
    queue<int> L; // To mark levels.
    Q.push(root);
    L.push(0); // The root is at level 0.
    visited[root] = true;
    int prev = 0;
    while (!Q.empty()) {
        int u = Q.front();
        int l = L.front();
        Q.pop();
        L.pop();

        // Each level in it's own line.
        if (prev != l) {
            cout << endl;
        }
        prev = l;
        cout << u << " ";

        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                Q.push(v);
                L.push(l + 1); // Childs of u are part of the next level.
            }
        }
    }
}

int main(int argc, char **argv) {
    vector<int> graph[N];
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Start Breadth-First Search at node 0
    bfs(graph, 0);
    return EXIT_SUCCESS;
}
