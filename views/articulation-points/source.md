# Articulation points
2016-02-18 2024-05-07 #algorithms #data-structures #post

## Welcome

Currently I am training for a programming contest and I have no time to publish. I am learning many interesting topics about algorithms and programming and I want to share that with you. However, to write an article consumes much of my time and I'm devising a format that is both brief and useful: Algorithm or Data structure, brief info, sample problem, solution and references.

## Articulation points

Today's topic is about [graph theory](http://en.wikipedia.org/wiki/Graph_theory), articulation points. Here a [brief info from Dave Mount](http://www.cs.umd.edu/~samir/451/bc.ps):

> **Articulation Points and Biconnected Graphs:** Today we discuss another application of DFS, this time to a problem on undirected graphs. Let *G = (V, E)* be a ** connected** undirected graph. Consider de following definitions.
> 
> **Articulation Point( or Cut Vertex):** Is any vertex whose removal(together with the removal of any incident edges) results in a disconnected graph.

![Articulation points example](/articulation-points/artpoints.svg)

## Sample problem

A problem where you can put in practice this topic is [1063 Ant Hills](https://lightoj.com/volume_showproblem.php?problem=1063) from [lightoj.com](https://lightoj.com).

## Solution to sample problem

```cpp
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

```

## References

1. [Articulation Points and Biconnected Components](http://www.cs.umd.edu/~samir/451/bc.ps)
3. [Biconnected component](http://en.wikipedia.org/wiki/Biconnected_component)
