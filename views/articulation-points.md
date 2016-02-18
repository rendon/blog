"=========== Meta ============
"StrID : 117
"Title : Articulation points
"Slug  : articulation-points
"Cats  : Sin categoría
"Tags  : Algorithms, Programming contests
"=============================
"EditType   : post
"EditFormat : Markdown
"TextAttach : wpid1398-vimpress_5377c834_mkd.txt
"========== Content ==========
[php]
set_setting("show_numbers_in_sections", false);
[/php]

[php]section("Welcome");[/php]

Hi friends! Currently I am training for a programming contest and I have no time to publish. I am learning many interesting topics about algorithms and programming and I want to share that with you. However, to write an article consumes much of my time and I'm devising a format that is both brief and useful: Algorithm or Data structure, brief info, sample problem, solution and references.

[php]section("Articulation points");[/php]

Today's topic is about <a href="http://en.wikipedia.org/wiki/Graph_theory" target="_blank">graph theory</a>, articulation points. Here a <a href="http://www.cs.umd.edu/~samir/451/bc.ps" target="_blank">brief info from Dave Mount</a>:

<div class="box">
<strong>Articulation Points and Biconnected Graphs:</strong> Today we discuss another application of DFS, this time to a problem on undirected graphs. Let <em>G = (V, E)</em> be a <strong> connected</strong> undirected graph. Consider de following definitions.

<strong>Articulation Point( or Cut Vertex):</strong> Is any vertex whose removal(together with the removal of any incident edges) results in a disconnected graph.
</div>

[php]figure('ArtPoints', 'Articulation points example', 'ArtPoints', 'svg', 'EN');[/php]

[php]section("Sample problem");[/php]

A problem where you can put in practice this topic is <a href="http://lightoj.com/volume_showproblem.php?problem=1063" target="_blank">1063 Ant Hills</a> from <a href="http://lightoj.com" target="_blank">lightoj.com</a>.

[php]section("Solution to sample problem");[/php]

<pre lang="cpp" theme="slate">
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int LIMIT = 10010;

vector<int> G[LIMIT];
int D[LIMIT];
int P[LIMIT];
int L[LIMIT];
bool V[LIMIT];

int n, m, ap, order;

int art_points(int u)
{
    int i, v, found = 0, sum = 0;
    V[u] = true;
    L[u] = D[u] = order++;

    for (i = 0; i < int(G[u].size()); i++) {
        v = G[u][i];

        if (!V[v]) {
            P[v] = u;
            sum += art_points(v);
            L[u] = min(L[u], L[v]);

            if (P[u] == -1) { // Special case: root
                if (i > 0) {    // Two or more childs
                    ap++;
                    found = 1;
                }
            } else {
                if (L[v] >= D[u]) {
                    ap++;
                    found = 1;
                }
            }
        } else if (v != P[u]) {
            L[u] = min(L[u], D[v]);
        }
    }

    return sum + found;
}

int main(int argc, char **argv)
{
    int t, tc, i, u, v;

    scanf("%d", &t);

    for (tc = 1; tc <= t; tc++) {
        scanf("%d %d", &n, &m);

        for (i = 0; i < m; i++) {
            scanf("%d %d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }

        order = 0;
        ap = 0;
        P[1] = -1;


        printf("Case %d: %d\n", tc, art_points(1));

        if (tc < t) {
            memset(V, 0, sizeof V);
            memset(L, 0, sizeof L);
            memset(D, 0, sizeof D);
            memset(P, 0, sizeof P);
        }

        for (i = 0; i <= n; i++)
            G[i].clear();
    }

    return 0;
}
</pre>

[php]section("References");[/php]

<table border="0">
  <tr><td>1</td>   <td><a href="http://www.cs.umd.edu/~samir/451/bc.ps" target="_blank">Articulation Points and Biconnected Components</a></td></tr>
  <tr><td>2</td>   <td><a href="http://www.ibluemojo.com/school/articul_algorithm.html" target="_blank">Articulation Points Detection Algorithm</a></td></tr>
  <tr><td>3</td><td><a href="http://en.wikipedia.org/wiki/Biconnected_component" target="_blank">Biconnected component</a></td></tr>
</table>

[php]finalize();[/php]
