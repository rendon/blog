---
tags:
    - algorithms
    - data-structures
    - post
created: 2016-02-18
updated: 2024-05-07
---
# Eulerian tour

I'm taking [Intro to Algorithms](https://classroom.udacity.com/courses/cs215), which focuses mostly on graphs, and one of the first topics is about Eulerian paths and tours, you can easily find the theory of these topics in the course or on Wikipedia, let's write some code.

This is my brute force solution to the challenge in problem set 1: Find Eulerian tour:


```py
---
tags:
    - algorithms
    - data-structures
    - post
created: 2016-02-18
updated: 2024-05-07
---
# Find Eulerian Tour
#
---
tags:
    - algorithms
    - data-structures
    - post
created: 2016-02-18
updated: 2024-05-07
---
# Write a function that takes in a graph
---
tags:
    - algorithms
    - data-structures
    - post
created: 2016-02-18
updated: 2024-05-07
---
# represented as a list of tuples
---
tags:
    - algorithms
    - data-structures
    - post
created: 2016-02-18
updated: 2024-05-07
---
# and return a list of nodes that
---
tags:
    - algorithms
    - data-structures
    - post
created: 2016-02-18
updated: 2024-05-07
---
# you would follow on an Eulerian Tour
#
---
tags:
    - algorithms
    - data-structures
    - post
created: 2016-02-18
updated: 2024-05-07
---
# For example, if the input graph was
---
tags:
    - algorithms
    - data-structures
    - post
created: 2016-02-18
updated: 2024-05-07
---
# [(1, 2), (2, 3), (3, 1)]
---
tags:
    - algorithms
    - data-structures
    - post
created: 2016-02-18
updated: 2024-05-07
---
# A possible Eulerian tour would be [1, 2, 3, 1]
import copy

def contains_all_nodes(path, nodes):
    unique = {}
    for p in path:
        unique[p] = True
    for node in nodes:
        if node not in unique:
            return False
    return True

def tour(u, graph, visited, path, nodes):
    path.append(u)
    for v in graph[u]:
        e = (min(u, v), max(u, v))
        if e not in visited:
            visited_copy = copy.deepcopy(visited)
            visited_copy[e] = True
            path_copy = copy.deepcopy(path)
            p = tour(v, graph, visited_copy, path_copy, nodes)
            if contains_all_nodes(p, nodes):
                return p
    return path

def find_eulerian_tour(edges):
    graph = {}
    nodes = {}
    for edge in edges:
        u = edge[0]
        v = edge[1]
        nodes[u] = True
        nodes[v] = True
        if u not in graph:
            graph[u] = []
        graph[u].append(v)
        if v not in graph:
            graph[v] = []
        graph[v].append(u)

    for n in nodes:
        path = tour(n, graph, {}, [], nodes)
        if contains_all_nodes(path, nodes):
            return path
    return []

#edges = [(1, 2), (2, 3), (3, 1)]
edges = [(0, 1), (1, 5), (1, 7), (4, 5), (4, 8), (1, 6), (3, 7),
        (5, 9), (2, 4), (0, 4), (2, 5), (3, 6), (8, 9)]
print find_eulerian_tour(edges)

```
