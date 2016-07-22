/* Copyright 2016 Rafael Rendón Pablo <rafaelrendonpablo@gmail.com> */
// region Template
#include <bits/stdc++.h>
using namespace std;
typedef long long           int64;
typedef unsigned long long  uint64;
const double kEps   = 10e-8;
const int kMax      = 10005;
const int kInf      = 1 << 30;
// endregion
vector<int> graph[kMax];
bool visited[kMax];
int discovery[kMax];
int low[kMax];

void find_bridges(int u, int& t, int p, vector<pair<int, int> >& links) {
    visited[u] = true;
    low[u] = t;
    discovery[u] = t;
    t++;
    for (int i = 0; i < int(graph[u].size()); i++) {
        int v = graph[u][i];
        if (!visited[v]) {
            find_bridges(v, t, u, links);
            low[u] = min(low[u], low[v]);
            if (low[v] > discovery[u]) {
                links.push_back(make_pair(min(u, v), max(u, v)));
            }
        } else if (v != p) {
            low[u] = min(low[u], low[v]);
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            graph[i].clear();
            int u, k;
            scanf("%d (%d)", &u, &k);
            for (int j = 0; j < k; j++) {
                int v;
                scanf("%d", &v);
                graph[u].push_back(v);
            }
        }
        printf("Case %d:\n", tc);
        fill(visited, visited + n, false);
        fill(discovery, discovery + n, 0);
        fill(low, low + n, 0);
        vector<pair<int, int> > clinks;
        for (int u = 0; u < n; u++) {
            if (visited[u]) {
                continue;
            }
            int time = 0;
            int parent = -1;
            find_bridges(u, time, parent, clinks);
        }
        printf("%ld critical links\n", clinks.size());
        sort(clinks.begin(), clinks.end());
        for (int i = 0; i < int(clinks.size()); i++) {
            printf("%d - %d\n", clinks[i].first, clinks[i].second);
        }
    }
    return EXIT_SUCCESS;
}
