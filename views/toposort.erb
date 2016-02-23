"=========== Meta ============
"StrID : 1775
"Title : Topological sorting
"Slug  : toposort
"Cats  : Sin categoría
"Tags  : 
"=============================
"EditType   : post
"EditFormat : Markdown
"TextAttach : wpid1780-vimpress_54735456_mkd.txt
"========== Content ==========
Let's start this topic with an example, we have some tasks to do, some tasks are independent of each other, but some tasks depend on other tasks and those tasks must be done before these tasks. We can model this problem with a graph, the tasks are vertices and the dependencies are edges. Topological sorting is an algorithm that helps us to find an ordering of tasks such that for every task _u_ that has to be done before task _v_, _u_ comes before _v_ in the ordering.

Topological sorting works on [DAGs](http://en.wikipedia.org/wiki/Directed_acyclic_graph), that is, graphs wit no cycles, if the graph contains a cycle it's impossible to find a solutions. For example, if task _A_ depends on task _B_ and task _B_ depends on task _A_ then it's impossible to determine which task has to be done first, see [Chicken or Egg](http://en.wikipedia.org/wiki/Chicken_or_the_egg).

[php]section("Example problem");[/php]
Here you have a problem where you have to literally find an ordering for tasks: [10305 - Ordering Tasks](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1246). Here is a working implementation of Topological sorting.

<pre lang="cpp" theme="slate">
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

</pre>

The solutions works as follows:

1. If task _u_ has to be done before task _v_ create a directed edge from _v_ to _u_.
2. Create a table _visited[]_ such that _visited[u]_ is true if node _u_ has been visited.
3. Run a [Depth-First Search](/recipe-002-dfs/) on all nodes that has not been visited yet and print the nodes in reverse order, we can do that by printing node _u_ before leaving the recursive function.

The resulting sequence of nodes is a valid ordering. Notice that it's possible to have multiple valid solutions.

The previous problem is easy because is the classical example to explain Topological sorting. However, most of the time these problems are not so obvious and we have to work a bit to uncover the underlying problem, for example [1034 - Hit the Light Switches](http://lightoj.com/volume_showproblem.php?problem=1034) (hint, think a bout connected components).

[php]section("References");[/php]

[php]
add_bib('algs4', 'Robert Sedgewick and Kevin Wayne', 'Algorithms, 4th Edition', 'http://algs4.cs.princeton.edu/home/'); 
generate_bib_table('EN');
[/php]
