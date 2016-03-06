#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

class Graph {
private:
    vector<vector<int> > G;
public:
    Graph() {}
    Graph(int nodes) {
        G.resize(nodes);
    }

    void addEdge(int u, int v) {
        G[u].push_back(v);
    }

    void dfs(int u, vector<bool> &visited) {
        visited[u] = true;
        for (int v : G[u]) {
            if (!visited[v]) {
                dfs(v, visited);
            }
        }

        printf("%d ", u + 1);
    }

    void sort() {
        vector<bool> visited(G.size(), false);
        for (int u = 0; u < int(G.size()); u++) {
            if (!visited[u]) {
                dfs(u, visited);
            }
        }
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    while (n != 0 || m != 0) {
        Graph graph(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            graph.addEdge(v - 1, u - 1);

        }
        graph.sort();
        scanf("%d %d", &n, &m);
    }

    return 0;
}

