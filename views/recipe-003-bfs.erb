"=========== Meta ============
"StrID : 1770
"Title : Recipe 003: Breadth-First Search
"Slug  : recipe-003-bfs
"Cats  : Sin categoría
"Tags  : 
"=============================
"EditType   : post
"EditFormat : Markdown
"TextAttach : 
"========== Content ==========
[Breadth-First Search](http://en.wikipedia.org/wiki/Breadth-first_search) is another fundamental algorithm in [graph theory](http://en.wikipedia.org/wiki/Graph_theory), it's a must to know!.

[php]figure('graph','A graph', 'graph', 'svg', 'EN');[/php]

For this algorithm we need a [queue](http://en.wikipedia.org/wiki/Queue_%28abstract_data_type%29).

<pre lang="cpp" theme="slate">
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
</pre>

Example input(figure [php]ref('graph');[/php]):

<pre theme="slate">
5 4
0 1
0 2
2 4
2 3
</pre>

Example output:
<pre theme="slate">
0
1 2
4 3
</pre>

And that's it. Remember, Breadth-First Search must be part of your toolbox!
